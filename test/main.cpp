#include <gtest/gtest.h>
#include <typeinfo>
#include <iostream>
#include "../src/world.h"

struct Position
{
  int x;
  int y;
};

struct Velocity
{
  int x;
  int y;
};

struct Health
{
  int level;
};

void testUpdate(World *w, const set<unsigned int> *index)
{
  for (const auto id : *index)
  {
    auto *health = w->GetComponent<Health>(id);
    cout << health->level;
  }
}

// Demonstrate some basic assertions.
TEST(WorldTest, EntityBuilding)
{
  World *w = new World(10);

  unsigned int entityId = w->NewEntityBuilder()
                              ->GetId();

  Health health;
  health.level = 3;

  Position position;
  position.x = 10;
  position.y = 20;

  Velocity velocity;
  velocity.x = 10;
  velocity.y = 20;

  w->AddSystem(&testUpdate);

  int entityId1 = w->NewEntityBuilder()
                      ->With<Health>(health)
                      ->With<Position>(position)
                      ->GetId();

  health.level = 11;

  int entityId2 = w->NewEntityBuilder()
                      ->With<Health>(health)
                      ->With<Velocity>(velocity)
                      ->GetId();

  unsigned int query = w->NewQueryBuilder()
                           ->Include<Health>()
                           ->Ready()
                           ->GetQuery();

  for (unsigned int id = 0; id < w->GetEntitiesCount(); id++)
  {
    Health *health1 = w->GetComponent<Health>(id);
    cout << health1->level;
  }

  EXPECT_EQ(3, w->GetEntitiesCount());

  auto index1 = w->GetIndex(query);

  // EXPECT_EQ(3, index1.count());

  testUpdate(w, &index1);

  w->RemoveComponent<Health>(entityId1);

  auto index2 = w->GetIndex(query);

  testUpdate(w, &index2);

  // EXPECT_EQ(2, index1.count());
}