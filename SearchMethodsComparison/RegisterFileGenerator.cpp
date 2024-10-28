﻿#include "RegisterFileGenerator.h"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <unordered_set>

void Generator::RecordFileGenerator::GenerateFile()
{
    std::fstream file;
    const std::string& filePath = GetFilePath();
    file.open(filePath, std::ios::out);

    if(file.is_open())
    {
        std::vector<RecordWithKey> records;
        GenerateRandomRecordsWithKey(records);

        if(isSorted)
        {
            std::sort(records.begin(), records.end(), [](const RecordWithKey& a, const RecordWithKey& b) {return a.key < b.key;} );
        }

        for(int i = 0; i < recordCount; i++)
        {
            const RecordWithKey& recordWithKey = records[i];
            file << recordWithKey.key << "," << recordWithKey.record->firstData << "," << recordWithKey.record->secondData;

            if(i < recordCount - 1)
            {
                file << "\n";
            }
        }

        file.close();
    }
}

void Generator::RecordFileGenerator::GenerateRandomRecordsWithKey(std::vector<RecordWithKey>& records) const
{
    srand(time(0));
    std::unordered_set<int> alreadyUsedKeys;
    alreadyUsedKeys.reserve(recordCount);
    records.reserve(recordCount);

    for(int i = 0; i < recordCount; i++)
    {
        int key = rand();

        while (alreadyUsedKeys.find(key) != alreadyUsedKeys.end())
        {
            key = rand();
        }

        Record record = GenerateRandomRecord();
        alreadyUsedKeys.insert(key);
        records.emplace_back(key, std::make_unique<Record>(record));
    }
}

void Generator::RecordFileGenerator::PopulateSetsWithFile(const std::vector<ISearchableSet<int, std::shared_ptr<Record>>*>& sets) const
{
    std::ifstream file(GetFilePath());

    if(file.is_open())
    {
        std::string line;
        
        while (std::getline(file, line))
        {
            std::istringstream lineStream(line);
            int key;
            int firstData;
            std::string secondData;
            char delimiter;

            if(lineStream >> key >> delimiter >> firstData >> delimiter && std::getline(lineStream, secondData))
            {
                std::shared_ptr<Record> record = std::make_shared<Record>(firstData, secondData);
                
                for (ISearchableSet<int, std::shared_ptr<Record>>* set : sets)
                {
                    set->Insert(key, record);                    
                }
            }
        }

        file.close();
    }
}

std::string Generator::RecordFileGenerator::GetFilePath() const
{
    const std::string fileNamePrefix = isSorted ? "Output_Sorted_" : "Output_";
    const std::string fileExtension = ".txt";
    const std::string filePath = directory + fileNamePrefix + std::to_string(recordCount) + fileExtension;
    return filePath;
}

Generator::Record Generator::RecordFileGenerator::GenerateRandomRecord()
{
    const int firstData = rand();
    std::string secondData;

    for(int i = 0; i < 1000; i++)
    {
        constexpr char initialLetter =  'A';
        constexpr char finalLetter =  'Z';
        char letter = static_cast<char>(initialLetter + rand() % (finalLetter - initialLetter));

        if(rand() % 100 < 50)
        {
            letter = static_cast<char>(std::tolower(letter));
        }

        secondData += letter;
    }

    return Record(firstData, secondData);
}
