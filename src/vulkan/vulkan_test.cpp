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

const unsigned int MinPointCount = 4;
const unsigned int MaxPointCount = 1000*1024*1024;
static unsigned int LogLevel = 3;

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
using CalcFunc = std::function<void(ThreadPool&, Vector&, const Vector&, const Vector&)>;

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

void calcMSM_Mock(ThreadPool &threadPool, Vector &c, const Vector &a, const Vector &b)
{
    TestCurve        g;
    TestCurve::Point r;
    uint64_t         n = a.size();
    auto             bases = (TestCurve::PointAffine*)a.data();
    uint8_t*         scalars = (uint8_t*)b.data();
    uint64_t         scalarSize = sizeof(Vector::value_type);

    MSM_Mock<TestCurve> msm(g, bases, scalars, scalarSize, n, threadPool);

    msm.run(r);

    c[0] = r.v;
}

void calcMSM_G1(ThreadPool &threadPool, Vector &c, const Vector &a, const Vector &b)
{
    AltBn128::Engine          E;
    AltBn128::Engine::G1Point result;
    uint64_t                  nPoints = a.size() / 2;
    auto                      bases = (AltBn128::Engine::G1PointAffine*)a.data();
    uint8_t*                  scalars = (uint8_t*)b.data();
    uint64_t                  scalarSize = sizeof(Vector::value_type);

    E.g1.multiMulByScalarMSM(result, bases, scalars, scalarSize, nPoints);

    std::memcpy(c.data(), &result, sizeof(result));
}

void calcMSM_G2(ThreadPool &threadPool, Vector &c, const Vector &a, const Vector &b)
{
    AltBn128::Engine          E;
    AltBn128::Engine::G2Point result;
    uint64_t                  nPoints = a.size() / 4;
    auto                      bases = (AltBn128::Engine::G2PointAffine*)a.data();
    uint8_t*                  scalars = (uint8_t*)b.data();
    uint64_t                  scalarSize = sizeof(Vector::value_type);

    E.g2.multiMulByScalarMSM(result, bases, scalars, scalarSize, nPoints);

    std::memcpy(c.data(), &result, sizeof(result));
}

long measureTime(std::function<void()> func)
{
    auto start = std::chrono::high_resolution_clock::now();

    func();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    return duration.count();
}

void test_cpu(
    Vector &r_par, const Vector &a, const Vector &b,
    unsigned int  testLevel,
    CalcFunc      calcFunc,
    std::ostream &oss)
{
    Vector r_sngl(r_par.size());

    ThreadPool &threadPoolDef = ThreadPool::defaultPool();

    const auto parallelTime = measureTime([&] {

        calcFunc(threadPoolDef, r_par, a, b);
    });

    printMsg(0, oss, "Parallel execution time: ", parallelTime, " ms");

    if (testLevel >= 2) {
        ThreadPool threadPool1(1);

        const auto singleTime = measureTime([&] {

            calcFunc(threadPool1, r_sngl, a, b);
        });

        printMsg(0, oss, "Single   execution time: ", singleTime, " ms");
    }

    printMsg(0, oss, "Threads: ", threadPoolDef.getThreadCount());

    if (testLevel >= 2) {
        printMsg(2, oss, "CPU eq: ", std::boolalpha, cmpVec(r_sngl, r_par));
    }
}

void test_cpu_msm(
    Vector &r, const Vector &a, const Vector &b,
    unsigned int  testLevel,
    std::ostream &oss)
{
    test_cpu(r, a, b, testLevel, calcMSM_G1, oss);
}

