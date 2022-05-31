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
#include "query.h"
#include "worldManager.h"

class QueryBuilder
{
private:
    WorldManager *m_world;
    Query *m_query;

public:
    QueryBuilder(WorldManager *world, unsigned int id)
    {
        m_world = world;
        m_query = new Query(id);
    }

    template <typename T>
    QueryBuilder *Include()
    {
        auto key = m_world->GetKeys()->Key<T>();
        m_query->Include(key);
        return this;
    }

    template <typename T>
    QueryBuilder *Exclude()
    {
        auto key = m_world->GetKeys()->Key<T>();
        m_query->Exclude(key);
        return this;
    }

    QueryBuilder *Ready()
    {
        m_world->GetIndex()->AddQuery(m_query->GetInclude());

        for (unsigned int id = 0; id < m_world->GetEntities()->GetCount(); id++)
        {
            m_world->GetIndex()->UpdateEntityIndex(id, m_world->GetEntities()->GetEntity(id));
        }

        return this;
    }

    unsigned int GetQuery()
    {
        return m_query->GetInclude();
    }
};
