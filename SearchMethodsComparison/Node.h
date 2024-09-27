#pragma once

template<typename TKey, typename TValue>
struct Node
{
    TKey key;
    TValue value;

    Node* left = nullptr;
    Node* right = nullptr;
    
    int height;

    Node(const TKey& key, const TValue& value)
        : key(key), value(value)
    {
    }

    static int GetHeightDifference(Node* node)
    {
        if(node == nullptr)
        {
            return 0;
        }
        
        int leftHeight = GetHeight(node->left);
        int rightHeight = GetHeight(node->right);
        return rightHeight - leftHeight;
    }

    static int GetHeight(Node* node)
    {
        if(node == nullptr)
        {
            return 0;
        }

        return node->height;
    }
};
