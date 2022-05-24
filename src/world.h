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

typedef void(TSystemUpdate)(World *, const set<unsigned int> *index);

class SystemConfig
{
public:
    TSystemUpdate update;
    unsigned int priority;
    set<unsigned int> *index;
};

class Index
{
private:
    map<unsigned int, set<unsigned int>> m_indexes;

    bool IsEntitySignatureInQuery(const unsigned int signature, const unsigned int query)
    {
        return (signature & query) == query;
    }

    void AddEntityToIndex(const unsigned int id, const unsigned int query)
    {
        m_indexes[query].insert(id);
    }

    void RemoveEntityFromIndex(const unsigned int id, const unsigned int query)
    {
        m_indexes[query].erase(id);
    }

    void InsertOrRemoveEntityFromIndex(const unsigned int id, const unsigned int signature, const unsigned int query)
    {
        if (IsEntitySignatureInQuery(signature, query))
        {
            AddEntityToIndex(id, query);
            return;
        }

        RemoveEntityFromIndex(id, query);
    }

public:
    void AddQuery(const unsigned int query)
    {
        set<unsigned int> index;
        m_indexes[query] = index;
    }

    void RemoveQuery(const unsigned int query)
    {
        m_indexes.erase(query);
    }

    set<unsigned int> GetIndex(const unsigned int query)
    {
        return m_indexes[query];
    }

    void UpdateEntityIndex(const unsigned int id, const unsigned int signature)
    {
        for (auto pair : m_indexes)
        {
            InsertOrRemoveEntityFromIndex(id, signature, pair.first);
        }
    }
};

class World
{
private:
    unsigned int m_size;
    unsigned int m_entities_count;
    unsigned int *m_entities;
    unordered_map<TypeInfoRef, unsigned int, Hasher, EqualTo> m_keys;
    map<unsigned int, void *> m_values;
    Index m_index;
    vector<TSystemUpdate *> m_systems;

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

    unsigned int NewEntity()
    {
        unsigned int id = m_entities_count++;
        return id;
    }

    void AddQuery(const unsigned int query)
    {
        m_index.AddQuery(query);

        for (unsigned int id = 0; id < GetEntitiesCount(); id++)
        {
            m_index.UpdateEntityIndex(id, m_entities[id]);
        }
    }

public:
    World(const unsigned int size)
    {
        m_size = size;
        m_entities = new unsigned int(size);
    }

    template <typename T>
    void SetComponent(const unsigned int id, const T value)
    {
        auto components = GetComponent<T>(id);
        *components = value;

        m_index.UpdateEntityIndex(id, m_entities[id]);
    }

    template <typename T>
    void SetComponent(const unsigned int id)
    {
        auto key = Key<T>();
        auto bits = GetEntity(id);
        *bits |= key;

        m_index.UpdateEntityIndex(id, m_entities[id]);
    }

    template <typename T>
    T *GetComponent(const unsigned int id)
    {
        unsigned int key = Key<T>();
        auto values = static_cast<T *>(m_values[key]);
        return &values[id];
    }

    template <typename T>
    void RemoveComponent(const unsigned int id)
    {
        unsigned int key = Key<T>();
        auto bits = GetEntity(id);
        *bits ^= key;

        m_index.UpdateEntityIndex(id, m_entities[id]);
    }

    bool HasComponent(const unsigned int id, const unsigned int key)
    {
        return GetEntity(id) && key == 0;
    }

    unsigned int *GetEntity(const unsigned int id)
    {
        unsigned int *key = &m_entities[id];
        return key;
    }

    unsigned int GetEntitiesCount()
    {
        return m_entities_count;
    }

    set<unsigned int> GetIndex(const unsigned int query)
    {
        return m_index.GetIndex(query);
    }

    void AddSystem(TSystemUpdate update)
    {
        m_systems.push_back(update);
    }

    void Update()
    {
        for(auto update : m_systems) {

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
    private:
        World *m_world;
        Query *m_query;
    public:
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

        unsigned int GetQuery()
        {
            return m_query->include;
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
        World *m_world;
        unsigned int id;
    public:
        EntityBuilder(World *world)
        {
            m_world = world;
            id = m_world->NewEntity();
        }

        template <typename T>
        EntityBuilder *With(const T value)
        {
            m_world->SetComponent<T>(id);
            m_world->SetComponent<T>(id, value);

            return this;
        }

        template <typename T>
        EntityBuilder *With()
        {
            m_world->SetComponent<T>(id);

            return this;
        }

        int GetId()
        {
            return id;
        }
    };
};