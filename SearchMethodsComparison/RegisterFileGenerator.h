#pragma once
#include <memory>
#include <string>

#include "ISearchableSet.h"

namespace RegisterFileGenerator
{
    struct Register
    {
        int firstData;
        std::string secondData;
        
        Register(const int firstData, std::string secondData)
            : firstData(firstData), secondData(std::move(secondData))
        {
        }
    };

    void GenerateFile(int registerCount, const std::string&& fileDirectory);
    void PopulateSetWithFile(ISearchableSet<int, std::shared_ptr<Register>>* set, const std::string&& filePath);
    
    std::shared_ptr<Register> GenerateRandomRegister();
};