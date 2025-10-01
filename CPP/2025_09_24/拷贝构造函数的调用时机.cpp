#include <iostream>
using namespace std;

class Person
{
public:
    Person()
    {
        cout << "Person 默认构造函数调用" << endl;
    }
    Person(int age)
    {
        Age = age;
        cout << "Person 有参构造函数调用" << endl;
    }
    Person(const Person &P)
    {
        Age = P.Age;
        cout << "Person 拷贝构造函数调用" << endl;
    }
    ~Person()
    {
        cout << "Person 默认析构函数调用" << endl;
    }

    int Age;
};

// 1.使用一个已经创建完毕的对象来初始化一个新对象
void Test01()
{
    Person P1(20);
    Person P2(P1);

    cout << "P2的年龄是：" << P2.Age << endl;
}

// 2.值传递的方式给函数参数传值
void DoWork(Person P)
{
}
void Test02()
{
    Person P;
    DoWork(P);
}

//3.值方式返回局部对象
Person DoWork3()
{
    Person P3;
    return P3;
}

void Test03()
{
    Person P4 = DoWork3();
}
int main()
{
    Test03();
}