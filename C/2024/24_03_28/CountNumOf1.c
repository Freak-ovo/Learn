#include <stdio.h>

/* 
    算法一
    取模
 */
int CountNumOf1(unsigned int n)
{
    int count = 0;

    while (n)
    {
        if ((n % 2) == 1) //按位模2
        {
            count++;
        }
        n /= 2;//舍去最后一位
    }
    return count;
}

/**
 * 算法二
 * 右移按位与
 * 
 */
int CountNumOf_1(unsigned int n)
{
    int count = 0;
    for (int i = 0; i < 32; i++)//右移
    {
        if ((n >> i) & 1 == 1)//按位与1 判断该位是否为1
        {
            count++;
        }
    }
    return count;

}
/**
 * 算法三
 * n &(n-1)
 * 
 * 
 */
int CountNumOfOne(unsigned int n)
{
    int count = 0;
    while (n)
    {
        n = n &(n - 1);
        count++;
    }
    return count;
}
int main()
{
    int num = 0;
    scanf("%d", &num);

    int n = CountNumOf1(num);
    printf("%d\n", n);
    int t =  CountNumOf_1(num);
    printf("%d\n", t);

    return 0;
}