#include <stdio.h>
void print(unsigned int n)
{
    if (n > 9)
    {
        print(n / 10);//递归调用
    }
    printf("%d ", n % 10);
}
int main()
{
    unsigned int num;
    scanf("%d", &num);
    print(num);
    return 0;
}