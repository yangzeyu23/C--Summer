#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main()
{
  int i;
  cout << "On this computer, the RAND_MAX is" << RAND_MAX << ".\n";
  cout << "Five numbers the rand function generates as follows:\n";

  srand((int)(time(0))); 
  for( i = 0; i < 5; i++ )
    cout << rand() << "; ";
  cout << endl;
  return 0;
}
