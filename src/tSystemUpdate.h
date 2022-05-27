#pragma once

#include <array>
#include <vector>
#include <map>
#include <iostream>
#include <typeinfo>
#include <unordered_map>
#include <string>
#include <functional>
#include <memory>
#include <set>
#include "world.fwd.h"

typedef void(TSystemUpdate)(World *, const set<unsigned int> *index);