#include <stdio.h>
#include <stdlib.h>
#include "fileInput/fileInputTreatment.h"

struct Point
{
    int x;
    int y;
};

double calculateTriangleArea (Point p1, Point p2, Point p3);
size_t skipSpaces (char* str);
char* skipNumbers (char* str);
void sortCircle (Point* arr, int amountOfPoints, double centerX, double centerY);
void swap(Point *xp, Point *yp);
int cmpPoints (Point p1, Point p2, double centerX, double centerY);
void printPoints (Point* points, int amountOfPoints);
int getQuarter (Point point, double centerX, double centerY);
void calculatePolygonArea (Point* points, int amountOfPoints);

int main ()
{
    FILE* inputFile = fopen ("input.txt", "r");
    Text text = {};
    
    
    transitFileToLineArray (inputFile, &text);

    Point* points = (Point*) calloc (text.nLines, sizeof(Point));

    double centerX = 0;
    double centerY = 0;

    for (int i = 0; i < text.nLines; i++)
    {
        text.lines[i].line += skipSpaces (text.lines[i].line);
        sscanf (text.lines[i].line, "%d %d", &(points[i].x), &(points[i].y));
        centerX += points[i].x;
        centerY += points[i].y;
    }
 
    centerX /= (int)text.nLines;
    centerY /= (int)text.nLines;

    sortCircle (points, text.nLines, centerX, centerY);

    calculatePolygonArea (points, text.nLines);

    freeArrayLines (text.lines);
    free (text.textArray);
    free (points);
    fclose (inputFile);
    return 0;
}

double calculateTriangleArea (Point p1, Point p2, Point p3)
{
    double area = 0.5*abs((p2.x - p1.x)*(p3.y - p1.y) - (p3.x - p1.x)*(p2.y - p1.y));

    return area;
}

size_t skipSpaces (char* str)
{
    size_t thisSymbolPlace = 0;
    for (; thisSymbolPlace < sizeof(str); thisSymbolPlace++)
    {
        if (*(str + thisSymbolPlace) != ' ')
            return thisSymbolPlace;
    }

    return thisSymbolPlace;
}

char* skipNumbers (char* str)
{
    while (isdigit (*str))
    {
        str++;
    }
    return str;
}

double getAngle (Point p1, Point p2, double centerX, double centerY)
{
    double angle = 0;
    return angle;    
}

void swap(Point *xp, Point *yp)
{
    Point temp = *xp;
    *xp = *yp;
    *yp = temp;
}
 
// A function to implement bubble sort
void sortCircle (Point* arr, int amountOfPoints, double centerX, double centerY)
{
    int i = 0, j = 0;

    for (i = 0; i < amountOfPoints - 1; i++)     
        for (j = 0; j < amountOfPoints - i - 1; j++)
        {
            if (cmpPoints (arr[j], arr[j+1], centerX, centerY) > 0)
                swap(&arr[j], &arr[j+1]);
        }
}

int cmpPoints (Point p1, Point p2, double centerX, double centerY)
{
    double dif = 0;
    
    int quarterP1 = getQuarter (p1, centerX, centerY);
    int quarterP2 = getQuarter (p2, centerX, centerY);

    if (quarterP1 != quarterP2)
        return quarterP1 - quarterP2;

    dif = (p1.x - centerX) * (p2.y - centerY) - (p2.x - centerX) * (p1.y - centerY);
    if (dif < 0)
        return 1;
    if (dif > 0)
        return -1;

    return dif;
}

void printPoints (Point* points, int amountOfPoints)
{
    printf ("\n\nDumping the elemtnts\n");
    for (int i = 0; i < amountOfPoints; i++)
    {
        printf ("%5d %5d\n", points[i].x, points[i].y);
    }

    printf ("Finished dumping the elements\n\n");
}

int getQuarter (Point point, double centerX, double centerY)
{
    if (point.x >= centerX && point.y >= centerY)
        return 1;

    if (point.x < centerX && point.y >= centerY)
        return 2;

    if (point.x < centerX && point.y < centerY)
        return 3;
    
    if (point.x >= centerX && point.y < centerY)
        return 4;

    return 0;
}

void calculatePolygonArea (Point* points, int amountOfPoints)
{
    double area = 0;
    for (int i = 1; i < amountOfPoints - 1; i++)
    {
        area += calculateTriangleArea (points[0], points[i], points[i+1]);
    }

    printf ("Area = %lg\n", area);
}