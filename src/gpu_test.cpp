#include "gpu_test.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdint>
#include <cstring>
#include <limits>
#include <thread>
#include <memory>
#include <vector>
#include <chrono>
#include <cassert>
#include "fq.hpp"
#include "misc.hpp"
#include "vulkan_manager.h"

const unsigned int MaxPointCount = 1000*1024*1024;
const unsigned int MaxIterCount  = 1000*1000;
const unsigned int WorkgroupSize = 128;
static unsigned int LogLevel = 3;

struct Params
{
    uint32_t iterNum;
};

Params CreateParams(unsigned int iter_count)
{
    return { iter_count };
}

struct Element
{
    uint64_t& operator[](int i) { return val[i]; }
    const uint64_t& operator[](int i) const  { return val[i]; }

    operator FqRawElement& () { return val; }
    operator const FqRawElement& () const { return val; }

    FqRawElement val;
};

using Vector = std::vector<Element>;

VulkanBufferView Vector2View(Vector &v)
{
    return {v.data(), v.size() * sizeof(Vector::value_type)};
}

void printMsg(std::ostream& os)
{
    os << std::endl;
}

template <typename T, typename... Args>
void printMsg(std::ostream& os, T value, Args... args)
{
    os << value;
    printMsg(os, args...);
}

template <typename... Args>
void printMsg(unsigned int level, std::ostream& os, Args... args)
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

std::ostream& operator<<(std::ostream& os, const FqRawElement val)
{
    os << format(val[0]) << ","
       << format(val[1]) << ","
       << format(val[2]) << ","
       << format(val[3]);

    return os;
}

void vecAdd(Element& c, const Element& a, const Element& b)
{
    c[0] = a[0] + b[0];
    c[1] = a[1] + b[1];
    c[2] = a[2] + b[2];
    c[3] = a[3] + b[3];
}

void vecMul(Element& c, const Element& a, const Element& b)
{
    c[0] = a[0] * b[0];
    c[1] = a[1] * b[1];
    c[2] = a[2] * b[2];
    c[3] = a[3] * b[3];
}

void calcIdle(Vector& c, const Vector& a, const Vector& b)
{
    const int size = c.size();

    assert(size == a.size());
    assert(size == b.size());

    for (size_t i = 0; i < size; i++) {
        vecAdd(c[i], a[i], b[i]);
    }
}

void calcSingle(Vector& c, const Vector& a, const Vector& b, unsigned int iter_count)
{
    const int size = c.size();

    assert(size == a.size());
    assert(size == b.size());

    for (size_t i = 0; i < size; i++) {
        for (size_t k = 0; k < iter_count; k++) {
            Fq_rawAdd(c[i], a[i], b[i]);
            Fq_rawMMul(c[i], a[i], b[i]);
        }
    }
}

void calcParallel(ThreadPool &threadPool, Vector& c, const Vector& a, const Vector& b, unsigned int iter_count)
{
    const int size = c.size();

    assert(size == a.size());
    assert(size == b.size());

    threadPool.parallelFor(0, size, [&] (int begin, int end, int numThread) {

        for (size_t i = begin; i < end; i++) {
            for (size_t k = 0; k < iter_count; k++) {
                Fq_rawAdd(c[i], a[i], b[i]);
                Fq_rawMMul(c[i], a[i], b[i]);
            }
        }
    });
}

void initVecInc(Vector& a, size_t initVal)
{
    for (size_t i = 0; i < a.size(); i++) {
        a[i][0] = i + initVal;
        a[i][1] = i + initVal;
        a[i][2] = i + initVal;
        a[i][3] = i + initVal;
    }
}

void initVecVal(Vector& a, size_t initVal = 0)
{
    for (size_t i = 0; i < a.size(); i++) {
        a[i][0] = initVal;
        a[i][1] = initVal;
        a[i][2] = initVal;
        a[i][3] = initVal;
    }
}

bool cmpVec(const Vector& a, const Vector& b)
{
    const std::size_t size = a.size();

    assert(a.size() == b.size());

    for (size_t i = 0; i < size; i++) {
        if (!Fq_rawIsEq(a[i], b[i])) {
            return false;
        }
    }

    return true;
}

void printVec(unsigned int level, std::ostream& oss, const Vector& r, const Vector& a, const Vector& b)
{
    printMsg(level, oss, "a[0]: ", a[0]);
    printMsg(level, oss, "b[0]: ", b[0]);
    printMsg(level, oss, "r[0]: ", r[0]);
    printMsg(level, oss, "r[M]: ", r[r.size()-1]);
}

