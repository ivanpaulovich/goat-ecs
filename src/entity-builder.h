#pragma once

#include "world-manager.h"

namespace goat
{
    class EntityBuilder
    {
        WorldManager *m_world;
        unsigned int m_id;

        template <typename T>
        Key init()
        {
            auto key = m_world->getKeys()->getKey<T>();
            m_world->getComponents()->key<T>(key.getId(), m_world->getEntities()->getSize());
            m_world->getEntities()->getEntity(m_id)->include(key.getId());

            return key;
        }
    public:
        EntityBuilder(WorldManager *world, const unsigned int id)
        {
            m_world = world;
            m_id = id;
        }

        template <typename T>
        EntityBuilder *include(const T value)
        {
            auto key = init<T>();
            m_world->getComponents()->setComponent(key.getId(), m_id, value);

            return this;
        }

        template <typename T>
        EntityBuilder *include()
        {
            init<T>();

            return this;
        }

        template <typename T>
        EntityBuilder *exclude()
        {
            auto key = m_world->getKeys()->getKey<T>();
            m_world->getEntities()->getEntity(m_id)->exclude(key.getId());

            return this;
        }

        template <typename T>
        T *get()
        {
            auto key = m_world->getKeys()->getKey<T>();
            return m_world->getComponents()->getComponents<T>(key.getId())[m_id];
        }

        void destroy()
        {

        }

        void apply()
        {
            auto signature = m_world->getEntities()->getEntity(m_id)->getId();
            m_world->getIndexes()->updateEntityIndex(m_id, signature);
        }

        int getId()
        {
            return m_id;
        }
    };
}
