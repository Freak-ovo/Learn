#include <iostream>
using namespace std;

class Phone
{
public:
    string PNmae;
    Phone(string Pname)
    {
        PNmae = Pname;
        cout << "Phone 构造函数调用" << endl;
    }
    ~Phone()
    {
        cout << "Phone 析构函数调用" << endl;

    }
};
class Person
{
public:
    Person(string name, string Pname) : Name(name), Phone(Pname)
    {
        cout << "Person 构造函数调用" << endl;
    }
    ~Person()
    {
        cout << "Person 析构数调用" << endl;

    }
    string Name;
    Phone Phone;
};

void Test()
{
    Person P("张三", "iPhone");
}

int main()
{
    Test();
}