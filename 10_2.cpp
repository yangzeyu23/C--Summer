#include <iostream>
#include <cstdlib>
#include <new>
using namespace std;

//new与delete操作符可以被重载。研究存储管理技术，重载这两个操作符以实现程序独有的动态存储管理策略。
class CustomMemoryManager 
{
private:
    static size_t totalAllocated; 

public:
    static void* operator new(size_t size) 
    {
        void* ptr = malloc(size);
        if (!ptr) {
            throw bad_alloc();
        }
        totalAllocated += size;
        cout << "Custom new: Allocated " << size << " bytes. Total allocated: " << totalAllocated << " bytes." << endl;
        return ptr;
    }

    static void operator delete(void* ptr, size_t size) 
    {
        free(ptr);
        totalAllocated -= size;
        cout << "Custom delete: Freed " << size << " bytes. Total allocated: " << totalAllocated << " bytes." << endl;
    }

    static void* operator new[](size_t size)
    {
        void* ptr = malloc(size);
        if (!ptr) {
            throw bad_alloc();
        }
        totalAllocated += size;
        cout << "Custom new[]: Allocated " << size << " bytes. Total allocated: " << totalAllocated << " bytes." << endl;
        return ptr;
    }

    static void operator delete[](void* ptr, size_t size) 
    {
        free(ptr);
        totalAllocated -= size;
        cout << "Custom delete[]: Freed " << size << " bytes. Total allocated: " << totalAllocated << " bytes." << endl;
    }
};

// 初始化静态变量
size_t CustomMemoryManager::totalAllocated = 0;

// 测试自定义内存管理
int main() 
{
    try {
        cout << "Creating a single object using custom new." << endl;
        CustomMemoryManager* obj = new CustomMemoryManager;

        cout << "Deleting the single object using custom delete." << endl;
        delete obj;

        cout << "Creating an array of objects using custom new[]." << endl;
        CustomMemoryManager* objArray = new CustomMemoryManager[5];

        cout << "Deleting the array of objects using custom delete[]." << endl;
        delete[] objArray;

    } catch (const bad_alloc& e) {
        cout << "Memory allocation failed: " << e.what() << endl;
    }

    return 0;
}