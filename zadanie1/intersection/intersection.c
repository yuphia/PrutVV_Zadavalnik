#include "stdio.h"
#include "stdlib.h"
#include "fileInput/fileInputTreatment.h"

#define $ printf("in line: %d\n", __LINE__);\
          fflush (stdout);

#define middle (left + right)/2

struct Set 
    {
        int* array;
        size_t amountOfElements;
    };

size_t skipSpaces (char* str);
Set readArrayFromStr (char* str);
char* skipNumbers (char* str);

int partition (int* array, int lowIndex, int highIndex);
void quickSort (int* array, int lowIndex, int highIndex);
void swap (int *n1, int *n2);

void printArray (int * array, size_t arraySize);

int binarySearch (int target, Set set);

void rewriteIntersection (Set set1, Set set2);

int main (int argc, char* argv[])
{
    Text arrays = {};

    if (argc != 2)
    {
        printf ("Rerun the program with such input: ./intersection.o filename.txt");
        return 1;
    }

    FILE* setFile = nullptr;
    setFile = fopen (argv[1], "r");

    transitFileToLineArray (setFile, &arrays);

    Set set1 = readArrayFromStr (arrays.lines[0].line);
    Set set2 = readArrayFromStr (arrays.lines[1].line);

    quickSort (set1.array, 0, set1.amountOfElements - 1);
    quickSort (set2.array, 0, set2.amountOfElements - 1);

    printArray (set1.array, set1.amountOfElements);
    printArray (set2.array, set2.amountOfElements);
 

    rewriteIntersection (set1, set2);

    free (set1.array);
    free (set2.array);
    fclose (setFile);
    free (arrays.lines);
    free (arrays.textArray);
    return 0;
}

Set readArrayFromStr (char* str)
{
    int* array = (int*) calloc (1, sizeof(int));
    Set set = {array, 1};

    str = str + skipSpaces(str);
      
    sscanf (str, "%d", array);
    str = skipNumbers (str);    
    str += skipSpaces (str);

    for (int i = 1; *str != '\n' && *str != '\0'; i++)
    {
        array = (int*)realloc (array, (i + 1)*sizeof (int));

        sscanf (str, "%d", array + i);

        str = skipNumbers (str);
        str += skipSpaces (str);            
        set.amountOfElements = i + 1;

        if (*str == '\n' || *str == '\0')
            break;
    }
    set.array = array;
    return set;
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

void quickSort (int* array, int lowIndex, int highIndex)
{
    if (highIndex > lowIndex)
    {
        int pivotInd = partition (array, lowIndex, highIndex);
        
        quickSort (array, lowIndex, pivotInd);
        quickSort (array, pivotInd + 1, highIndex);
    }
}

int partition (int* array, int lowIndex, int highIndex)
{
    int pivot = array [(lowIndex + highIndex)/2];
    int i = lowIndex;
    int j = highIndex;

    while (true)
    {
        while (array [i] < pivot)
            i++;
        while (array [j] > pivot)
            j--;

        if (i >= j)
            return j;

        swap (array + i, array + j);        
        i++;
        j--;
    }

    return 0;
}

void swap (int *n1, int *n2)
{
    int tempN = *n1;
    *n1 = *n2;
    *n2 = tempN;
}

void printArray (int * array, size_t arraySize)
{
    for (int i = 0; i < arraySize; i++)
    {
        printf ("%d ", array[i]);   
    }
    printf ("\n");
}

int binarySearch (int target, Set set)
{
    int left  = 0;
    int right = set.amountOfElements - 1;

    if (target == set.array[right])
        return right;

    if (target == set.array[left])
        return left;

    while (left < right)
    {
        if (target == set.array[right])
            return right;

        if (target == set.array[left])
            return left;

        if (set.array[middle] == target)
           return middle;
        else if(set.array[middle] > target)
            right = middle - 1;
        else
            left = middle + 1;
    }
    return -1;
}

void rewriteIntersection (Set set1, Set set2)
{
    int* intersection = (int*) calloc (1, sizeof(int));
    size_t elementsInter = 0;

    for (int i = 0; i < set1.amountOfElements; i++)
    {
        int indOfElInSet2 = binarySearch (set1.array[i], set2);

        Set set = {intersection, elementsInter};
        if (indOfElInSet2 != -1 && binarySearch (set1.array[i], set) == -1)
        {
            elementsInter++;
            intersection = (int*) realloc (intersection, elementsInter * sizeof(int));
            intersection[elementsInter - 1] = set1.array[i];
        }
    }
    if (elementsInter == 0)
        printf ("empty\n");
    else
        printArray (intersection, elementsInter);

    free (intersection);
}