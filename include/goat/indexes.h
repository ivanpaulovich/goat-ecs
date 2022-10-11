#pragma once

#include <map>
#include <set>

namespace goat {
class Indexes {
  private:
  std::map<unsigned int, std::set<unsigned int>> m_indexes;

  bool isEntitySignatureInQuery(const unsigned int signature,
                                const unsigned int query);

  void addEntityToIndex(const unsigned int id, const unsigned int query);

  void removeEntityFromIndex(const unsigned int id, const unsigned int query);

  void insertOrRemoveEntityFromIndex(const unsigned int id,
                                     const unsigned int signature,
                                     const unsigned int query);

  public:
  void addQuery(const unsigned int query);

  void removeQuery(const unsigned int query);

  std::set<unsigned int> *getIndex(const unsigned int query);

  void updateEntityIndex(const unsigned int id, const unsigned int signature);
};
}  // namespace goat
