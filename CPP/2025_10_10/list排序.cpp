#include <iostream>
using namespace std;
#include <list>
#include <algorithm>


class Person
{
public:
    string __name;// 姓名
    int __age;// 年龄
    int __height;// 身高
    Person(string name, int age, int height)
    {
        __name = name;
        __age = age;
        __height = height;
    }
};
// 自定义排序规则
// 按照年龄升序排序，如果年龄相同，按照身高降序排序
bool Compare_Person(Person &p1, Person &p2)
{
    if (p1.__age == p2.__age)
    {
        return p1.__height > p2.__height;
    }
    else
    {
        return p1.__age < p2.__age;
    }
}
void Test_list_Sort()
{
    list<Person> lst;   // 定义一个列表，存储 Person 类型的数据
    lst.push_back(Person("张三", 18, 180));
    lst.push_back(Person("李四", 20, 175));
    lst.push_back(Person("王五", 19, 185));
    lst.push_back(Person("赵六", 22, 170));
    lst.push_back(Person("钱七", 21, 178));

    // 遍历
    cout << "排序前的列表为：" << endl;
    for (list<Person>::iterator it = lst.begin(); it != lst.end(); it++)
    {
        cout << "姓名：" << it->__name << " 年龄：" << it->__age << " 身高：" << it->__height << endl;
    }
    cout <<"----------------" << endl;
    // 排序
    //自定义数据类型 排序需要指定规则
    lst.sort(Compare_Person);
    // 遍历
    cout << "排序后的列表为：" << endl;
    for (list<Person>::iterator it = lst.begin(); it != lst.end(); it++)
    {
        cout << "姓名：" << it->__name << " 年龄：" << it->__age << " 身高：" << it->__height << endl;
    }   
}

int main()
{
    Test_list_Sort();
    return 0;
}