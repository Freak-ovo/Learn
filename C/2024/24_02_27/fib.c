#include <stdio.h>
/* 小乐乐上课需要走n阶台阶，因为他腿脚长，一次可以走一个台阶或者两个台阶，那么他一共有多少种走法呢？ */


//递归调用
int fib(int n)
{
    if (n <= 2)
    {
        return n;
    }
    else
    {
        return fib(n-1) + fib(n-2);
    }
}



int main()
{
    int n = 0;
    scanf("%d", &n);

    int m = fib(n);
    printf("%d", m);


    return 0;
}
