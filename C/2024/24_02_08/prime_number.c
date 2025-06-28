#include <stdio.h>
#include <math.h>
// 素数只能被1和本身整除
int main()
{
    int count = 0;
    // flag=1表示是素数
    for (int i = 0; i < 200; i++)
    {
        int flag = 1;
        for (int j = 2; j <= i - 1; j++)
        {
            if (i % j == 0)
            {
                flag = 0;
                break;
            }
        }

        if (flag == 1)
        {
            count++;
            printf("%d ", i);
        }
    }

    printf("\ncount:%d\n", count);
    return 0;
}
int IsPrime(int num)
{
    for (int j = 2; j < sqrt(num); j++)
    {
        if (num % j == 0)
        {
            return 0;
        }
    }
    return 1;
}