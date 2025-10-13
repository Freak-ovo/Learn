#include <iostream>
using namespace std;

//类模板与继承
template <class T>
class Base
{
    T m;

};
//1.指定父类的数据类型 子类才能继承
class Son :public Base<int>
{


};
//2.如果想灵活的指定父类中T的类型，子类也需要变成类模板
template <class T1, class T2>
class Son2: public Base<T>
{
    T1 obj:
};
void Test()
{
    Son s1;
}

int main()
{
    Test();
}