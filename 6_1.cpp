#include <iostream>
using namespace std;

//编写函数Sort，对包含n个元素的整数数组a，按从小到大顺序排序。此问题有多种算法，不同算法的效率可能不同。
void Sort(int a[], int n);

int main() {
    int n;
    cout << "请输入数组的元素个数: ";
    cin >> n;

    int* a = new int[n];
    cout << "请输入数组的元素: ";
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    Sort(a, n);

    cout << "排序后的数组为: ";
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

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
