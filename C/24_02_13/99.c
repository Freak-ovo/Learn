#include <stdio.h>

int main()
{
    for (int i = 1; i < 10; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            printf("%d*%d=%-2d ", i, j, i * j);//  %2：2位左对齐
        }
        printf("\n");
    }
    return 0;
}
