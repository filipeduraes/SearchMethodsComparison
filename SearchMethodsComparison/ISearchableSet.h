#pragma once

template<typename TKey, typename TValue>
class ISearchableSet
{
protected:
    int lastComparisonCount = 0;
    
public:
    int GetLastComparisonCount() const
    {
        return lastComparisonCount;
    }
    
    virtual ~ISearchableSet() = default;
    virtual void Insert(TKey key, TValue value) = 0;
    virtual TValue* Search(TKey key) = 0;

    friend std::ostream& operator<<(std::ostream& stream, const ISearchableSet& searchableSet)
    {
        return searchableSet.GenerateOutput(stream);
    }

protected:
    virtual std::ostream& GenerateOutput(std::ostream& stream) const = 0;
};