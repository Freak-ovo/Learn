#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
using namespace std;

template <class T1, class T2>
class Person
{
public:
    Person();
    Person(T1 Name, T2 Age);
    void ShowPerson();
    T1 __Name;
    T2 __Age;
};

// 模板类的实现也必须放在头文件中
template <class T1, class T2>
Person<T1, T2>::Person() {}

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

#endif