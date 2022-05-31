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
#include "typeInfoRef.h"
#include "index.h"
#include "entities.h"
#include "keys.h"
#include "components.h"
#include "queryBuilder.h"
#include "entityBuilder.h"
#include "tSystemUpdate.h"
#include "worldManager.h"

class World : public WorldManager
{
private:
    Entities *m_entities;
    Keys *m_keys;
    Components *m_components;
    Index *m_index;
    vector<TSystemUpdate *> m_systems;

public:
    World(const unsigned int size)
    {
        m_entities = new Entities(size);
        m_keys = new Keys();
        m_components = new Components();
        m_index = new Index();
    }

    ~World() {}

    Keys *GetKeys()
    {
        return m_keys;
    }

    Entities *GetEntities()
    {
        return m_entities;
    }

    Components *GetComponents()
    {
        return m_components;
    }

    Index *GetIndex()
    {
        return m_index;
    }

    void AddSystem(TSystemUpdate update)
    {
        m_systems.push_back(update);
    }

    void Update()
    {
        for (auto update : m_systems)
        {
        }
    }

    QueryBuilder *NewQuery()
    {
        auto queryBuilder = new QueryBuilder(this);
        return queryBuilder;
    }

    QueryBuilder *LoadQuery(const unsigned int id)
    {
        auto queryBuilder = new QueryBuilder(this, id);
        return queryBuilder;
    }

    EntityBuilder *NewEntity()
    {
        auto entityBuilder = new EntityBuilder(this, GetEntities()->NewEntity());
        return entityBuilder;
    }

    EntityBuilder *LoadEntity(const unsigned int id)
    {
        auto entityBuilder = new EntityBuilder(this, id);
        return entityBuilder;
    }
};
