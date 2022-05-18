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

// Demonstrate some basic assertions.
TEST(WorldTest, EntityBuilding)
{
  World *w = new World(10);

  int key1 = w->Key<Position>();
  int key2 = w->Key<Velocity>();
  int key3 = w->Key<Health>();
  int key4 = w->Key<Health>();

  cout << "Position" << key1;
  cout << "Velocity" << key2;
  cout << "Health" << key3;
  cout << "Health" << key4;

  size_t entityId = w->NewEntity();

  Health health;
  health.level = 3;

  Position position;
  position.x = 10;
  position.y = 20;

  Velocity velocity;
  velocity.x = 10;
  velocity.y = 20;

  w->NewEntityBuilder()
    ->With<Health>(health)
    ->With<Position>(position);

  health.level = 11;

  w->NewEntityBuilder()
    ->With<Health>(health)
    ->With<Velocity>(velocity);

  for (size_t id = 0; id < w->GetEntitiesCount(); id++)
  {
    Health* health1 = w->GetComponent<Health>(id);
    cout << health1->level;
  }

  Health *healths = w->GetComponents<Health>();

  for (int i = 0; i < 5; i++)
  {
    cout << healths->level;
    healths++;
  }

  EXPECT_EQ(1000, 1000);
}