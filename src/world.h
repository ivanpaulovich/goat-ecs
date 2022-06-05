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
#include "type-info-ref.h"
#include "index.h"
#include "entities.h"
#include "keys.h"
#include "components.h"
#include "query-builder.h"
#include "entity-builder.h"
#include "t-system-update.h"
#include "world-manager.h"
#include "entities-set.h"
#include "keys-map.h"

namespace goat
{
    class World : public WorldManager
    {
    private:
        Entities *m_entities;
        Keys *m_keys;
        Components *m_components;
        Index *m_index;
        vector<TSystemUpdate *> m_systems;
        EntitiesSet *m_entities_created;
        EntitiesSet *m_entities_destroyed;
        KeysMap *m_components_included;
        KeysMap *m_components_excluded;

    public:
        World(const unsigned int size)
        {
            m_entities = new Entities(size);
            m_keys = new Keys();
            m_components = new Components();
            m_index = new Index();
            m_entities_created = new EntitiesSet();
            m_entities_destroyed = new EntitiesSet();
            m_components_included = new KeysMap();
            m_components_excluded = new KeysMap();
        }

        ~World() {}

        Keys *getKeys()
        {
            return m_keys;
        }

        Entities *getEntities()
        {
            return m_entities;
        }

        KeysMap *getIncludedComponents()
        {
            return m_components_included;
        }

        KeysMap *getExcludedComponents()
        {
            return m_components_excluded;
        }

        EntitiesSet *getCreatedEntities()
        {
            return m_entities_created;
        }

        EntitiesSet *getDestroyedEntities()
        {
            return m_entities_destroyed;
        }

        Components *getComponents()
        {
            return m_components;
        }

        Index *getIndex()
        {
            return m_index;
        }

        void addSystem(TSystemUpdate update)
        {
            m_systems.push_back(update);
        }

        void update()
        {
            for (auto update : m_systems)
            {
            }
        }

        QueryBuilder *newQuery()
        {
            auto queryBuilder = new QueryBuilder(this, 0);
            return queryBuilder;
        }

        QueryBuilder *loadQuery(const unsigned int id)
        {
            auto queryBuilder = new QueryBuilder(this, id);
            return queryBuilder;
        }

        EntityBuilder *newEntity()
        {
            auto entityBuilder = new EntityBuilder(this, getEntities()->newEntity());
            return entityBuilder;
        }

        EntityBuilder *loadEntity(const unsigned int id)
        {
            auto entityBuilder = new EntityBuilder(this, id);
            return entityBuilder;
        }
    };
}
