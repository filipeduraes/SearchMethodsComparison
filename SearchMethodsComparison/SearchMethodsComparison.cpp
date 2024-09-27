#include <cmath>
#include <iostream>

#include "Benchmark.h"
#include "BinaryTree.h"

int main(int argc, char* argv[])
{
    BinaryTree<int, void*> testTree;

    testTree.Insert(92, nullptr);
    testTree.Insert(51, nullptr);
    testTree.Insert(52, nullptr);
    testTree.Insert(22, nullptr);
    testTree.Insert(54, nullptr);
    testTree.Insert(57, nullptr);
    testTree.Insert(3, nullptr);
    testTree.Insert(5, nullptr);
    testTree.Insert(1, nullptr);
    testTree.Insert(4, nullptr);
    
    return 0;
}
