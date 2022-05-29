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
    // template <typename T>
    // unsigned int Key()
    // {
    //     unsigned int key = m_keys->Key<T>();
    //     m_components->Key<T>(key, m_entities->GetSize());
    //     return key;
    // }

    World(const unsigned int size)
    {
        m_entities = new Entities(size);
        m_keys = new Keys();
        m_components = new Components();
        m_index = new Index();
    }

    ~World() {}

    // World() : WorldManager()
    // {
    //     m_entities = new Entities(10);
    //     m_keys = new Keys();
    // }

    // World(const unsigned int size) : WorldManager()
    // {
    //     m_entities = new Entities(size);
    //     m_keys = new Keys();
    // }

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

    // template <typename T>
    // T *GetComponent(const unsigned int id)
    // {
    //     unsigned int key = Key<T>();
    //     return GetComponents()->GetComponent<T>(key, id);
    // }

    // template <typename T>
    // void RemoveComponent(const unsigned int id)
    // {
    //     unsigned int key = Key<T>();
    //     GetEntities()->RemoveComponent(id, key);
    //     GetIndex()->UpdateEntityIndex(id, m_entities->GetEntity(id));
    // }

    set<unsigned int> GetIndex(const unsigned int query)
    {
        return GetIndex()->GetIndex(query);
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

    void AddQuery(const unsigned int query)
    {
        GetIndex()->AddQuery(query);

        for (unsigned int id = 0; id < GetEntities()->GetCount(); id++)
        {
            GetIndex()->UpdateEntityIndex(id, GetEntities()->GetEntity(id));
        }
    }

    QueryBuilder *NewQueryBuilder()
    {
        auto queryBuilder = new QueryBuilder(this);
        return queryBuilder;
    }

    EntityBuilder *NewEntityBuilder()
    {
        auto entityBuilder = new EntityBuilder(this);
        return entityBuilder;
    }
};
