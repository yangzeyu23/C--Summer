#include <iostream>
#include <ctime>
using namespace std;

//设计并实现有理数库。使用整数表示有理数的分子与分母，完成有理数的加减乘除与化简运算。
int main() 
{
    
    srand(static_cast<unsigned int>(time(0)));

    
    int numerator1 = rand() % 100 + 1; // 分子1，范围1-100
    int denominator1 = rand() % 100 + 1; // 分母1，范围1-100
    int numerator2 = rand() % 100 + 1; // 分子2，范围1-100
    int denominator2 = rand() % 100 + 1; // 分母2，范围1-100

    cout << "有理数1: " << numerator1 << "/" << denominator1 << endl;
    cout << "有理数2: " << numerator2 << "/" << denominator2 << endl;

    return 0;
}