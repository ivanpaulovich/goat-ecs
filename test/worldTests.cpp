#include <gtest/gtest.h>
#include <typeinfo>
#include <iostream>
#include <set>
#include "world.h"
#include "world-manager.h"
#include "entities.h"
#include "components.h"

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
    float level;
};

// class Component1
// {
// private:
//     void *m_values;
// public:
//   template <typename T>
//   void Init(const unsigned int size)
//   {
//       m_values = new T[size];
//   }

//   template <typename T>
//   T *GetValues()
//   {
//       return static_cast<T *>(m_values);
//   }
// };

const unsigned int WORLD_SIZE = 10;

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

    Health health;
    health.level = 100.0f;

    Position position;
    position.x = 10;
    position.y = 20;

    Velocity velocity;
    velocity.x = 2;
    velocity.y = 4;

    auto entityId0 = w.newEntity()
        ->with<Health>(health)
        ->with<Position>(position)
        ->getId();

    w.newEntity()
        ->with<Health>(health)
        ->with<Position>(position)
        ->with<Velocity>(velocity);

    w.newEntity()
        ->with<Position>(position)
        ->with<Velocity>(velocity);

    auto entity = w.loadEntity(entityId0);

    entity->disable<Position>();

    // auto h = entity->getComponents<Health>()[entity->];

    // EXPECT_EQ(100, h->level);

    // auto queryHealth = w.newQuery()
    //                        ->include<Health>()
    //                        ->Ready()
    //                        ->getKey();

    // auto queryPosVel = w.newQuery()
    //                        ->include<Position>()
    //                        ->include<Velocity>()
    //                        ->Ready()
    //                        ->getKey();

    // auto queryPos = w.newQuery()
    //                     ->include<Position>()
    //                     ->Ready()
    //                     ->getKey();

    // auto healthObjects = w.getIndex()->.getIndex(queryHealth);
    // auto posVelObjects = w.getIndex().getIndex(queryPosVel);
    // auto posObjects = w.getIndex().getIndex(queryPos);

    // EXPECT_EQ(2, healthObjects.count());
    // EXPECT_EQ(2, posVelObjects.count());
    // EXPECT_EQ(1, posObjects.count());
}

// void testUpdate(World *w, const set<unsigned int> *index)
// {
//   for (const auto id : *index)
//   {
//     auto *health = w->GetComponent<Health>(id);
//     cout << health->level;
//   }
// }

// // Demonstrate some basic assertions.
// TEST(WorldTest, EntityBuilding)
// {
//   World *w = new World(10);

//   unsigned int entityId = w->NewEntityBuilder()
//                               ->getId();

//   Health health;
//   health.level = 3;

//   Position position;
//   position.x = 10;
//   position.y = 20;

//   Velocity velocity;
//   velocity.x = 10;
//   velocity.y = 20;

//   w->addSystem(&testUpdate);

//   int entityId1 = w->NewEntityBuilder()
//                       ->With<Health>(health)
//                       ->With<Position>(position)
//                       ->getId();

//   health.level = 11;

//   // int entityId2 = w->NewEntityBuilder()
//   //                     ->With<Health>(health)
//   //                     ->With<Velocity>(velocity);

//   unsigned int query = w->NewQueryBuilder()
//                            ->include<Health>()
//                            ->Ready()
//                            ->GetQuery();

//   for (unsigned int id = 0; id < w->getEntities()->GetEntitiesCount(); id++)
//   {
//     Health *health1 = w->GetComponent<Health>(id);
//     cout << health1->level;
//   }

//   EXPECT_EQ(3, w->getEntities()->GetEntitiesCount());

//   auto index1 = w->getIndex(query);

//   // EXPECT_EQ(3, index1.count());

//   testUpdate(w, &index1);

//   w->RemoveComponent<Health>(entityId1);

//   auto index2 = w->getIndex(query);

//   testUpdate(w, &index2);

//   // EXPECT_EQ(2, index1.count());
// }
