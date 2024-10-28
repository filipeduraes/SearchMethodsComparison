#include <iostream>

#include "AVLTree.h"
#include "Benchmark.h"
#include "BinaryTree.h"
#include "RegisterFileGenerator.h"
#include "SequentialSet.h"

int main(int argc, char* argv[])
{
    Generator::RecordFileGenerator generator(R"(D:\Projects\Github\SearchMethodsComparison\SearchMethodsComparison\)", 10000, true);
    //generator.GenerateFile();

    ISearchableSet<int, std::shared_ptr<Generator::Record>>* avl = new AVLTree<int, std::shared_ptr<Generator::Record>>();
    ISearchableSet<int, std::shared_ptr<Generator::Record>>* binary = new BinaryTree<int, std::shared_ptr<Generator::Record>>();
    ISearchableSet<int, std::shared_ptr<Generator::Record>>* sequential = new SequentialSet<int, std::shared_ptr<Generator::Record>>();

    const std::vector<ISearchableSet<int, std::shared_ptr<Generator::Record>>*> sets { avl, binary, sequential };
    generator.PopulateSetsWithFile(sets);
    
    int searchedKey = 27808;
    
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
