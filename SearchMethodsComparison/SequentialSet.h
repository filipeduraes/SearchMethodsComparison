﻿#pragma once
#include <vector>

#include "ISearchableSet.h"
#include "Node.h"

/*
 * Implementa a busca sequencial
 * Para simplicidade do código de inserção, foi usado um std::vector como estrutura de dados
 * Sua implementação depende do compilador, mas geralmente é feita usando uma array comum que é realocada após seu limite ser atingido, geralmente dobrando de tamanho
 */
template<typename TKey, typename TValue>
class SequentialSet final : public ISearchableSet<TKey, TValue>
{
private:
    std::vector<Node<TKey, TValue>*> set;
    
public:
    ~SequentialSet() override;
    void Insert(TKey key, TValue value) override;
    TValue* Search(TKey key) override;

protected:
    std::ostream& GenerateOutput(std::ostream& stream) const override;
};

template <typename TKey, typename TValue>
SequentialSet<TKey, TValue>::~SequentialSet()
{
    for(int i = 0; i < set.size(); i++)
    {
        delete set[i];
    }

    set.clear();
}

template <typename TKey, typename TValue>
void SequentialSet<TKey, TValue>::Insert(TKey key, TValue value)
{
    Node<TKey, TValue>* node = new Node<TKey, TValue>(key, value);
    set.push_back(node);
}

template <typename TKey, typename TValue>
TValue* SequentialSet<TKey, TValue>::Search(TKey key)
{
    this->lastComparisonCount = 0;
    
    for(int i = 0; i < set.size(); i++)
    {
        ++this->lastComparisonCount;
        
        if(set[i]->key == key)
        {
            return &set[i]->value;
        }
    }

    return nullptr;
}

template <typename TKey, typename TValue>
std::ostream& SequentialSet<TKey, TValue>::GenerateOutput(std::ostream& stream) const
{
    for (int i = 0; i < set.size(); i++)
    {
        stream << set[i]->key << " ";
    }
    
    return stream;
}
