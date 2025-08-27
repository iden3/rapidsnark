#include "vulkan_test.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdint>
#include <cstring>
#include <limits>
#include <memory>
#include <vector>
#include <chrono>
#include <cassert>
#include <algorithm>
#include <functional>
#include <alt_bn128.hpp>
#include "fq.hpp"
#include "misc.hpp"
#include "vulkan_manager.h"
#include "vulkan_msm.h"
#include "msm_mock.h"

namespace {

const unsigned int IterCount = 1;
const unsigned int MinPointCount = 4;
const unsigned int MaxPointCount = 1000*1024*1024;
unsigned int LogLevel = 3;

struct CurveShaderParams
{
    uint32_t iterCount;
    uint32_t pointCount;
};

struct Element
{
    uint64_t&       operator[](int i)        { return val[i]; }
    const uint64_t& operator[](int i) const  { return val[i]; }

    operator       FqRawElement& ()       { return val; }
    operator const FqRawElement& () const { return val; }

    FqRawElement& operator=(const FqRawElement &other)
    {
        std::memcpy(&val, &other, sizeof(val));
        return *this;
    }

    bool operator==(const FqRawElement &other) const
    {
        return Fq_rawIsEq(val, other);
    }

    bool operator!=(const FqRawElement &other) const
    {
        return !operator==(other);
    }

    void clear()
    {
        std::memset(&val, 0, sizeof(val));
    }

