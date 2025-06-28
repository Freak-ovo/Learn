 /* 
 *Copyright(c) 2022,Lee Wen Long
 *All rights reserved.
 *
 * 文件名称：findmin.c
 * 文件标识：
 * 摘    要：二分查找数组中最小值
 * 
 * 当前版本：1.0
 * 作    者：李文龙
 * 完成日期：2024年2月6日
 * 
 * 取代版本：
 * 原作者  ：
 * 完成日期： 
 */

#include <stdio.h>

int main()
{
    int arr[100] = {0}; // 假设最多存放100个数字
    int num, i = 0;

    printf("请输入数字（以'%'结束输入）：");

    // 读取输入的数字，直到遇到0为止
    do {
        scanf("%d", &num);
        arr[i] = num;
        i++;
    } while (getchar() != '%');

    int len = i;

    int left = 0;
    int right = len-1;

    while (left < right) 
    {
        int mid = left + (right - left) / 2; //防止mid溢出

        // 如果mid位置的元素比right位置的元素大，说明最小元素在mid右侧
        if (arr[mid] > arr[right]) 
        {
            left = mid + 1;
        }
        // 如果mid位置的元素比right位置的元素小，说明最小元素在mid左侧或者就是mid
        else if (arr[mid] < arr[right]) 
        {
            right = mid;
        }
        // 如果mid位置的元素和right位置的元素相等，无法确定最小元素在哪一侧，逐渐缩小搜索范围
        else 
        {
            right--;
        }
    }
        // 输出存放的数字
    printf("你输入的数字为：\n");
    for (int j = 0; j < i-1; j++) 
    { // 最后一个数字是0，不输出
        printf("%d ", arr[j]);
    }

    printf("\n排列中最小的元素为：%d\n", arr[left]);



    return 0;
}

/* 
 * 函数介绍：二分查找来逐步缩小搜索范围。我们比较数组的中间元素arr[mid]和末尾元素arr[right]的大小关系来判断最小元素的位置。
 * 输入参数：数组元素：arr[]， 数组长度 ：int len
 * 输出参数：数组中最小值
 * 返回值  ：return arr[left];
 * 
 */
int findMin(int arr[], int len) 
{
    int left = 0;
    int right = len - 1;

    while (left < right) 
    {
        int mid = left + (right - left) / 2;

        // 如果mid位置的元素比right位置的元素大，说明最小元素在mid右侧
        if (arr[mid] > arr[right]) 
        {
            left = mid + 1;
        }
        // 如果mid位置的元素比right位置的元素小，说明最小元素在mid左侧或者就是mid
        else if (arr[mid] < arr[right]) 
        {
            right = mid;
        }
        // 如果mid位置的元素和right位置的元素相等，无法确定最小元素在哪一侧，逐渐缩小搜索范围
        else 
        {
            right--;
        }
    }

    // 最小元素即为left位置的元素
    return arr[left];
}
