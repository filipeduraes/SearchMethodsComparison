#include "RecordFileHandler.h"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <unordered_set>

std::string RecordFileHandler::GenerateFile()
{
    std::fstream file;
    const std::string& filePath = GetFilePath();
    file.open(filePath, std::ios::out);

    if(file.is_open())
    {
        std::vector<RecordKeyPair> records;
        GenerateRandomRecordsWithKey(records);

        if(isSorted)
        {
            std::sort(records.begin(), records.end(), [](const RecordKeyPair& a, const RecordKeyPair& b) {return a.key < b.key;} );
        }

        for(int i = 0; i < recordCount; i++)
        {
            const RecordKeyPair& recordWithKey = records[i];
            file << recordWithKey.key << "," << recordWithKey.record->firstData << "," << recordWithKey.record->secondData;

            if(i < recordCount - 1)
            {
                file << "\n";
            }
        }

        file.close();
        return filePath;
    }

    return "";
}

void RecordFileHandler::GenerateRandomRecordsWithKey(std::vector<RecordKeyPair>& records)
{
    std::srand(std::time(nullptr));
    std::unordered_set<int> alreadyUsedKeys;
    alreadyUsedKeys.reserve(recordCount);
    records.reserve(recordCount);

    for(int i = 0; i < recordCount; i++)
    {
        int key = std::rand();

        while (alreadyUsedKeys.find(key) != alreadyUsedKeys.end())
        {
            key = std::rand();
        }

        Record record = GenerateRandomRecord();
        alreadyUsedKeys.insert(key);
        records.emplace_back(key, std::make_unique<Record>(record));
    }

    GenerateRandomKeys(alreadyUsedKeys);
}

void RecordFileHandler::PopulateSetsWithFile(const std::vector<ISearchableSet<int, std::shared_ptr<Record>>*>& sets) const
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

std::string RecordFileHandler::GetFilePath() const
{
    const std::string fileNamePrefix = isSorted ? "Output_Sorted_" : "Output_";
    const std::string fileExtension = ".txt";
    const std::string filePath = directory + fileNamePrefix + std::to_string(recordCount) + fileExtension;
    return filePath;
}

Record RecordFileHandler::GenerateRandomRecord()
{
    const int firstData = std::rand();
    std::string secondData;

    for(int i = 0; i < 1000; i++)
    {
        constexpr char initialLetter =  'A';
        constexpr char finalLetter =  'Z';
        char letter = static_cast<char>(initialLetter + std::rand() % (finalLetter - initialLetter));

        if(std::rand() % 100 < 50)
        {
            letter = static_cast<char>(std::tolower(letter));
        }

        secondData += letter;
    }

    return Record(firstData, secondData);
}

void RecordFileHandler::GenerateRandomKeys(std::unordered_set<int> alreadyUsedKeys)
{
    std::vector<int> presentKeys(randomKeysLength);
    std::vector<int> notPresentKeys(randomKeysLength);

    FillNotPresentKeys(alreadyUsedKeys, notPresentKeys);
    FillPresentKeys(alreadyUsedKeys, presentKeys);
    
    randomKeys = RandomRecordKeys(presentKeys, notPresentKeys);
}

void RecordFileHandler::FillNotPresentKeys(std::unordered_set<int>& keys, std::vector<int>& notPresentKeys)
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


void RecordFileHandler::FillPresentKeys(std::unordered_set<int>& keys, std::vector<int>& presentKeys)
{
    const std::vector<int> keysVector(keys.begin(), keys.end());

    for (int& presentKey : presentKeys)
    {
        const int index = std::rand() % keysVector.size();
        presentKey = keysVector[index];
    }
}