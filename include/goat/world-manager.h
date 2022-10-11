#pragma once

#include "components.h"
#include "entities.h"
#include "indexes.h"
#include "keys.h"

namespace goat {
class WorldManager {
  public:
  WorldManager() {}
  virtual ~WorldManager() {}
  virtual Keys *getKeys() = 0;
  virtual Entities *getEntities() = 0;
  virtual Components *getComponents() = 0;
  virtual Indexes *getIndexes() = 0;
};
}  // namespace goat
