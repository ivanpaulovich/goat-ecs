#pragma once

class Entities
{
private:
    unsigned int m_size;
    unsigned int m_entities_count;
    unsigned int *m_entities;

    void SetComponents(const unsigned int id, const unsigned int key);

public:
    Entities(const unsigned int size);

    unsigned int NewEntity();

    unsigned int GetEntity(const unsigned int id);

    unsigned int GetCount();

    unsigned int GetSize();

    bool HasComponent(const unsigned int id, const unsigned int key);

    void AddComponent(const unsigned int id, const unsigned int key);

    void RemoveComponent(const unsigned int id, const unsigned int key);
};