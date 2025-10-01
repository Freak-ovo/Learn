#include <iostream>
using namespace std;

class Person
{
public:
    int A;
    int B;
public:
    //类函数重载
/*     Person operator+(Person &p)
    {
        Person Temp; 
        Temp.A = this->A + p.A;
        Temp.B = this->B + p.B;
        return Temp;
    } */
};
//全局函数重载
Person operator+(Person &p1, Person &p2)
{
        Person Temp;
        Temp.A = p1.A + p2.A;
        Temp.B = p1.B + p2.B;
        return Temp;
    
}
void Test()
{
    Person P1;
    P1.A = 10;
    P1.B = 10;

    Person P2;
    P2.A = 20;
    P2.B = 30;
    
    //成员函数重载本质调用
    Person P3 = P1 + P2;
    cout << "P3.A = " << P3.A << endl;
    cout << "P3.B = " << P3.B << endl;
    //全局函数重载的本质调用
    Person P4 = operator+(P1, P2);
    cout << "P4.A = " << P3.A << endl;
    cout << "P4.B = " << P3.B << endl;

    //运算符重载 也可也发生函数重载

}

int main()
{
    Test();
}