# Goat-ECS

Goat-ECS is a friendly and pure Entity-Component System. Dynamically build objects, then query the ones with similar properties the same approach you would query a database. Goat-ECS library is an API to manipulate object properties which tracks schema changes and indexes the entity ids optimized for the best query performance.

## Entities Building

```c
World w = World(100);

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
```

## Queries

```c
auto queryHealth = w.newQuery()
    ->include<Health>()
    ->apply()
    ->getKey();

auto healthObjects = w.getIndex()
    ->getIndex(queryHealth.getId());

std::cout << healthObjects.size();
// Prints 2
```

## Design Your Own Components

```c
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
```

## Systems

Coming soon.
