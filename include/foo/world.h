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
#include "typeInfoRef.h"
#include "index.h"
#include "entities.h"
#include "keys.h"
#include "components.h"
#include "queryBuilder.h"
#include "entityBuilder.h"
#include "world.fwd.h"
#include "tSystemUpdate.h"

class World
{
private:
    Entities *m_entities;
    Keys *m_keys;
    Components *m_components;
    Index m_index;
    vector<TSystemUpdate *> m_systems;

    template <typename T>
    unsigned int Key();

public:
    World(const unsigned int size);

    Entities *GetEntities();

    Components *GetComponents();

    template <typename T>
    void AddComponent(const unsigned int id, const T value);

    template <typename T>
    void AddComponent(const unsigned int id);

    template <typename T>
    T *GetComponent(const unsigned int id);

    template <typename T>
    void RemoveComponent(const unsigned int id);

    set<unsigned int> GetIndex(const unsigned int query);

    void AddSystem(TSystemUpdate update);

    void AddQuery(const unsigned int query);

    void Update();

    QueryBuilder *NewQueryBuilder();

    EntityBuilder *NewEntityBuilder();
};