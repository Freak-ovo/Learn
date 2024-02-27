#include <stdio.h>

/* 
    输入一个数组
    求出最高分与最低分之差
 */

int main()
{
    int n = 0;
    scanf("%d", &n);

    //输入数组元素
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }


    int max = arr[0];
    int min = arr[0];
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];    //寻找最大值
        }
        if (arr[i] < min)
        {
            min = arr[i];    //寻找最小值
        }
    }



    int D = max - min;
    printf("%d", D);

    return 0;
}