#pragma once

#include <memory>
#include <string>

#include "Benchmark.h"
#include "ISearchableSet.h"
#include "RecordFileHandler.h"

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

    bool TryGenerateRecordFiles();
    void BenchmarkAllFiles();

private:
    void BenchmarkKeysSearch(const std::vector<int>& keys);
    void ShowBenchmarkResults();
};