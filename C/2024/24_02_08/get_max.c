#include <stdio.h>

int GetMax(int x, int y)
{
    return (x > y ? x : y);
    /* if (x > y)
    {
        return x;
    }
    else
    {
        return y;
    } */
}

int main()
{
    int a = 0;
    int b = 0;
    scanf("%d %d", &a, &b);

    int m = GetMax(a, b);
    printf("%d", m);

    return 0;
}
