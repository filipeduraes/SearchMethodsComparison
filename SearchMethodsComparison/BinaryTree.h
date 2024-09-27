#pragma once
#include "Node.h"

template<typename TKey, typename TValue>
class BinaryTree
{
protected:
    Node<TKey, TValue>* root = nullptr;
    
public:
    ~BinaryTree();

    virtual void Insert(TKey key, TValue value);
    TValue* Search(TKey key);

private:
    virtual void InsertRecursive(TKey key, TValue value, Node<TKey, TValue>* currentNode);
    virtual TValue* SearchRecursive(TKey key, Node<TKey, TValue>* currentNode);
    virtual void DisposeAllRecursive(Node<TKey, TValue>* currentNode);
};


template <typename TKey, typename TValue>
BinaryTree<TKey, TValue>::~BinaryTree()
{
    DisposeAllRecursive(root);
}

template <typename TKey, typename TValue>
void BinaryTree<TKey, TValue>::Insert(TKey key, TValue value)
{
    if(root == nullptr)
    {
        root = new Node<TKey, TValue>(key, value);
    }
    else
    {
        InsertRecursive(key, value, root); //TODO: Check if iterative solution is needed
    }
}

template <typename TKey, typename TValue>
TValue* BinaryTree<TKey, TValue>::Search(TKey key)
{
    return SearchRecursive(key, root);
}

template <typename TKey, typename TValue>
void BinaryTree<TKey, TValue>::InsertRecursive(TKey key, TValue value, Node<TKey, TValue>* currentNode)
{
    if(key == currentNode->key)
    {
        currentNode->value = value;
    }
    else if(key < currentNode->key)
    {
        if(currentNode->left == nullptr)
        {
            currentNode->left = new Node<TKey, TValue>(key, value);
        }
        else
        {
            InsertRecursive(key, value, currentNode->left);
        }
    }
    else if(key > currentNode->key)
    {
        if(currentNode->right == nullptr)
        {
            currentNode->right = new Node<TKey, TValue>(key, value);
        }
        else
        {
            InsertRecursive(key, value, currentNode->right);
        }
    }
}

template <typename TKey, typename TValue>
TValue* BinaryTree<TKey, TValue>::SearchRecursive(TKey key, Node<TKey, TValue>* currentNode)
{
    if(currentNode != nullptr)
    {
        if(currentNode->key == key)
        {
            return &currentNode->value;
        }

        if(key < currentNode->key)
        {
            return SearchRecursive(key, currentNode->left);
        }

        if(key > currentNode->key)
        {
            return SearchRecursive(key, currentNode->right);
        }
    }

    return nullptr;
}

template <typename TKey, typename TValue>
void BinaryTree<TKey, TValue>::DisposeAllRecursive(Node<TKey, TValue>* currentNode)
{
    if(currentNode == nullptr)
    {
        return;
    }
    
    Node<TKey, TValue>* left = currentNode->left;
    Node<TKey, TValue>* right = currentNode->right;

    delete currentNode;

    DisposeAllRecursive(left);
    DisposeAllRecursive(right);
}
