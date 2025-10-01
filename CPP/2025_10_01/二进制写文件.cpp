#include <iostream>
#include <fstream>
using namespace std;

//二进制 写文件
class Person
{
public:
    char _Name[64];
    int _Age;

};

void TestBinaryWrite()
{
    ofstream ofs;
    ofs.open("Person.txt", ios::out | ios::binary);

    Person P = {"李明", 18};
    ofs.write((const char*)&P, sizeof(Person));

    ofs.close();

}

int main()
{
    TestBinaryWrite();
}