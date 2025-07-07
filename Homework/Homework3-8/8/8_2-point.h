#ifndef POINT_H
#define POINT_H

typedef struct __POINT * POINT;

POINT PtCreate(double x, double y);
void PtDestroy(POINT point);
void PtGetValue(POINT point, double * x, double * y);
void PtSetValue(POINT point, double x, double y);
bool PtCompare(POINT point1, POINT point2);
char * PtTransformIntoString(const char *format, POINT point);
void PtPrint(POINT point);

#endif