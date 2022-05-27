#include "keys.h"

template <typename T>
unsigned int Keys::Key()
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