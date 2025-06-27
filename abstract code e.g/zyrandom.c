#include <stdlib.h>
#include <time.h>

#ifndef __ZYRANDOM__
#include "zyrandom.h"
#endif

#ifndef __ZYLIB__
#include "zylib.h"
#endif



/*****************************************************************************/
/*  ���������  */
/*****************************************************************************/

void Randomize()
{
  srand((int)time(NULL));
}

int GenerateRandomNumber(int low, int high)
{
  double _d;
  if( low > high )
    PrintErrorMessage( FALSE, "GenerateRandomNumber: Make sure low <= high.\n" );
  _d = (double)rand() / ((double)RAND_MAX + 1.0);
  return (low + (int)(_d * (high - low + 1)));
}

double GenerateRandomReal(double low, double high)
{
  double _d;
  if( low > high )
    PrintErrorMessage( FALSE, "GenerateRandomReal: Make sure low <= high.\n" );
  _d = (double)rand() / ((double)RAND_MAX + 1.0);
  return (low + _d * (high - low));
}
