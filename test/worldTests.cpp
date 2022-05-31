#include <gtest/gtest.h>
#include <typeinfo>
#include <iostream>
#include <set>
#include "world.h"
#include "worldManager.h"
#include "component.h"
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

TEST(WorldTest, EntityBuilding)
{
    Entities entities = Entities(WORLD_SIZE);
    unsigned int id = entities.NewEntity();
    Component component;
    component.Init<Position>(WORLD_SIZE);
    Position *c = component.GetValues<Position>();
}

TEST(WorldTest, ComponentBuilding)
{
    Component component;
    component.Init<Position>(WORLD_SIZE);
    Position *positions = component.GetValues<Position>();
}

TEST(WorldTest, ComponentsBuilding)
{
    const unsigned int POSITION_KEY = 0;
    const unsigned int POSITION_SIZE = 10;
    const unsigned int POSITION_ELEMENT_ID = 0;

    Components components;
    components.Key<Position>(POSITION_KEY, POSITION_SIZE);

    Position *pos1 = components.GetComponent<Position>(POSITION_KEY, POSITION_ELEMENT_ID);

    EXPECT_EQ(0, pos1->x);
    EXPECT_EQ(0, pos1->y);

    pos1->x = 10;
    pos1->y = 20;

    Position *pos2 = components.GetComponent<Position>(POSITION_KEY, POSITION_ELEMENT_ID);

    EXPECT_EQ(10, pos2->x);
    EXPECT_EQ(20, pos2->y);
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

    auto entityId0 = w.NewEntity()
        ->With<Health>(health)
        ->With<Position>(position)
        ->GetId();

    w.NewEntity()
        ->With<Health>(health)
        ->With<Position>(position)
        ->With<Velocity>(velocity);

    w.NewEntity()
        ->With<Position>(position)
        ->With<Velocity>(velocity);

    auto entity = w.LoadEntity(entityId0);

    entity->RemoveComponent<Position>();

    auto h = entity->GetComponent<Health>();

    EXPECT_EQ(100, h->level);

    auto queryHealth = w.NewQuery()
                           ->Include<Health>()
                           ->Ready()
                           ->GetQuery();

    auto queryPosVel = w.NewQuery()
                           ->Include<Position>()
                           ->Include<Velocity>()
                           ->Ready()
                           ->GetQuery();

    auto queryPos = w.NewQuery()
                        ->Include<Position>()
                        ->Ready()
                        ->GetQuery();

    auto healthObjects = w.GetIndex().GetIndex(queryHealth);
    auto posVelObjects = w.GetIndex().GetIndex(queryPosVel);
    auto posObjects = w.GetIndex().GetIndex(queryPos);

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
//                               ->GetId();

//   Health health;
//   health.level = 3;

//   Position position;
//   position.x = 10;
//   position.y = 20;

//   Velocity velocity;
//   velocity.x = 10;
//   velocity.y = 20;

//   w->AddSystem(&testUpdate);

//   int entityId1 = w->NewEntityBuilder()
//                       ->With<Health>(health)
//                       ->With<Position>(position)
//                       ->GetId();

//   health.level = 11;

//   // int entityId2 = w->NewEntityBuilder()
//   //                     ->With<Health>(health)
//   //                     ->With<Velocity>(velocity);

//   unsigned int query = w->NewQueryBuilder()
//                            ->Include<Health>()
//                            ->Ready()
//                            ->GetQuery();

//   for (unsigned int id = 0; id < w->GetEntities()->GetEntitiesCount(); id++)
//   {
//     Health *health1 = w->GetComponent<Health>(id);
//     cout << health1->level;
//   }

//   EXPECT_EQ(3, w->GetEntities()->GetEntitiesCount());

//   auto index1 = w->GetIndex(query);

//   // EXPECT_EQ(3, index1.count());

//   testUpdate(w, &index1);

//   w->RemoveComponent<Health>(entityId1);

//   auto index2 = w->GetIndex(query);

//   testUpdate(w, &index2);

//   // EXPECT_EQ(2, index1.count());
// }
