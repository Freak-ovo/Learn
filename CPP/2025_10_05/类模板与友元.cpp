#include <iostream>
#include <string>
using namespace std;
// 提前声明
template<class T1, class T2> class Person;

// 提前声明友元函数模板
template<class T1, class T2> 
void PrintPerson2(Person<T1, T2> P);
template <class T1, class T2>
class Person
{
    // 全局函数 类内实现
    friend void PrintPerson(Person<T1, T2> P)
    {
        cout << "类内实现--姓名：" << P.__Name << " 年龄：" << P.__Age  << endl;
    }
    // 全局函数 类外实现
    //加一个空模板的从参数列表
    friend void PrintPerson2<>(Person<T1, T2> P);
public:
    Person();
    Person(T1 Name, T2 Age)
    {
    this->__Name = Name;
    this->__Age = Age;
    }

private:
    T1 __Name;
    T2 __Age;
};

template <class T1, class T2>
void PrintPerson2(Person<T1, T2> P)
{
    cout << "类外实现--姓名：" << P.__Name << " 年龄：" << P.__Age  << endl;

}

void Test()
{
    Person<string ,int> P("Leo", 25);
    PrintPerson(P);
    Person<string ,int> P2("Lee", 25);
    PrintPerson2(P2);
}

int main()
{
    Test();
}