#ifndef UTILS_H
#define UTILS_H

#include <chrono>
#include <functional>

template <typename T1, typename T2>
auto div_ceil(T1 a, T2 b)
{
    return (a + b - 1) / b;
}

inline long measureTime(std::function<void()> func)
{
    auto start = std::chrono::high_resolution_clock::now();

    func();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    return duration.count();
}

#endif // UTILS_H
