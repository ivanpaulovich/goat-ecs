#pragma once

#include <queue>
#include "key.h"

class EntitiesQueue
{
private:
    std::queue<unsigned int> m_modifiedEntities;
public:
    EntitiesQueue();

    void push(const unsigned int id);
    unsigned int pop(const unsigned int id);
};