void test_gpu_msm(
    Vector &r, Vector &a, Vector &b,
    const std::string &shaderPath,
    std::ostream      &oss)
{
    AltBn128::Engine E;
    const uint32_t   pointCount      = a.size() / 2;
    const uint32_t   pointSize       = sizeof(AltBn128::Engine::G1Point);
    const uint32_t   affinePointSize = sizeof(AltBn128::Engine::G1PointAffine);
    const uint32_t   scalarSize      = sizeof(Vector::value_type);

    VulkanMSM vkMSM;

    auto gpuTime = measureTime([&] {

        vkMSM.run(shaderPath, a.data(), b.data(), pointSize, affinePointSize, scalarSize, pointCount);

        vkMSM.computeResult(E.g1, r.data());
    });

    const size_t shaderSize = vkMSM.getLastShaderSize();

    VulkanManager vkMgr;
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
    Vector r_cpu(4);
    Vector r_vk(4);
    Vector r_idle(pointCount);
    const size_t pointSize = sizeof(Vector::value_type);

    printMsg(0, oss, "LogLevel: ", LogLevel, " TestLevel: ", testLevel);

    initVecInc(a, 0xccbbaa998877);
    initVecInc(b, 0xeeddccbbaa99);

    calcIdle(r_idle, a, b);

    test_gpu_msm(r_vk, a, b, shaderPath, oss);

    if (testLevel >= 1) {
        test_cpu_msm(r_cpu, a, b, testLevel, oss);

        printMsg(0, oss, "Vulkan eq: ", std::boolalpha, cmpVec(r_cpu, r_vk));
    }

    printMsg(1, oss, "PointSize: ",  pointSize, " bytes");
    printMsg(0, oss, "PointCount: ", pointCount);

    printVec(2, oss, a, b, r_cpu, r_vk);
    printMsg(2, oss, "Work: MSM_G1");

    strncat(msg, oss.str().c_str(), msgMaxSize);
}

long measure_msm_time_cpu_g1(
    Vector &r, const Vector &a, const Vector &b)
{
    ThreadPool &threadPool = ThreadPool::defaultPool();

    const auto cpuTime = measureTime([&] {

        calcMSM_G1(threadPool, r, a, b);
    });

    return cpuTime;
}

long measure_msm_time_cpu_g2(
    Vector &r, const Vector &a, const Vector &b)
{
    ThreadPool &threadPool = ThreadPool::defaultPool();

    const auto cpuTime = measureTime([&] {

        calcMSM_G2(threadPool, r, a, b);
    });

    return cpuTime;
}

long measure_msm_time_gpu_g1(
    Vector &r, Vector &a, Vector &b,
    const std::string &shaderPath)
{
    const uint32_t   pointCount      = a.size() / 2;
    const uint32_t   pointSize       = sizeof(AltBn128::Engine::G1Point);
    const uint32_t   affinePointSize = sizeof(AltBn128::Engine::G1PointAffine);
    const uint32_t   scalarSize      = sizeof(Vector::value_type);
    AltBn128::Engine E;

    VulkanMSM vkMSM;

    auto gpuTime = measureTime([&] {

        vkMSM.run(shaderPath, a.data(), b.data(), pointSize, affinePointSize, scalarSize, pointCount);

        vkMSM.computeResult(E.g1, r.data());
    });

    return gpuTime;
}

long measure_msm_time_gpu_g2(
    Vector &r, Vector &a, Vector &b,
    const std::string &shaderPath)
{
    const uint32_t   pointCount      = a.size() / 4;
    const uint32_t   pointSize       = sizeof(AltBn128::Engine::G2Point);
    const uint32_t   affinePointSize = sizeof(AltBn128::Engine::G2PointAffine);
    const uint32_t   scalarSize      = sizeof(Vector::value_type);
    AltBn128::Engine E;

    VulkanMSM vkMSM;

    auto gpuTime = measureTime([&] {

        vkMSM.run(shaderPath, a.data(), b.data(), pointSize, affinePointSize, scalarSize, pointCount);

        vkMSM.computeResult(E.g2, r.data());
    });

    return gpuTime;
}

bool measure_msm_time(
    const std::string &shaderPath,
    int                curve_id,
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

    if (curve_id == VULKAN_TEST_CURVE_G1) {
        msmTime->gpu = measure_msm_time_gpu_g1(r_vk, a, b, shaderPath);
        msmTime->cpu = measure_msm_time_cpu_g1(r_cpu, a, b);

    } else if (curve_id == VULKAN_TEST_CURVE_G2) {
        msmTime->gpu = measure_msm_time_gpu_g2(r_vk, a, b, shaderPath);
        msmTime->cpu = measure_msm_time_cpu_g2(r_cpu, a, b);
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