    FqRawElement val = {};
};

using Vector = std::vector<Element>;

template <typename CurveT>
using CalcFunc = std::function<void(ThreadPool&, CurveT &g, Vector&, const Vector&, const Vector&)>;

void printMsg(std::ostream &os)
{
    os << std::endl;
}

template <typename T, typename... Args>
void printMsg(std::ostream &os, T value, Args... args)
{
    os << value;
    printMsg(os, args...);
}

template <typename... Args>
void printMsg(unsigned int level, std::ostream &os, Args... args)
{
    if (level <= LogLevel) {
        printMsg(os, args...);
    }
}

std::string format(uint64_t val)
{
    std::ostringstream  oss;

    oss << "0x" << std::hex << std::setw(16) << std::setfill('0') << val;

    return oss.str();
}

std::ostream& operator<<(std::ostream &os, const FqRawElement val)
{
    os << format(val[0]) << ","
       << format(val[1]) << ","
       << format(val[2]) << ","
       << format(val[3]);

    return os;
}

void printVec(unsigned int level, std::ostream &oss, const std::string &msg, const Vector &a, size_t count = 0)
{
    size_t size = a.size();

    if (count != 0) {
        size = std::min(size, count);
    }

    printMsg(level, oss, msg);

    for (int i = 0; i < size; i++) {
        printMsg(level, oss, "a[", i, "]: ", a[i]);
    }
}

void printVec(unsigned int level, std::ostream &oss,
              const Vector &a, const Vector &b, const Vector &c, const Vector &r)
{
    printMsg(level, oss, "a[0]: ", a[0]);
    printMsg(level, oss, "b[0]: ", b[0]);
    printMsg(level, oss, "c[0]: ", c[0]);
    printMsg(level, oss, "r[0]: ", r[0]);
    printMsg(level, oss, "c[1]: ", c[1]);
    printMsg(level, oss, "r[1]: ", r[1]);
    printMsg(level, oss, "c[2]: ", c[2]);
    printMsg(level, oss, "r[2]: ", r[2]);
    printMsg(level, oss, "c[3]: ", c[3]);
    printMsg(level, oss, "r[3]: ", r[3]);
    printMsg(level, oss, "a[M]: ", a[a.size()-1]);
    printMsg(level, oss, "b[M]: ", b[b.size()-1]);
    printMsg(level, oss, "c[M]: ", c[c.size()-1]);
    printMsg(level, oss, "r[M]: ", r[r.size()-1]);
}

void initVecInc(Vector &a, size_t initVal)
{
    for (size_t i = 0; i < a.size(); i++) {
        a[i][0] = i + initVal;
        a[i][1] = i + initVal;
        a[i][2] = i + initVal;
        a[i][3] = i + initVal;
    }
}

void initVecVal(Vector &a, size_t initVal = 0)
{
    for (size_t i = 0; i < a.size(); i++) {
        a[i][0] = initVal;
        a[i][1] = initVal;
        a[i][2] = initVal;
        a[i][3] = initVal;
    }
}

void initVecVal1(Vector &a, size_t initVal = 0)
{
    for (size_t i = 0; i < a.size(); i++) {
        a[i][0] = initVal;
        a[i][1] = 0;
        a[i][2] = 0;
        a[i][3] = 0;
    }
}

bool cmpVec(const Vector &a, const Vector &b, size_t count = 0)
{
    size_t size = a.size();

    assert(a.size() == b.size());

    if (count != 0) {
        size = std::min(size, count);
    }

    for (size_t i = 0; i < size; i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }

    return true;
}

void vecAdd(Element &c, const Element &a, const Element &b)
{
    c[0] = a[0] + b[0];
    c[1] = a[1] + b[1];
    c[2] = a[2] + b[2];
    c[3] = a[3] + b[3];
}

void calcIdle(Vector &c, const Vector &a, const Vector &b)
{
    assert(c.size() >= a.size());
    assert(a.size() == b.size());

    const int size = a.size();

    for (size_t i = 0; i < size; i++) {
        vecAdd(c[i], a[i], b[i]);
    }
}

template <typename CurveT>
uint64_t curvePointCount(uint64_t vectorSize)
{
    const uint64_t elementSize = sizeof(Vector::value_type);
    const uint64_t pointSize = sizeof(typename CurveT::Point);

    assert(elementSize <= pointSize);

    return vectorSize / (pointSize / elementSize);
}

template <typename CurveT>
void calcMSM_gpu(VulkanMSM &vkMSM, CurveT &curve, Vector &r, Vector &a, Vector &b,
                 const std::string &shaderPath)
{
    const uint64_t nPoints         = curvePointCount<CurveT>(a.size());
    const uint64_t pointSize       = sizeof(typename CurveT::Point);
    const uint32_t affinePointSize = sizeof(typename CurveT::PointAffine);
    const uint32_t scalarSize      = sizeof(Vector::value_type);

    vkMSM.run(shaderPath, a.data(), b.data(), pointSize, affinePointSize, scalarSize, nPoints);
    vkMSM.computeResult(curve, r.data());
}

template <typename CurveT>
void calcMSM_cpu(ThreadPool &threadPool, CurveT &curve, Vector &r, const Vector &a, const Vector &b)
{
    typename CurveT::Point result;
    const uint64_t         nPoints    = curvePointCount<CurveT>(a.size());
    const uint64_t         scalarSize = sizeof(Vector::value_type);
    auto                   bases      = (typename CurveT::PointAffine*)a.data();
    uint8_t*               scalars    = (uint8_t*)b.data();

    curve.multiMulByScalarMSM(result, bases, scalars, scalarSize, nPoints, threadPool);

    std::memcpy(r.data(), &result, sizeof(result));
}

template <typename CurveT>
void calcCurve_cpu(ThreadPool &threadPool, CurveT &curve, Vector& r, const Vector& a, const Vector& b)
{
    const uint64_t nPoints = curvePointCount<CurveT>(a.size());

    auto pa = (typename CurveT::Point*)a.data();
    auto pb = (typename CurveT::Point*)b.data();
    auto pr = (typename CurveT::Point*)r.data();

    threadPool.parallelFor(0, nPoints, [&] (int begin, int end, int numThread) {

        for (size_t i = begin; i < end; i++) {
            for (size_t k = 0; k < IterCount; k++) {
                curve.add(pr[i], pa[i], pb[i]);
            }
        }
    });
}

template <typename CurveT>
size_t calcCurve_gpu(VulkanManager &vkMgr, CurveT &curve, Vector &r, Vector &a, Vector &b,
                 const std::string &shaderPath)
{
    assert(r.size() >= a.size());
    assert(a.size() == b.size());

    const uint64_t nPoints = curvePointCount<CurveT>(a.size());
    const uint64_t pointSize = sizeof(typename CurveT::Point);
    const size_t   sizeTemp  = 16;
    const uint32_t workgroupSize = 64;

    CurveShaderParams params     = { IterCount, (uint32_t)nPoints };
    VulkanWorkgroups  workgroups = { (uint32_t)div_ceil(nPoints, workgroupSize) };

    VulkanBufferView   vR = { r.data(), nPoints * pointSize };
    VulkanBufferView   vA = { a.data(), nPoints * pointSize };
    VulkanBufferView   vB = { b.data(), nPoints * pointSize };
    VulkanMemoryLayout memoryLayout = {sizeof(params), vR.size, vA.size, vB.size, sizeTemp, sizeTemp};

    auto vkPipeline = vkMgr.createPipeline(shaderPath, workgroups, memoryLayout, &params);

    vkPipeline->run(vR, vA, vB);

    return vkPipeline->shaderSize();
}

long measureTime(std::function<void()> func)
{
    auto start = std::chrono::high_resolution_clock::now();

    func();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    return duration.count();
}

template <typename CurveT, typename FuncT>
void test_cpu(
    CurveT &curve, Vector &r_par, const Vector &a, const Vector &b,
    unsigned int  testLevel,
    FuncT         calcFunc,
    std::ostream &oss)
{
    Vector r_sngl(r_par.size());

    ThreadPool &threadPoolDefault = ThreadPool::defaultPool();

    const auto parallelTime = measureTime([&] {

        calcFunc(threadPoolDefault, curve, r_par, a, b);
    });

    printMsg(0, oss, "Parallel execution time: ", parallelTime, " ms");

    if (testLevel >= 2) {
        ThreadPool threadPool1(1);

        const auto singleTime = measureTime([&] {

            calcFunc(threadPool1, curve, r_sngl, a, b);
        });

        printMsg(0, oss, "Single   execution time: ", singleTime, " ms");
    }

    printMsg(0, oss, "Threads: ", threadPoolDefault.getThreadCount());

    if (testLevel >= 2) {
        printMsg(2, oss, "CPU eq: ", std::boolalpha, cmpVec(r_sngl, r_par));
    }
}

template <typename CurveT>
void test_cpu_msm(
    CurveT &curve, Vector &r, const Vector &a, const Vector &b,
    unsigned int  testLevel,
    std::ostream &oss)
{
    test_cpu(curve, r, a, b, testLevel, calcMSM_cpu<CurveT>, oss);
}

template <typename CurveT>
void test_gpu_msm(
    CurveT &curve, Vector &r, Vector &a, Vector &b,
    const std::string &shaderPath,
    std::ostream      &oss)
{
    VulkanMSM vkMSM;

    auto gpuTime = measureTime([&] {

        calcMSM_gpu(vkMSM, curve, r, a, b, shaderPath);
    });

    const size_t shaderSize = vkMSM.getShaderSize();

    VulkanManager vkMgr;
    vkMgr.debugInfo(oss, LogLevel);

    printMsg(1, oss, "Shader path: ", shaderPath);
    printMsg(1, oss, "Shader size: ", shaderSize, " bytes");
    printMsg(0, oss, "GPU      execution time: ", gpuTime, " ms");
}

template <typename CurveT>
void test_cpu_curve(
    CurveT &curve, Vector &r, const Vector &a, const Vector &b,
    unsigned int  testLevel,
    std::ostream &oss)
{
    test_cpu(curve, r, a, b, testLevel, calcCurve_cpu<CurveT>, oss);
}

template <typename CurveT>
void test_gpu_curve(
    CurveT &curve, Vector &r, Vector &a, Vector &b,
    const std::string &shaderPath,
    std::ostream      &oss)
{
    VulkanManager vkMgr;
    size_t shaderSize = 0;

    auto gpuTime = measureTime([&] {

        shaderSize = calcCurve_gpu(vkMgr, curve, r, a, b, shaderPath);
    });

    vkMgr.debugInfo(oss, LogLevel);

    printMsg(1, oss, "Shader path: ", shaderPath);
    printMsg(1, oss, "Shader size: ", shaderSize, " bytes");
    printMsg(0, oss, "GPU      execution time: ", gpuTime, " ms");
}

void test(
    const std::string &shaderPath,
    unsigned int       pointCount,
    unsigned int       testLevel,
    char              *msg,
    long               msgMaxSize)
{
    std::ostringstream oss;
    Vector a(pointCount);
    Vector b(pointCount);
//    Vector r_cpu(pointCount);
//    Vector r_vk(pointCount);
    Vector r_cpu(4);
    Vector r_vk(4);
    Vector r_idle(pointCount);
    const size_t pointSize = sizeof(Vector::value_type);

    AltBn128::Engine E;
    CurveMock g;
    auto &curve = E.g1;

    printMsg(0, oss, "LogLevel: ", LogLevel, " TestLevel: ", testLevel);

    initVecVal(a, 1);
    initVecVal1(b, 4);

    calcIdle(r_idle, a, b);

    test_gpu_msm(curve, r_vk, a, b, shaderPath, oss);

    if (testLevel >= 1) {
        test_cpu_msm(curve, r_cpu, a, b, testLevel, oss);

        printMsg(0, oss, "Vulkan eq: ", std::boolalpha, cmpVec(r_cpu, r_vk));
    }

    printMsg(1, oss, "PointSize: ",  pointSize, " bytes");
    printMsg(0, oss, "PointCount: ", pointCount);

    printVec(2, oss, a, b, r_cpu, r_vk);
    printMsg(2, oss, "Work: MSM_G1");

    strncat(msg, oss.str().c_str(), msgMaxSize);
}

template <typename CurveT>
long measure_msm_time_cpu(
    CurveT &curve, Vector &r, const Vector &a, const Vector &b)
{
    ThreadPool &threadPool = ThreadPool::defaultPool();

    const auto cpuTime = measureTime([&] {

        calcMSM_cpu(threadPool, curve, r, a, b);
    });

    return cpuTime;
}

template <typename CurveT>
long measure_msm_time_gpu(
    CurveT &curve, Vector &r, Vector &a, Vector &b,
    const std::string &shaderPath)
{
    VulkanMSM vkMSM;

    auto gpuTime = measureTime([&] {

        calcMSM_gpu(vkMSM, curve, r, a, b, shaderPath);
    });

    return gpuTime;
}

bool measure_msm_time(
    const std::string &shaderPath,
    int                curveId,
    unsigned int       pointCount,
    vulkan_msm_time   *msmTime)
{
    Vector a(pointCount);
    Vector b(pointCount);
    Vector r_cpu(8);
    Vector r_vk(8);
    Vector r_idle(pointCount);

    initVecInc(a, 0xccbbaa998877);
    initVecInc(b, 0xeeddccbbaa99);
    initVecVal(r_cpu);
    initVecVal(r_vk);

    calcIdle(r_idle, a, b);

    AltBn128::Engine E;

    if (curveId == VULKAN_TEST_CURVE_G1) {
        msmTime->gpu = measure_msm_time_gpu(E.g1, r_vk, a, b, shaderPath);
        msmTime->cpu = measure_msm_time_cpu(E.g1, r_cpu, a, b);

    } else if (curveId == VULKAN_TEST_CURVE_G2) {
        msmTime->gpu = measure_msm_time_gpu(E.g2, r_vk, a, b, shaderPath);
        msmTime->cpu = measure_msm_time_cpu(E.g2, r_cpu, a, b);
    }

    return cmpVec(r_cpu, r_vk);
}

} // namespace

