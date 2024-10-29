#pragma once

#include <chrono>
#include <stack>
#include <string>

class Benchmark
{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTimePoint;
    std::string label;
    
    long long microsecondsSum = 0;
    double millisecondsSum = 0;

    int testsCount = 0;
    
public:
    void Start();
    void Stop();

    double GetMediumMicroseconds() const
    {
        return (double) microsecondsSum / testsCount;
    }

    double GetMediumMilliseconds() const
    {
        return millisecondsSum / testsCount;
    }
};
