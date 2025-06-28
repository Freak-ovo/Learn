/*
 *Copyright(c) 李文龙
 *All rights reserved.
 *
 * 文件名称：struct.c
 * 文件标识：
 * 摘    要：结构体基础知识
 *
 * 当前版本：1.0
 * 作    者：李文龙
 * 完成日期：2024年2月29日
 *
 * 取代版本：
 * 原作者  ：
 * 完成日期：
 */

/*
    结构是一些值的集合，这些值称为成员变量
    结构的每个成员可以是不同类型的变量

    struct tag
    {
        member-list;
    }varible-list;

*/

#include <stdio.h>

// 声明结构体类型
struct people
{
    char name[20];
    char tele[11];
    char sex[5];
    int high;
} peo1, peo2; // p1和p2是全局的结构体变量
// p1,p2是使用struct people 结构类型创建的成员变量
//  struct people peo4,peo5; 结构体变量的创建

struct st
{
    struct people p;
    int num;
    float f;
};

void print1(struct people *sp)
{
    printf("%s %s %s %d\n", sp->name, sp->tele, sp->sex, sp->high);//结构体指针->成员变量
}

void print2(struct people p)
{
    printf("%s %s %s %d\n", p.name, p.tele, p.sex, p.high);//结构体变量.成员变量
}

int main()
{
    // 创建结构体变量并初始化
    struct people peo3 = {"张三", "15995276959", "男", 175};

    struct st s = {{"李四", "15966449588", "女", 165}, 100, 3.14f};

    printf("%s %s %s %d\n", peo3.name, peo3.tele, peo3.sex, peo3.high);

    printf("%s %s %s %d %d %f\n", s.p.name, s.p.tele, s.p.sex, s.p.high, s.num, s.f);

    print1(&peo3);//传参：结构体地址
    print2(peo3);//传参：结构体本身（形参） 消耗内存大
    /* 
        函数传参的时候，参数需要压栈
        若传递一个结构体对象的时候，结构体过大，参数压栈的系统开销较大，所以会导致性能下降。
        故结构体传参尽可能传地址。
    
    
    
    
     */
    return 0;
}