#include <vector>
#include "entities.h"
#include "key.h"

Entities::Entities(const unsigned int size)
{
    m_size = size;
    m_entities_count = 0;
    m_entities = new Key[m_size];
}

unsigned int Entities::newEntity()
{
    unsigned int id = m_entities_count++;
    return id;
}

Key *Entities::getEntity(const unsigned int id)
{
    return &m_entities[id];
}

unsigned int Entities::getCount()
{
    return m_entities_count;
}

unsigned int Entities::getSize()
{
    return m_size;
}
