 /* 
 *Copyright(c) 2022,Lee Wen Long
 *All rights reserved.
 *
 * 文件名称：max.c
 * 文件标识：输出数组中最大值
 * 摘    要：输出数组中最大值
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
    int arr[4] = {0};
    int i = 0;
    while (i < 4)
    {
        scanf("%d",&arr[i]);
        i++;
    }
    i = 1;
    int max = arr[0];
    while (i < 4)
    {
        if (arr[i]>max)
        {
            max = arr[i];
        }
        i++;
    }
    printf("%d\n",max);
    return 0;
}