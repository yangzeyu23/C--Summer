#include <iostream>
#include <ctime>
using namespace std;

void Sort(int a[], int n);

//编写函数Search，对于已排序的包含n个元素的整数数组a，在其中查找整数key。如果该整数在数组中，函数返回true，否则返回false。
bool Search(int a[], int n, int key);

int main() 
{
    int n, key;
    cout << "请输入数组的元素个数: ";
    cin >> n;

    srand(time(0)); 
    int* a = new int[n];
    for (int i = 0; i < n; i++) {
         a[i]= rand() % 100; 
    }
    cout << "生成的随机数组为: ";
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    Sort(a, n);

    cout << "已排序的数组为:   ";
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    cout << "请输入要查找的整数: ";
    cin >> key;

    if (Search(a, n, key)) {
        cout << "整数" << key << "存在。" << endl;
    } else {
        cout << "整数" << key << "不存在。" << endl;
    }

    delete[] a;
    return 0;
}


void Sort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = 0; j < n - i - 1; j++) 
        {
            if (a[j] > a[j + 1]) 
            {
                swap(a[j], a[j + 1]);
            }
        }
    }
}

bool Search(int a[], int n, int key) {
    int left = 0, right = n - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;  
        if (a[mid] == key) {
            return true;
        } 
        else if (a[mid] < key) {
            left = mid + 1; 
        } 
        else {
            right = mid - 1; 
        }
    }
    return false; 
}