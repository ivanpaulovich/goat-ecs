#include "component.h"

template <typename T>
void Component::Init(const unsigned int size)
{
    m_values = new T[size];
}

template <typename T>
T *Component::GetValues()
{
    return static_cast<T *>(m_values);
}