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
#include <cassert>
#include <algorithm>
#include <functional>
#include <alt_bn128.hpp>
#include "fq.hpp"
#include "misc.hpp"
#include "vulkan_manager.h"
#include "vulkan_msm.h"
#include "msm_mock.h"
#include "utils.h"

namespace {

const unsigned int IterCount = 1;
const unsigned int MinPointCount = 1;
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


std::string curveName(const CurveMock&)
{
    return "Mock";
}

std::string curveName(const typename AltBn128::Engine::G1&)
{
    return "G1";
}

std::string curveName(const typename AltBn128::Engine::G2&)
{
    return "G2";
}

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

std::ostream& operator<<(std::ostream &os, const typename RawFq::Element val)
{
    os << format(val.v[0]) << ","
       << format(val.v[1]) << ","
       << format(val.v[2]) << ","
       << format(val.v[3]);

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

template <typename CurveT>
uint64_t pointSizeInElements(CurveT &g)
{
    const uint64_t elementSize = sizeof(Vector::value_type);
    const uint64_t pointSize = sizeof(typename CurveT::Point);

    assert(elementSize <= pointSize);

    return (pointSize / elementSize);
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
void initPoints(CurveT &curve, Vector &a)
{
    auto points = (typename CurveT::PointAffine *)a.data();

    const int nPoints = curvePointCount<CurveT>(a.size());
    const int maxGenPoints = std::min(nPoints, 1000);

    assert(nPoints > 0);

    curve.copy(points[0], curve.oneAffine());

    int i = 1;
    for (; i < maxGenPoints; i++) {
        curve.add(points[i], points[i-1], curve.oneAffine());
    }

    for (; i < nPoints; i++) {
        auto idx = i % maxGenPoints;

        curve.copy(points[i], points[idx]);
    }
}

template <typename CurveT>
auto calcMSM_gpu(VulkanMSM &vkMSM, CurveT &curve, Vector &r, Vector &a, Vector &b,
                 const std::string &shaderPath)
{
    const uint64_t nPoints         = curvePointCount<CurveT>(a.size());
    const uint64_t pointSize       = sizeof(typename CurveT::Point);
    const uint32_t affinePointSize = sizeof(typename CurveT::PointAffine);
    const uint32_t scalarSize      = sizeof(Vector::value_type);

    vkMSM.init(shaderPath, a.data(), b.data(), pointSize, affinePointSize, scalarSize, nPoints);
    vkMSM.run();
    vkMSM.computeResultAffine(curve, r.data());

    return vkMSM.getPerf();
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

    typename CurveT::PointAffine resultAffine;

    curve.copy(resultAffine, result);

    std::memcpy(r.data(), &resultAffine, sizeof(resultAffine));
}

template <typename CurveT>
void calcMSM_cpu_old(ThreadPool &threadPool, CurveT &curve, Vector &r, const Vector &a, const Vector &b)
{
    typename CurveT::Point result;
    const uint64_t         nPoints    = curvePointCount<CurveT>(a.size());
    const uint64_t         scalarSize = sizeof(Vector::value_type);
    auto                   bases      = (typename CurveT::PointAffine*)a.data();
    uint8_t*               scalars    = (uint8_t*)b.data();

    curve.multiMulByScalar(result, bases, scalars, scalarSize, nPoints);

    typename CurveT::PointAffine resultAffine;

    curve.copy(resultAffine, result);

    std::memcpy(r.data(), &resultAffine, sizeof(resultAffine));
}

template <typename CurveT>
void calcMSM_Mock_cpu(ThreadPool &threadPool, CurveT &curve, Vector &r, const Vector &a, const Vector &b)
{
    typename CurveT::Point result;
    const uint64_t         nPoints    = curvePointCount<CurveT>(a.size());
    const uint64_t         scalarSize = sizeof(Vector::value_type);
    auto                   bases      = (typename CurveT::PointAffine*)a.data();
    uint8_t*               scalars    = (uint8_t*)b.data();

    MSM_Mock<CurveT> msm(curve, bases, scalars, scalarSize, nPoints, threadPool, 8);
    msm.run(result);

    typename CurveT::PointAffine resultAffine;

    curve.copy(resultAffine, result);

    std::memcpy(r.data(), &resultAffine, sizeof(resultAffine));
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
auto calcCurve_gpu(VulkanManager &vkMgr, CurveT &curve, Vector &r, Vector &a, Vector &b,
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

    return vkPipeline->getPerf();
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
void test_cpu_msm_old(
    CurveT &curve, Vector &r, const Vector &a, const Vector &b,
    unsigned int  testLevel,
    std::ostream &oss)
{
    test_cpu(curve, r, a, b, testLevel, calcMSM_cpu_old<CurveT>, oss);
}

template <typename CurveT>
void test_cpu_msm_mock(
    CurveT &curve, Vector &r, const Vector &a, const Vector &b,
    unsigned int  testLevel,
    std::ostream &oss)
{
    test_cpu(curve, r, a, b, testLevel, calcMSM_Mock_cpu<CurveT>, oss);
}

template <typename CurveT>
void test_gpu_msm(
    CurveT &curve, Vector &r, Vector &a, Vector &b,
    const std::string &shaderPath,
    std::ostream      &oss)
{
    VulkanMSM vkMSM;

    calcMSM_gpu(vkMSM, curve, r, a, b, shaderPath);

    const auto perf = vkMSM.getPerf();
    const size_t shaderSize = perf.shaderSize;
    const auto compileTime = perf.compileTime;
    const auto computeTime = perf.computeTime;
    const auto gpuTime = compileTime + computeTime;

    VulkanManager vkMgr;
    vkMgr.debugInfo(oss, LogLevel);

    printMsg(1, oss, "Shader path: ", shaderPath);
    printMsg(1, oss, "Shader size: ", shaderSize, " bytes");
    printMsg(1, oss, "GPU        compile time: ", compileTime, " ms");
    printMsg(1, oss, "GPU        compute time: ", computeTime, " ms");
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

    auto perf = calcCurve_gpu(vkMgr, curve, r, a, b, shaderPath);

    vkMgr.debugInfo(oss, LogLevel);

    const size_t shaderSize = perf.shaderSize;
    const auto compileTime = perf.compileTime;
    const auto computeTime = perf.computeTime;
    const auto gpuTime = compileTime + computeTime;

    printMsg(1, oss, "Shader path: ", shaderPath);
    printMsg(1, oss, "Shader size: ", shaderSize, " bytes");
    printMsg(1, oss, "GPU        compile time: ", compileTime, " ms");
    printMsg(1, oss, "GPU        compute time: ", computeTime, " ms");
    printMsg(0, oss, "GPU      execution time: ", gpuTime, " ms");
}

template <typename CurveT>
void test_msm(
    CurveT            &curve,
    const std::string &shaderPath,
    unsigned int       pointCount,
    unsigned int       testLevel,
    char              *msg,
    long               msgMaxSize)
{
    std::ostringstream oss;
    const size_t pointSize     = sizeof(typename CurveT::Point);
    const size_t factor        = pointSizeInElements(curve);
    const size_t inVectorSize  = pointCount * factor;
    const size_t outVectorSize = 1 * factor;

    Vector a(inVectorSize);
    Vector b(inVectorSize);
    Vector r_cpu(outVectorSize);
    Vector r_vk(outVectorSize);

    printMsg(0, oss, "LogLevel: ", LogLevel, " TestLevel: ", testLevel);

    initPoints(curve, a);
    initVecInc(b, 2);
    test_gpu_msm(curve, r_vk, a, b, shaderPath, oss);

    if (testLevel >= 1) {
        test_cpu_msm(curve, r_cpu, a, b, testLevel, oss);

        printMsg(0, oss, "Vulkan eq: ", std::boolalpha, cmpVec(r_cpu, r_vk));
    }

    printMsg(1, oss, "PointSize: ",  pointSize, " bytes");
    printMsg(0, oss, "PointCount: ", pointCount);

    printVec(2, oss, a, b, r_cpu, r_vk);
    printMsg(2, oss, "Work: MSM_" + curveName(curve));

    strncat(msg, oss.str().c_str(), msgMaxSize);
}

template <typename CurveT>
void test_curve(
    CurveT            &curve,
    const std::string &shaderPath,
    unsigned int       pointCount,
    unsigned int       testLevel,
    char              *msg,
    long               msgMaxSize)
{
    std::ostringstream oss;
    const size_t pointSize  = sizeof(typename CurveT::Point);
    const size_t vectorSize = pointCount * pointSizeInElements(curve);

    Vector a(vectorSize);
    Vector b(vectorSize);
    Vector r_cpu(vectorSize);
    Vector r_vk(vectorSize);

    printMsg(0, oss, "LogLevel: ", LogLevel, " TestLevel: ", testLevel);

    initVecInc(a, 0xccbbaa998877);
    initVecInc(b, 0xeeddccbbaa99);

    test_gpu_curve(curve, r_vk, a, b, shaderPath, oss);

    if (testLevel >= 1) {
        test_cpu_curve(curve, r_cpu, a, b, testLevel, oss);

        printMsg(0, oss, "Vulkan eq: ", std::boolalpha, cmpVec(r_cpu, r_vk));
    }

    printMsg(1, oss, "PointSize: ",  pointSize, " bytes");
    printMsg(0, oss, "PointCount: ", pointCount);

    printVec(2, oss, a, b, r_cpu, r_vk);
    printMsg(2, oss, "Work: Curve_" + curveName(curve));

    strncat(msg, oss.str().c_str(), msgMaxSize);
}

void test(
    const std::string &shaderPath,
    const std::string &testType,
    unsigned int       pointCount,
    unsigned int       testLevel,
    char              *msg,
    long               msgMaxSize)
{
    const std::string fullShaderPath = shaderPath + "/" + testType;

    AltBn128::Engine E;
    CurveMock mock;

    if (testType == "msm_mock") {
        test_msm(mock, fullShaderPath, pointCount, testLevel, msg, msgMaxSize);

    } else if (testType == "msm_g1") {
        test_msm(E.g1, fullShaderPath, pointCount, testLevel, msg, msgMaxSize);

    } else if (testType == "curve_mock") {
        test_curve(mock, fullShaderPath, pointCount, testLevel, msg, msgMaxSize);

    } else if (testType == "curve_g1") {
        test_curve(E.g1, fullShaderPath, pointCount, testLevel, msg, msgMaxSize);

    } else {
        const auto error = std::string("Unknown test type: ") + testType;

        strncat(msg, error.c_str(), msgMaxSize);
    }
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
auto measure_msm_time_gpu(
    CurveT &curve, Vector &r, Vector &a, Vector &b,
    const std::string &shaderPath)
{
    VulkanMSM vkMSM;

    return calcMSM_gpu(vkMSM, curve, r, a, b, shaderPath);
}

size_t calcSizeFactor(AltBn128::Engine &E, int curveId)
{
    if (curveId == VULKAN_TEST_CURVE_G1) {
        return pointSizeInElements(E.g1);

    } else if (curveId == VULKAN_TEST_CURVE_G2) {
        return pointSizeInElements(E.g2);

    } else {
        assert(0 && "Invalid curveId");
    }
}

void initPoints(AltBn128::Engine &E, int curveId, Vector &a)
{
    if (curveId == VULKAN_TEST_CURVE_G1) {
        initPoints(E.g1, a);

    } else if (curveId == VULKAN_TEST_CURVE_G2) {
        initPoints(E.g2, a);

    } else {
        assert(0 && "Invalid curveId");
    }
}

bool measure_msm_time(
    int                curveId,
    const std::string &shaderPath,
    unsigned int       pointCount,
    vulkan_msm_time   *msmTime)
{
    AltBn128::Engine E;

    const auto factor = calcSizeFactor(E, curveId);
    const size_t inVectorSize  = pointCount * factor;
    const size_t outVectorSize = 1 * factor;

    Vector a(inVectorSize);
    Vector b(inVectorSize);
    Vector r_cpu(outVectorSize);
    Vector r_vk(outVectorSize);

    initPoints(E, curveId, a);
    initVecInc(b, 2);

    if (curveId == VULKAN_TEST_CURVE_G1) {
        const auto perf  = measure_msm_time_gpu(E.g1, r_vk, a, b, shaderPath);
        msmTime->cpu     = measure_msm_time_cpu(E.g1, r_cpu, a, b);
        msmTime->gpu     = perf.compileTime + perf.computeTime;
        msmTime->compile = perf.compileTime;

    } else if (curveId == VULKAN_TEST_CURVE_G2) {
        msmTime->cpu     = measure_msm_time_cpu(E.g2, r_cpu, a, b);
        msmTime->gpu     = -1;
        msmTime->compile = 0;

        initVecVal(r_cpu, 0);
    }

    return cmpVec(r_cpu, r_vk);
}

} // namespace

int vulkan_test_params(
    const char   *shader_path,
    const char   *test_type,
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
        test(shader_path, test_type, point_count, test_level, msg, msg_max_size);

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
    const char         *test_type = "msm_g1";
    const unsigned int  point_count = 500*1024;
    const unsigned int  log_level = 0;
    const unsigned int  test_level = 1;

    return vulkan_test_params(shader_path, test_type, point_count,
                              log_level, test_level, msg, msg_max_size);
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
        const bool comp_eq = measure_msm_time(curve_id, shader_path, point_count, msm_time);

        if (comp_eq) {
            return VULKAN_TEST_RESULT_OK;

        } else {
            result = "GPU and CPU computation results are not equal";
            error  = VULKAN_TEST_RESULT_COMP_NOT_EQUAL;
        }

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
