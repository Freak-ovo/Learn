#include <iostream>
#include <fstream>
using namespace std;

//二进制读文件
class Person
{
public:
    char _Name[64];
    int _Age;

};

void TestBinaryRead()
{
    ifstream ifs;

    ifs.open("Person.txt", ios::in | ios::binary);
    if (!ifs.is_open())
    {
        cout << "文件读取失败！" << endl;
        return;
    }
    
    Person P;
    ifs.read((char*)&P, sizeof(Person));
    cout << "姓名：" << P._Name << " 年龄：" << P._Age << endl;

    ifs.close();
}

int main()
{
    TestBinaryRead();
}