#include <iostream>
#include "Person.h"
#include "Person.cpp"
#include "Person.hpp"

using namespace std;

/* template <class T1, class T2>
class Person
{
public:
    // 添加默认构造函数
    Person() {}  // 默认构造函数
    
    // 带参数的构造函数
    Person(T1 Name, T2 Age);
    
    void ShowPerson();
    
    T1 __Name;
    T2 __Age;
};

// 类外实现 - 带参数的构造函数
template <class T1, class T2>
Person<T1, T2>::Person(T1 Name, T2 Age)
{
    this->__Name = Name;
    this->__Age = Age;
}

// 类外实现 - ShowPerson方法
template <class T1, class T2>
void Person<T1, T2>::ShowPerson()
{
    cout << "姓名：" << this->__Name << " 年龄：" << this->__Age << endl;  // 修正：性别改为年龄
} */

void Test()
{
    // 方法1：使用默认构造函数，然后赋值
    Person<string, int> P1;
    P1.__Name = "李明";
    P1.__Age = 25;
    P1.ShowPerson();
    
    // 方法2：直接使用带参数的构造函数（推荐）
    Person<string, int> P2("张三", 30);
    P2.ShowPerson();
}

int main()
{
    Test();
    return 0;
}