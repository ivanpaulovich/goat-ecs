#include "query.h"

Query::Query()
{
    include = 0;
}

void Query::Include(unsigned int key)
{
    include |= key;
}

unsigned int Query::GetInclude()
{
    return include;
}