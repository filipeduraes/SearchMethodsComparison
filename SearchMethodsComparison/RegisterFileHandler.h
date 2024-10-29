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

template<int KeysLength>
struct RandomRecordKeys
{
    std::array<int, KeysLength> presentKeys;
    std::array<int, KeysLength> notPresentKeys;

    RandomRecordKeys(const std::array<int, KeysLength>& presentKeys, const std::array<int, KeysLength>& notPresentKeys)
        : presentKeys(presentKeys), notPresentKeys(notPresentKeys)
    {
    }
};

class RecordFileHandler
{
private:
    std::string directory;
    int recordCount;
    bool isSorted;
    
public:
    RecordFileHandler(std::string fileDirectory, const int recordCount, const bool isOrdered = false)
        : directory(std::move(fileDirectory)), recordCount(recordCount), isSorted(isOrdered)
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
    
    std::string GenerateFile() const;
    void PopulateSetsWithFile(const std::vector<ISearchableSet<int, std::shared_ptr<Record>>*>& sets) const;

    template<int KeysLength>
    RandomRecordKeys<KeysLength> GetRandomKeysFromFile() const;
    
private:
    std::string GetFilePath() const;
    void GenerateRandomRecordsWithKey(std::vector<RecordKeyPair>& records) const;
    static Record GenerateRandomRecord();

    template<int KeysLength>
    static void FillNotPresentKeys(std::unordered_set<int>& keys, std::array<int, KeysLength>& notPresentKeys);
    
    template<int KeysLength>
    static void FillPresentKeys(std::unordered_set<int>& keys, std::array<int, KeysLength>& presentKeys);
};

template<int KeysLength>
RandomRecordKeys<KeysLength> RecordFileHandler::GetRandomKeysFromFile() const
{
    std::ifstream file(GetFilePath());
    std::unordered_set<int> keys;
    keys.reserve(recordCount);

    if(file.is_open())
    {
        std::string line;

        while (!file.eof())
        {
            int key = -1;
            std::getline(file, line);
            file >> key;
            keys.insert(key);
        }

        file.close();
    }

    std::array<int, KeysLength> presentKeys;
    std::array<int, KeysLength> notPresentKeys;

    RecordFileHandler::FillNotPresentKeys(keys, notPresentKeys);
    RecordFileHandler::FillPresentKeys(keys, presentKeys);

    return RandomRecordKeys<KeysLength>(presentKeys, notPresentKeys);
}

template<int KeysLength>
void RecordFileHandler::FillNotPresentKeys(std::unordered_set<int>& keys, std::array<int, KeysLength>& notPresentKeys)
{
    int count = 0;

    while (count < notPresentKeys.size())
    {
        int randomKey = std::rand();

        if(keys.find(randomKey) == keys.end())
        {
            notPresentKeys[count] = randomKey;
            count++;
        }
    }
}

template<int KeysLength>
void RecordFileHandler::FillPresentKeys(std::unordered_set<int>& keys, std::array<int, KeysLength>& presentKeys)
{
    const std::vector<int> keysVector(keys.begin(), keys.end());

    for (int& presentKey : presentKeys)
    {
        const int index = std::rand() % keysVector.size();
        presentKey = keysVector[index];
    }
}