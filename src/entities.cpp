#include <foo/entities.h>

void Entities::SetComponents(const unsigned int id, const unsigned int key)
{
    m_entities[id] = key;
}

Entities::Entities(const unsigned int size)
{
    m_size = size;
    m_entities = new unsigned int(size);
}

unsigned int Entities::NewEntity()
{
    unsigned int id = m_entities_count++;
    return id;
}

unsigned int Entities::GetEntity(const unsigned int id)
{
    return m_entities[id];
}

unsigned int Entities::GetCount()
{
    return m_entities_count;
}

unsigned int Entities::GetSize()
{
    return m_size;
}

bool Entities::HasComponent(const unsigned int id, const unsigned int key)
{
    return GetEntity(id) && key == 0;
}

void Entities::AddComponent(const unsigned int id, const unsigned int key)
{
    SetComponents(id, GetEntity(id) | key);
}

void Entities::RemoveComponent(const unsigned int id, const unsigned int key)
{
    SetComponents(id, GetEntity(id) ^ key);
}