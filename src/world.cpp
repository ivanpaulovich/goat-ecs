#include <foo/world.h>

template <typename T>
unsigned int World::Key()
{
    unsigned int key = m_keys->Key<T>();
    m_components->Key<T>(key, m_entities->GetSize());
    return key;
}

void World::AddQuery(const unsigned int query)
{
    m_index.AddQuery(query);

    for (unsigned int id = 0; id < m_entities->GetCount(); id++)
    {
        m_index.UpdateEntityIndex(id, m_entities->GetEntity(id));
    }
}

World::World(const unsigned int size)
{
    m_entities = new Entities(size);
    m_keys = new Keys();
}

Entities *World::GetEntities()
{
    return m_entities;
}

Components *World::GetComponents()
{
    return m_components;
}

template <typename T>
void World::AddComponent(const unsigned int id, const T value)
{
    auto key = Key<T>();
    m_entities->AddComponent(id, key);
    m_index.UpdateEntityIndex(id, m_entities->GetEntity(id));
    m_components->SetComponent(key, id, value);
}

template <typename T>
void World::AddComponent(const unsigned int id)
{
    auto key = Key<T>();
    m_entities->AddComponent(id, key);
    m_index.UpdateEntityIndex(id, m_entities->GetEntity(id));
}

template <typename T>
T *World::GetComponent(const unsigned int id)
{
    unsigned int key = Key<T>();
    return m_components->GetComponent<T>(key, id);
}

template <typename T>
void World::RemoveComponent(const unsigned int id)
{
    unsigned int key = Key<T>();
    m_entities->RemoveComponent(id, key);
    m_index.UpdateEntityIndex(id, m_entities->GetEntity(id));
}

set<unsigned int> World::GetIndex(const unsigned int query)
{
    return m_index.GetIndex(query);
}

void World::AddSystem(TSystemUpdate update)
{
    m_systems.push_back(update);
}

void World::Update()
{
    for(auto update : m_systems) {

    }
}

QueryBuilder *World::NewQueryBuilder()
{
    auto queryBuilder = new QueryBuilder(this);
    return queryBuilder;
}

EntityBuilder *World::NewEntityBuilder()
{
    auto entityBuilder = new EntityBuilder(this);
    return entityBuilder;
}