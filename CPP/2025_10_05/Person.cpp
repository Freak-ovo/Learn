#include "Person.h"

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
