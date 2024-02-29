/* 统计二进制序列中1的个数 */


#include <stdio.h>

/* int count_num_of_1(int n)
{
    int count = 0;
    while (n)
    {
        if ((n % 2) == 1)
        {
            count++;
        }
        n /= 2;
    }

    return count;

} */

/* int count_num_of_1(int n)
{
    int count = 0;
    for (int i = 0; i < 32; i++)
    {
        if (((n >> i) & 1) == 1)
        {
            count++;
        }
    }
    return count;
} */

int count_num_of_1(int n)
{
    int count = 0;
    while (n)
    {
        n = n & (n - 1);
        count++;
    }
    return count;
}
int main()
{
    int num = 0;
    scanf("%d", &num);

    int n = count_num_of_1(num);
    printf("%d\n", n);


    return 0;
}