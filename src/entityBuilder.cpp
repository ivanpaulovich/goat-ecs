#include "entityBuilder.h"
#include "world.fwd.h"
#include "world.h"

EntityBuilder::EntityBuilder(World *world)
{
    m_world = world;
    id = m_world->GetEntities()->NewEntity();
}

template <typename T>
EntityBuilder *EntityBuilder::With(const T value)
{
    m_world->AddComponent<T>(id);
    m_world->AddComponent<T>(id, value);

    return this;
}

template <typename T>
EntityBuilder *EntityBuilder::With()
{
    m_world->AddComponent<T>(id);

    return this;
}

int EntityBuilder::GetId()
{
    return id;
}