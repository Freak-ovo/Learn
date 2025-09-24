#include <iostream>
using namespace std;

/* 常量定义方式 */
/* 常量不可以更改 */
/* 1.宏常量 */
#define Day 7

/* 2.const常量*/
const int Month = 12;
int main()
{

    int a = 10;
    cout << "一周总共有：" << Day << " 天" << endl;
    cout << "一年总共有：" << Month << " 个月" << endl;
    cout << "a = " << a << endl;




    int b = 0;
    cout << "请输入: b = " << endl;
    cin >> b;
    cout << "b = " << b << endl;

    return 0;
}        