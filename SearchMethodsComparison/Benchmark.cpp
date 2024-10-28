#include "Benchmark.h"

#include <iostream>

Benchmark::Benchmark(std::string label)
    : label(std::move(label))
{
    startTimePoint = std::chrono::high_resolution_clock::now();
}

Benchmark::~Benchmark()
{
    Stop();
}

void Benchmark::Stop() const
{
    std::chrono::steady_clock::time_point endTimePoint = std::chrono::high_resolution_clock::now();

    const long long start = std::chrono::time_point_cast<std::chrono::microseconds>(startTimePoint).time_since_epoch().count();
    const long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

    const long long durationMicroseconds = end - start;
    const double durationMiliseconds = durationMicroseconds * 0.001;

    if(!label.empty())
    {
        std::cout << label << ": ";
    }

    std::cout << "Duration microseconds: " << durationMicroseconds << ", miliseconds: " << durationMiliseconds << "\n";
}
