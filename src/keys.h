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
#include "typeInfoRef.h"

class Keys
{
private:
    unordered_map<TypeInfoRef, unsigned int, Hasher, EqualTo> m_keys;
public:
    template <typename T>
    unsigned int Key();
};