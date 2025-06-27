#ifndef __POINT__
#define __POINT__

#ifndef __ZYLIB__
#include "zylib.h"
#endif

typedef struct __POINT * POINT;

POINT PtCreate( int x, int y );
void PtDestroy( POINT point );
void PtGetValue( POINT point, int * x, int * y );
void PtSetValue( POINT point, int x, int y );
BOOL PtCompare( POINT point1, POINT point2 );
STRING PtTransformIntoString( CSTRING format, POINT point );
void PtPrint( POINT point );

#endif