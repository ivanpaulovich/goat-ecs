#pragma once

#include <set>
#include "world.fwd.h"

namespace goat
{
    typedef void(TSystemUpdate)(World *, const set<unsigned int> *index);
}
