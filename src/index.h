#pragma once

#include <set>

class Index
{
private:
    std::map<unsigned int, std::set<unsigned int>> m_indexes;

    bool IsEntitySignatureInQuery(const unsigned int signature, const unsigned int query);

    void AddEntityToIndex(const unsigned int id, const unsigned int query);

    void RemoveEntityFromIndex(const unsigned int id, const unsigned int query);

    void InsertOrRemoveEntityFromIndex(const unsigned int id, const unsigned int signature, const unsigned int query);

public:
    void AddQuery(const unsigned int query);

    void RemoveQuery(const unsigned int query);

    std::set<unsigned int> getIndex(const unsigned int query);

    void UpdateEntityIndex(const unsigned int id, const unsigned int signature);
};
