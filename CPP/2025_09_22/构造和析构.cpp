#include <iostream>
using namespace std;

class Base
{
public:
    Base()
    {
        cout << "Base构造函数" << endl;
    }
    ~Base()
    {
        cout << "Base析构函数" << endl;
    }
};

class Son: public Base
{
public:
    Son()
    {
        cout << "Base构造函数" << endl;
    }
    ~Son()
    {
        cout << "Base析构函数" << endl;
    }
};


void test()
{
    //Base b;
    Son a;
}
int main()
{
    test();
}