#include <vector>
#include "entities.h"
#include "key.h"

Entities::Entities(const unsigned int size)
{
    m_entities_count = 0;
    m_entities = std::vector<Key>(size);
}

unsigned int Entities::NewEntity()
{
    unsigned int id = m_entities_count++;
    return id;
}

Key *Entities::GetEntity(const unsigned int id)
{
    return &m_entities[id];
}

unsigned int Entities::GetCount()
{
    return m_entities_count;
}

unsigned int Entities::GetSize()
{
    return m_entities.size();
}
