#pragma once
#include "ISearchableSet.h"
#include "Node.h"

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
    Node<TKey, TValue>* InsertRecursive(TKey key, TValue value, Node<TKey, TValue>* currentNode);

private:
    virtual TValue* SearchRecursive(TKey key, Node<TKey, TValue>* currentNode);
    virtual void DisposeAllRecursive(Node<TKey, TValue>* currentNode);
    
    std::ostream& GenerateTreeOutputRecursive(std::ostream& stream, Node<TKey, TValue>* parentNode, int level = 0) const;
};

template <typename TKey, typename TValue>
BinaryTree<TKey, TValue>::~BinaryTree()
{
    BinaryTree::DisposeAllRecursive(root);
}

template <typename TKey, typename TValue>
void BinaryTree<TKey, TValue>::Insert(TKey key, TValue value)
{
    BinaryTree::InsertRecursive(key, value, root);
}

template <typename TKey, typename TValue>
TValue* BinaryTree<TKey, TValue>::Search(TKey key)
{
    this->lastComparisonCount = 0;
    return BinaryTree::SearchRecursive(key, root);
}

template <typename TKey, typename TValue>
std::ostream& BinaryTree<TKey, TValue>::GenerateOutput(std::ostream& stream) const
{
    return BinaryTree::GenerateTreeOutputRecursive(stream, root);
}

template <typename TKey, typename TValue>
std::ostream& BinaryTree<TKey, TValue>::GenerateTreeOutputRecursive(std::ostream& stream, Node<TKey, TValue>* parentNode, int level) const
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
Node<TKey, TValue>* BinaryTree<TKey, TValue>::InsertRecursive(TKey key, TValue value, Node<TKey, TValue>* currentNode)
{
    if(currentNode == nullptr)
    {
        root = new Node<TKey, TValue>(key, value);
    }
    else if(key == currentNode->key)
    {
        currentNode->value = value;
        return currentNode;
    }
    else if(key < currentNode->key)
    {
        if(currentNode->left == nullptr)
        {
            currentNode->left = new Node<TKey, TValue>(key, value, currentNode);
            return currentNode->left;
        }
        if(currentNode->left->key != key)
        {
            return BinaryTree::InsertRecursive(key, value, currentNode->left);
        }
    }
    else if(key > currentNode->key)
    {
        if(currentNode->right == nullptr)
        {
            currentNode->right = new Node<TKey, TValue>(key, value, currentNode);
            return currentNode->right;
        }
        if(currentNode->right != nullptr)
        {
            return BinaryTree::InsertRecursive(key, value, currentNode->right);
        }
    }

    return root;
}

template <typename TKey, typename TValue>
TValue* BinaryTree<TKey, TValue>::SearchRecursive(TKey key, Node<TKey, TValue>* currentNode)
{
    if(currentNode != nullptr)
    {
        if(currentNode->key == key)
        {
            ++this->lastComparisonCount;
            return &currentNode->value;
        }

        if(key < currentNode->key)
        {
            ++this->lastComparisonCount;
            return BinaryTree::SearchRecursive(key, currentNode->left);
        }

        if(key > currentNode->key)
        {
            ++this->lastComparisonCount;
            return BinaryTree::SearchRecursive(key, currentNode->right);
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

    BinaryTree::DisposeAllRecursive(left);
    BinaryTree::DisposeAllRecursive(right);
}
