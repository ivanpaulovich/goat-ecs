#include <gtest/gtest.h>
#include <typeinfo>
#include <iostream>
#include <set>
#include <world.h>
#include <world-manager.h>
#include <entities.h>
#include <components.h>
#include "game-components.h"

using namespace goat;

TEST(WorldTest, ComponentsBuilding)
{
    const unsigned int POSITION_KEY = 0;
    const unsigned int POSITION_SIZE = 10;
    const unsigned int POSITION_ELEMENT_ID = 0;

    Components components;
    components.key<Position>(POSITION_KEY, POSITION_SIZE);

    Position pos1 = components.getComponents<Position>(POSITION_KEY)[POSITION_ELEMENT_ID];

    EXPECT_EQ(0, pos1.x);
    EXPECT_EQ(0, pos1.y);

    pos1.x = 10;
    pos1.y = 20;

    components.setComponent<Position>(POSITION_KEY, POSITION_ELEMENT_ID, pos1);

    Position pos2 = components.getComponents<Position>(POSITION_KEY)[POSITION_ELEMENT_ID];

    EXPECT_EQ(10, pos2.x);
    EXPECT_EQ(20, pos2.y);
}

TEST(WorldTest, WorldBuilding)
{
    World w = World(WORLD_SIZE);

    w.newEntity()
        ->with<Health>({50.0f})
        ->with<Position>({10, 30})
        ->getId();

    w.newEntity()
        ->with<Health>({10.0f})
        ->with<Position>({20, 40})
        ->with<Velocity>({2, 3});

    w.newEntity()
        ->with<Velocity>({0, 3})
        ->with<Position>({2, 1});

    auto queryHealth = w.newQuery()
                           ->include<Health>()
                           ->Ready()
                           ->GetKey();

    auto healthObjects = w.getIndex()
                             ->getIndex(queryHealth.getId());

    EXPECT_EQ(2, healthObjects->size());
}
