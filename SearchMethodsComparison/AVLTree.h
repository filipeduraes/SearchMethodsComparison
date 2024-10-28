#pragma once

#include "BinaryTree.h"

template<typename TKey, typename TValue>
class AVLTree : public BinaryTree<TKey, TValue>
{
public:
    void Insert(TKey key, TValue value) override;

private:
    int GetHeight(Node<TKey, TValue>* current);
    void BalanceNode(Node<TKey, TValue>** parentSubtree, Node<TKey, TValue>* current);
    void RightRotation(Node<TKey, TValue>** parentSubtree, Node<TKey, TValue>* node);
    void LeftRotation(Node<TKey, TValue>** parentSubtree, Node<TKey, TValue>* node);
};

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::Insert(TKey key, TValue value)
{
    BinaryTree<TKey, TValue>::Insert(key, value);
    AVLTree::BalanceNode(&this->root, this->root);
}

template <typename TKey, typename TValue>
int AVLTree<TKey, TValue>::GetHeight(Node<TKey, TValue>* current)
{
    if(current == nullptr)
    {        
        return -1;
    }

    return std::max(AVLTree::GetHeight(current->left), AVLTree::GetHeight(current->right)) + 1;    
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::BalanceNode(Node<TKey, TValue>** parentSubtree, Node<TKey, TValue>* current)
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
            AVLTree::RightRotation(parentSubtree, current);
        }
        else
        {
            AVLTree::LeftRotation(&current->left, current->left);
            AVLTree::RightRotation(parentSubtree, current);
        }
    }
    else if(isUnbalancedOnRight)
    {
        int rightHeightDifference = Node<TKey, TValue>::GetHeightDifference(current->right);

        if(rightHeightDifference <= 0)
        {
            AVLTree::RightRotation(&current->right, current->right);
            AVLTree::LeftRotation(parentSubtree, current);
        }
        else
        {
            AVLTree::LeftRotation(parentSubtree, current);
        }
    }
    
    AVLTree::BalanceNode(&current->left, current->left);
    AVLTree::BalanceNode(&current->right, current->right);
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::RightRotation(Node<TKey, TValue>** parentSubtree, Node<TKey, TValue>* node)
{
    *parentSubtree = node->left;
    node->left = node->left->right;
    (*parentSubtree)->right = node;
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::LeftRotation(Node<TKey, TValue>** parentSubtree, Node<TKey, TValue>* node)
{
    *parentSubtree = node->right;
    node->right = node->right->left;
    (*parentSubtree)->left = node;
}
