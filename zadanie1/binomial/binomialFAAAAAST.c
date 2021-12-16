// Program to calculate C(n, k)
#include <stdio.h>
 
// Returns value of Binomial Coefficient C(n, k)
int binomialCoeff(int n, int k)
{
    int res = 1;
 
    // Since C(n, k) = C(n, n-k)
    if (k > n - k)
        k = n - k;
 
    // Calculate value of
    // [n * (n-1) *---* (n-k+1)] / [k * (k-1) *----* 1]
    for (int i = 0; i < k; ++i) {
        res *= (n - i);
        res /= (i + 1);
    }
 
    return res;
}
 
/* Driver program to test above function*/
int main()
{
    int n = 0, k = 0;
    scanf ("%d %d", &n, &k);

    printf(
        "Value of C(%d, %d) is %d ",
        n, k, binomialCoeff(n, k));
    return 0;
}