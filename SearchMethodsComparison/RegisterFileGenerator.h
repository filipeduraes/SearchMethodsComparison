#pragma once
#include <memory>
#include <string>
#include <vector>

#include "ISearchableSet.h"

namespace Generator
{    
    struct Record
    {
        int firstData;
        std::string secondData;
        
        Record(const int firstData, std::string secondData)
            : firstData(firstData), secondData(std::move(secondData))
        {
        }
    };
    
    struct RecordWithKey
    {
        int key;
        std::unique_ptr<Record> record;

        RecordWithKey(const int key, std::unique_ptr<Record> record)
            : key(key), record(std::move(record))
        {
        }
    };

    class RecordFileGenerator
    {
    private:
        std::string directory;
        int recordCount;
        bool isSorted;

    public:
        RecordFileGenerator(const std::string&& fileDirectory, const int recordCount, const bool isOrdered = false)
            : directory(fileDirectory), recordCount(recordCount), isSorted(isOrdered)
        {
            
        }
        
        void GenerateFile();
        void PopulateSetsWithFile(const std::vector<ISearchableSet<int, std::shared_ptr<Record>>*>& sets) const;
        
    private:
        std::string GetFilePath() const;
        void GenerateRandomRecordsWithKey(std::vector<RecordWithKey>& records) const;
        static Record GenerateRandomRecord();            
    };
    
};