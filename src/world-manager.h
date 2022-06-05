#pragma once

#include "entities.h"
#include "components.h"
#include "index.h"
#include "keys.h"
#include "entities-set.h"
#include "keys-map.h"

namespace goat
{
    class WorldManager
    {
    public:
        WorldManager() {}
        virtual ~WorldManager() {}
        virtual Keys *getKeys() = 0;
        virtual Entities *getEntities() = 0;
        virtual Components *getComponents() = 0;
        virtual Index *getIndex() = 0;
        virtual KeysMap *getIncludedComponents() = 0;
        virtual KeysMap *getExcludedComponents() = 0;
        virtual EntitiesSet *getCreatedEntities() = 0;
        virtual EntitiesSet *getDestroyedEntities() = 0;
    };
}
