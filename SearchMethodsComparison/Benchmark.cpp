#include "Benchmark.h"

#include <iostream>

Benchmark::Benchmark()
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
    
    long long start = std::chrono::time_point_cast<std::chrono::microseconds>(startTimePoint).time_since_epoch().count();
    long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

    long long duration = end - start;
    double ms = duration * 0.001;

    std::cout << "Duration microseconds: " << duration << "\nDuration miliseconds: " << ms << std::endl;
}
