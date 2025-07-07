#ifndef _DYNAMIC_ARRAY_H_
#define _DYNAMIC_ARRAY_H_

class Array {
private:
    const int maxCapacity; // 最大容量
    int currentSize;       // 当前大小
    int *data;             // 数据指针

public:
    Array(int capacity): maxCapacity(capacity), currentSize(0), data(nullptr) {}

    Array(const Array &other);

    Array(int capacity, int *elements, int count);

    Array &operator=(const Array &other);

    ~Array()
    {
        if (data)
        {
            delete[] data;
        }
    }

    void add(int value);

    int size() const;

    int &operator[](int index) { return data[index]; }

    void forEach(void (*func)(int*));

    void insertAt(int index, int value);

    void removeAt(int index);
};

#endif