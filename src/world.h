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

typedef void(TSystemUpdate)(World, unsigned int *);

class World
{
private:
    unsigned int m_size;
    unsigned int m_entities_count;
    unsigned int *m_entities;
    unordered_map<TypeInfoRef, unsigned int, Hasher, EqualTo> m_keys;
    map<unsigned int, void *> m_values;
    map<Query, unsigned int *> m_indexes;
    vector<TSystemUpdate *> m_systems;

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
    T *GetComponents()
    {
        unsigned int key = Key<T>();
        return (T *)(m_values[key]);
    }

    unsigned int NewEntity()
    {
        int id = m_entities_count++;
        return id;
    }

    unsigned int GetEntity(unsigned int id)
    {
        int key = m_entities[id];
        return id;
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
            auto components = m_world->GetComponents<T>();
            components[id] = value;
        }

        template <typename T>
        void SetComponentKey()
        {
            auto key = m_world->Key<T>();
            auto bits = m_world->GetEntity(id);
            bits |= key;
        }

    public:
        World *m_world;
        unsigned int id;

        EntityBuilder(World *world)
        {
            m_world = world;
        }

        void NewEntity()
        {
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