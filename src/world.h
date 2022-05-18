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
#include "query.h"
#include "typeInfoRef.h"

class World;

typedef void(TSystemUpdate)(World, size_t *);

class World
{
private:
    size_t m_size;
    size_t m_entities_count;
    size_t *m_entities;
    unordered_map<TypeInfoRef, size_t, Hasher, EqualTo> m_keys;
    map<size_t, void *> m_values;
    map<Query, size_t *> m_indexes;
    vector<TSystemUpdate *> m_systems;

public:
    World(size_t size)
    {
        m_size = size;
        m_entities = new size_t(size);
    }

    template <typename T>
    size_t Key()
    {
        TypeInfoRef type = typeid(T);
        if (m_keys.find(type) != m_keys.end())
        {
            return m_keys[type];
        }

        size_t key = 1 << m_keys.size();
        m_keys[type] = key;
        T *components = new T[m_size];
        m_values[key] = components;

        return key;
    }

    template <typename T>
    T *GetComponents()
    {
        size_t key = Key<T>();
        auto values = static_cast<T*>(m_values[key]);
        return values;
    }

    template <typename T>
    T *GetComponent(size_t id)
    {
        size_t key = Key<T>();
        auto values = static_cast<T*>(m_values[key]);
        return &values[id];
    }

    template <typename T>
    void RemoveComponent(size_t id)
    {
        size_t key = Key<T>();
        auto bits = GetEntity(id);
    }

    bool HasComponent(size_t id, size_t key) {
        return GetEntity(id) && key == 0;
    }

    size_t NewEntity()
    {
        size_t id = m_entities_count++;
        return id;
    }

    size_t *GetEntity(size_t id)
    {
        size_t *key = &m_entities[id];
        return key;
    }

    size_t GetEntitiesCount()
    {
        return m_entities_count;
    }

    class QueryBuilder
    {
    public:
        World *m_world;
        Query m_query;

        QueryBuilder(World *world)
        {
            m_world = world;
        }

        QueryBuilder *Include(const TypeInfoRef *types)
        {
            return this;
        }

        QueryBuilder *Exclude(const TypeInfoRef *types)
        {
            return this;
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
        size_t id;

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
    };
};