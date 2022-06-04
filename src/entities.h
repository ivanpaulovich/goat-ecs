#pragma once

#include <vector>
#include "key.h"

class Entities
{
private:
    unsigned int m_size;
    unsigned int m_entities_count;
    Key *m_entities;
public:
    Entities(const unsigned int size);

    unsigned int newEntity();

    Key *getEntity(const unsigned int id);

    unsigned int getCount();

    unsigned int getSize();
};
