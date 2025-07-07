#include <iostream>
using namespace std;

int main()
{
  int a;
  int & ref = a;
  a = 5;
  cout << "a: " << a << endl;  cout << "ref: " << ref << endl;
  ref = 8;
  cout << "a: " << a << endl;  cout << "ref: " << ref << endl;
  return 0;
}
