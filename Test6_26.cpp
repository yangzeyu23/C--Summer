#include <iostream>
#include <cstdlib>
#include <ctime>
#include "zyrandom.h"

using namespace std;

void Randomize()
{
  srand( (int)time(NULL) );
}

int GenerateRandomNumber( int low, int high )
{
  Randomize();
  double n;
  if( low > high )
  {
    cout << "GenerateRandomNumber: Make sure low <= high.\n";
    exit( 1 );
  }
  n = (double)rand() / ((double)RAND_MAX + 1.0);
  return (low + (int)(n * (high - low + 1)));
}


double GenerateRandomReal( double low, double high )
{
  Randomize();
  double m;
  if( low > high )
  {
    cout << "GenerateRandomReal: Make sure low <= high.\n";
    exit( 2 );
  }
  m = (double)rand() / (double)RAND_MAX;
  return (low + m * (high - low));
}