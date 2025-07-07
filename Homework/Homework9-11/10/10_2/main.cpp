#include "MemoryManager.h"

class Test : public MemoryManager 
{
private:
    int data;

public:
    Test(int value) : data(value) {
        std::cout << "[Test] Constructor called with value: " << value << "\n";
    }

    ~Test() {
        std::cout << "[Test] Destructor called for value: " << data << "\n";
    }
};

int main() 
{
    std::cout << "=== Dynamic Memory Management Test ===\n";

    Test* obj1 = new Test(42);
    MemoryManager::printMemoryUsage();

    Test* obj2 = new Test(84);
    MemoryManager::printMemoryUsage();

    delete obj1;
    MemoryManager::printMemoryUsage();

    delete obj2;
    MemoryManager::printMemoryUsage();

    std::cout << "=== Test Completed ===\n";
    return 0;
}