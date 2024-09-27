#pragma once

template<typename TKey, typename TValue>
struct Node
{
    TKey key;
    TValue value;

    Node* left = nullptr;
    Node* right = nullptr;

    Node(const TKey& key, const TValue& value)
        : key(key), value(value)
    {
    }
};