void test_cpu(
    Vector& r_par, const Vector& a, const Vector& b,
    unsigned int  point_count,
    unsigned int  iter_count,
    unsigned int  test_level,
    std::ostream& oss)
{
    Vector r_sngl(point_count);

    ThreadPool &threadPool = ThreadPool::defaultPool();

    auto start = std::chrono::high_resolution_clock::now();

    calcParallel(threadPool, r_par, a, b, iter_count);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    printMsg(0, oss, "Parallel execution time: ", duration.count(), " ms");

    if (test_level >= 2) {
        start = std::chrono::high_resolution_clock::now();

        calcSingle(r_sngl, a, b, iter_count);

        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        printMsg(0, oss, "Single   execution time: ", duration.count(), " ms");
    }

    printMsg(0, oss, "threads: ", threadPool.getThreadCount());

    if (test_level >= 2) {
        printMsg(2, oss, "CPU eq: ", std::boolalpha, cmpVec(r_sngl, r_par));
    }
}

void test_gpu(
    Vector& r, Vector& a, Vector& b,
    unsigned int  point_count,
    unsigned int  iter_count,
    const char*   shader_path,
    std::ostream& oss)
{
    VulkanBufferView   vR = Vector2View(r);
    VulkanBufferView   vA = Vector2View(a);
    VulkanBufferView   vB = Vector2View(b);
    Params             params = CreateParams(iter_count);
    VulkanBufferView   vParams = {&params, sizeof(params)};
    VulkanMemoryLayout memoryLayout = {vR.size, vA.size, vB.size, vParams.size, point_count*4};
    const uint32_t     groupCount = point_count / WorkgroupSize;
    VulkanManager      vkMgr;

    auto start = std::chrono::high_resolution_clock::now();

    auto vkPipeline = vkMgr.createPipeline(shader_path, memoryLayout, groupCount, vParams);

    vkPipeline->run(vR, vA, vB);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    vkMgr.debugInfo(oss, LogLevel);

    printMsg(1, oss, "Shader path: ",  shader_path);
    printMsg(1, oss, "Shader size: ",  vkPipeline->shaderSize(), " bytes");
    printMsg(0, oss, "GPU      execution time: ", duration.count(), " ms");
}

void test(
    const char*   shader_path,
    unsigned int  point_count,
    unsigned int  iter_count,
    unsigned int  test_level,
    char*         msg,
    long          msg_max_size)
{
    std::ostringstream oss;
    Vector a(point_count);
    Vector b(point_count);
    Vector r_cpu(point_count);
    Vector r_vk(point_count);
    Vector temp(point_count);
    const size_t pointSize = sizeof(Vector::value_type);

    printMsg(0, oss, "LogLevel: ", LogLevel);
    printMsg(0, oss, "TestLevel: ", test_level);

    initVecInc(a, 1);
    initVecInc(b, 2);
    initVecVal(r_cpu);
    initVecVal(r_vk);

    calcIdle(temp, a, b);

    test_gpu(r_vk, a, b, point_count, iter_count, shader_path, oss);

    if (test_level >= 1) {
        test_cpu(r_cpu, a, b, point_count, iter_count, test_level, oss);

        printMsg(0, oss, "Vulkan eq: ", std::boolalpha, cmpVec(r_cpu, r_vk));
    }

    printMsg(1, oss, "PointSize: ",  pointSize, " bytes");
    printMsg(0, oss, "PointCount: ", point_count);
    printMsg(0, oss, "IterCount: ",  iter_count);

    printVec(2, oss, r_vk, a, b);
    printMsg(2, oss, "Work: Fq_rawAdd + Fq_rawMMul");

    strncat(msg, oss.str().c_str(), msg_max_size);
}

void gpu_test_params(
    const char*   shader_path,
    unsigned int  point_count,
    unsigned int  iter_count,
    unsigned int  log_level,
    unsigned int  test_level,
    char*         msg,
    long          msg_max_size)
{
    if (point_count < WorkgroupSize) {
        point_count = WorkgroupSize;

    } else if (point_count > MaxPointCount) {
        point_count = MaxPointCount;
    }

    point_count = ((point_count + WorkgroupSize - 1) / WorkgroupSize) * WorkgroupSize;

    if (iter_count < 1) {
        iter_count = 1;

    } else if (iter_count > MaxIterCount) {
        iter_count = MaxIterCount;
    }

    LogLevel = log_level;

    std::string result;

    msg[0] = 0;

    try {
        test(shader_path, point_count, iter_count, test_level, msg, msg_max_size);
        return;

    } catch (std::exception& e) {
        result = "Failed: ";
        result += e.what();
    }
    catch (...) {
        result += "Failed: unknown error";
    }

    strncat(msg, result.c_str(), msg_max_size);
}

void gpu_test(
    const char* shader_path,
    char*       msg,
    long        msg_max_size)
{
    const unsigned int point_count = 500*1024;
    const unsigned int iter_count = 160;
    const unsigned int log_level = 0;
    const unsigned int test_level = 1;

    gpu_test_params(shader_path, point_count, iter_count, log_level, test_level, msg, msg_max_size);
}
