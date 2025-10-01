#include <iostream>
using namespace std;

class Person
{
    public:
    //1.构造函数
    //无返回值  不用写void
    //函数名与 类名相同
    //构造函数可以有参数 可以发生重载
    //创建对象的时候 构造函数会自动调用 而且只调用一次
    Person()
    {
        cout << "Person 无参数构造函数调用" << endl;
    }
    //有参构造函数
    Person(int a)
    {
        age = a;
        cout << "Person 有参数构造函数调用" << endl;
    }

    //拷贝构造函数
    Person(const Person &P)
    {
        age = P.age;
        cout << "Person 拷贝构造函数调用" << endl;

    }
    //2。析构函数
    //无返回值  不用写void
    //函数名与 类名相同 在前面加上~
    //构造函数不可以有参数 不可以发生重载
    //对象在销毁前 会自动调用析构函数 而且只会调用一次
    ~Person()
    {
        cout << "Person 析构函数调用" << endl;
    }

private:
    int age;
};
//构造和析构都是必须有的实现 如果我们自己不提供 编译器会提供一个空实现的构造和析构
void test01()
{
    //构造函数调用不用加（）
    //直接调用
    Person P1;//在栈上的数据 test01执行完毕后 释放这个对象
    Person P2(10);
    Person P3(P2);
    //显示法调用
    Person P4 = Person(20);
    Person P5 = Person(P4);
    //匿名对象
    Person(30);

    //隐式转换法
    Person P6 = 10; // 相当于 Person P6 = Person(10); 有参构造
    Person P7 = P6; // 相当于 Person P7 = Person(P6); 拷贝构造

}

int main()
{
    test01();
}