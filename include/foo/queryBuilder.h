#pragma once

#include <array>
#include <vector>
#include <map>
#include <iostream>
#include <typeinfo>
#include <unordered_map>
#include <string>
#include <functional>
#include <memory>
#include <set>
#include "query.h"

class World;

class QueryBuilder
{
private:
    World *m_world;
    Query *m_query;
public:
    QueryBuilder(World *world);

    template <typename T>
    QueryBuilder *Include();

    QueryBuilder *Ready();

    unsigned int GetQuery();
};
