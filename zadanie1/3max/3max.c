#include "stdio.h"
#include "stdlib.h"
#include <ctype.h>


int partition (double* array, int lowIndex, int highIndex);
void quickSort (double* array, int lowIndex, int highIndex);
void swap (double *n1, double *n2);
size_t skipSpaces (char* str);
char* skipNumbers (char* str);
void printArray (double * array, size_t arraySize);

int main()
{
    //int n = 0;
    //printf ("Enter the amount of numbers you will enter:\n");
    //scanf ("%d", &n);
    //printf ("Enter the numbers");
    
    char* str = (char*) calloc (100, sizeof(char));
    char* strSave = str;
    int a = 0;

    do 
    {
        str [a] = getchar();
        a++;
    }
    while (str[a-1] != '\n');

    double* arr = (double*) calloc (10, sizeof(double));
    int size = 0;

    for (; *str != 0 && *str != '\n'; str++ )
    {
        sscanf (str, "%lg", arr + size);

        str = skipNumbers (str); 
        str += skipSpaces (str) - 1;     
        
        size++;
        arr = (double*)realloc (arr, (size + 1)*sizeof(double));
        //str--;
    }

    //printArray (arr, size);

    double* subarr = (double*) calloc (1, sizeof(double));
    int sizeSub = 0;
    for (int i = 0; i < size; i++)
    {

        if (arr[i] > 0)
        { 
            subarr[sizeSub] = arr[i];

            sizeSub++;
            subarr = (double*) realloc (subarr, (sizeSub + 1)*sizeof(double));
        }
    }
    quickSort (subarr, 0, sizeSub - 1);
    
    for (int i = 0, j = 0; i < size; i++)
    {
        //printArray (arr, size);

        if (arr[i] > 0)
        {
            arr[i] = subarr[i - j];
        }
        else
        {
            j++;
        }
    }
//    quickSort (arr, 0, size - 1);
    
    printArray (arr, size);

    free (arr);
    free (strSave);
    free (subarr);

    return 0;
}

void quickSort (double* array, int lowIndex, int highIndex)
{
    //printArray (array, highIndex - lowIndex);

    if (highIndex - lowIndex > 1)
    {
        //printArray (array, highIndex - lowIndex);
        double pivotInd = partition (array, lowIndex, highIndex);
        
        quickSort (array, lowIndex, pivotInd);
        quickSort (array, pivotInd + 1, highIndex);
    }
}

int partition (double* array, int lowIndex, int highIndex)
{
    int pivot = array [(lowIndex + highIndex)/2];
    int i = lowIndex;
    int j = highIndex;

    while (true)
    {
        //printArray (array, highIndex - lowIndex);
        while (array [i] < pivot)
        {
            //printf ("%lg\n", array[i]);
            i++;
        }
        while (array [j] > pivot)
        {
            //printf ("%lg\n", array[j]);
            j--;
        }

        if (i >= j)
            return j;

        swap (array + i, array + j);        
        i++;
        j--;

//        printArray (array, highIndex - lowIndex);
    }

    return 0;
}

void swap (double *n1, double *n2)
{
    double tempN = *n1;
    *n1 = *n2;
    *n2 = tempN;
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
    while (isdigit (*str) || *str == '-' || *str == '.')
    {
        str++;
    }
    return str;
}

void printArray (double * array, size_t arraySize)
{
    for (int i = 0; i < arraySize; i++)
    {
        printf ("%0.3f ", array[i]);   
    }
    printf ("\n");
}