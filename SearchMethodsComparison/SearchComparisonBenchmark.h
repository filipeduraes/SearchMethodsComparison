#pragma once

#include <memory>
#include <string>

#include "Benchmark.h"
#include "ISearchableSet.h"
#include "RecordFileHandler.h"

/*
 * Guarda o estado do teste atual
 * Cada teste tem:
 *  - std::string setLabel: o nome do método de pesquisa (Sequencial, Árvore Binária ou Árvore AVL)
 *  - ISearchableSet<int, std::shared_ptr<Record>> searchableSet: a estrutura de dados que guarda o método de pesquisa atual
 *      Nota: foi usado um std::shared_ptr para que possa compartilhar a referência entre os três métodos de busca (evitar alocação extra de memória)
 *            e também para evitar de ter que liberar todos eles manualmente após o destrutor ser chamado
 *            (quando todas as referências forem perdidas, ele será liberado automaticamente)
 *  - Benchmark benchmark: o benchmark usado para calcular a média do tempo de execução
 *  - int comparisonSum: a soma dos números de comparação que será usado para calcular a média no final
 */
struct BenchmarkSetup
{
    std::string setLabel;
    ISearchableSet<int, std::shared_ptr<Record>>* searchableSet;
    Benchmark benchmark;
    int comparisonSum = 0;

    BenchmarkSetup(std::string setLabel, ISearchableSet<int, std::shared_ptr<Record>>* searchableSet)
        : setLabel(std::move(setLabel)), searchableSet(searchableSet)
    {
    }
};

/*
 * Realiza os testes específicos da comparação de métodos de busca
 * Guarda o estado do setup de testes para cada método de busca
 * Mostra o resultado dos testes no console
 */
class SearchComparisonBenchmark
{
private:
    std::vector<RecordFileHandler> handlers;
    std::vector<BenchmarkSetup> setup;
    
public:
    explicit SearchComparisonBenchmark(const std::vector<RecordFileHandler>& handlers)
        : handlers(handlers)
    {
        
    }

    bool TryGenerateRecordFiles();
    void BenchmarkAllFiles();

private:
    void BenchmarkKeysSearch(const std::vector<int>& keys);
    void ShowBenchmarkResults(int keysCount);
};