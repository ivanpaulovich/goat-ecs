# Goat-ECS

Goat-ECS is a friendly and pure Entity-Component System. Dynamically build objects, then query the ones with similar properties the same approach you would query a database. Goat-ECS library is an API to manipulate object properties which tracks schema changes and indexes the entity ids optimized for the best query performance.

## Define Your Own Components

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

## Entities Building

```c
World w = World(WORLD_SIZE);

w.newEntity()
    ->with<Health>({50.0f})
    ->with<Position>({10, 30});

w.newEntity()
    ->with<Health>({10.0f})
    ->with<Position>({20, 40})
    ->with<Velocity>({2, 3});

w.newEntity()
    ->with<Velocity>({0, 3})
    ->with<Position>({2, 1});
```

## Queries

```c
auto queryHealth = w.newQuery()
                        ->include<Health>()
                        ->Ready()
                        ->GetKey();

auto healthObjects = w.getIndex()
                            ->getIndex(queryHealth.getId());

cout << healthObjects.size();
// Prints 2
```

## Systems

Coming soon.
