#include <stdio.h>

/* 
debug  调试版本 
release 发布版本 
window环境 调试工具 开发环境选择debug
linux环境 调试工具 gdb

    调试快捷键
        F5 启动调试 直接跳到下一个断点处
        F9 创建断点和取消断点 条件断点
        F10 逐过程 一个函数 一个
        F11 逐语句 可以进入函数内部
        ctrl + F5 开始执行不调试
    查看变量
        调试开始后 窗口中可以选择变量 
*/
const int num = 10; //表示常量不能修改 可以通过地址修改
int *p = &num;
*p = 30;
/* const 
    修饰指针变量
        1.const 在*的左边 表示p指向的的对象不能通过p来改变，但是p变量本身的值是可以改变的
        const int *p = &n  *p = &m
        2.const 在*的右边 表示p指向的对象可以通过p来改变，但不能修改p变量本身的值
         int * const p = &n  *p = 0
    
    
    */
int main()
{

    for(int i = 0; i < 10; i++){
        printf("%d", i);
    }

    return 0;
}