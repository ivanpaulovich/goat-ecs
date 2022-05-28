#include <foo/queryBuilder.h>
#include <foo/query.h>
#include <foo/world.fwd.h>
#include <foo/world.h>

QueryBuilder::QueryBuilder(World *world)
{
    m_world = world;
    m_query = new Query();
}

template <typename T>
QueryBuilder *QueryBuilder::Include()
{
    auto key = m_world->Key<T>();
    m_query->Include(key);
    return this;
}

QueryBuilder *QueryBuilder::Ready()
{
    m_world->AddQuery(m_query->GetInclude());
    return this;
}

unsigned int QueryBuilder::GetQuery()
{
    return m_query->GetInclude();
}