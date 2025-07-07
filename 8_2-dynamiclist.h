#ifndef DYNLIST_H
#define DYNLIST_H

typedef struct LinkedList * PLinkedList;

typedef void * ElementType;
typedef const void * ConstElementType;
typedef int (*CompareFunc)(ConstElementType e1, ConstElementType e2);
typedef void (*DestroyFunc)(ElementType e);
typedef void (*ManipulateFunc)(ElementType e, ElementType tag);

PLinkedList CreateList();
void DestroyList(PLinkedList list, DestroyFunc destroy);
void AppendToList(PLinkedList list, ElementType element);
void InsertIntoList(PLinkedList list, ElementType element, int position);
void RemoveFromList(PLinkedList list, int position, DestroyFunc destroy);
void ClearList(PLinkedList list, DestroyFunc destroy);
void TraverseList(PLinkedList list, ManipulateFunc manipulate, ElementType tag);
bool SearchInList(PLinkedList list, ElementType element, CompareFunc compare);
int GetListSize(PLinkedList list);
bool IsListEmpty(PLinkedList list);

#endif