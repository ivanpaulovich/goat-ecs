#pragma once

#include "world-manager.h"

namespace goat
{
    class EntityBuilder
    {
        WorldManager *m_world;
        unsigned int m_id;
        template <typename T>
        Key include()
        {
            auto key = m_world->getKeys()->getKey<T>();
            m_world->getComponents()->key<T>(key.getId(), m_world->getEntities()->getSize());
            m_world->getEntities()->getEntity(m_id)->include(key.getId());
            m_world->getModifiedEntities()->insert(m_id);
            return key;
        }

    public:
        EntityBuilder(WorldManager *world, const unsigned int id)
        {
            m_world = world;
            m_id = id;
        }

        template <typename T>
        EntityBuilder *with(const T value)
        {
            auto key = include<T>();
            m_world->getComponents()->setComponent(key.getId(), m_id, value);

            return this;
        }

        template <typename T>
        EntityBuilder *with()
        {
            include<T>();

            return this;
        }

        template <typename T>
        EntityBuilder *disable()
        {
            auto key = m_world->getKeys()->getKey<T>();
            m_world->getEntities()->getEntity(m_id)->exclude(key.getId());
            m_world->getModifiedEntities()->insert(m_id);

            return this;
        }

        template <typename T>
        T *get()
        {
            auto key = m_world->getKeys()->getKey<T>();
            return m_world->getComponents()->getComponents<T>(key.getId())[m_id];
        }

        void disable()
        {
            m_world->getModifiedEntities()->insert(m_id);
        }

        int getId()
        {
            return m_id;
        }
    };
}
