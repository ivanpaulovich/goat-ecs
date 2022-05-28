#include <array>
#include <vector>
#include <map>
#include <iostream>
#include <typeinfo>
#include <unordered_map>
#include <string>
#include <functional>
#include <memory>
#include <set>
#include <foo/index.h>

bool Index::IsEntitySignatureInQuery(const unsigned int signature, const unsigned int query)
{
    return (signature & query) == query;
}

void Index::AddEntityToIndex(const unsigned int id, const unsigned int query)
{
    m_indexes[query].insert(id);
}

void Index::RemoveEntityFromIndex(const unsigned int id, const unsigned int query)
{
    m_indexes[query].erase(id);
}

void Index::InsertOrRemoveEntityFromIndex(const unsigned int id, const unsigned int signature, const unsigned int query)
{
    if (IsEntitySignatureInQuery(signature, query))
    {
        AddEntityToIndex(id, query);
        return;
    }

    RemoveEntityFromIndex(id, query);
}

void Index::AddQuery(const unsigned int query)
{
    std::set<unsigned int> index;
    m_indexes[query] = index;
}

void Index::RemoveQuery(const unsigned int query)
{
    m_indexes.erase(query);
}

std::set<unsigned int> Index::GetIndex(const unsigned int query)
{
    return m_indexes[query];
}

void Index::UpdateEntityIndex(const unsigned int id, const unsigned int signature)
{
    for (auto pair : m_indexes)
    {
        InsertOrRemoveEntityFromIndex(id, signature, pair.first);
    }
}