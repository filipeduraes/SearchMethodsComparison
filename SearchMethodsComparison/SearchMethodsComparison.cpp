#include <iostream>

#include "AVLTree.h"
#include "Benchmark.h"
#include "BinaryTree.h"
#include "RegisterFileGenerator.h"
#include "SequentialSet.h"

int main(int argc, char* argv[])
{
    AVLTree<int, void*> testAVL;
    BinaryTree<int, void*> testBinary;

    int keys[] = {20, 10, 40, 50, 30, 55, 3, 11, 4, 28, 36, 33, 52, 7, 25, 13};

    for(int& key : keys)
    {
        testAVL.Insert(key, nullptr);
        testBinary.Insert(key, nullptr);
    }
    
    for(int& key : keys)
    {
        testAVL.Search(key);
        testBinary.Search(key);
    
        std::cout << key << " - AVL: " << testAVL.GetLastComparisonCount() << ", Binary: " << testBinary.GetLastComparisonCount() << "\n";
    }
    return 0;
    //RegisterFileGenerator::GenerateFile(1000, R"(D:\Projects\Github\SearchMethodsComparison\SearchMethodsComparison\)");
    ISearchableSet<int, std::shared_ptr<RegisterFileGenerator::Register>>* avl = new AVLTree<int, std::shared_ptr<RegisterFileGenerator::Register>>();
    ISearchableSet<int, std::shared_ptr<RegisterFileGenerator::Register>>* binary = new BinaryTree<int, std::shared_ptr<RegisterFileGenerator::Register>>();
    ISearchableSet<int, std::shared_ptr<RegisterFileGenerator::Register>>* sequential = new SequentialSet<int, std::shared_ptr<RegisterFileGenerator::Register>>();

    PopulateSetWithFile(avl, R"(D:\Projects\Github\SearchMethodsComparison\SearchMethodsComparison\Output_1000.txt)");
    PopulateSetWithFile(binary, R"(D:\Projects\Github\SearchMethodsComparison\SearchMethodsComparison\Output_1000.txt)");
    PopulateSetWithFile(sequential, R"(D:\Projects\Github\SearchMethodsComparison\SearchMethodsComparison\Output_1000.txt)");

    int searchedKey = 12496;
    
    {
        Benchmark benchmark("AVL");
        avl->Search(searchedKey);
    }
    {
        Benchmark benchmark("Binary");
        binary->Search(searchedKey);
    }
    {
        Benchmark benchmark("Sequential");
        sequential->Search(searchedKey);
    }
    
    std::cout << "\nAVL Comparisons: " << avl->GetLastComparisonCount();
    std::cout << "\nBinary Comparisons: " << binary->GetLastComparisonCount();
    std::cout << "\nSequencial Comparisons: " << sequential->GetLastComparisonCount();
    
    delete avl;
    delete binary;
    delete sequential;
    
    return 0;
}
