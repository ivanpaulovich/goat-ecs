//#include <goat/entities.h>
#include <goat/key.h>

//#include <iostream>
#include <stdexcept>
//#include <vector>

using namespace std;

namespace goat {
Entities::Entities(const unsigned int size) {
  m_size = size;
  m_entities_count = 0;
  m_entities = new Key[m_size];
}

unsigned int Entities::newEntity() {
  if (m_entities_count == m_size) {
    throw std::exception();
  }

  int id = m_entities_count;

  while (id < m_size) {
    if (m_entities[id].getId() == 0) {
      m_entities_count++;
      return id;
    }

    id++;
  }

  id = 0;

  while (id < m_entities_count) {
    if (m_entities[id].getId() == 0) {
      m_entities_count++;
      return id;
    }

    id++;
  }

  throw std::exception();
}

Key *Entities::getEntity(const unsigned int id) { return &m_entities[id]; }

void Entities::destroy(const unsigned int id) {
  m_entities[id] = Key(0);
  m_entities_count--;
}

unsigned int Entities::getCount() { return m_entities_count; }

unsigned int Entities::getSize() { return m_size; }
}  // namespace goat
