#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);

    printf("%s", n % 2 == 0 ? "Páros\n" : "Páratlan\n");

    return 0;
}