#ifndef _ABSTRACT_LINKED_LIST_H_
#define _ABSTRACT_LINKED_LIST_H_

#include <stdexcept>

template <typename T>
class AbstractLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(T value) : data(value), next(nullptr) {}
    };

    Node* head;
    int length;

public:
    AbstractLinkedList() : head(nullptr), length(0) {}
    virtual ~AbstractLinkedList() { clear(); }

    virtual void addAtHead(T value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        length++;
    }

    virtual void addAtTail(T value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        length++;
    }

    virtual bool removeAt(int index) {
        if (index < 0 || index >= length) return false;

        Node* current = head;
        if (index == 0) {
            head = current->next;
            delete current;
        } else {
            Node* previous = nullptr;
            for (int i = 0; i < index; i++) {
                previous = current;
                current = current->next;
            }
            previous->next = current->next;
            delete current;
        }
        length--;
        return true;
    }

    virtual bool getAt(int index, T& value) const {
        if (index < 0 || index >= length) return false;

        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        value = current->data;
        return true;
    }

    virtual void traverse(void (*func)(T)) const {
        Node* current = head;
        while (current != nullptr) {
            func(current->data);
            current = current->next;
        }
    }

    virtual void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        length = 0;
    }

    int size() const {
        return length;
    }

    bool isEmpty() const {
        return length == 0;
    }
};

#endif