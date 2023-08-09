# Goat-ECS

Goat-ECS is an Entity-Component System with a friendly API to build objects with dynamic components.

## Compiling

```
cmake -S . -B build
cmake --build build -j 12
GTEST_COLOR=1 ctest --test-dir build --output-on-failure -j12
```

## Vim

```
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1
```

## Debug

```
lldb test/test/goat-tests
(lldb) b main
```

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
// Returns the ids of entities matching the component type Health
auto healthIds = w.newQuery()
    ->include<Health>()
    ->apply()
    ->getIndex();

for (auto id : *healthIds)
{
    auto health = w.loadEntity(id)
        ->get<Health>();

    std::cout << health->level << " ";
}
```

## Design Your Own Components

```
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
