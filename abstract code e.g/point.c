#include <stdio.h>

#ifndef __POINT__
#include "point.h"
#endif

#ifndef __ZYLIB__
#include "zylib.h"
#endif

struct __POINT{ int x, y; };

POINT PtCreate( int x, int y )
{
  POINT t = NewObject( struct __POINT );
  t->x = x;
  t->y = y;
  return t;
}

void PtDestroy( POINT point )
{
  if( point ){  DestroyObject( point );  }
}

void PtGetValue( POINT point, int * x, int * y )
{
  if( point ){  if( x )  *x = point->x;  if( y )  *y = point->y;  }
}

void PtSetValue( POINT point, int x, int y )
{
  if( point ){  point->x = x;  point->y = y;  }
}

BOOL PtCompare( POINT point1, POINT point2 )
{
  if( !point1 || !point2 )  PrintErrorMessage( FALSE, "PtCompare: Parameter(s) illegal." );
  return ( point1->x == point2->x ) && ( point1->y == point2->y );
}

STRING PtTransformIntoString( CSTRING format, POINT point )
{
  char buf[BUFSIZ];
  if( point ){
    sprintf( buf, format, point->x, point->y );
    return DuplicateString( buf );
  }
  else  return "NULL";
}

void PtPrint( POINT point )
{
  if( point )
    printf( "(%d,%d)", point->x, point->y );
  else
    printf( "NULL" );
}
