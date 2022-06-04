#pragma once

#include "entities.h"
#include "components.h"
#include "index.h"
#include "keys.h"
#include "entities-set.h"

class WorldManager
{
public:
    WorldManager(){}
    virtual ~WorldManager(){}
    virtual Keys *getKeys() = 0;
    virtual Entities *getEntities() = 0;
    virtual Components *getComponents() = 0;
    virtual Index *getIndex() = 0;
    virtual EntitiesSet *getAddedEntities() = 0;
    virtual EntitiesSet *getModifiedEntities() = 0;
    virtual EntitiesSet *getDisabledEntities() = 0;
};
