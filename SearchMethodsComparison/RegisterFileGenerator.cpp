#include "RegisterFileGenerator.h"

#include <fstream>
#include <sstream>
#include <unordered_set>

void RegisterFileGenerator::GenerateFile(int registerCount, const std::string&& fileDirectory)
{
    std::fstream file;
    const std::string fileNamePrefix = "Output_";
    const std::string fileExtension = ".txt";
    const std::string filePath = fileDirectory + fileNamePrefix + std::to_string(registerCount) + fileExtension;
    
    file.open(filePath, std::ios::out);

    if(file.is_open())
    {
        srand(time(0));
        std::unordered_set<int> alreadyUsedKeys;
        alreadyUsedKeys.reserve(registerCount);

        for(int i = 0; i < registerCount; i++)
        {
            int key = rand();

            while (alreadyUsedKeys.find(key) != alreadyUsedKeys.end())
            {
                key = rand();
            }

            alreadyUsedKeys.insert(key);
            std::shared_ptr<Register> randomRegister = GenerateRandomRegister();

            file << key << "," << randomRegister->firstData << "," << randomRegister->secondData << "\n";
        }

        file.close();
    }
}

void RegisterFileGenerator::PopulateSetWithFile(ISearchableSet<int, std::shared_ptr<Register>>* set, const std::string&& filePath)
{
    std::ifstream file(filePath);

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
                std::shared_ptr<Register> data = std::make_shared<Register>(firstData, secondData);
                set->Insert(key, data);
            }
        }

        file.close();
    }
}

std::shared_ptr<RegisterFileGenerator::Register> RegisterFileGenerator::GenerateRandomRegister()
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

    return std::make_shared<Register>(firstData, secondData);
}