#include <map>
#include "indexes.h"

namespace goat
{
    bool Indexes::isEntitySignatureInQuery(const unsigned int signature, const unsigned int query)
    {
        return (signature & query) == query;
    }

    void Indexes::addEntityToIndex(const unsigned int id, const unsigned int query)
    {
        m_indexes[query].insert(id);
    }

    void Indexes::removeEntityFromIndex(const unsigned int id, const unsigned int query)
    {
        m_indexes[query].erase(id);
    }

    void Indexes::insertOrRemoveEntityFromIndex(const unsigned int id, const unsigned int signature, const unsigned int query)
    {
        if (isEntitySignatureInQuery(signature, query))
        {
            addEntityToIndex(id, query);
            return;
        }

        removeEntityFromIndex(id, query);
    }

    void Indexes::addQuery(const unsigned int query)
    {
        std::set<unsigned int> index;
        m_indexes[query] = index;
    }

    void Indexes::removeQuery(const unsigned int query)
    {
        m_indexes.erase(query);
    }

    std::set<unsigned int> *Indexes::getIndex(const unsigned int query)
    {
        return &m_indexes[query];
    }

    void Indexes::updateEntityIndex(const unsigned int id, const unsigned int signature)
    {
        for (auto pair : m_indexes)
        {
            insertOrRemoveEntityFromIndex(id, signature, pair.first);
        }
    }
}
