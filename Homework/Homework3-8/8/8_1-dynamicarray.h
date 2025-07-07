//实现动态数组的接口

#ifndef _ARRAY_LIBRARY_H_
#define _ARRAY_LIBRARY_H_

struct Array;
typedef struct Array* ArrayPtr;

ArrayPtr CreateArray(int size);
int ArraySize(const ArrayPtr& arr);
int* ArrayData(const ArrayPtr& arr);
void FillArray(ArrayPtr& arr);
void PrintArray(const ArrayPtr& arr);
void SwapValues(ArrayPtr& arr, int idx1, int idx2);
void SortArray(ArrayPtr& arr);
int SearchArray(const ArrayPtr& arr, int value);
void ResizeArray(ArrayPtr& arr, int newSize);
void AddElements(ArrayPtr& arr, int count);
void InsertElement(ArrayPtr& arr, int index, int value);
void RemoveElements(ArrayPtr& arr, int count);
void RemoveAtIndex(ArrayPtr& arr, int index);
void UpdateElement(ArrayPtr& arr, int index, int value);

#endif