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
    void SimpleRightRotation(Node<TKey, TValue>* node);
    void SimpleLeftRotation(Node<TKey, TValue>* node);
};

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::Insert(TKey key, TValue value)
{
    BinaryTree<TKey, TValue>::Insert(key, value);
    const int rootHeight = GetHeight(this->root);
    UpdateHeights(rootHeight, this->root);
    BalanceNode(this->root);
}

template <typename TKey, typename TValue>
int AVLTree<TKey, TValue>::GetHeight(Node<TKey, TValue>* current)
{
    if(current == nullptr)
    {        
        return -1;
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
    if(current == nullptr)
    {
        return;
    }
    
    const int heightDifference = Node<TKey, TValue>::GetHeightDifference(current);
    const bool isUnbalancedOnLeft = heightDifference < -1;
    const bool isUnbalancedOnRight = heightDifference > 1;
    
    if(isUnbalancedOnLeft)
    {
        int leftHeightDifference = Node<TKey, TValue>::GetHeightDifference(current->left);

        if(leftHeightDifference <= 0)
        {
            SimpleRightRotation(current);
        }
        else
        {
            SimpleLeftRotation(current->left);
            SimpleRightRotation(current);
        }
    }
    else if(isUnbalancedOnRight)
    {
        int rightHeightDifference = Node<TKey, TValue>::GetHeightDifference(current->left);

        if(rightHeightDifference <= 0)
        {
            SimpleRightRotation(current->right);
            SimpleLeftRotation(current);
        }
        else
        {
            SimpleLeftRotation(current);
        }
    }

    if(isUnbalancedOnLeft || isUnbalancedOnRight)
    {
        const int rootHeight = GetHeight(this->root);
        UpdateHeights(rootHeight, this->root);
    }
    
    BalanceNode(current->left);
    BalanceNode(current->right);
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::SimpleRightRotation(Node<TKey, TValue>* node)
{
    Node<TKey, TValue>* leftTree = node->left;
    node->left = leftTree->right;
    leftTree->right = node;

    if(node == this->root)
    {
        this->root = leftTree;
    }
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::SimpleLeftRotation(Node<TKey, TValue>* node)
{
    Node<TKey, TValue>* rightTree = node->right;
    node->right = rightTree->right;
    rightTree->left = node;

    if(node == this->root)
    {
        this->root = rightTree;
    }
}
