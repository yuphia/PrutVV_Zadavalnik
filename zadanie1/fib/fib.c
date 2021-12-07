#include "stdio.h"
#include "stdlib.h"

unsigned int fib (size_t amount, unsigned int *fibArr);

int main()
{
    size_t fibNumber = 0;

    printf ("Please print which fib number do you want to calculate\n");
    scanf ("%zu", &fibNumber);

    if (fibNumber == 0)
    {
        printf ("Number should be > 0\n");
        return 0;
    }

    unsigned int fibArr [fibNumber + 2] = {0, 1};

    printf ("fib = %u\n", fib (fibNumber, fibArr));

    return 0;
}

unsigned int fib (size_t amount, unsigned int* fibArr)
{
    int i = 0;
  
    for (i = 2; i <= amount; i++)
        fibArr[i] = fibArr[i-1] + fibArr[i-2];

    return fibArr [i - 1]; 
}