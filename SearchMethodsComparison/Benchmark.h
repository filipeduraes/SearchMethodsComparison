#pragma once

#include <chrono>

class Benchmark
{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTimePoint;
    
public:
    Benchmark();
    ~Benchmark();

private:
    void Stop() const;
};
