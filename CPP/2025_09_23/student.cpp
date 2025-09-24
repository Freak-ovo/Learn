#include <iostream>
using namespace std;

class student
{

/**************************************
 * 类中的属性和行为我们统称为 成员
 * 属性     成员属性    成员变量  
 * 行为     成员函数    成员方法
 * 
 * 
 *  */ 
public:
    string Name;
    int ID;

    void SetName(string name)
    {
        Name = name;
    }
    void SetID(int Id)
    {
        ID = Id;
    }
    void ShowName()
    {
        cout << "姓名：" << Name <<endl;
    }
    void ShowID()
    {
        cout << "学号：" << ID <<endl;
    }
};




int main()
{
    student s1;
    s1.Name = "李明";
    s1.ID = 2252222;
    s1.ShowName();
    s1.ShowID();
    student s2;
    s2.SetName("张三");
    s2.SetID(20160216);
    s2.ShowName();
    s2.ShowID();
    
}