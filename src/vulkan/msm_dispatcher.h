#ifndef MSM_DISPATCHER_H
#define MSM_DISPATCHER_H

#include <cstdlib>
#include <array>
#include <algorithm>
#include <functional>
#include <cassert>

template <unsigned JobCount>
class MsmDispatcher
{
public:
    enum JobType {CpuJob = 0, GpuJob = 1};

private:
    static_assert(JobCount <= 16, "Too many jobs");

    static const uint64_t SchedCount = (1 << JobCount);
    static const uint64_t SchedMask = SchedCount - 1;

public:
    template <typename UserData>
    using Jobs = std::array<std::function<void (UserData)>, JobCount>;

    using JobSizes = std::array<uint64_t, JobCount>; // the number of elements to process

public:
    MsmDispatcher()
        : m_cpuTimePerJob(0)
        , m_gpuTimePerJob(0)
        , m_minGpuJobSize(0)
        , m_schedule(0) // all jobs on CPU by default
    {}

    MsmDispatcher(uint64_t cpuTimePerJob, uint64_t gpuTimePerJob, uint64_t minGpuJob = 0)
    {
        init(cpuTimePerJob, gpuTimePerJob, minGpuJob);
    }

    void init(uint64_t cpuTimePerJob, uint64_t gpuTimePerJob, uint64_t minGpuJob = 0)
    {
        m_cpuTimePerJob = cpuTimePerJob;
        m_gpuTimePerJob = gpuTimePerJob;
        m_minGpuJobSize = minGpuJob;
        m_schedule      = 0;

        if (m_cpuTimePerJob == 0 && m_gpuTimePerJob != 0) {
            m_schedule = SchedMask; // all jobs on GPU
        }
    }

    void schedule(const JobSizes &jobSizes)
    {
        if (m_cpuTimePerJob == 0 || m_gpuTimePerJob == 0) {
            return;
        }

        calcMinSched(jobSizes);
        adjustShedToMinGpuJob(jobSizes);
    }

    template <typename UserData>
    void run(const Jobs<UserData> &jobs, JobType jobType, UserData &&userData)
    {
        for (int i = 0; i < jobs.size(); i++) {
            auto &job = jobs[i];

            if (job && isOf(jobType, i)) {
                job(userData);
            }
        }
    }

    bool hasGpuJobs() const
    {
        return m_schedule != 0;
    }

    bool isOf(JobType type, int jobNumber) const
    {
        if (type == GpuJob) {
            return isOnGPU(jobNumber);
        }

        return !isOnGPU(jobNumber);
    }

    bool isOnGPU(int jobNumber) const
    {
        assert(jobNumber < JobCount);

        const uint64_t jobMask = (1 << jobNumber);

        return (m_schedule & jobMask) != 0;
    }

    unsigned jobCount() const
    {
        return JobCount;
    }

private:
    bool isSmallJob(uint64_t jobSize) const
    {
        return (jobSize == 0) || (m_minGpuJobSize != 0 && jobSize < m_minGpuJobSize);
    }

    void calcMinSched(const JobSizes& jobSizes)
    {
        uint64_t minSched = 0;
        uint64_t minTime = calcSchedTime(jobSizes, 0);

        for (uint64_t s = 1; s < SchedCount; s++) {
            const uint64_t curTime = calcSchedTime(jobSizes, s);

            if (curTime < minTime) {
                minTime = curTime;
                minSched = s;
            }
        }

        m_schedule = minSched;
    }

    uint64_t calcSchedTime(const JobSizes& jobSizes, uint64_t sched) const
    {
        uint64_t cpuTime = 0;
        uint64_t gpuTime = 0;

        uint64_t jobMask = 1;

        for (int i = 0; i < jobSizes.size(); i++) {
            const auto jobSize = jobSizes[i];

            if (isSmallJob(jobSize)) {
                cpuTime += jobSize * m_cpuTimePerJob;

            } else if (sched & jobMask) {
                gpuTime += jobSize * m_gpuTimePerJob;

            } else {
                cpuTime += jobSize * m_cpuTimePerJob;
            }

            jobMask <<= 1;
        }

        return std::max(cpuTime, gpuTime);
    }

    void adjustShedToMinGpuJob(const JobSizes& jobSizes)
    {
        uint64_t newShed = m_schedule;
        uint64_t jobMask = 1;

        for (int i = 0; i < jobSizes.size(); i++) {
            const auto jobSize = jobSizes[i];

            if (isSmallJob(jobSize)) {
                newShed &= ~jobMask;
            }

            jobMask <<= 1;
        }

        m_schedule = newShed;
    }

private:
    uint64_t m_cpuTimePerJob;
    uint64_t m_gpuTimePerJob;
    uint64_t m_minGpuJobSize;  // smaller jobs are dispatched to CPU
    uint64_t m_schedule;       // for each bit: 0 - on CPU, 1 - on GPU
};

#endif // MSM_DISPATCHER_H