int vulkan_test_params(
    const char   *shader_path,
    unsigned int  point_count,
    unsigned int  log_level,
    unsigned int  test_level,
    char         *msg,
    long          msg_max_size)
{
    point_count = std::clamp(point_count, MinPointCount, MaxPointCount);

    LogLevel = log_level;

    std::string result;
    int         error  = VULKAN_TEST_RESULT_OK;

    msg[0] = '\0';

    try {
        test(shader_path, point_count, test_level, msg, msg_max_size);

        return error;

    } catch (std::exception& e) {
        result = e.what();
        error  = VULKAN_TEST_RESULT_OTHER_ERROR;
    }
    catch (...) {
        result = "unknown error";
        error  = VULKAN_TEST_RESULT_OTHER_ERROR;
    }

    strncat(msg, result.c_str(), msg_max_size);

    return error;
}

int vulkan_test(
    const char *shader_path,
    char       *msg,
    long        msg_max_size)
{
    const unsigned int point_count = 500*1024;
    const unsigned int log_level = 0;
    const unsigned int test_level = 1;

    return vulkan_test_params(shader_path, point_count, log_level, test_level, msg, msg_max_size);
}

int vulkan_measure_msm_time(
    const char             *shader_path,
    int                     curve_id,
    unsigned int            point_count,
    struct vulkan_msm_time *msm_time,
    char                   *error_msg,
    unsigned long long      error_msg_maxsize)
{
    std::string result;
    int         error = VULKAN_TEST_RESULT_OK;

    if (curve_id != VULKAN_TEST_CURVE_G1 && curve_id != VULKAN_TEST_CURVE_G2) {
        result = "unrecognized curve ID";
        error = VULKAN_TEST_RESULT_INVALID_CURVE_ID;
        goto out;
    }

    point_count = std::max(point_count, MinPointCount);

    if (point_count > MaxPointCount) {
        result = "the point count is greater than a reasonable number of points";
        error  = VULKAN_TEST_RESULT_TOO_BIG_POINT_COUNT;
        goto out;
    }

    try {
        const bool comp_eq = measure_msm_time(shader_path, curve_id, point_count, msm_time);

        if (comp_eq) {
            return VULKAN_TEST_RESULT_OK;
        }

        result = "GPU and CPU computation results are not equal";
        error  = VULKAN_TEST_RESULT_COMP_NOT_EQUAL;

    } catch (InvalidPathException& e) {
        result = e.what();
        error  = VULKAN_TEST_RESULT_INVALID_PATH;

    } catch (InvalidShaderException& e) {
        result = e.what();
        error  = VULKAN_TEST_RESULT_INVALID_SHADER;

    } catch (TimeoutException& e) {
        result = e.what();
        error  = VULKAN_TEST_RESULT_TIMEOUT;

    } catch (std::exception& e) {
        result = e.what();
        error  = VULKAN_TEST_RESULT_OTHER_ERROR;

    } catch (...) {
        result = "unknown error";
        error  = VULKAN_TEST_RESULT_OTHER_ERROR;
    }

out:
    if (error_msg != NULL) {

        error_msg[0] = '\0';
        strncat(error_msg, result.c_str(), error_msg_maxsize);
    }

    return error;
}
