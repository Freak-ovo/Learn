#include <iostream>
using namespace std;

class Person
{
public:
    void SetName(string NAME)
    {
        Name = NAME;
    }
    
    string GetName()
    {
        return Name;
    }

    int GetAge()
    {
        return Age;
    }

    void SetIdol(string Name)
    {
        Idol = Name;
    }
    string GetIdol()
    {
        return Idol;
    }
private:
    string Name;
    int Age = 19;
    string Idol;

};

int main()
{
    Person P1;
    P1.SetName("李明");
    P1.SetIdol("张三");
    cout << "姓名：" << P1.GetName() << endl;
    cout << "年龄：" << P1.GetAge() << endl;
    cout << "偶像：" << P1.GetIdol() << endl;

}
