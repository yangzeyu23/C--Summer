#ifndef _ABSTRACT_LINKED_LIST_H_
#define _ABSTRACT_LINKED_LIST_H_

#include "AbstractLinkedList.cpp"

template <typename T>
class AbstractLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;
    int length;

public:
    AbstractLinkedList() : head(nullptr), length(0) {}
    virtual ~AbstractLinkedList() { clear(); }

    virtual void addAtHead(const T& value);
    virtual void addAtTail(const T& value);
    virtual bool removeAt(int index);
    virtual T getAt(int index) const;
    virtual void clear();
    bool isEmpty() const { return length == 0; }
    int size() const { return length; }
};

#endif