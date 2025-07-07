#include "MemoryManager.h"
#include <cassert>

class Dummy : public MemoryManager 
{
public:
    int value;
    Dummy(int v) : value(v) {}
};

void testMemoryAllocation() 
{
    Dummy* obj = new Dummy(100);
    assert(obj->value == 100);
    MemoryManager::printMemoryUsage();
    delete obj;
    MemoryManager::printMemoryUsage();
}

int main() 
{
    std::cout << "Running memory management tests...\n";
    testMemoryAllocation();
    std::cout << "All tests passed!\n";
    return 0;
}
