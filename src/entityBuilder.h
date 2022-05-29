#pragma once

#include "worldManager.h"

class EntityBuilder
{
    WorldManager *m_world;
    unsigned int id;
public:
    EntityBuilder(WorldManager *world)
    {
        m_world = world;
        id = m_world->GetEntities()->NewEntity();
    }

    template <typename T>
    EntityBuilder *With(const T value)
    {
        auto key = m_world->GetKeys()->Key<T>();
        m_world->GetComponents()->Key<T>(key, m_world->GetEntities()->GetSize());
        m_world->GetEntities()->AddComponent(id, key);
        m_world->GetIndex()->UpdateEntityIndex(id, m_world->GetEntities()->GetEntity(id));
        m_world->GetComponents()->SetComponent(key, id, value);

        return this;
    }

    template <typename T>
    EntityBuilder *With()
    {
        auto key = m_world->GetKeys()->Key<T>();
        m_world->GetComponents()->Key<T>(key, m_world->GetEntities()->GetSize());
        m_world->GetEntities()->AddComponent(id, key);
        m_world->GetIndex()->UpdateEntityIndex(id, m_world->GetEntities()->GetEntity(id));

        return this;
    }

    int GetId()
    {
        return id;
    }
};
