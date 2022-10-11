#include <goat/components.h>
#include <goat/entities.h>
#include <goat/world-manager.h>
#include <goat/world.h>
#include <gtest/gtest.h>

#include <iostream>
#include <set>
#include <stdexcept>
#include <typeinfo>

#include "game-components.h"
#include "gmock/gmock.h"

using namespace goat;

TEST(WorldTesting, WorldBuildingOversize) {
  EXPECT_THAT(
      []() {
        World w = World(WORLD_SIZE);

        for (int i = 0; i < WORLD_SIZE; i++) {
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

TEST(WorldTesting, Deleting) {
  World w = World(WORLD_SIZE);

  for (int i = 0; i < WORLD_SIZE; i++) {
    w.newEntity()
        ->include<Health>({50.0f})
        ->include<Position>({10, 30})
        ->apply();
  }

  w.loadEntity(4)->destroy();

  w.newEntity()->include<Health>({50.0f})->include<Position>({10, 30})->apply();
}
