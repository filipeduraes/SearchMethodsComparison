#pragma once
#include <array>
#include <fstream>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "ISearchableSet.h"

struct Record
{
    int firstData;
    std::string secondData;
    
    Record(const int firstData, std::string secondData)
        : firstData(firstData), secondData(std::move(secondData))
    {
    }
};

struct RecordKeyPair
{
    int key;
    std::unique_ptr<Record> record;

    RecordKeyPair(const int key, std::unique_ptr<Record> record)
        : key(key), record(std::move(record))
    {
    }
};

struct RandomRecordKeys
{
    std::vector<int> presentKeys;
    std::vector<int> notPresentKeys;

    RandomRecordKeys() = default;

    RandomRecordKeys(const std::vector<int>& presentKeys, const std::vector<int>& notPresentKeys)
        : presentKeys(presentKeys), notPresentKeys(notPresentKeys)
    {
    }
};

// Gera e lê os arquivos com registros aleatórios no formato: chave,dado1,dado2
class RecordFileHandler
{
private:
    RandomRecordKeys randomKeys;
    std::string directory;
    int recordCount;
    int randomKeysLength;
    bool isSorted;
    
public:
    RecordFileHandler(std::string fileDirectory, const int recordCount, const bool isOrdered = false, const int randomKeysLength = 15)
        : directory(std::move(fileDirectory))
        , recordCount(recordCount)
        , randomKeysLength(randomKeysLength)
        , isSorted(isOrdered)
    {
    }

    int GetRecordCount() const
    {
        return recordCount;
    }

    bool GetIsSorted() const
    {
        return isSorted;
    }
    
    std::string GenerateFile();
    void PopulateSetsWithFile(const std::vector<ISearchableSet<int, std::shared_ptr<Record>>*>& sets) const;

    RandomRecordKeys GetRandomKeysFromFile()
    {
        return randomKeys;
    }
    
private:
    std::string GetFilePath() const;
    void GenerateRandomRecordsWithKey(std::vector<RecordKeyPair>& records);
    static Record GenerateRandomRecord();

    void GenerateRandomKeys(std::unordered_set<int> alreadyUsedKeys);
    static void FillNotPresentKeys(std::unordered_set<int>& keys, std::vector<int>& notPresentKeys);
    static void FillPresentKeys(std::unordered_set<int>& keys, std::vector<int>& presentKeys);
};