#include "stdio.h"
#include "stdlib.h"
#include "fileInput/fileInputTreatment.h"

#define $ printf("in line: %d\n", __LINE__);\
          fflush (stdout);

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
void swap (int n1, int n2);

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

    quickSort (set1.array, 0, set1.amountOfElements);

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
        while (array [i] < lowIndex)
            i++;
        while (array [j] > highIndex)
            j++;

        if (i >= j)
            return j;

        swap (array [i], array[j]);        
    }

    return 0;
}

void swap (int n1, int n2)
{
    int tempN = n1;
    n1 = n2;
    n2 = tempN;
}