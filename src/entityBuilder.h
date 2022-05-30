#pragma once

#include "worldManager.h"

class EntityBuilder
{
    WorldManager *m_world;
    unsigned int m_id;
public:
    EntityBuilder(WorldManager *world, const unsigned int id)
    {
        m_world = world;
        m_id = id;
    }

    template <typename T>
    EntityBuilder *With(const T value)
    {
        auto key = m_world->GetKeys()->Key<T>();
        m_world->GetComponents()->Key<T>(key, m_world->GetEntities()->GetSize());
        m_world->GetEntities()->AddComponent(m_id, key);
        m_world->GetIndex()->UpdateEntityIndex(m_id, m_world->GetEntities()->GetEntity(m_id));
        m_world->GetComponents()->SetComponent(key, m_id, value);

        return this;
    }

    template <typename T>
    EntityBuilder *With()
    {
        auto key = m_world->GetKeys()->Key<T>();
        m_world->GetComponents()->Key<T>(key, m_world->GetEntities()->GetSize());
        m_world->GetEntities()->AddComponent(m_id, key);
        m_world->GetIndex()->UpdateEntityIndex(m_id, m_world->GetEntities()->GetEntity(m_id));

        return this;
    }

    template <typename T>
    EntityBuilder *RemoveComponent()
    {
        auto key = m_world->GetKeys()->Key<T>();
        m_world->GetEntities()->RemoveComponent(m_id, key);
        m_world->GetIndex()->UpdateEntityIndex(m_id, m_world->GetEntities()->GetEntity(m_id));

        return this;
    }

    template <typename T>
    T *GetComponent()
    {
        auto key = m_world->GetKeys()->Key<T>();
        return m_world->GetComponents()->GetComponent<T>(key, m_id);
    }

    int GetId()
    {
        return m_id;
    }
};
