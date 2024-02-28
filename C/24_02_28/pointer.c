/*
 *Copyright(c) 李文龙
 *All rights reserved.
 *
 * 文件名称：pointer.c
 * 文件标识：
 * 摘    要：指针初步学习
 *
 * 当前版本：1.0
 * 作    者：李文龙
 * 完成日期：2024年2月28日
 *
 * 取代版本：
 * 原作者  ：
 * 完成日期：
 */

/* ********************
 *  内存单元，一个单元的大小是一个字节(byte)，每一个内存单元有唯一的地址（地址也称为指针）
 *  指针就是内存中一个最小单元的编号
 *  指针变量里存放的是地址，通过地址可以找到一个内存单元
 * 
 * 32为电脑有32跟地址总线
 * 00000000 00000000 00000000 00000000
 * · · · · · · · · · · · · · · · · · · 
 * 11111111 11111111 11111111 11111111
 * 2^32地址
 * 每一个地址标识一个字节
 * 2^32Byte == 2^32/1024kb == 2^32/1024/1024mb == 2^32/1024/1024/1024GB == 4GB
 * 2^32 == 4294967296 字节 转化为kb == 4194304 在转换为mb == 4096 在转化为GB == 4GB
 * 
 * 指针的大小在32位平台是4个字节，在64位平台是8个字节
 * 
 * 
 * ***************** */

#include <stdio.h>

int main()
{
    /* 
        bit     比特
        byte    字节
        kb =1024byte  
        mb
        gb
     */
    //int  4byte
    //char 1byte
    int a = 10;//a是整形变量，占了4byte（字节）
    int *pa = &a;//pa是一个指针变量，用来存放地址的

    char   *pc = NULL;
    int    *pi = NULL;
    short  *ps = NULL;
    long   *pl = NULL;
    float  *pf = NULL;
    double *pd = NULL;
    
    printf("%zu\n", sizeof(pc));//8
    printf("%zu\n", sizeof(pi));//8
    printf("%zu\n", sizeof(ps));//8
    printf("%zu\n", sizeof(pl));//8
    printf("%zu\n", sizeof(pf));//8
    printf("%zu\n", sizeof(pd));//8

    int num_1 = 0x11223344;//16个字节
    int *pnum_1 = &num_1;
    *pnum_1 = 0;//解引用

    char *pnum_01 = (char*)&num_1;//num_1是int类型 强制转换位char
    /* 
        指针类型决定了指针在被解引用的时候访问几个字节
        如果是int * 指针，解引用访问4个字节
        如果是char * 指针，解引用访问1个字节

     */



    /* 
        100      -10进制
        0x64     -16进制
        110 0100 -2进制
        144      -8进制
    
     */

    printf("pnum_1 = %p\n", pnum_1);
    printf("pnum_1 + 1 = %p\n", pnum_1 + 1);//加了4个字节

    printf("pnum_01 = %p\n", pnum_01);
    printf("pnum_01 + 1 = %p\n", pnum_01 + 1);//加了1个字节

    /* 
        指针类型决定了 + 1 -1（加1 减1）操作的时候。跳过几个字节
        决定了指针的步长
        不同类型的指针不可以混用
    
     */


    /* 
        野指针：指针指向位置不知所踪
        1.指针未初始化
        2.指针越界访问
        3.指针指向空间释放

     */

/*     int arr[10] = {0};
    int *p = arr;//p指向数组首元素地址

    for (int i = 0; i <= 10;i++)
    {
        *p = i;
        p++;
    }
 */
    /* 
                如何使用指针
        1.明确初始化指针 int *p = NULL 空指针(NULL 0指针)
        int *p = NULL;
        if (p != NULL)
        {
            *p = 100;
        }
    
    
    
    
     */


    /* 指针运算 */
    #define N_values 5
    float values[N_values];
    float *vp;//未初始化 当前未野指针
    for (vp = &values[0]; vp < &values[N_values];)//对vp初始化 vp不再为野指针
    {
        *vp++ = 0;
    }

    /* 
        vp < &values 指针关系运算  
        vp++ = 0 等价于 *vp = 0 然后 vp++
        *vp++   等价于 *vp  然后 vp++
        (*vp)++ 找到*vp指向的对象 然后++

     */


    int arr[10] = {0};

    int sz = sizeof(arr) / sizeof(arr[0]);

    /* 数组下标初始化 */
    for (int i = 0; i < sz; i++)
    {
        arr[i] = 1;
    }

    /* 指针对数组初始化 */
    int *p = arr;
    for (int i = 0; i < sz; i++)
    {
        *p = 1;
        p++;
    }

    /* 另一 写法 */
    for (int i = 0; i < sz; i++)
    {
        *(p + i) = 1;
    }

    /* 指针相减 */
    int arr2[10] = {0};
    printf("%d\n", &arr2[9] - &arr2[0]);//指针减去指针得到的是指针和指针之间元素的个数

    /* 指针不可以加指针  地址+地址error */
    /* 
        数组：一组相同元素的集合
        指针变量：是一个变量，存放的是地址
    
        数组名 位数组首元素的地址 &array[0] 
        可以通过指针变量来访问数组 int *p = array
    
     */


    int array[10] = {0};
    int *p_a = array;
    int sz_a = sizeof(array) / sizeof(array[0]);
    for (int i = 0; i < sz_a; i++)
    {
        printf("%d ", *(p_a + i)); //通过指针访问数组
        printf("%p-----%p\n", &array[i], p_a + i);
    }



    /* 二级指针 */
    int num_a = 10;
    int *pnum_a = &num_a;//*pnum_a 是一个指针变量，一级指针变量
    int **ppnum_a = &pnum_a;//**ppnum_a 二级指针变量

    int num_2 = 20;
    int num_3 = 30;
    int num_4 = 40;

    int arr_num[10];

    int *pnum_2 = &num_2;
    int *pnum_3 = &num_3;
    int *pnum_4 = &num_4;
    
    int *parr_num[10] = {&num_2, &num_3, &num_4};//*parr_num就是存放指针的数组
    for (int i = 0; i < 3; i++)
    {
        printf("%d ", *(parr_num[i]));
    }

    printf("\n");

    /* 指针模拟二维数组 */
    int arr_1[4] = {1, 2, 3, 4};
    int arr_2[4] = {1, 2, 3, 4};
    int arr_3[4] = {1, 2, 3, 4};

    int *parr[3] = {arr_1, arr_2, arr_3};

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%d ", parr[i][j]);//parr[i] 表示3个数组的首元素地址 parr[i][j]表示每行的第j个  
        }
        printf("\n");
    }
    

    return 0;
}
