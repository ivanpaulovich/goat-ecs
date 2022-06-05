#include <map>
#include "index.h"

namespace goat
{
    bool Index::isEntitySignatureInQuery(const unsigned int signature, const unsigned int query)
    {
        return (signature & query) == query;
    }

    void Index::addEntityToIndex(const unsigned int id, const unsigned int query)
    {
        m_indexes[query].insert(id);
    }

    void Index::removeEntityFromIndex(const unsigned int id, const unsigned int query)
    {
        m_indexes[query].erase(id);
    }

    void Index::insertOrRemoveEntityFromIndex(const unsigned int id, const unsigned int signature, const unsigned int query)
    {
        if (isEntitySignatureInQuery(signature, query))
        {
            addEntityToIndex(id, query);
            return;
        }

        removeEntityFromIndex(id, query);
    }

    void Index::addQuery(const unsigned int query)
    {
        std::set<unsigned int> index;
        m_indexes[query] = index;
    }

    void Index::removeQuery(const unsigned int query)
    {
        m_indexes.erase(query);
    }

    std::set<unsigned int> *Index::getIndex(const unsigned int query)
    {
        return &m_indexes[query];
    }

    void Index::updateEntityIndex(const unsigned int id, const unsigned int signature)
    {
        for (auto pair : m_indexes)
        {
            insertOrRemoveEntityFromIndex(id, signature, pair.first);
        }
    }
}
