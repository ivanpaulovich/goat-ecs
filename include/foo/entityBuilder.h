#pragma once

#include "world.fwd.h"

class EntityBuilder
{
    World *m_world;
    unsigned int id;
public:
    EntityBuilder(World *world);

    template <typename T>
    EntityBuilder *With(const T value);

    template <typename T>
    EntityBuilder *With();

    int GetId();
};