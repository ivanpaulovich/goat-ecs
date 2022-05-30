#pragma once

class Component
{
private:
    void *m_values;
public:
    template <typename T>
    void Init(const unsigned int size)
    {
        m_values = new T[size];
    }

    template <typename T>
    T *GetValues()
    {
        return static_cast<T *>(m_values);
    }
};