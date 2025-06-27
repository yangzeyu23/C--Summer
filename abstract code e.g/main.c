#include <stdio.h>
#include <stdlib.h>
#include <zylib.h>
#include <zyrandom.h>

#ifndef __POINT__
#include "point.h"
#endif

#ifndef __LIST__
#include "list.h"
#endif

int DoCompareObject( CADT e1, CADT e2 );
void DoDestroyObject( ADT e );
void DoPrintObject( ADT e, ADT tag );

int main()
{
  POINT pt;
  int i;
  LINKED_LIST list = LlCreate();
  Randomize();
  for( i = 0; i < 8; ++i )
  {
    pt = PtCreate( GenerateRandomNumber(10, 99), GenerateRandomNumber(10, 99) );
    LlInsert( list, pt, 0 );
  }
  pt = PtCreate( 6, 6 );
  LlInsert( list, pt, 1 );
  LlTraverse( list, DoPrintObject, "(%d,%d)" );
  printf( "NULL\n" );

  if( LlSearch( list, pt, DoCompareObject ) )
    printf( "Yes, %s exists.\n", PtTransformIntoString("(%d,%d)", pt) );
  else
    printf( "No, %s doesn't exist.\n", PtTransformIntoString("(%d,%d)", pt) );

  LlDelete( list, 1, DoDestroyObject );
  LlTraverse( list, DoPrintObject, "(%d,%d)" );
  printf( "NULL\n" );

  pt = PtCreate( 6, 6 );
  if( LlSearch( list, pt, DoCompareObject ) )
    printf( "Yes, %s exists.\n", PtTransformIntoString("(%d,%d)", pt) );
  else
    printf( "No, %s doesn't exist.\n", PtTransformIntoString("(%d,%d)", pt) );

  LlClear( list, DoDestroyObject );
  LlTraverse( list, DoPrintObject, "(%d,%d)" );
  printf( "NULL\n" );

  LlDestroy( list, DoDestroyObject );
  return 0;
}

int DoCompareObject( CADT e1, CADT e2 )
{
  return PtCompare( (POINT)e1, (POINT)e2 );
}

void DoDestroyObject( ADT e )
{
  DestroyObject( (POINT)e );
}

void DoPrintObject( ADT e, ADT tag )
{
  printf( PtTransformIntoString( (CSTRING)tag, (POINT)e ) );
  printf( " -> " );
}
