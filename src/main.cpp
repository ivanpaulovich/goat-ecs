#include <iostream>
#include "world.h"

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

int main() {
    Component component;
    component.Init<Position>(10);
    Position *positions = component.GetValues<Position>();

    return 0;
}