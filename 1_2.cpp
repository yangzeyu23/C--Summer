#include <iostream>
using namespace std;

//编制程序完成下述任务。接受两个数，一个为用户一年期定期存款金额，一个为按照百分比格式表示的一年期定期存款年利率。程序计算一年期满后本金与利息总额，要求结果精确到分。
int main() 
{
    double principal, rate, total;

    cout << "Enter the principal amount for a one-year fixed deposit: ";
    cin >> principal;
    
    cout << "Enter the annual interest rate (in percentage): ";
    cin >> rate;

    rate /= 100;
    total = principal * (1 + rate);

    printf("Total amount after one year (including interest): %.2f\n", total);

    system("pause");
    return 0;
}