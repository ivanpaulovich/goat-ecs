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

class World;

typedef void(TSystemUpdate)(World*, set<unsigned int> *index);

class World
{
private:
    unsigned int m_size;
    unsigned int m_entities_count;
    unsigned int *m_entities;
    unordered_map<TypeInfoRef, unsigned int, Hasher, EqualTo> m_keys;
    map<unsigned int, void *> m_values;
    map<unsigned int, set<unsigned int>> m_indexes;
    vector<TSystemUpdate *> m_systems;

    unsigned int NewEntity()
    {
        unsigned int id = m_entities_count++;
        return id;
    }

    void AddQuery(const unsigned int query)
    {
        set<unsigned int> index;
        m_indexes[query] = index;
    }

    bool IsEntityInQuery(unsigned int id, unsigned int query) {
        return (m_entities[id] & query) == query;
    }

public:
    World(unsigned int size)
    {
        m_size = size;
        m_entities = new unsigned int(size);
    }

    template <typename T>
    unsigned int Key()
    {
        TypeInfoRef type = typeid(T);
        if (m_keys.find(type) != m_keys.end())
        {
            return m_keys[type];
        }

        unsigned int key = 1 << m_keys.size();
        m_keys[type] = key;
        T *components = new T[m_size];
        m_values[key] = components;

        return key;
    }

    template <typename T>
    T *GetComponent(unsigned int id)
    {
        unsigned int key = Key<T>();
        auto values = static_cast<T*>(m_values[key]);
        return &values[id];
    }

    template <typename T>
    void RemoveComponent(unsigned int id)
    {
        unsigned int key = Key<T>();
        auto bits = GetEntity(id);
        *bits ^= key;
    }

    bool HasComponent(unsigned int id, unsigned int key) {
        return GetEntity(id) && key == 0;
    }



    unsigned int *GetEntity(unsigned int id)
    {
        unsigned int *key = &m_entities[id];
        return key;
    }

    unsigned int GetEntitiesCount()
    {
        return m_entities_count;
    }

    void Update(Query *query, TSystemUpdate update)
    {
        auto index = m_indexes[query->include];
        update(this, &index);
    }

    void Index()
    {
        for (unsigned int id = 0; id < GetEntitiesCount(); id++)
        {
            for (auto itr = m_indexes.begin(); 
                itr != m_indexes.end(); itr++) 
            {
                if (IsEntityInQuery(id, itr->first))
                {
                    itr->second.insert(id);
                }
            }
        }
    }

    class QueryBuilder;

    QueryBuilder *NewQueryBuilder()
    {
        auto queryBuilder = new World::QueryBuilder(this);
        return queryBuilder;
    }

    class QueryBuilder
    {
    public:
        World *m_world;
        Query *m_query;

        QueryBuilder(World *world)
        {
            m_world = world;
            m_query = new Query();
        }

        template <typename T>
        QueryBuilder *Include()
        {
            auto key = m_world->Key<T>();
            m_query->Include(key);
            return this;
        }

        QueryBuilder *Ready()
        {
            m_world->AddQuery(m_query->include);
            return this;
        }

        Query *GetQuery()
        {
            return m_query;
        }
    };

    class EntityBuilder;

    EntityBuilder *NewEntityBuilder()
    {
        auto entityBuilder = new World::EntityBuilder(this);
        return entityBuilder;
    }

    class EntityBuilder
    {
    private:
        template <typename T>
        void SetComponentValue(T value)
        {
            auto components = m_world->GetComponent<T>(id);
            *components = value;
        }

        template <typename T>
        void SetComponentKey()
        {
            auto key = m_world->Key<T>();
            auto bits = m_world->GetEntity(id);
            *bits |= key;
        }

    public:
        World *m_world;
        unsigned int id;

        EntityBuilder(World *world)
        {
            m_world = world;
            id = m_world->NewEntity();
        }

        template <typename T>
        EntityBuilder *With(T value)
        {
            SetComponentKey<T>();
            SetComponentValue<T>(value);

            return this;
        }

        template <typename T>
        EntityBuilder *With()
        {
            SetComponentKey<T>();

            return this;
        }

        int GetId()
        {
            return id;
        }
    };
};