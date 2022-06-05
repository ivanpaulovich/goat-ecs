#pragma once

#include <set>
#include "key.h"

namespace goat
{
    class KeysMap
    {
    private:
        std::map<unsigned int, Key> m_entities;

    public:
        Key *getEntity(const unsigned int id)
        {
            return &m_entities[id];
        }
    };
}
