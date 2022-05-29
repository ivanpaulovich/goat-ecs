#pragma once

class Query
{
private:
    unsigned int include;

public:
    Query();

    void Include(unsigned int key);

    unsigned int GetInclude();
};