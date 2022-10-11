#pragma once

#include <iostream>
#include <typeinfo>

using namespace std;

namespace goat {
struct EqualTo {
  bool operator()(reference_wrapper<const type_info> lhs,
                  reference_wrapper<const type_info> rhs) const {
    return lhs.get() == rhs.get();
  }
};
}  // namespace goat
