#include <gtest/gtest.h>
#include <typeinfo>
#include <iostream>
#include <set>
#include <goat/world.h>
#include <goat/world-manager.h>
#include <goat/entities.h>
#include <goat/components.h>
#include "game-components.h"
#include <stdexcept>
#include "gmock/gmock.h"

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
        ->include<Health>({50.0f})
        ->include<Position>({10, 30})
        ->apply();

    w.newEntity()
        ->include<Health>({10.0f})
        ->include<Position>({20, 40})
        ->include<Velocity>({2, 3})
        ->apply();

    w.newEntity()
        ->include<Velocity>({0, 3})
        ->include<Position>({2, 1})
        ->apply();

    auto healthObjects = w.newQuery()
                           ->include<Health>()
                           ->apply()
                           ->getIndex();

    for (auto itr : *healthObjects)
    {
        auto health = w.loadEntity(itr)
            ->get<Health>();

        cout << health->level << " ";
    }

    EXPECT_EQ(2, healthObjects->size());
}

