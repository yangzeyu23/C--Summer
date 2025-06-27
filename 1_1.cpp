#include <iostream>
using namespace std;
int GetInteger(int idx);

//编写程序，接受用户输入的10个整数，输出它们的和。
int main() 
{
    int num, sum = 0;
    cout << "This program will calculate the sum of 10 integers." << endl;
    
    for (int n=1; n <= 10; n++) {
        num = GetInteger(n);
        sum += num;
    }

    cout << "The sum of the 10 integers is: " << sum << endl;
    system("pause");
    return 0;
}

int GetInteger(int idx) 
{
    int n;
    cout << "No." << idx << ": ";
    cin >> n;
    return n;
}