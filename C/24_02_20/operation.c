#include <stdio.h>
#include <string.h>

struct stu
{
    char name[20];
    int age;
    double score;
};

void set_stu(struct stu *ps)
{
/*     strcpy((*ps).name,"lili");
    (*ps).age = 20;
    (*ps).score = 100.0;

    两种形式等价
 */
    strcpy(ps->name, "lile");//结构体指针 -> 成员
    ps->age = 20;
    ps->score = 100.0;
}

void print_stu(struct stu ss)
{
    printf("%s %d %lf\n", ss.name, ss.age, ss.score);//结构体对象.成员
}

int main()
{
    int a = 7 % 2;
    printf("7%%2 = %d\n", a); // 取余=1 取模等式两边都是整数
    int b = 7 / 2;
    printf("7/2 = %d\n", b); // 除法=3

    /*
     移位运算符 二进制
     进制
     16进制 0~9 A~F
     8进制 0~8
     7进制 0~7
     2进制 0~1

     二进制 7
     原码 0110
     反码 1001
     补码 1010

     左移 左边丢弃 右边补0
     右移 右边丢弃 左边补0
     */
    int c = 7;      // 00000000000000000000000000000110 //7
    int d = c << 1; // 00000000000000000000000000001110//14
    printf("%d\n", c);
    printf("c << 1 = %d\n", d);

    int c1 = -7;
    int d1 = c1 << 1;
    printf("%d\n", c1);
    printf("c << 1 = %d\n", d1);

    /* 按位取反 是二进制取反
    符号位也要取反 */
    int num_1 = 0;
    printf("~0 = %d\n", ~num_1);

    int num_2 = 13;
    num_2 |= (1 << 1); // 按位或
    printf("%d\n", num_2);
    /*
     * 00000000 num_1 = 0
     * 11111111 ~num_1
     * 11111110  -1反码
     * 10000001    原码 -1
     */

    int num_3 = 13;
    num_3 &= (~(1 << 2)); // 按位与
    printf("%d\n", num_3);
    /*
     * 00001101
     * 00000100 1 << 2
     * 11111011(~(1 << 2))
     * 00001001 num_3 &= (~(1 << 2))=9
     */

    /*
     * 自增 ++
     * 自减 --
     *
     */

    int num_4 = 1;
    int num_6 = num_4++; // 后置++ 先使用 后++
    printf("num_4++ = %d\n", num_6);
    int num_5 = ++num_4; // 前置++ 先++ 后使用
    printf("++num_4 = %d\n", num_5);

    /* 解引用操作符 */
    int num_7 = 10;
    int *p = &num_7;//指向num_7的地址
    *p = 30;
    printf("%d\n", num_7);

    (num_7 > 5) ? (num_6 = 3): (num_6 = -3);
    printf("num_6 = %d\n", num_6);

    /*
     * 数组元素引用
     * arr[7] == *(arr+7)
     * arr是数组首元素地址
     * arr+7 就是跳过7个元素，指向了第8个元素
     * *(arr+7) 就是第8个元素
     * 
     *   */


    /* 结构体 */

/*  struct stu
    {
        char name[20];
        int age;
        double score;
    }; */
    struct stu s = {0};
    set_stu(&s);
    print_stu(s);
    return 0;
}


