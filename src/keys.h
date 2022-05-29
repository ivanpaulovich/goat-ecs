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
    unsigned int Key()
    {
        TypeInfoRef type = typeid(T);
        if (m_keys.find(type) != m_keys.end())
        {
            return m_keys[type];
        }

        unsigned int key = 1 << m_keys.size();
        m_keys[type] = key;

        return key;
    }
};