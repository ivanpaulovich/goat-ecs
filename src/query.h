#pragma once

class Query
{
private:
    unsigned int m_id;

public:
    Query(unsigned int id)
    {
        m_id = id;
    }

    void Include(unsigned int key)
    {
        m_id |= key;
    }

    void Exclude(unsigned int key)
    {
        m_id ^= key;
    }

    unsigned int GetId()
    {
        return m_id;
    }
};