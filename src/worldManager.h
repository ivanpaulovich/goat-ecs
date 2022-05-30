#pragma once

#include "entities.h"
#include "components.h"
#include "index.h"
#include "keys.h"

class WorldManager
{
public:
    WorldManager(){}
    virtual ~WorldManager(){}
    virtual Keys *GetKeys() = 0;
    virtual Entities *GetEntities() = 0;
    virtual Components *GetComponents() = 0;
    virtual Index *GetIndex() = 0;
};
