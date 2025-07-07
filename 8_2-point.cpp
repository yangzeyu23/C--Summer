#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include "8_2-point.h"

using namespace std;

static char * DuplicateString(const char *s);

char* DuplicateString(const char *s)
{
    int n = strlen(s);
    char *t = new char[n+1];
    for (int i = 0; i < n; ++i)
        t[i] = s[i];
    t[n] = '\0';
    return t;
}

struct __POINT{double x, y;};

POINT PtCreate(double x, double y)
{
    POINT t = new __POINT;
    t->x = x;
    t->y = y;
    return t;
}

void PtDestroy(POINT point)
{
    if (point)
    {
        delete point;
    }
}

void PtGetValue(POINT point, double * x , double * y)
{
    if (point) 
    {
        if (x) *x = point->x;
        if (y) *y = point->y;
    }
}

void PtSetValue(POINT point, double x, double y)
{
    if (point) 
    {
        point->x = x;
        point->y = y;
    }
}

bool PtCompare(POINT point1, POINT point2)
{
    if (!point1 || !point2) 
    {
        exit(1);
    }
    return (point1->x == point2->x) && (point1->y == point2->y);
}

char * PtTransformIntoString(const char *format, POINT point)
{
    char buf[BUFSIZ];
    if (point) 
    {
        sprintf(buf, format, point->x, point->y);
        return DuplicateString(buf);
    }
    else
    {
        return "NULL";
    }
}

void PtPrint(POINT point)
{
    if (point)
        printf("(%lf, %lf)", point->x, point->y);
    else
        printf("NULL");
}
