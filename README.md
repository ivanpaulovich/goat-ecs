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

## Initialize the Properties

```c
Health health;
health.level = 100.0f;

Position position;
position.x = 10;
position.y = 20;

Velocity velocity;
velocity.x = 2;
velocity.y = 4;
```

## Entities Building

```c
World w = new World(100);

w.newEntity()
    ->with<Health>(health)
    ->with<Position>(position)
    ->with<Velocity>(velocity);

/* Queries (coming soon) */

/* Systems (coming soon) */

```

## Queries

Coming soon.

## Systems

Coming soon.
