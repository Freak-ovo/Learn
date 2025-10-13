#pragma once
#include <iostream>
using namespace std;

template <class T1, class T2>
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