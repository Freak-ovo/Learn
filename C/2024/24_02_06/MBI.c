 /* 
 *Copyright(c) 李文龙
 *All rights reserved.
 *
 * 文件名称：BMI.c
 * 文件标识：
 * 摘    要：BMI（Body Mass Index）指数，简称体质指数，是国际上常用的衡量人体胖瘦程度以及是否健康的一个标准。
 * 计算公式为：BMI=体重÷身高÷身高。（体重单位：千克；身高单位：米。）
 * 合理范围：18.5~24kg/㎡之间。低于18.5kg/㎡为体重过低，高于24kg/㎡为超重，高于28kg/㎡为肥胖。
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
    int high = 0;
    int weight = 0;
    printf("请输入你的身高(cm)与体重(kg):");
    scanf("%d%d", &high, &weight);

    float BMI = weight/(high/100.0f)/(high/100.0f);
    printf("您的BMI指数为:%.2f", BMI);

    return 0;
}