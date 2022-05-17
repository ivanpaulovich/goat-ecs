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

  unsigned int entityId = w->NewEntity();

  Health health;
  health.level = 3;

  w->NewEntityBuilder()->With<Health>(health);

  Health* healths = w->GetComponents<Health>();

  for (int i = 0; i < 5; i++)
  {
    cout << healths->level;
    healths++;
  }
  
  EXPECT_EQ(1000, 1000);
}