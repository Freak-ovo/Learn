#include <iostream>
using namespace std;

template <class NameType, class AgeType>
class Person
{
public:
    NameType __Name;
    AgeType __Age;
    Person(NameType Name, AgeType Age)
    {
        this->__Name = Name;
        this->__Age = Age;
    }
    void ShowInfo()
    {
        cout << "Name: " << this->__Name
             << " Age: " << this->__Age << endl;
    }
    ~Person()
    {
    }
};
// 参数模板化
template <class T1, class T2>
void PrintPerson(Person<T1, T2> &P)
{
}

// 整个类模板化
template <class T>
void PrintPerson3(T &P)
{
    P.ShowInfo();
}

void Test()
{
    Person<string, int> P1("李明", 25);
    P1.ShowInfo();
    PrintPerson3(P1);
}

int main()
{
    Test();
}