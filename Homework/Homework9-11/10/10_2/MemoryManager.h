#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <iostream>
#include <cstdlib>
#include <new> 

class MemoryManager 
{
private:
    static size_t totalAllocated; 
    static size_t totalFreed;    

public:

    // 重载全局 new 操作符
    static void* operator new(size_t size) 
    {
        void* ptr = std::malloc(size); 
        if (!ptr) 
        {
            throw std::bad_alloc(); 
        }
        totalAllocated += size;
        std::cout << "[MemoryManager] Allocated " << size << " bytes. Total allocated: " << totalAllocated << " bytes.\n";
        return ptr;
    }

    // 重载全局 delete 操作符
    static void operator delete(void* ptr, size_t size) noexcept 
    {
        if (ptr) 
        {
            std::free(ptr); // 使用 free 释放内存
            totalFreed += size;
            std::cout << "[MemoryManager] Freed " << size << " bytes. Total freed: " << totalFreed << " bytes.\n";
        }
    }

    // 获取当前内存使用情况
    static void printMemoryUsage() 
    {
        std::cout << "[MemoryManager] Current memory usage: " << (totalAllocated - totalFreed) << " bytes.\n";
    }
};

// 初始化静态成员变量
size_t MemoryManager::totalAllocated = 0;
size_t MemoryManager::totalFreed = 0;

#endif