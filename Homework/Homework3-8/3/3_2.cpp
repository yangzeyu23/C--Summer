#include <iostream>
#include <math.h>
using namespace std;

unsigned int a, b;

//编写函数gcd与lcm，分别求两个正整数的最大公约数与最小公倍数。
unsigned int gcd(unsigned int a,unsigned int b);
unsigned int lcm(unsigned int a,unsigned int b);

int main()
{
    cout << "This program calculates the greatest common divisor and least common multiple of two positive integers." << endl;
    cout << "The first number:  ";
    cin >> a;
    cout << "The second number: ";
    cin >> b;
    cout << "gcd(" << a <<", "<< b << ")=" << gcd(a, b) << endl;
    cout << "lcm(" << a <<", "<< b << ")=" << lcm(a, b) << endl;
    return 0;
}


unsigned int gcd( unsigned int a, unsigned int b )
{
  unsigned int r;
  while( true )
  {
    r = a % b;
    if( r == 0 )
        return b;
    a = b;
    b = r;
  }
}

unsigned int lcm( unsigned int a, unsigned int b)
{
  unsigned int max;
	max=(a >= b)? a : b;

  unsigned int i = 1, j = max;

	while (true)
	{
		if (j % a == 0 && j % b == 0 )
		{
			return j;
		}
		i++;
    j= max * i;
	}
}