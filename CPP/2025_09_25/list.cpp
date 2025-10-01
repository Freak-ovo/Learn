#include <iostream>
using namespace std;

class Person
{
public:
    int A;
    int B;
    int C;
/*     // 传统初始化操作
    Person(int a, int b, int c)
    {
        A = a;
        B = b;
        C = c;
    } */
    // 列表初始化属性
    Person() : A(10), B(20), C(30)
    {
    }

     Person(int a, int b, int c) :A(a), B(b), C(c)
    {
    }
};

void Test01()
{
/*     Person P(10, 20, 30); */
    Person P;

    cout << "A = " << P.A << endl;
    cout << "B = " << P.B << endl;
    cout << "C = " << P.C << endl;
}

int main()
{
    Test01();
}