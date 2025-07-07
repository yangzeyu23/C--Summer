#include <iostream>
#include "8_2-dynamiclist.h"

struct Node
{
    ElementType value;
    Node* next;
};

struct LinkedList
{
    int size;
    Node* head;
    Node* tail;
};

PLinkedList CreateList()
{
    PLinkedList list = new LinkedList;
    list->size = 0;
    list->head = nullptr;
    list->tail = nullptr;
    return list;
}

void DestroyList(PLinkedList list, DestroyFunc destroy)
{
    if (list)
    {
        ClearList(list, destroy);
        delete list;
    }
}

void AppendToList(PLinkedList list, ElementType element)
{
    if (!list || !element)
    {
        exit(1);
    }

    Node* newNode = new Node;
    newNode->value = element;
    newNode->next = nullptr;

    if (list->size == 0)
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        list->tail->next = newNode;
        list->tail = newNode;
    }
    list->size++;
}

void InsertIntoList(PLinkedList list, ElementType element, int position)
{
    if (!list || !element)
    {
        exit(1);
    }

    if (position < list->size)
    {
        Node* newNode = new Node;
        newNode->value = element;

        if (position == 0)
        {
            newNode->next = list->head;
            list->head = newNode;
        }
        else
        {
            Node* current = list->head;
            for (int i = 1; i < position; ++i)
            {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
        list->size++;
    }
    else
    {
        AppendToList(list, element);
    }
}

void RemoveFromList(PLinkedList list, int position, DestroyFunc destroy)
{
    if (!list || list->size == 0)
    {
        return;
    }

    if (position < list->size)
    {
        Node* current = list->head;

        if (position == 0)
        {
            list->head = current->next;
            if (list->head == nullptr)
            {
                list->tail = nullptr;
            }
            if (destroy)
            {
                destroy(current->value);
            }
            delete current;
        }
        else
        {
            for (int i = 0; i < position - 1; ++i)
            {
                current = current->next;
            }
            Node* toDelete = current->next;
            current->next = toDelete->next;
            if (toDelete->next == nullptr)
            {
                list->tail = current;
            }
            if (destroy)
            {
                destroy(toDelete->value);
            }
            delete toDelete;
        }
        list->size--;
    }
}

void ClearList(PLinkedList list, DestroyFunc destroy)
{
    while (list->head)
    {
        Node* current = list->head;
        list->head = current->next;
        if (destroy)
        {
            destroy(current->value);
        }
        delete current;
    }
    list->tail = nullptr;
    list->size = 0;
}

void TraverseList(PLinkedList list, ManipulateFunc manipulate, ElementType tag)
{
    if (!list)
    {
        exit(1);
    }

    Node* current = list->head;
    while (current)
    {
        if (manipulate)
        {
            manipulate(current->value, tag);
        }
        current = current->next;
    }
}

bool SearchInList(PLinkedList list, ElementType element, CompareFunc compare)
{
    if (!list || !element)
    {
        exit(1);
    }

    Node* current = list->head;
    while (current)
    {
        if (compare(current->value, element))
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

int GetListSize(PLinkedList list)
{
    return list->size;
}

bool IsListEmpty(PLinkedList list)
{
    return list->size == 0;
}