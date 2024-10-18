#include <stdio.h>
#include <stdlib.h>

int pow2(int n, int pow)
{
    if (!pow) return 1;
    int acc = n;
    while (pow-- > 1) acc *= n;
    return acc;
}

int digits_nth_sum(int n, int pow)
{
    int sum = pow2(n % 10, pow);
    while ((n /= 10, n != 0)) sum += pow2(n % 10, pow);
    return sum;
}

int digit_num(int n)
{
    int dig = 1;
    while ((n /= 10, n != 0)) dig++;
    return dig;
}

int main(int argc, char *argv[])
{
    int n = strtol(*argv, NULL, 10);
    printf("%d", n);
    for (int i = 0; i <= n; i++)
        if (digits_nth_sum(i, digit_num(i)) == i) printf("%d\n", i);

    return 0;
}