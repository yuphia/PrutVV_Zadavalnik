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

int main (int argc, char* argv[])
{
    Text arrays = {};

    if (argc != 2)
    {
        printf ("Rerun the program with such input: ./intersection.o filename.txt");
        return 1;
    }

    FILE* setFile = nullptr;
    setFile = fopen (argv[1], "rb");

    transitFileToLineArray (setFile, &arrays);

    printf ("%p %p\n", arrays.lines[0].line, arrays.lines[1].line);

    Set set1 = readArrayFromStr (arrays.lines[0].line);
    Set set2 = readArrayFromStr (arrays.lines[1].line);

    for (int i = 0; i < set1.amountOfElements; i++)
        printf ("set1[%d] = %d\n", i, set1.array[i]);


    printf ("%zu\n", sizeof set2);
    for (int i = 0; i < set2.amountOfElements; i++)
        printf ("set2[%d] = %d\n", i, set2.array[i]);

    free (set1.array);
    free (set2.array);
    fclose (setFile);
    free (arrays.lines);
    free (arrays.textArray);
    return 0;
}

Set readArrayFromStr (char* str)
{
    $
    int* array = (int*) calloc (1, sizeof(int));
    Set set = {array, 0};
$
//    str = str + skipSpaces(str);
    printf ("%p\n", str);
//    sscanf (str, "%d", array);
//    str = skipNumbers (str);    
$
    for (int i = 1; *str != '\n'; str++, i++)
    {
        $

        str = skipSpaces(str) + str;
        printf ("str = %s\n", str);
        array = (int*)realloc (array, (i + 1)*sizeof (int));
        sscanf (str, "%d", array + i);

        str = skipNumbers (str);
            
        printf ("str = %c\n", *str);
        printf ("str = %s\n", str);

        printf ("number read = %d\n", array[i]); 
        set.amountOfElements = i + 1;
    }
 
    return set;
}

size_t skipSpaces (char* str)
{
$

    size_t thisSymbolPlace = 0;
    for (; thisSymbolPlace < sizeof(str); thisSymbolPlace++)
    {
        $
        if (*(str + thisSymbolPlace) != ' ')
            return thisSymbolPlace;
    }
$
    return thisSymbolPlace;
}

char* skipNumbers (char* str)
{
    while (isalpha (*str))
    {
        str++;
    }
    return str - 1;
}