#pragma once

#include <map>

namespace goat
{
    class Components
    {
    private:
        std::map<unsigned int, void *> m_values;

    public:
        template <typename T>
        void key(const unsigned int key, const unsigned int size)
        {
            T *component = new T[size];
            m_values[key] = component;
        }

        template <typename T>
        T *getComponents(const unsigned int key)
        {
            auto component = m_values[key];
            auto values = static_cast<T *>(component);
            return values;
        }

        template <typename T>
        T *getComponent(const unsigned int key, const unsigned int id)
        {
            auto values = getComponents<T>(key);
            return values[id];
        }

        template <typename T>
        void setComponent(const unsigned int key, const unsigned int id, const T value)
        {
            auto values = getComponents<T>(key);
            values[id] = value;
        }
    };

}
