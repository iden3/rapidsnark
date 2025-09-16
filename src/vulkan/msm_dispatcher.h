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
    enum JobDevice {CPU = 0, GPU = 1};
    enum JobType   {G1, G2};

    struct JobSize
    {
        uint64_t size;
        JobType  type;
    };

private:
    static_assert(JobCount <= 16, "Too many jobs");

    static const int64_t  InvalidPace = -1;
    static const uint64_t ScheduleCount = (1 << JobCount);
    static const uint64_t ScheduleMask = ScheduleCount - 1;

public:
    template <typename UserData>
    using Jobs = std::array<std::function<void (UserData)>, JobCount>;

    using JobSizes = std::array<JobSize, JobCount>; // the number of elements to process

public:
    MsmDispatcher()
        : m_paceCpuG1(InvalidPace)
        , m_paceGpuG1(InvalidPace)
        , m_paceCpuG2(InvalidPace)
        , m_paceGpuG2(InvalidPace)
        , m_minGpuJobSize(0)
        , m_schedule(0) // all jobs on CPU by default
    {}

    MsmDispatcher(int64_t paceCpuG1, int64_t paceGpuG1,
                  int64_t paceCpuG2, int64_t paceGpuG2,
                  uint64_t minGpuJob = 0)
    {
        init(paceCpuG1, paceGpuG1, paceCpuG2, paceGpuG2, minGpuJob);
    }

    // If 'pace' is invalid then its device is disabled for its curve
    void init(int64_t paceCpuG1, int64_t paceGpuG1,
              int64_t paceCpuG2, int64_t paceGpuG2,
              uint64_t minGpuJob = 0)
    {
        m_paceCpuG1 = paceCpuG1;
        m_paceGpuG1 = paceGpuG1;
        m_paceCpuG2 = paceCpuG2;
        m_paceGpuG2 = paceGpuG2;
        m_minGpuJobSize = minGpuJob;
        m_schedule = 0;
    }

    void schedule(const JobSizes &jobSizes)
    {
        uint64_t minSchedule = 0;
        uint64_t minTime     = UINT64_MAX;

        for (uint64_t s = 0; s < ScheduleCount; s++) {
            const uint64_t curSchedule = adjustSchedule(jobSizes, s);
            const uint64_t curTime     = calcScheduleTime(jobSizes, curSchedule);

            if (curTime < minTime) {
                minTime = curTime;
                minSchedule = curSchedule;
            }
        }

        m_schedule = minSchedule;
    }

    template <typename UserData>
    void run(const Jobs<UserData> &jobs, JobDevice jobDevice, UserData &&userData) const
    {
        for (int i = 0; i < jobs.size(); i++) {
            auto &job = jobs[i];

            if (job && isOn(jobDevice, i)) {
                job(userData);
            }
        }
    }

    bool hasGpuJobs() const
    {
        return m_schedule != 0;
    }

    bool isOnGPU(int jobNumber) const
    {
        assert(jobNumber < JobCount);

        const uint64_t jobMask = (1 << jobNumber);

        return (m_schedule & jobMask) != 0;
    }

    auto jobCount() const
    {
        return JobCount;
    }

    std::string scheduleStr() const
    {
        std::string result;

        for (int i = 0; i < jobCount(); i++) {
            result += isOnGPU(i) ? 'g' : '.';
        }

        return result;
    }

private:
    uint64_t adjustSchedule(const JobSizes& jobSizes, uint64_t schedule) const
    {
        uint64_t newSchedule = schedule;
        uint64_t jobMask = 1;

        for (int i = 0; i < jobSizes.size(); i++) {
            const auto jobSize = jobSizes[i].size;
            const auto jobType = jobSizes[i].type;

            if (isSmallJob(jobSize)) {
                assignToCpu(newSchedule, jobMask);

            } else if (!isValidPace(paceGpu(jobType))) {
                assignToCpu(newSchedule, jobMask);

            } else if (!isValidPace(paceCpu(jobType))) {
                assignToGpu(newSchedule, jobMask);
            }

            jobMask <<= 1;
        }

        return newSchedule;
    }

    uint64_t calcScheduleTime(const JobSizes& jobSizes, uint64_t schedule) const
    {
        uint64_t timeCpu = 0;
        uint64_t timeGpu = 0;

        uint64_t jobMask = 1;

        for (int i = 0; i < jobSizes.size(); i++) {
            const auto jobSize = jobSizes[i].size;
            const auto jobType = jobSizes[i].type;

            if (schedule & jobMask) {
                timeGpu += jobSize * normalizePace(paceGpu(jobType));

            } else {
                timeCpu += jobSize * normalizePace(paceCpu(jobType));
            }

            jobMask <<= 1;
        }

        return std::max(timeCpu, timeGpu);
    }

    bool isOn(JobDevice device, int jobNumber) const
    {
        if (device == GPU) {
            return isOnGPU(jobNumber);
        }

        return !isOnGPU(jobNumber);
    }

    void assignToCpu(uint64_t &schedule, uint64_t jobMask) const
    {
        schedule &= ~jobMask;
    }

    void assignToGpu(uint64_t &schedule, uint64_t jobMask) const
    {
        schedule |= jobMask;
    }

    bool isSmallJob(uint64_t jobSize) const
    {
        return (jobSize == 0) || (m_minGpuJobSize != 0 && jobSize < m_minGpuJobSize);
    }

    auto paceCpu(JobType jobType) const
    {
        return (jobType == G1) ? m_paceCpuG1 : m_paceCpuG2;
    }

    auto paceGpu(JobType jobType) const
    {
        return (jobType == G1) ? m_paceGpuG1 : m_paceGpuG2;
    }

    bool isValidPace(int64_t pace) const
    {
        return (pace >= 0);
    }

    auto normalizePace(int64_t pace) const
    {
        return isValidPace(pace) ? pace : 0;
    }

private:
    int64_t  m_paceCpuG1;       // Pace is time per job item
    int64_t  m_paceGpuG1;
    int64_t  m_paceCpuG2;
    int64_t  m_paceGpuG2;
    uint64_t m_minGpuJobSize;   // smaller jobs are always dispatched to CPU
    uint64_t m_schedule;        // for each bit: 0 - on CPU, 1 - on GPU
};

#endif // MSM_DISPATCHER_H
