#pragma once
#include <iostream>
#include <memory>
#include <string>

#include "AVLTree.h"
#include "Benchmark.h"
#include "BinaryTree.h"
#include "ISearchableSet.h"
#include "RegisterFileHandler.h"
#include "SequentialSet.h"

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

template<int KeysCount>
class SearchComparisonBenchmark
{
private:
    std::vector<RecordFileHandler> handlers;
    std::vector<BenchmarkSetup> setup;
    
public:
    SearchComparisonBenchmark(const std::vector<RecordFileHandler>& handlers)
        : handlers(handlers)
    {
        
    }

    bool TryGenerateRecordFiles() const;
    void BenchmarkAllFiles();

private:
    void BenchmarkKeysSearch(const std::array<int, KeysCount>& keys);
    void ShowBenchmarkResults();
};

template <int KeysCount>
bool SearchComparisonBenchmark<KeysCount>::TryGenerateRecordFiles() const
{
    for (const RecordFileHandler& handler : handlers)
    {
        std::string path = handler.GenerateFile();

        if(path.empty())
        {
            std::cerr << "Erro na geracao dos arquivos";
            return false;
        }
            
        std::cout << "Arquivo gerado em: " << path << "\n";
    }
        
    return true;
}

template <int KeysCount>
void SearchComparisonBenchmark<KeysCount>::BenchmarkAllFiles()
{
    for (const RecordFileHandler& handler : handlers)
    {
        std::cout << "\n====== Arquivo com " << handler.GetRecordCount() << " registros -- " << (handler.GetIsSorted() ? "Ordenado" : "Nao Ordenado") << " ======";

        setup = {
            BenchmarkSetup("Sequencial", new SequentialSet<int, std::shared_ptr<Record>>()),
            BenchmarkSetup("Binaria", new BinaryTree<int, std::shared_ptr<Record>>()),
            BenchmarkSetup("AVL", new AVLTree<int, std::shared_ptr<Record>>()),
        };

        std::vector<ISearchableSet<int, std::shared_ptr<Record>>*> sets;
        sets.reserve(setup.size());

        for(BenchmarkSetup& benchmarkSetup : setup)
        {
            sets.push_back(benchmarkSetup.searchableSet);
        }

        handler.PopulateSetsWithFile(sets);

        RandomRecordKeys<KeysCount> randomKeys = handler.GetRandomKeysFromFile<KeysCount>();

        std::cout << "\nChaves presentes: ";
        SearchComparisonBenchmark::BenchmarkKeysSearch(randomKeys.presentKeys);
            
        std::cout << "\n\nChaves nao presentes: ";
        SearchComparisonBenchmark::BenchmarkKeysSearch(randomKeys.notPresentKeys);
           
        std::cout << "\n========================================================\n";
    }
}

template <int KeysCount>
void SearchComparisonBenchmark<KeysCount>::BenchmarkKeysSearch(const std::array<int, KeysCount>& keys)
{
    for(BenchmarkSetup& benchmarkSetup : setup)
    {
        benchmarkSetup.benchmark = Benchmark();
    }
    
    for (const int& key : keys)
    {
        std::cout << key << " ";
    }
            
    for (const int& key : keys)
    {
        for(BenchmarkSetup& benchmarkSetup : setup)
        {
            benchmarkSetup.benchmark.Start();
            benchmarkSetup.searchableSet->Search(key);
            benchmarkSetup.benchmark.Stop();
            benchmarkSetup.comparisonSum += benchmarkSetup.searchableSet->GetLastComparisonCount();
        }
    }

    ShowBenchmarkResults();
}

template <int KeysCount>
void SearchComparisonBenchmark<KeysCount>::ShowBenchmarkResults()
{
    std::cout << "\nTempo medio de execucao: ";
        
    for(BenchmarkSetup& benchmarkSetup : setup)
    {
        std::cout << "\n - " << benchmarkSetup.setLabel << ": " << benchmarkSetup.benchmark.GetMediumMicroseconds() << " microssegundos, " << benchmarkSetup.benchmark.GetMediumMilliseconds() << " milissegundos";
    }

    std::cout << "\n\nNumero medio de comparacoes:";
        
    for(BenchmarkSetup& benchmarkSetup : setup)
    {
        std::cout << "\n - " << benchmarkSetup.setLabel << ": " << benchmarkSetup.comparisonSum / 15;
    }
}
