 /* 
 *Copyright(c) 2022,Lee Wen Long
 *All rights reserved.
 *
 * 文件名称：volume.c
 * 文件标识：球的体积计算
 * 摘    要：球的体积计算
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
    double R = 0.0f;
    double V = 0.0f;
    double PI = 3.1415926f;

    printf("Please input R:");
    scanf("%f",&R);

    V = (4/3.0)*PI*R*R;

    printf("V:%.3f\n",V);

    return 0;
}