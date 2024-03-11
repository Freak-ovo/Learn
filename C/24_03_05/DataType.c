#include <stdio.h>

int main()
{
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    printf("%p\n", arr[0]);

    for (int i = 0; i <= 12; i++)
    {
        printf("%p ", &i);
        printf("%d \n", arr[i]);
    }

    /* 

        1. char     字符数据类型    1bit
        2. short    短整型          4bit
        3. int        整形          4/8bit          sizeof(long) >= sizeof(int)
        4. long     长整型          8bit            4   /    8   >=     4
        5. long long  更长整形      8bit            32位    /  64位
        6. float      单精度浮点数  4bit
        7. double    双精度浮点数   8bit


        ## 1.2构造类型

        ## 1.2.1数据类型

            1. 结构体类型 struct
            2. 枚举类型 enum
            3. 联合类型 union

        ## 1.2.2 指针类型

            1. int *p；
            2. char *pc;
            3. float *pf;
            4. void *pv;

        ## 1.2.3空类型

            void 表示空白格类型 
    

        数值在计算机中存储一律用补码来表示。原因在于，使用补码，可以将符号位和数值域统一处理
        同时，加法和减法也可以统一处理（cpu只有加法器）
        此外，补码与原码相互转换，其运算过程是相同的，不需要额外的硬件电路
     */


    int a = 1;
    //&a 取地址a int类型 
    //*&a解引用 (char*)&a 取出a的地址强行转化为字符类型
    //*(char*)&a  解引用 

    if (*(char*)&a == 1)
    {
        printf("小端\n");
    }
    else
    {
        printf("大端\n");
    }


    /* 

        ### 内存中数据存储

        ​	00000000
        ​	00000001        有符号 (-1)-(-128) 0-127 
        ​	10000000        无符号  0-255
        ​	.....
        ​	111111110       -2
        ​	111111111 补码  -1

     */



    char num_1 = -1;
    signed char num_2 = -1;
    unsigned char num_3 = -1;
    printf("%d %d %d", num_1, num_2, num_3);//整型提升
    /* 
        %d 打印有符号整数
        %u 打印无符号整数
    
     */
    
    return 0;
}

void test(void)
{
    /* 
    
        第一个void 表示函数不会返回值
        第二个void 表示函数不需要传入任何参数
     */
}


int check_sys()
{
    int a = 1;
    //&a 取地址a int类型 
    //*&a解引用 (char*)&a 取出a的地址强行转化为字符类型
    //*(char*)&a  解引用 

    if (*(char*)&a == 1)
    {
        return 0;//printf("小端\n");
    }
    else
    {
        return 1;//printf("大端\n");
    }

}