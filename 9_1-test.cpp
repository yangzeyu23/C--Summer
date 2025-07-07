#include <iostream>
#include "9_1-dynarrayOOP.h"

using namespace std;

void printElement(int *data)
{
    cout << *data << " ";
}

int main()
{
    int initialData[6] = {100, 200, 300, 400, 500, 600};

    cout << "Creating dynamic array 1 with capacity 10." << endl;
    Array array1(10);

    cout << "Adding element 600 to array 1." << endl;
    array1.add(600);
    cout << "Contents of array 1: ";
    array1.forEach(printElement);

    cout << "Adding elements 500 and 400 to array 1." << endl;
    array1.add(500);
    array1.add(400);
    cout << "Contents of array 1: ";
    array1.forEach(printElement);

    cout << "Creating dynamic array 2 and initializing with test data." << endl;
    Array array2(20, initialData, 6);
    cout << "Contents of array 2: ";
    array2.forEach(printElement);

    cout << "Creating dynamic array 3 using array 2 (copy constructor)." << endl;
    Array array3(array2);
    cout << "Contents of array 3: ";
    array3.forEach(printElement);

    cout << "Assigning array 1 to array 3." << endl;
    array3 = array1;
    cout << "Contents of array 3: ";
    array3.forEach(printElement);

    cout << "Accessing the second element of array 3: " << array3[1] << endl;

    cout << "Inserting element 133 at position 2 in array 3." << endl;
    array3.insertAt(1, 133);
    cout << "Contents of array 3: ";
    array3.forEach(printElement);

    cout << "Removing the element at position 3 in array 3." << endl;
    array3.removeAt(2);
    cout << "Contents of array 3: ";
    array3.forEach(printElement);

    return 0;
}