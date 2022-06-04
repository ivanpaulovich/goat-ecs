#pragma once

class Key
{
private:
    unsigned int m_id;
public:
    Key()
    {
        m_id = 0;
    }

    Key(unsigned int id)
    {
        m_id = id;
    }

    void include(unsigned int value)
    {
        m_id |= value;
    }

    void exclude(unsigned int value)
    {
        m_id ^= value;
    }

    bool hasComponent(const unsigned int value)
    {
        return m_id && value == 0;
    }

    unsigned int getId()
    {
        return m_id;
    }
};
