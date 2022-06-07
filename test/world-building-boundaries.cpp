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

TEST(WorldTesting, WorldBuildingOversize)
{
    EXPECT_THAT([]()
        {
            World w = World(WORLD_SIZE);

            for (int i = 0; i < WORLD_SIZE; i++)
            {
                w.newEntity()
                    ->include<Health>({50.0f})
                    ->include<Position>({10, 30})
                    ->apply();
            }

            w.newEntity()
                ->include<Health>({50.0f})
                ->include<Position>({10, 30})
                ->apply();
        },
        testing::Throws<std::exception>());
}

TEST(WorldTesting, Deleting)
{
    World w = World(WORLD_SIZE);

    for (int i = 0; i < WORLD_SIZE; i++)
    {
        w.newEntity()
            ->include<Health>({50.0f})
            ->include<Position>({10, 30})
            ->apply();
    }

    w.loadEntity(4)->destroy();

    w.newEntity()
        ->include<Health>({50.0f})
        ->include<Position>({10, 30})
        ->apply();
}

