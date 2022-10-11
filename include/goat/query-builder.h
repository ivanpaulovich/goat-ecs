#pragma once

#include "key.h"
#include "world-manager.h"

namespace goat {
class QueryBuilder {
  private:
  WorldManager *m_world;
  Key *m_key;

  public:
  QueryBuilder(WorldManager *world, unsigned int id) {
    m_world = world;
    m_key = new Key(id);
  }

  template <typename T>
  QueryBuilder *include() {
    auto key = m_world->getKeys()->getKey<T>();
    m_key->include(key.getId());
    return this;
  }

  template <typename T>
  QueryBuilder *exclude() {
    auto key = m_world->getKeys()->getKey<T>();
    m_key->exclude(key.getId());
    return this;
  }

  QueryBuilder *apply() {
    m_world->getIndexes()->addQuery(m_key->getId());

    for (unsigned int id = 0; id < m_world->getEntities()->getCount(); id++) {
      auto key = m_world->getEntities()->getEntity(id);

      if (key->getId() != -1) {
        m_world->getIndexes()->updateEntityIndex(id, key->getId());
      }
    }

    return this;
  }

  Key getKey() { return *m_key; }

  std::set<unsigned int> *getIndex() {
    return m_world->getIndexes()->getIndex(m_key->getId());
  }
};
}  // namespace goat
