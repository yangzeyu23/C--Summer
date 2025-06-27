#include <iostream>
using namespace std;
int func( int x );

int main()
{
  int i;
  for( i = 1; i < 6; i++ )
    cout << "Invoke func " << i << " time(s): Return " <<  func(i) << ".\n";
  return 0;
}
int func( int x )
{
  static int count = 0;  /* 定义静态局部变量count，函数结束后仍存在 */
  cout << "x = " << x << ".\n";
  return ++count;
}
