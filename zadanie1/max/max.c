#include "stdlib.h"
#include "stdio.h"

int main()
{
    int amount = 0;
    scanf ("%d\n", &amount);

    if (amount == 0)
    {
        printf ("Please enter numbers in intended way:\n"
                "In the first line amount of numbers\n"
                "In the second line all the nummbers\n");

        return 0;
    }

    int number = 0;
    int max = number;

    for (int i = 0; i < amount; i++)
    {
        scanf ("%d", &number);

        (number > max) ? max = number : number = 0;
    }

    printf ("max = %d\n", max);

    return 0;
}