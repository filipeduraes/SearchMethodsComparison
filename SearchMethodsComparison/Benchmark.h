#pragma once

#include <chrono>
#include <stack>
#include <string>

/*
 * Cuida da medição do tempo de execução e do cálculo da média entre eles
 * Ao começar o benchmark, guarda o tempo inicial
 * Ao finalizar o benchmark, marca o tempo final, diminui do tempo inicial, soma no tempo total e atualiza a quantidade de testes
 * Retorna o tempo médio ao dividir o tempo total pela quantidade de testes
 */
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
