#include <stdio.h>

int main()
{
    int n = 0;
    printf("please enter a number:");
    scanf("%d", &n);

    long sum = 1;
    long add = 0;

    for (int i=1; i <= n; i++)
    {
        sum *= i;
        add +=sum;
    }

    printf("%d! = %ld sum:%ld\n", n, sum, add);

    return 0;
}
