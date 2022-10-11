#pragma once

#include <map>

#include "equal-to.h"
#include "hasher.h"
#include "key.h"
#include "unordered_map"

namespace goat {
class Keys {
  private:
  unordered_map<reference_wrapper<const type_info>, Key, Hasher, EqualTo>
      m_keys;

  public:
  template <typename T>
  Key getKey() {
    reference_wrapper<const type_info> type = typeid(T);
    if (m_keys.find(type) != m_keys.end()) {
      return m_keys[type];
    }

    unsigned int key = 1 << m_keys.size();
    m_keys[type] = Key(key);

    return key;
  }
};
}  // namespace goat
