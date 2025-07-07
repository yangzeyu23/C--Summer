//实现动态数组库

#include <iostream>
#include <cstdlib>
#include "8_1-dynamicarray.h"

struct Array 
{
    int size;
    int* data;
};

ArrayPtr CreateArray(int size) 
{
    auto arr = new Array;
    arr->size = size;
    arr->data = new int[size];
    return arr;
}

int ArraySize(const ArrayPtr& arr) 
{
    return arr->size;
}

int* ArrayData(const ArrayPtr& arr) 
{
    return arr->data;
}

void FillArray(ArrayPtr& arr) 
{
    int len = ArraySize(arr);
    int* data = ArrayData(arr);
    std::cout << "Please input " << len << " elements: ";

    for (int i = 0; i < len; ++i) {
        std::cin >> data[i];
    }
}

void PrintArray(const ArrayPtr& arr) {
    int* data = ArrayData(arr);
    int len = ArraySize(arr);

    for (int i = 0; i < len; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}

void SwapValues(ArrayPtr& arr, int idx1, int idx2) {
    int len = ArraySize(arr);

    if (idx1 < 0 || idx1 >= len || idx2 < 0 || idx2 >= len) {
        std::cerr << "Invalid indices!" << std::endl;
        exit(1);
    }
    int* data = ArrayData(arr);
    std::swap(data[idx1], data[idx2]);
}

void SortArray(ArrayPtr& arr) {
    int len = ArraySize(arr);
    int* data = ArrayData(arr);
    
    for (int i = 0; i < len - 1; ++i) {
        for (int j = 0; j < len - i - 1; ++j) {
            if (data[j] > data[j + 1]) {
                SwapValues(arr, j, j + 1);
            }
        }
    }
}

int SearchArray(const ArrayPtr& arr, int value) {
    int len = ArraySize(arr);
    int* data = ArrayData(arr);
    int low = 0, high = len - 1;
    
    while (low <= high) {
        int mid = (low + high) / 2;
        if (data[mid] == value) 
        {
            return mid;
        } 
        else if (data[mid] < value) 
        {
            low = mid + 1;
        } 
        else 
        {
            high = mid - 1;
        }
    }
    return -1;
}

void ResizeArray(ArrayPtr& arr, int newSize) {
    int oldSize = ArraySize(arr);
    int* newData = new int[newSize];
    int copySize = (oldSize < newSize) ? oldSize : newSize;
    int* oldData = ArrayData(arr);
    
    for (int i = 0; i < copySize; ++i) {
        newData[i] = oldData[i];
    }
    for (int i = oldSize; i < newSize; ++i) {
        newData[i] = 0;
    }
    delete[] arr->data;
    arr->data = newData;
    arr->size = newSize;
}

void AddElements(ArrayPtr& arr, int count) {
    ResizeArray(arr, ArraySize(arr) + count);
}

void InsertElement(ArrayPtr& arr, int index, int value) {
    int len = ArraySize(arr);
    if (index < 0 || index > len) {
        std::cerr << "Invalid index!" << std::endl;
        exit(1);
    }
    ResizeArray(arr, len + 1);
    int* data = ArrayData(arr);
    for (int i = len; i > index; --i) {
        data[i] = data[i - 1];
    }
    data[index] = value;
}

void RemoveElements(ArrayPtr& arr, int count) {
    int len = ArraySize(arr);
    if (count > len) 
    {
        std::cerr << "Invalid count!" << std::endl;
        exit(1);
    }
    ResizeArray(arr, len - count);
}

void RemoveAtIndex(ArrayPtr& arr, int index) {
    int len = ArraySize(arr);
    if (index < 0 || index >= len) 
    {
        std::cerr << "Invalid index!" << std::endl;
        exit(1);
    }
    int* data = ArrayData(arr);
    for (int i = index; i < len - 1; ++i) {
        data[i] = data[i + 1];
    }
    ResizeArray(arr, len - 1);
}

void UpdateElement(ArrayPtr& arr, int index, int value) {
    int len = ArraySize(arr);
    if (index < 0 || index >= len) 
    {
        std::cerr << "Invalid index!" << std::endl;
        exit(1);
    }
    int* data = ArrayData(arr);
    data[index] = value;
}