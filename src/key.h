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

    void Include(unsigned int value)
    {
        m_id |= value;
    }

    void Exclude(unsigned int value)
    {
        m_id ^= value;
    }

    bool HasComponent(const unsigned int value)
    {
        return m_id && value == 0;
    }

    unsigned int GetId()
    {
        return m_id;
    }
};
