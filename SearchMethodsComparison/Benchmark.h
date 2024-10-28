#pragma once

#include <chrono>
#include <string>

class Benchmark
{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTimePoint;
    std::string label;
    
public:
    Benchmark(std::string label = "");
    ~Benchmark();

private:
    void Stop() const;
};
