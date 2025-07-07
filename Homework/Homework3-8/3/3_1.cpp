#include <iostream>
#include <math.h>
using namespace std;

const int failed_in_testing_primality = 1;
unsigned int n;

//编写函数IsPrime，判断某个大于2的正整数是否为素数。
bool IsPrime(unsigned int n);

int main()
{
    cout << "This programm gets a number greater than 2 and determines whether it is a prime number." << endl;
    cout << "Please enter a number: ";
    cin >> n;

    IsPrime(n) ? cout << n << " is a prime number." << endl :
                 cout << n << " is NOT a prime number." << endl;         
    return 0;
}

bool IsPrime( unsigned int n )
{
  unsigned int i = 3, t = (unsigned int)sqrt(n) + 1;
  if( n <= 2 )
  {
    cout << "IsPrime: Failed in testing the primality of " << n << endl;
    exit( failed_in_testing_primality );
  }
  if( n % 2 == 0 )
    return false;
  while( i <= t )
  {
    if( n % i == 0 )
      return false;
    i += 2;
  }
  return true;
}