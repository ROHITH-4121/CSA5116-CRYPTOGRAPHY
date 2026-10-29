
#include <stdio.h>
#include <math.h>

int main() {
    long double factorial = 1.0L;
    int i;
    long double totalKeys, uniqueKeys;
    long double power;

    for (i = 1; i <= 25; i++) {
        factorial *= i;
    }

    totalKeys = factorial;

    printf("Total possible keys = 25! = %.0Lf\n", totalKeys);
    printf("Approximate power of 2 = 2^%.2Lf\n",
           log2l(totalKeys));

    uniqueKeys = totalKeys / (25.0L * 24.0L);
    
    printf("Effectively unique keys (under this equivalence assumption) = %.0Lf\n",
           uniqueKeys);
    printf("Approximate power of 2 = 2^%.2Lf\n",
           log2l(uniqueKeys));

    return 0;
}
