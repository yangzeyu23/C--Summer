#ifndef _DYNLIST_OOP_H_
#define _DYNLIST_OOP_H_

typedef void* AbstractData;

class Element {
public:
    AbstractData value;
    Element* next;

    void display(void (*func)(AbstractData));
};

class DynamicList {
private:
    Element* head;
    int length;

public:
    DynamicList();
    ~DynamicList();

    void clear();
    bool isEmpty() const;
    bool addAtHead(Element* elem);
    bool addAtTail(Element* elem);
    bool addAt(int index, Element* elem);
    bool removeAt(int index, Element* elem);
    bool getAt(int index, Element* elem);
    int find(Element* elem) const;
    bool getPrevious(Element* current, Element* previous);
    bool getNext(Element* current, Element* next);
    void traverse(void (*func)(AbstractData)) const;
};

void printInt(AbstractData data);

#endif