#include "stdio.h"
#include "stdlib.h"


struct _Decimal {
    char * a;          // number is a[0]*10^0 + a[1]*10^1 + ..+ a[n]*10^n
    unsigned int n;    // наибольшая степень десяти
    unsigned int size; // размер выделенной динамической памяти в а (можно это поле не использовать).
};
typedef struct _Decimal Decimal;

Decimal* div10 (const Decimal* a);

int main(){
    Decimal a;  
    Decimal * res;
    
    char* bebrra = (char*) calloc (3, sizeof(char));
    bebrra [0] = 7;
    bebrra [1] = 4;
    bebrra [2] = 1;
    a = {bebrra, 2, 2};            // 147 is {{7, 4, 1}, 2};
    
    res = div10(&a);            // res = a/10 = 147/10 = 14
    
    //print(res);                  // print 14
    //printf("\n");
    
    free (res->a);
    free (res);
    free (bebrra);
    return 0;
}

Decimal * div10 (const Decimal * a)
{
    Decimal* newD = (Decimal*) calloc (1, sizeof(Decimal));
    newD->a = (char*) calloc (a->n, sizeof(char));

    if (a->n == 0)
    {
        newD->a[0] = 0;
        newD->n = 0;
        return newD;
    }

    for (int i = 1; i < a->n + 1; i++)
    {
        newD->a[i-1] = a->a[i];
    }

    newD->n = a->n - 1;
    newD->size = a->n * sizeof(char);

    return newD;
}

