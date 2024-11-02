#pragma once

/*
 * Estrutura utilizada por todos os métodos de busca (Sequencial, Árvore Binária e Árvore AVL)
 * Utiliza template para que possa ser usado qualquer tipo de chave (desde que possa ser comparada) e qualquer tipo de valor
 * Guarda um par de chave e valor, e ponteiros para os filhos da esquerda, direita e para o nó pai
 * Na pesquisa sequencial, os três ponteiros permanecem nulos
 */
template<typename TKey, typename TValue>
struct Node
{
    TKey key;
    TValue value;

    Node* parent = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;
    
    Node(const TKey& key, TValue value, Node* parent = nullptr)
        : key(key), value(std::move(value)), parent(parent)
    {
    }

    Node** GetParentSubtree()
    {
        if(parent == nullptr)
            return nullptr;
        
        if(parent->left != nullptr && parent->left->key == key)
            return &parent->left;
        
        return &parent->right;
    }

    static int GetHeightDifference(Node* node)
    {
        if(node == nullptr)
        {
            return 0;
        }

        const int leftHeight = Node::GetHeight(node->left);
        const int rightHeight = Node::GetHeight(node->right);
        return rightHeight - leftHeight;
    }

    static int GetHeight(Node* node)
    {
        if(node == nullptr)
        {
            return 0;
        }

        return std::max(Node::GetHeight(node->left), Node::GetHeight(node->right)) + 1;
    }
};