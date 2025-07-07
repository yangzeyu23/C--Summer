#include <iostream>
#include <cstdlib>
#include "9_2-dynlistOOP.h"

using namespace std;

int main() 
{
    int values[6] = {10, 20, 30, 40, 50, 60};

    cout << "Initializing elements with values." << endl;
    Element elem1, elem2, elem3, elem4, elem5, elem6;
    elem1.value = new int(values[0]);
    elem2.value = new int(values[1]);
    elem3.value = new int(values[2]);
    elem4.value = new int(values[3]);
    elem5.value = new int(values[4]);
    elem6.value = new int(values[5]);

    cout << "Creating a dynamic list and adding elements to the tail." << endl;
    DynamicList* list = new DynamicList();
    list->addAtTail(&elem1);
    list->addAtTail(&elem2);
    list->addAtTail(&elem3);
    list->addAtTail(&elem4);
    list->addAtTail(&elem5);

    cout << "Traversing the list: ";
    list->traverse(printInt);

    cout << "Inserting an element at position 2." << endl;
    list->addAt(2, &elem6);
    cout << "Getting the next element of the inserted element:" << endl;
    Element temp;
    list->getNext(&elem6, &temp);
    temp.display(printInt);
    cout << endl;

    delete list;

    return 0;
}