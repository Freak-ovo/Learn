#include <iostream>
using namespace std;
int G_a = 10;
int G_b = 10;
//const 修饰全局变量
const int C_G_a = 10;
int main()
{
    int a = 10;
    int b = 10;
    cout << "局部变量a的地址是：" << &a << endl;
    cout << "局部变量b的地址是：" << &b << endl;

    cout << "全局变量G_a的地址是：" << &G_a << endl;
    cout << "全局变量G_b的地址是：" << &G_b << endl;

    //静态变量
    static int S_a = 10;
    static int S_b = 10;
    cout << "静态变量S_a的地址是：" << &S_a << endl;
    cout << "静态变量S_b的地址是：" << &S_b << endl;

    //常量 字符串常量 const修饰常量
    string A = "hello world";
    cout << "字符串常量A的地址是：" << &A << endl;
    
    //const 修饰全局变量
    //const int C_G_a = 10
    cout << "const修饰全局变量C_G_a的地址是：" << &C_G_a << endl;

    //const 修饰局部变量
    const int C_b = 10;
    cout << "const修饰局部变量C_b的地址是：" << &C_b << endl;

}
