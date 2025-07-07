//测试动态数组库功能

#include <iostream>
#include "8_1-dynamicarray.h"

int main() 
{
    // 创建动态数组
    auto arr = CreateArray(6);
    std::cout << "Dynamic array created with size: " << ArraySize(arr) << std::endl;

    // 初始化数组元素
    FillArray(arr);
    std::cout << "Array elements initialized:" << std::endl;
    PrintArray(arr);

    // 测试交换元素
    std::cout << "Swapping elements at index 2 and 3:" << std::endl;
    SwapValues(arr, 2, 3);
    PrintArray(arr);

    // 测试冒泡排序
    std::cout << "Sorting the array using bubble sort:" << std::endl;
    SortArray(arr);
    PrintArray(arr);

    // 测试二分查找
    std::cout << "Searching for element 3 in the array:" << std::endl;
    int index = SearchArray(arr, 3);
    if (index != -1) 
    {
        std::cout << "Element found at index: " << index << std::endl;
    } 
    else 
    {
        std::cout << "Element not found." << std::endl;
    }

    // 测试数组大小调整
    std::cout << "Resizing the array to size 8:" << std::endl;
    ResizeArray(arr, 8);
    PrintArray(arr);

    // 测试更新元素
    std::cout << "Updating element at index 6 to value 10:" << std::endl;
    UpdateElement(arr, 6, 10);
    PrintArray(arr);

    // 测试插入元素
    std::cout << "Inserting element 50 at index 7:" << std::endl;
    InsertElement(arr, 7, 50);
    PrintArray(arr);

    // 测试删除元素
    std::cout << "Removing 2 elements from the end of the array:" << std::endl;
    RemoveElements(arr, 2);
    PrintArray(arr);

    std::cout << "Removing element at index 1:" << std::endl;
    RemoveAtIndex(arr, 1);
    PrintArray(arr);

    // 释放动态数组
    delete[] ArrayData(arr);
    delete arr;

    return 0;
}