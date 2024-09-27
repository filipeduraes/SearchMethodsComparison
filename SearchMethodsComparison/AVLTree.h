#pragma once

#include "BinaryTree.h"

template<typename TKey, typename TValue>
class AVLTree : BinaryTree<TKey, TValue>
{
public:
    void Insert(TKey key, TValue value) override;

private:
    int GetHeight(Node<TKey, TValue>* current);
    void UpdateHeights(int currentHeight, Node<TKey, TValue>* current);
    void BalanceNode(Node<TKey, TValue>* current);
};

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::Insert(TKey key, TValue value)
{
    BinaryTree<TKey, TValue>::Insert(key, value);
    const int rootHeight = GetHeight(this->root);
    UpdateHeights(rootHeight, this->root);
    BalanceNode();
}

template <typename TKey, typename TValue>
int AVLTree<TKey, TValue>::GetHeight(Node<TKey, TValue>* current)
{
    if(current == nullptr)
    {        
        return 0;
    }

    const int height = std::max(GetHeight(current->left), GetHeight(current->right)) + 1;    
    return height;
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::UpdateHeights(int currentHeight, Node<TKey, TValue>* current)
{
    if(current == nullptr)
    {
        return; 
    }
    
    current->height = currentHeight;
    UpdateHeights(currentHeight - 1, current->right);
    UpdateHeights(currentHeight - 1, current->left);
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::BalanceNode(Node<TKey, TValue>* current)
{
    const int leftHeight = Node<TKey, TValue>::GetHeight(current->left);
    const int rightHeight = Node<TKey, TValue>::GetHeight(current->right->height);

    const int heightDifference = rightHeight - leftHeight;
    const bool isUnbalancedOnRight = heightDifference > 1;
    const bool isUnbalancedOnLeft = heightDifference < -1;
    
    if(isUnbalancedOnRight)
    {
    }
    else if(isUnbalancedOnLeft)
    {
        
    }
}
