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

using namespace std;

using TypeInfoRef = reference_wrapper<const type_info>;
 
struct Hasher {
    size_t operator()(TypeInfoRef code) const
    {
        return code.get().hash_code();
    }
};
 
struct EqualTo {
    bool operator()(TypeInfoRef lhs, TypeInfoRef rhs) const
    {
        return lhs.get() == rhs.get();
    }
};

class World;

typedef void (TSystemUpdate)(World, unsigned int*);

struct Component {

};

struct Query
{
    unsigned int *include;
    unsigned int *exclude;
};

class World
{
private:
    unsigned int m_size;
    unsigned int m_entities_count;
    unsigned int* m_entities;
    unordered_map<TypeInfoRef, unsigned int, Hasher, EqualTo> m_keys;
    map<unsigned int, Component*> m_values;
    map<Query, unsigned int*> m_indexes;
    vector<TSystemUpdate*> m_systems;

public:
    World(unsigned int size)
    {
        m_size = size;
        m_entities = new unsigned int(size);
    }

    template<typename T>
    unsigned int Key() {
        TypeInfoRef type = typeid(T);
        if (m_keys.find(type) != m_keys.end()) {
            return m_keys[type];
        }

        unsigned int key = 1 << m_keys.size();
        m_keys[type] = key;
        T* components = new T[m_size];
        m_values[key] = components;

        return key;
    }

    template<typename T>
    T* GetComponents() {
        unsigned int key = Key<T>();
        return static_cast<T*>(m_values[key]);
    }

    // template<typename T>
    // void BuildComponents() {
    //     unsigned int key = Key<T>();
        
    // }

    unsigned int NewEntity() {
        int id = m_entities_count++;

        // for (auto &componentPair : m_keys) {
        //     componentPair.second++;
        // }

        return id;
    }

    // template<typename T>
    // inline T& getComponent() const {
    //     auto ptr(compArray[getComponentTypeID<T>()]);
    //     return *static_cast<T*>(ptr);
    // }

    // template<typename T>
    // void setComponent(const T component) {
    //     unsigned int key = Key(typeid(T));
    // }

    // void SetComponent(const Component component) {
    //     unsigned int key = Key(typeid(component));
    //     m_values[key] = new Component[m_size];
    // }
};
