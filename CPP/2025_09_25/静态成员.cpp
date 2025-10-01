#include <iostream>
using namespace std;

class Person
{
private:
    /* data */
public:
    static void func()
    {
        A = 100; //静态成员函数可以访问静态成员变量
        //B = 200; //静态成员函数不能访问非静态成员变量
        cout << "static void func调用" << endl;
    }
    static int A; //静态成员变量
    int B;

    //静态成员函数也是有访问权限的
private:
    static void func2()
    {
        cout << "static void func2调用" << endl;
    }
};
int Person ::A = 0;
void Test()
{
    // 1.通过类对象访问
    Person P;
    P.func();
    // 2.通过类名访问
    Person ::func();
    //Person ::func2(); //类外访问不到私有的静态成员函数

}

int main()
{
    Test();
}