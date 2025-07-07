#include <iostream>
#include <cstdlib>
#include <cstring>
#include "8_2-dynamiclist.h"
#include "8_2-point.h"

using namespace std;

void PrintElement(ElementType e, ElementType tag)
{
    cout << PtTransformIntoString((const char *)tag, (POINT)e) << " -> ";
}

void DestroyElement(ElementType e)
{
    PtDestroy((POINT)e);
}

int CompareElements(ConstElementType e1, ConstElementType e2)
{
    return PtCompare((POINT)e1, (POINT)e2);
}

int main()
{
    PLinkedList list = CreateList();

    if (IsListEmpty(list))
    {
        cout << "The list is empty." << endl;
    }

    POINT point1 = PtCreate(1.0, 2.0);
    AppendToList(list, (ElementType)point1);
    cout << "List contents: ";
    TraverseList(list, PrintElement, (ElementType)"(%lf, %lf)");
    cout << endl;

    AppendToList(list, (ElementType)PtCreate(5.0, 6.0));
    AppendToList(list, (ElementType)PtCreate(7.0, 8.0));
    AppendToList(list, (ElementType)PtCreate(9.0, 10.0));
    TraverseList(list, PrintElement, (ElementType)"(%lf, %lf)");
    cout << endl;

    InsertIntoList(list, (ElementType)PtCreate(3.0, 4.0), 2);
    TraverseList(list, PrintElement, (ElementType)"(%lf, %lf)");
    cout << endl;

    cout << "List size: " << GetListSize(list) << endl;

    if (SearchInList(list, (ElementType)PtCreate(7.0, 8.0), CompareElements))
    {
        cout << "Element found!" << endl;
    }
    else
    {
        cout << "Element not found." << endl;
    }

    RemoveFromList(list, 1, DestroyElement);
    TraverseList(list, PrintElement, (ElementType)"(%lf, %lf)");
    cout << endl;

    cout << "List size after removal: " << GetListSize(list) << endl;

    DestroyList(list, DestroyElement);

    return 0;
}