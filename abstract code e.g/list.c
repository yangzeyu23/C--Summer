#include <stdio.h>

#ifndef __ZYLIB__
#include "zylib.h"
#endif

#ifndef __LIST__
#include "list.h"
#endif

typedef struct __NODE * NODE;
struct __LINKED_LIST{ unsigned int count; NODE head, tail; };
struct __NODE{ ADT data; NODE next; };

LINKED_LIST LlCreate()
{
  LINKED_LIST p = NewObject( struct __LINKED_LIST );
  p->count = 0;
  p->head = NULL;
  p->tail = NULL;
  return p;
}

void LlDestroy( LINKED_LIST list, DESTROY_OBJECT destroy )
{
  if( list ){  LlClear( list, destroy );  DestroyObject( list );  }
}

void LlClear( LINKED_LIST list, DESTROY_OBJECT destroy )
{
  if( !list )  PrintErrorMessage( FALSE, "LlClear: Parameter illegal." );
  while( list->head )
  {
    NODE t = list->head;
    list->head = t->next;
    if( destroy )  ( *destroy )( t->data );
    DestroyObject( t );
    list->count--;
  }
  list->tail = NULL;
}

void LlAppend( LINKED_LIST list, ADT object )
{
  NODE t = NewObject( struct __NODE );
  if( !list || !object )  PrintErrorMessage( FALSE, "LlAppend: Parameter illegal." );
  t->data = object;
  t->next = NULL;
  if( !list->head )  // singly linked list with no elements
  {
    list->head = t;
    list->tail = t;
  }
  else
  {
    list->tail->next = t;
    list->tail = t;
  }
  list->count++;
}

void LlInsert( LINKED_LIST list, ADT object, unsigned int pos )
{
  if( !list || !object )  PrintErrorMessage( FALSE, "LlInsert: Parameter illegal." );
  if( pos < list->count ){
    NODE t = NewObject( struct __NODE );
    t->data = object;
    t->next = NULL;
    if( pos == 0 ){
      t->next = list->head;
      list->head = t;
    }
    else{
      unsigned int i;
      NODE u = list->head;
      for( i = 0; i < pos - 1; ++i )  u = u->next;
      t->next = u->next;
      u->next = t;
    }
    list->count++;
  }
  else  LlAppend( list, object );
}

void LlDelete( LINKED_LIST list, unsigned int pos, DESTROY_OBJECT destroy )
{
  if( !list )  PrintErrorMessage( FALSE, "LlDelete: Parameter illegal." );
  if( list->count == 0 )  return;
  if( pos == 0 ){
    NODE t = list->head;
    list->head = t->next;
    if( !t->next )  list->tail = NULL;
    if( destroy )  ( *destroy )( t->data );
    DestroyObject( t );
    list->count--;
  }
  else if( pos < list->count ){
    unsigned int i;
    NODE u = list->head, t;
    for( i = 0; i < pos - 1; ++i )  u = u->next;
    t = u->next;
    u->next = t->next;
    if( !t->next )  list->tail = u;
    if( destroy )  ( *destroy )( t->data );
    DestroyObject( t );
    list->count--;
  }
}

void LlTraverse( LINKED_LIST list, MANIPULATE_OBJECT manipulate, ADT tag )
{
  NODE t = list->head;
  if( !list )  PrintErrorMessage( FALSE, "LlTraverse: Parameter illegal." );
  while( t ){
    if( manipulate )  ( *manipulate )(t->data, tag );
    t = t->next;
  }
}

BOOL LlSearch( LINKED_LIST list, ADT object, COMPARE_OBJECT compare )
{
  NODE t = list->head;
  if( !list || !object || !compare )  PrintErrorMessage( FALSE, "LlSearch: Parameter illegal." );
  while( t ){
    if( ( *compare )( t->data, object ) )  return TRUE;
    t = t->next;
  }
  return FALSE;
}

unsigned int LlGetCount( LINKED_LIST list )
{
  if( !list )  PrintErrorMessage( FALSE, "LlGetCount: Parameter illegal." );
  return list->count;
}

BOOL LlIsEmpty( LINKED_LIST list )
{
  if( !list )  PrintErrorMessage( FALSE, "LlIsEmpty: Parameter illegal." );
  return list->count == 0;
}
