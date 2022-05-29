#pragma once

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

    std::set<unsigned int> GetIndex(const unsigned int query);

    void UpdateEntityIndex(const unsigned int id, const unsigned int signature);
};