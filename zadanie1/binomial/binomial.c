#include "stdio.h"
#include "stdlib.h"

unsigned int binomial (unsigned int n, unsigned int k);

int main()
{
    unsigned int n, k = 0;
    printf ("input n and k\n");
    scanf ("%u %u", &n, &k);

    if (k > n)
    {
        printf ("k shouldn't be > n\n");
        return 0;
    }

    printf ("bin = %u\n", binomial (n, k));

    return 0;
}

unsigned int binomial (unsigned int n, unsigned int k)
{
    int factorialN = 1;
    int factorialK = 1;
    int factorialNK = 1;

    for (int i = 1; i <= n; i++)
    {
        factorialN *= i;

        if (i <= k && k != 1)
            factorialK *= i;

        if (i <= n - k && k != n - 1)
            factorialNK *= i;
    }

    int bin = factorialN / (factorialK * factorialNK);

    return bin;
}