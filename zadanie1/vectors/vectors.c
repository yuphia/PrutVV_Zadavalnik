#include "stdio.h"
#include "stdlib.h"
#include "math.h"

double getAngle (double x1, double x2, double y1, double y2);

int main()
{
    double x1 = 0, x2 = 0, y1 = 0, y2 = 0;

    printf ("Input coefficients in this order: x1 y1 x2 y2\n");
    scanf ("%lg %lg %lg %lg", &x1, &y1, &x2, &y2);

    printf ("Polar angle = %lg\n", getAngle (x1, x2, y1, y2));
    return 0;
}

double getAngle (double x1, double x2, double y1, double y2)
{
    return acos ((x1*x2 + y1*y2)/(sqrt (x1*x1 + y1*y1) * sqrt (x2*x2 + y2*y2)));
}