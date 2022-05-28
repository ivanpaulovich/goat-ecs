#include <foo/component.h>
#include <foo/components.h>

template <typename T>
void Components::Key(const unsigned int key, const unsigned int size)
{
    Component *component = new Component();
    component->Init<T>(size);
    m_values[key] = component;
}

template <typename T>
T *Components::GetComponents(const unsigned int key)
{
    auto component = m_values[key];
    auto values = static_cast<T *>(component->GetValues<T>());
    return values;
}

template <typename T>
T *Components::GetComponent(const unsigned int key, const unsigned int id)
{
    auto values = GetComponents<T>(key);
    return &values[id];
}

template <typename T>
void Components::SetComponent(const unsigned int key, const unsigned int id, const T value)
{
    auto values = GetComponents<T>(key);
    values[id] = value;
}