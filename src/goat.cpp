#include <iostream>

class World
{
    public:
        World(int size);
        ~World();

    private:
        int _size;
        int _count;
};

void say_hello(){
    std::cout << "Hello, from goat!\n";
}
