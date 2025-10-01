#include <iostream>
using namespace std;


/****************************************
 *      this 指针是隐含每一个非静态成员的一种指针
 *      this 指针不需要定义，直接使用即可
 * 
 *      this 指针用途
 *      1.当形参成员和变量名同名时 可以用this指针来区分
 *      2.在类的非静态成员函数中返回对象本身，可以使用return *this
 * 
 * 
 * 
 */

class Person
{
public: 
    int Age;


    Person(int age)
    {
        //this 指针指向 被调用的成员函数 所属的对象
        this->Age = age;
    }
    Person & PersonAddAge(Person &p)
    {
        //this 指向P2的指针，而*this 指向的就是P2这个对象的本体
        this->Age += p.Age;
        return *this;
    }
}; 

void Test()
{
    Person P(18);
    cout << "P的年龄是：" << P.Age << endl;
}

void Test2()
{
    Person P1(18);
    Person P2(18);
    P2.PersonAddAge(P1).PersonAddAge(P1).PersonAddAge(P1);
    cout << "P2的年龄是：" << P2.Age << endl;
}

int main()
{
    Test();
    Test2();
    
}