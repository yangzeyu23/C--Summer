#include <iostream>
using namespace std;

//设计算法，将某个大于1的自然数n分解为其素因子的乘积，如6=2*3，7=7，8=2*2*2。
int main() {
    unsigned int n;
    cout << "This program gets a number greater than 1 and decomposes it into its prime factors." << endl;
    cout << "Please enter a number: ";
    cin >> n;

    if (n <= 1) {
        cout << "The number must be greater than 1." << endl;
        return 1;
    }

    cout << "The prime factorization of " << n << " is: ";
    for (unsigned int i = 2; i <= n; i++) {
        while (n % i == 0) {
            cout << i << (n == i ? "" : "*");
            n /= i;
        }
    }

    return 0;
}