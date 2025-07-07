#include <iostream> 
#include <cstdlib>
#include "9_2-dynlistOOP.h"

using namespace std;

int convertToInt(AbstractData data) {
    return *reinterpret_cast<int*>(data);
}

void printInt(AbstractData data) {
    cout << *reinterpret_cast<int*>(data) << " -> ";
}

void Element::display(void (*func)(AbstractData)) {
    func(value);
}

DynamicList::DynamicList() {
    head = new Element;
    head->value = nullptr;
    head->next = nullptr;
    length = 0;
}

DynamicList::~DynamicList() {
    clear();
    delete head;
    head = nullptr;
}

void DynamicList::clear() {
    Element* current = head->next;
    while (current != nullptr) {
        Element* temp = current->next;
        delete current;
        current = temp;
    }
    head->next = nullptr;
    length = 0;
}

bool DynamicList::isEmpty() const {
    return length == 0;
}

bool DynamicList::addAtHead(Element* elem) {
    Element* newElem = new Element;
    if (!newElem) return false;

    newElem->value = elem->value;
    newElem->next = head->next;
    head->next = newElem;
    length++;
    return true;
}

bool DynamicList::addAtTail(Element* elem) {
    Element* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }

    Element* newElem = new Element;
    if (!newElem) return false;

    newElem->value = elem->value;
    newElem->next = nullptr;
    current->next = newElem;
    length++;
    return true;
}

bool DynamicList::addAt(int index, Element* elem) {
    if (index < 0 || index > length) return false;

    Element* current = head;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }

    Element* newElem = new Element;
    if (!newElem) return false;

    newElem->value = elem->value;
    newElem->next = current->next;
    current->next = newElem;
    length++;
    return true;
}

bool DynamicList::removeAt(int index, Element* elem) {
    if (index < 0 || index >= length) return false;

    Element* current = head;
    Element* previous = nullptr;
    for (int i = 0; i <= index; ++i) {
        previous = current;
        current = current->next;
    }

    previous->next = current->next;
    elem->value = current->value;
    delete current;
    length--;
    return true;
}

bool DynamicList::getAt(int index, Element* elem) {
    if (index < 0 || index >= length) return false;

    Element* current = head;
    for (int i = 0; i <= index; ++i) {
        current = current->next;
    }

    elem->value = current->value;
    return true;
}

int DynamicList::find(Element* elem) const {
    Element* current = head->next;
    int position = 0;

    while (current != nullptr) {
        if (current->value == elem->value) {
            return position;
        }
        current = current->next;
        position++;
    }

    return -1;
}

bool DynamicList::getPrevious(Element* current, Element* previous) {
    Element* temp = head;
    Element* prev = nullptr;

    while (temp->next != nullptr) {
        prev = temp;
        temp = temp->next;

        if (temp->value == current->value) {
            if (prev == head) return false;

            previous->value = prev->value;
            return true;
        }
    }

    return false;
}

bool DynamicList::getNext(Element* current, Element* next) {
    Element* temp = head->next;

    while (temp != nullptr) {
        if (temp->value == current->value) {
            if (temp->next == nullptr) return false;

            next->value = temp->next->value;
            return true;
        }
        temp = temp->next;
    }

    return false;
}

void DynamicList::traverse(void (*func)(AbstractData)) const {
    Element* current = head->next;

    while (current != nullptr) {
        current->display(func);
        current = current->next;
    }

    cout << endl;
}