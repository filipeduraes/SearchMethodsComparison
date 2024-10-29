#include "Benchmark.h"

void Benchmark::Start()
{
    startTimePoint = std::chrono::high_resolution_clock::now();
}

void Benchmark::Stop()
{
    std::chrono::steady_clock::time_point endTimePoint = std::chrono::high_resolution_clock::now();

    const long long start = std::chrono::time_point_cast<std::chrono::microseconds>(startTimePoint).time_since_epoch().count();
    const long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

    const long long currentDurationMicroseconds = end - start;
    const double currentDurationMilliseconds = currentDurationMicroseconds * 0.001;

    microsecondsSum += currentDurationMicroseconds;
    millisecondsSum += currentDurationMilliseconds;
    testsCount++;
}
