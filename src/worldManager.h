#pragma once

#include "entities.h"
#include "components.h"
#include "index.h"
#include "keys.h"

class WorldManager
{
public:
    virtual Keys *GetKeys();
    virtual Entities *GetEntities();
    virtual Components *GetComponents();
    virtual Index *GetIndex();
};