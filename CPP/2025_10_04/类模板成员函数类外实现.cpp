#include <iostream>
using namespace std;

template <class T1, class T2>
class Person
{
public:
    Person(T1 Name, T2 Age);
    void ShowPerson();
    T1 __Name;
    T2 __Age;
};

// 类外实现
template <class T1, class T2>
Person<T1, T2>::Person(T1 Name, T2 Age)
{
    this->__Name = Name;
    this->__Age = Age;
}

template <class T1, class T2>
void Person<T1, T2>::ShowPerson()
{
    cout << "姓名：" << this->__Name << " 年龄：" << this->__Age << endl;
}

void Test()
{
    // 直接使用带参数的构造函数
    Person<string, int> P1("李明", 25);
    P1.ShowPerson();
}

int main()
{
    Test();
    return 0;
}