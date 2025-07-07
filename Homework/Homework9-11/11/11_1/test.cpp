#include <iostream>
#include "AbstractLinkedList.h"

int main() 
{
    AbstractLinkedList<int> intList;

    // Adding elements to the list

    intList.addAtHead(1);
    intList.addAtTail(2);
    intList.addAtTail(3);


    // Displaying elements

    std::cout << "List after adding elements: ";
    intList.traverse([](int data) { std::cout << data << " "; });
    std::cout << std::endl;


    // Removing an element
    intList.removeAt(0); 


    // Displaying elements after removal

    std::cout << "List after removing element at index 0: ";
    intList.traverse([](int data) { std::cout << data << " "; });
    std::cout << std::endl;


    // Getting an element

    int value;
    if (intList.getAt(1, value)) {
        std::cout << "Element at index 1: " << value << std::endl;
    }

    
    // Clearing the list

    intList.clear();
    std::cout << "List cleared. Is it empty?—— " << (intList.isEmpty() ? "Yes" : "No") << std::endl;

    return 0;
}