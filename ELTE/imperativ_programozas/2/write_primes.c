#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct PrimeArray
{
    unsigned long *array;
    int count;
};

void get_primes(const unsigned long num, struct PrimeArray *pa)
{
    long double sqrt = sqrtl(num);

    // Trying if has any prime divider
    for (unsigned long i = 0; pa->array[i] <= sqrt; i++)
        if (num % pa->array[i] == 0) return;

    pa->array[pa->count++] = num;
}

// Implement Meisser-Lehmer algorythm here
unsigned long estimate_number_of_primes(unsigned long num)
{
    // Based on trial and error
    return num * 0.08;
}

int main()
{
    unsigned long num;
    struct PrimeArray pa;
    register struct PrimeArray* pap = &pa;

    printf("Adj meg egy számot!\n");
    scanf("%ld", &num);

    pa.array = (unsigned long *)malloc(estimate_number_of_primes(num) * sizeof(unsigned long));
    pa.array[0] = 2;
    pa.count    = 1;

    for (unsigned long i = 3; i <= num; i += 2) get_primes(i, pap);

    for (int i = 0; i < pa.count; i++) printf("%ld ", pa.array[i]);

    free(pa.array);
}