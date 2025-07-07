#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "9_1-dynarrayOOP.h"

Array::Array(const Array &other): maxCapacity(other.maxCapacity), currentSize(other.currentSize)
{
    if (other.data)
    {
        data = new int[currentSize];
        if (!data)
        {
            printf("Memory allocation failed.\n");
            exit(1);
        }
        memcpy(data, other.data, sizeof(int) * currentSize);
    }
    else
    {
        data = nullptr;
    }
}

Array::Array(int capacity, int *elements, int count): maxCapacity(capacity), currentSize(count)
{
    if (maxCapacity < count)
    {
        printf("Capacity is less than the number of elements.\n");
        exit(2);
    }

    data = new int[maxCapacity];
    if (!data)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    memcpy(data, elements, sizeof(int) * count);
}

Array &Array::operator=(const Array &other)
{
    if (this == &other)
    {
        return *this;
    }

    if (data)
    {
        delete[] data;
    }

    currentSize = other.currentSize;
    data = new int[currentSize];
    if (!data)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    memcpy(data, other.data, sizeof(int) * currentSize);

    return *this;
}

void Array::add(int value)
{
    if (currentSize + 1 > maxCapacity)
    {
        printf("Exceeded maximum capacity.\n");
        exit(2);
    }

    int *temp = new int[currentSize + 1];
    if (!temp)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    if (data)
    {
        memcpy(temp, data, sizeof(int) * currentSize);
        delete[] data;
    }

    temp[currentSize++] = value;
    data = temp;
}

int Array::size() const
{
    return currentSize;
}

void Array::forEach(void (*func)(int*))
{
    for (int i = 0; i < currentSize; ++i)
    {
        func(&data[i]);
    }
    printf("\n");
}

void Array::insertAt(int index, int value)
{
    if (index < 0 || index > currentSize)
    {
        printf("Index out of bounds.\n");
        exit(2);
    }

    int *temp = new int[currentSize + 1];
    if (!temp)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    for (int i = 0; i < index; ++i)
    {
        temp[i] = data[i];
    }

    temp[index] = value;

    for (int i = index; i < currentSize; ++i)
    {
        temp[i + 1] = data[i];
    }

    delete[] data;
    data = temp;
    currentSize++;
}

void Array::removeAt(int index)
{
    if (index < 0 || index >= currentSize)
    {
        printf("Index out of bounds.\n");
        exit(2);
    }

    int *temp = new int[currentSize - 1];
    if (!temp)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    for (int i = 0; i < index; ++i)
    {
        temp[i] = data[i];
    }

    for (int i = index + 1; i < currentSize; ++i)
    {
        temp[i - 1] = data[i];
    }

    delete[] data;
    data = temp;
    currentSize--;
}