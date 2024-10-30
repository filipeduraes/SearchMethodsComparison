#pragma once

#include "BinaryTree.h"

/*
 * Implementação da árvore AVL
 * Deriva da árvore binária, já que a busca, a saída e a estrutura de dados continuam iguais
 * Sobrescreve a inserção
 *  - Após a inserção simples na árvore, começa a verificar desde o pai do nó inserido até o nó raíz
 *  - Calcula-se a diferença de altura, e verifica se está desbalanceado na direita ou na esquerda
 *  - Caso esteja desbalanceado, realiza as rotações necessárias para balancear o nó novamente
 */
template<typename TKey, typename TValue>
class AVLTree : public BinaryTree<TKey, TValue>
{
public:
    void Insert(TKey key, TValue value) override;

private:
    void BalanceNode(Node<TKey, TValue>* current);
    void RightRotation(Node<TKey, TValue>* node);
    void LeftRotation(Node<TKey, TValue>* node);
};

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::Insert(TKey key, TValue value)
{
    Node<TKey, TValue>* insertedNode = BinaryTree<TKey, TValue>::SimpleInsert(key, value);
    AVLTree::BalanceNode(insertedNode->parent);
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::BalanceNode(Node<TKey, TValue>* current)
{
    while (current != nullptr)
    {
        const int heightDifference = Node<TKey, TValue>::GetHeightDifference(current);
        const bool isUnbalancedOnLeft = heightDifference < -1;
        const bool isUnbalancedOnRight = heightDifference > 1;
        
        if(isUnbalancedOnLeft)
        {
            const int leftHeightDifference = Node<TKey, TValue>::GetHeightDifference(current->left);

            if(leftHeightDifference <= 0)
            {
                AVLTree::RightRotation(current);
            }
            else
            {
                AVLTree::LeftRotation(current->left);
                AVLTree::RightRotation(current);
            }
        }
        else if(isUnbalancedOnRight)
        {
            const int rightHeightDifference = Node<TKey, TValue>::GetHeightDifference(current->right);

            if(rightHeightDifference <= 0)
            {
                AVLTree::RightRotation(current->right);
                AVLTree::LeftRotation(current);
            }
            else
            {
                AVLTree::LeftRotation(current);
            }
        }
        
        current = current->parent;
    }
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::RightRotation(Node<TKey, TValue>* node)
{
    Node<TKey, TValue>* leftChild = node->left;
    Node<TKey, TValue>** parentSubtree = node->GetParentSubtree();

    if (parentSubtree == nullptr)
    {
        parentSubtree = &this->root;
    }

    node->left = leftChild->right;

    if (leftChild->right != nullptr)
    {
        leftChild->right->parent = node;
    }

    leftChild->right = node;
    leftChild->parent = node->parent;
    node->parent = leftChild;
    *parentSubtree = leftChild;
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::LeftRotation(Node<TKey, TValue>* node)
{
    Node<TKey, TValue>* rightChild = node->right;
    Node<TKey, TValue>** parentSubtree = node->GetParentSubtree();

    if (parentSubtree == nullptr)
    {
        parentSubtree = &this->root;
    }

    node->right = rightChild->left;

    if (rightChild->left != nullptr)
    {
        rightChild->left->parent = node;
    }

    rightChild->left = node;
    rightChild->parent = node->parent;
    node->parent = rightChild;
    *parentSubtree = rightChild;
}
