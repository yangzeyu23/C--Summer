#include <iostream>
using namespace std;

unsigned int n, k;
unsigned int binom(int n, int k);

//设计算法，分别使用循环和递归两种策略求二项式系数C(n,k)。其中，n为自然数，k为不大于n的非负整数。
int main() {

    cout << "Enter n: ";
    cin >> n; 
    cout << "Enter k: ";
    cin >> k;

    if ( n < 0 ||k < 0 || k > n) {
        cout << "Invalid input." << endl;
        return 1;
    }

    // 循环
    unsigned result = 1;
    for (int i = 1; i <= k; i++) 
    {
        result *= (n - i + 1);
        result /= i ;
    }
    cout << "循环结果:C(" << n << "," << k << ") = " << result << endl;

    // 递归
    cout << "递归结果:C(" << n << "," << k << ") = " << binom(n, k) << endl;

    return 0;
}

unsigned int binom(int n, int k) {
        if (k == 0 || k == n) {
            return 1;
        }
        return binom(n - 1, k - 1) + binom(n - 1, k);
    }