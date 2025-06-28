#include <stdio.h>

int main()
{
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int sz = sizeof(arr) / sizeof(arr[0]); // 计算数组长度

    // 数组名可以表示数组首元素地址
    // 但有2个例外
    // 1.sizeof（数组名）；这里表示整个数组，计算的是整个数组，单位是字节
    // 2.&数组名；这里数组名也表示整个数组，取出的是整个数组的地址
    printf("%p\n", arr); // arr就是首元素的地址
    printf("%p\n", arr + 1);
    printf("-------------\n");
    printf("%p\n", &arr[0]); // 就是首元素的地址
    printf("%p\n", &arr[0] + 1);
    printf("-------------\n");
    printf("%p\n", &arr); // 数组的地址
    printf("%p\n", &arr + 1);
    printf("-------------\n");
    // 顺序输出一维数组元素
    for (int i = 0; i < sz; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("-------------\n");
    // 倒叙输出一维数组元素
    for (int i = sz - 1; i >= 0; i--)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("-------------\n");

    // 打印数组元素地址
    for (int i = 0; i < sz; i++)
    {
        printf("&arr[%d] = %p \n", i, &arr[i]);
    }

    // 二维数组
    int arr_1[3][4] = {{1, 2, 3, 4},
                       {2, 3, 4, 5},
                       {3, 4, 5, 6}};


    // 二维数组元素输入
    printf("请输入数组元素12个数字\n");
    // 1 2 3 4 5 6 7 8 9 10 11 12

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            scanf("%d", &arr_1[i][j]);
        }
    }
    printf("-------------\n");

    // 二维数组元素打印
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%d ", arr_1[i][j]);
        }
        printf("\n");
    }
    printf("-------------\n");

    // 打印二维数组元素地址
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("&arr_1[%d][%d] = %p\n", i, j, &arr_1[i][j]);
        }
    }



    
    printf("%d\n", sizeof(arr_1) / sizeof(arr_1[0]));    // 48/16 整个二维数组地址/数组第一行元素地址
    printf("%d\n", sizeof(arr_1[0]) / sizeof(arr_1[0][0])); // 16/4 数组第一行元素地址/数组第一个元素（[0][0])地址
    return 0;
}
