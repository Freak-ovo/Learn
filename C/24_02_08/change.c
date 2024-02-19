#include <stdio.h>
#include <stdio.h>

void Swap(int *x, int *y)
{
    int temp = 0;
    temp = *x;
    *x = *y;
    *y = temp;
}

int main()
{
    int a = 0;
    int b = 0;
    scanf("%d %d", &a, &b);
    printf("a=%d b=%d\n", a, b);
    Swap(&a, &b);
    printf("a=%d b=%d\n", a, b);

    return 0;
}
