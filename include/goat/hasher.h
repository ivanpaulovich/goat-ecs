#pragma once

#include <iostream>
#include <typeinfo>

using namespace std;

namespace goat {
struct Hasher {
  unsigned int operator()(reference_wrapper<const type_info> code) const {
    return code.get().hash_code();
  }
};
}  // namespace goat
