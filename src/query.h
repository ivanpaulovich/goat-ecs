#pragma once

class Query
{
public:
    unsigned int include;

    Query() {
        include = 0;
    }

    void Include(unsigned int key)
    {
        include |= key;
    }
};