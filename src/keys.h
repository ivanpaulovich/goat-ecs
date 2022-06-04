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
#include "type-info-ref.h"
#include "key.h"

namespace goat
{
    class Keys
    {
    private:
        unordered_map<TypeInfoRef, Key, Hasher, EqualTo> m_keys;

    public:
        template <typename T>
        Key getKey()
        {
            TypeInfoRef type = typeid(T);
            if (m_keys.find(type) != m_keys.end())
            {
                return m_keys[type];
            }

            unsigned int key = 1 << m_keys.size();
            m_keys[type] = Key(key);

            return key;
        }
    };
}
