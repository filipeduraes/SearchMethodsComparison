#include "SearchComparisonBenchmark.h"

#include <iostream>

#include "AVLTree.h"
#include "BinaryTree.h"
#include "SequentialSet.h"

bool SearchComparisonBenchmark::TryGenerateRecordFiles()
{
    for (RecordFileHandler& handler : handlers)
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

void SearchComparisonBenchmark::BenchmarkAllFiles()
{
    for (RecordFileHandler& handler : handlers)
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

        RandomRecordKeys randomKeys = handler.GetRandomKeysFromFile();

        std::cout << "\nChaves presentes: ";
        BenchmarkKeysSearch(randomKeys.presentKeys);
            
        std::cout << "\n\nChaves nao presentes: ";
        BenchmarkKeysSearch(randomKeys.notPresentKeys);
           
        std::cout << "\n========================================================\n";
    }
}

void SearchComparisonBenchmark::BenchmarkKeysSearch(const std::vector<int>& keys)
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

    ShowBenchmarkResults((int) keys.size());
}

void SearchComparisonBenchmark::ShowBenchmarkResults(const int keysCount)
{
    std::cout << "\nTempo medio de execucao: ";
        
    for(BenchmarkSetup& benchmarkSetup : setup)
    {
        std::cout << "\n - " << benchmarkSetup.setLabel << ": " << benchmarkSetup.benchmark.GetMediumMicroseconds() << " microssegundos, " << benchmarkSetup.benchmark.GetMediumMilliseconds() << " milissegundos";
    }

    std::cout << "\n\nNumero medio de comparacoes:";
        
    for(BenchmarkSetup& benchmarkSetup : setup)
    {
        std::cout << "\n - " << benchmarkSetup.setLabel << ": " << benchmarkSetup.comparisonSum / keysCount;
    }
}
