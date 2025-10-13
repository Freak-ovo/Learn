#include <iostream>
using namespace std;

/**
 * @brief 函数对象（仿函数）
 * 函数对象（仿函数）是一个类，它重载了 operator() 运算符，
 * 使得该类的对象可以像函数一样被调用。
 * 函数对象（仿函数）可以有状态，这使得它在某些场景下比普通函数更灵活。
 */
// 1.函数对象在使用时可以像普通函数一样调用 ，可以有参数和返回值
class MyAdd
{
public:
    int operator()(int a, int b)
    {
        cout << "MyAdd调用:" << endl;
        return a + b;
    }
};
// 2.函数对象超出普通函数的概念，它可以有状态
// 例如，下面的函数对象可以记录调用次数
class MyAdd2
{
public:
    void operator()(string test)
    {
        cout << test << endl;
        count++;
    }

    int count = 0;
};
void Test_MyAdd2()
{
    MyAdd2 add2;
    cout << "MyAdd2调用:" << endl;
    add2("hello");
    add2("world");
    cout << "MyAdd2调用次数：" << add2.count << endl;

}
// 3.函数对象可以作为参数传递
// 例如，下面的函数可以接收一个函数对象作为参数
void Test_MyAdd3(MyAdd2 add2)
{
    cout << "Test_MyAdd3调用:" << endl;
    add2("hello");
    add2("c++");
    cout << "Test_MyAdd3调用次数：" << add2.count << endl;
}
void Test_MyAdd()
{
    MyAdd add;
    int ret = add(1, 2);
    cout << ret << endl;
}

int main()
{
    Test_MyAdd();
    Test_MyAdd2();
    Test_MyAdd3(MyAdd2());
    return 0;
}