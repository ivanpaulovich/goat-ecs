#pragma once

#include <set>

class EntitiesSet
{
private:
    std::set<unsigned int> m_entities;
public:
    void insert(const unsigned int id)
    {
        m_entities.insert(id);
    }

    std::set<unsigned int> get()
    {
        return m_entities;
    }

    void clear()
    {
        m_entities.clear();
    }
};
