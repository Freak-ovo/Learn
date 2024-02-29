/*
 *Copyright(c) 李文龙
 *All rights reserved.
 *
 * 文件名称：debug.c
 * 文件标识：
 * 摘    要：代码调试流程
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
    debug调试流程
    1.发现程序错误的存在
    2.以隔离、消除等方式对错误进行定位
    3.确定错误产生的原因
    4.提出纠错误的解决方法
    5.对程序错误予以改正，重新测试

    debug通常称为调试版本，它包含调试信息且不做任何优化，便于程序员调试程序
    Release通常称为发布版本，它往往是进行了各种优化，使得程序在代码大小和运行速度上都是最优的，以便用户更好的使用
    
    F5  启动调试
    F9  打断点 可以在程序任何地方打断点
    F10 逐过程 处理一个过程，一个过程可以是一次函数调用，或者是一条语句。
    F11 单步调试 每次执行一条语句，可以进入函数内部
    FN  辅助功能键


    监视 
    数组元素  数组名，元素个数



    栈区内存的使用习惯是先使用高地址的空间，在使用低地址处的空间
    数组随着下标的增长地址是由低到高变化的
    如果数组长度和循环变量 地址相近 若对数组越界访问可能会覆盖到循环变量 则可能造成死循环




    优秀代码
    1.代码运行正常
    2.bug很少
    3.效率高
    4.可读性强
    5.可维护性高
    6.注释清晰
    7.文档齐全

    常见coding技巧
    1.使用assert
    2.尽量使用const  
    const修饰指针变量 
    const 在*左边时p指向的对象不能通过p来改变，但是p本身的值是可以改变的
    const 在*右边是p指向对象是可以通过p来改变的，但是不能修改p变量本身的值
    3.养成良好的编码风格
    4.添加必要的注释
    5.避免编码陷阱

 */


#include <stdio.h>

int sum(int x, int y)
{
    return x + y;
}


int main()
{

    for (int i = 0; i < 10; i++)
    {
        printf("%d ",i);
    }

    int n = sum(3, 6);
    printf("%d", n);


    return 0;
}
