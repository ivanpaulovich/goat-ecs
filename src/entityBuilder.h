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
        auto key = m_world->GetKeys()->GetKey<T>();
        m_world->GetComponents()->key<T>(key.GetId(), m_world->GetEntities()->GetSize());
        m_world->GetEntities()->GetEntity(m_id)->Include(key.GetId());
        m_world->GetIndex()->UpdateEntityIndex(m_id, m_world->GetEntities()->GetEntity(m_id)->GetId());
        m_world->GetComponents()->SetComponent(key.GetId(), m_id, value);

        return this;
    }

    template <typename T>
    EntityBuilder *With()
    {
        auto key = m_world->GetKeys()->GetKey<T>();
        m_world->GetComponents()->key<T>(key.GetId(), m_world->GetEntities()->GetSize());
        m_world->GetEntities()->GetEntity(m_id)->Include(key.GetId());
        m_world->GetIndex()->UpdateEntityIndex(m_id, m_world->GetEntities()->GetEntity(m_id)->GetId());

        return this;
    }

    template <typename T>
    EntityBuilder *RemoveComponent()
    {
        auto key = m_world->GetKeys()->GetKey<T>();
        m_world->GetEntities()->GetEntity(m_id)->Exclude(key.GetId());
        m_world->GetIndex()->UpdateEntityIndex(m_id, m_world->GetEntities()->GetEntity(m_id)->GetId());

        return this;
    }

    template <typename T>
    T *GetComponent()
    {
        auto key = m_world->GetKeys()->GetKey<T>();
        return m_world->GetComponents()->GetComponents<T>(key.GetId())[m_id];
    }

    int GetId()
    {
        return m_id;
    }
};
