#include <stdio.h>

int sum_dividers(int num){
    int sum = 0;
    for (int i = 1; i < num; i++)
        if(num % i == 0)
            sum += i;
    
    return sum;
}

int main()
{
    int x, y;
    printf("Adjon meg két számot!\n");

    scanf("%d", &x);
    scanf("%d", &y);

    if(sum_dividers(x) == y && sum_dividers(y) == x)
        printf("A számok barátságosak.\n");
    else
        printf("A számok nem barátságosak.\n");
}
