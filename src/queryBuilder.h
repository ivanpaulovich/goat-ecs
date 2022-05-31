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
#include "key.h"
#include "worldManager.h"

class QueryBuilder
{
private:
    WorldManager *m_world;
    Key *m_key;

public:
    QueryBuilder(WorldManager *world, unsigned int id)
    {
        m_world = world;
        m_key = new Key(id);
    }

    template <typename T>
    QueryBuilder *Include()
    {
        auto key = m_world->GetKeys()->GetKey<T>();
        m_key->Include(key);
        return this;
    }

    template <typename T>
    QueryBuilder *Exclude()
    {
        auto key = m_world->GetKeys()->GetKey<T>();
        m_key->Exclude(key);
        return this;
    }

    QueryBuilder *Ready()
    {
        m_world->GetIndex()->AddQuery(m_key->GetId());

        for (unsigned int id = 0; id < m_world->GetEntities()->GetCount(); id++)
        {
            m_world->GetIndex()->UpdateEntityIndex(id, m_world->GetEntities()->GetEntity(id)->GetId());
        }

        return this;
    }

    Key GetKey()
    {
        return *m_key;
    }
};
