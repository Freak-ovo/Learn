#include <iostream>
using namespace std;


//1.创建一个类 cpp 编译器会给每一个类至少添加3个函数
/*****************************
 * 默认构造（空实现）
 * 析构函数（空实现）
 * 拷贝构造（值拷贝）
 * 
 * 
 *  */ 

 class Person
 {
public:
    Person()
    {
        cout << "Person 无参数构造函数调用" << endl;
    }
    //有参构造函数
    Person(int a, int height)
    {
        Age = a;
        Height = new int (height);
        cout << "Person 有参数构造函数调用" << endl;
    }

    //拷贝构造函数
    Person(const Person &P)
    {
        Age = P.Age;
        //Height = P.Height; //编译器默认实现
        cout << "Person 拷贝构造函数调用" << endl;
        //深拷贝
        Height = new int(*P.Height);
    }
    
    //2。析构函数
    //无返回值  不用写void
    //函数名与 类名相同 在前面加上~
    //构造函数不可以有参数 不可以发生重载
    //对象在销毁前 会自动调用析构函数 而且只会调用一次
    ~Person()
    {
        if (Height != NULL)
        {
            delete Height;
            Height = NULL;
        }
        
        cout << "Person 析构函数调用" << endl;
    }


    int Age;
    int *Height;

 };

void Test01()
{
    Person P(18, 180);
    P.Age = 18;
    Person P2(P);
    cout << "P2的年龄是：" << P.Age << " P2的身高是：" << *P.Height << endl;
}

int main()
{
    Test01();
}