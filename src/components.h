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
#include "component.h"

class Components
{
private:
    std::map<unsigned int, Component *> m_values;

public:
    template <typename T>
    void Key(const unsigned int key, const unsigned int size);

    template <typename T>
    T *GetComponents(const unsigned int key);

    template <typename T>
    T *GetComponent(const unsigned int key, const unsigned int id);

    template <typename T>
    void SetComponent(const unsigned int key, const unsigned int id, const T value);
};