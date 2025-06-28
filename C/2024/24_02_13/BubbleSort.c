/*
 *Copyright(c) 李文龙
 *All rights reserved.
 *
 * 文件名称：BubbleSort.c
 * 文件标识：
 * 摘    要：冒泡排序
 *
 * 当前版本：1.0
 * 作    者：李文龙
 * 完成日期：2024年2月13日
 *
 * 取代版本：
 * 原作者  ：
 * 完成日期：
 */

/*
 * 函数介绍：冒泡排序（两个相邻的元素进行比较
 * 输入参数：
 * 输出参数：
 * 返回值  ：
 *
 */

#include <stdio.h>

// 数组名是数组首元素的地址 应用指针来接 arr看似是数组 本质是指针变量
void BubbleSort(int arr[], int sz)
{
    for (int i = 0; i < sz - 1; i++)//遍历数组元素
    {
        for (int j = 0; j < sz - 1 - i; j++)//冒泡排序算法
        {
            if (arr[j] > arr[j + 1])
            {
                // 交换
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int arr[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int sz = sizeof(arr) / sizeof(arr[0]);
    BubbleSort(arr, sz);

    for (int i = 0; i < sz; i++)
    {
        printf("%d ", arr[i]);
    }
    return 0;
}