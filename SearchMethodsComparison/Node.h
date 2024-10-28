#pragma once

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
        
        int leftHeight = Node::GetHeight(node->left);
        int rightHeight = Node::GetHeight(node->right);
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