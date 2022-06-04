#pragma once

#include <iostream>
#include <typeinfo>

using namespace std;

using TypeInfoRef = reference_wrapper<const type_info>;

namespace goat
{
    struct Hasher
    {
        unsigned int operator()(TypeInfoRef code) const
        {
            return code.get().hash_code();
        }
    };

    struct EqualTo
    {
        bool operator()(TypeInfoRef lhs, TypeInfoRef rhs) const
        {
            return lhs.get() == rhs.get();
        }
    };
}
