#include <iostream>
using namespace std;

void MySwap_1(int X, int Y)
{
    int Temp;
    Temp = X;
    X = Y;
    Y = Temp;
    cout << "MySwap_1 X:" << X << endl;
    cout << "MySwap_1 Y:" << Y << endl;
}

void MySwap_2(int *X, int *Y)
{
    int Temp;
    Temp = *X;
    *X = *Y;
    *Y = Temp;
    cout << "MySwap_2 c:" << *X << endl;
    cout << "MySwap_2 d:" << *Y << endl;
}

void MySwap_3(int &X, int &Y)
{
    int Temp;
    Temp = X;
    X = Y;
    Y = Temp;
    cout << "MySwap_3 c:" << X << endl;
    cout << "MySwap_3 d:" << Y << endl;
}

int &test01()
{
    int t = 10;
    return t;
}
int &test02()
{
    static int t = 10;
    return t;
}
int main()
{
    int a = 10;
    int &b = a;
    cout << a << endl;
    cout << b << endl;

    b = 20;
    cout << a << endl;
    cout << b << endl;

    int c = 10;
    int d = 20;

    MySwap_1(c, d);
    cout << "MySwap_1 c:" << c << endl;
    cout << "MySwap_1 d:" << d << endl;

    MySwap_2(&c, &d);
    cout << "MySwap_2 c:" << c << endl;
    cout << "MySwap_2 d:" << d << endl;

    MySwap_3(c, d);
    cout << "MySwap_3 c:" << c << endl;
    cout << "MySwap_3 d:" << d << endl;

    int &Ref = test01();
    cout << "Ref = " << Ref << endl;

    int &Ref2 = test02();
    cout << "Ref2 = " << Ref2 << endl;

}