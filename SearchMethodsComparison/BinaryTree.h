#pragma once

#include <ostream>
#include <stack>

#include "ISearchableSet.h"
#include "Node.h"

/*
 * Implementação da árvore binária simples
 * Foram implementadas a inserção e a busca (usando métodos iterativos para evitar o StackOverflow)
 * Foi também implementado uma forma de mostrá-la no console, para facilitar nos testes durante o desenvolvimento
 */
template<typename TKey, typename TValue>
class BinaryTree : public ISearchableSet<TKey, TValue>
{
protected:
    Node<TKey, TValue>* root = nullptr;
    
public:
    ~BinaryTree() override;
    
    void Insert(TKey key, TValue value) override;
    TValue* Search(TKey key) override;

protected:
    std::ostream& GenerateOutput(std::ostream& stream) const override;
    Node<TKey, TValue>* SimpleInsert(TKey key, TValue value);

private:
    std::ostream& GenerateTreeOutputRecursive(std::ostream& stream, Node<TKey, TValue>* parentNode, int level = 0) const;
};

template <typename TKey, typename TValue>
BinaryTree<TKey, TValue>::~BinaryTree()
{
    if (root == nullptr)
    {
        return;
    }

    std::stack<Node<TKey, TValue>*> nodeStack;
    nodeStack.push(root);

    while (!nodeStack.empty())
    {
        Node<TKey, TValue>* currentNode = nodeStack.top();
        nodeStack.pop();

        if (currentNode->left)
        {
            nodeStack.push(currentNode->left);
        }
        if (currentNode->right)
        {
            nodeStack.push(currentNode->right);
        }

        delete currentNode;
    }

    root = nullptr;
}

template <typename TKey, typename TValue>
void BinaryTree<TKey, TValue>::Insert(TKey key, TValue value)
{
    BinaryTree::SimpleInsert(key, value);
}

template <typename TKey, typename TValue>
TValue* BinaryTree<TKey, TValue>::Search(TKey key)
{
    Node<TKey, TValue>* current = root;
    this->lastComparisonCount = 0;

    while(current != nullptr)
    {
        if(current->key == key)
        {
            ++this->lastComparisonCount;
            return &current->value;
        }
        if(key < current->key)
        {
            ++this->lastComparisonCount;
            current = current->left;
        }
        else if(key > current->key)
        {
            ++this->lastComparisonCount;
            current = current->right;
        }
    }
    
    return nullptr;
}

template <typename TKey, typename TValue>
std::ostream& BinaryTree<TKey, TValue>::GenerateOutput(std::ostream& stream) const
{
    return BinaryTree::GenerateTreeOutputRecursive(stream, root);
}

template <typename TKey, typename TValue>
std::ostream& BinaryTree<TKey, TValue>::GenerateTreeOutputRecursive(std::ostream& stream, Node<TKey, TValue>* parentNode, const int level) const
{
    for(int i = 0; i < level; i++)
    {
        stream << "| ";
    }
    
    if(parentNode != nullptr)
    {
        stream << level << ": " << parentNode->key;

        if(parentNode->left != nullptr || parentNode->right != nullptr)
        {
            stream << "\n";
            BinaryTree::GenerateTreeOutputRecursive(stream, parentNode->left, level + 1);
            stream << "\n";
            BinaryTree::GenerateTreeOutputRecursive(stream, parentNode->right, level + 1);
        }
    }
    else
    {
        stream << level << ": -";
    }

    return stream;
}

template <typename TKey, typename TValue>
Node<TKey, TValue>* BinaryTree<TKey, TValue>::SimpleInsert(TKey key, TValue value)
{
    if(root == nullptr)
    {
        root = new Node<TKey, TValue>(key, value);
        return root;
    }

    Node<TKey, TValue>* currentNode = root;
    Node<TKey, TValue>* parentNode = nullptr;

    while (currentNode != nullptr)
    {
        parentNode = currentNode;

        if(currentNode->key == key)
        {
            currentNode->value = value;
            return currentNode;
        }

        if(key < currentNode->key)
        {
            currentNode = currentNode->left;
        }
        else if(key > currentNode->key)
        {
            currentNode = currentNode->right;
        }
    }
        
    Node<TKey, TValue>* newNode = new Node<TKey, TValue>(key, value, parentNode);
        
    if(key < parentNode->key)
    {
        parentNode->left = newNode;
    }
    else if(key > parentNode->key)
    {
        parentNode->right = newNode;
    }

    return newNode;
}