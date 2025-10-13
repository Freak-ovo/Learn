#include <iostream>
#include <vector>
#include <algorithm> //C++11新特性 范围for循环
using namespace std;
/********************
 * cpp 三大特性 
 * 封装、继承、多态
 * vector 是一个容器 存放内置数据类型
 * vector 是一个模板类
 * vector 像一个数组 可以存放多个数据
 * 
 */

 void Print(int val)
 {
    cout << val << " ";
 }
void Test()
{
    //创建一个vector容器 存放int类型数据
    vector<int> arr(10);
    
    //遍历容器 并初始化
    for (int i = 0; i < 10; i++)
    {
        arr[i] = i;
    }
    arr.push_back(100); //在容器末尾添加一个数据
    arr.push_back(200); 

    vector<int>::iterator itBegin = arr.begin(); //起始迭代器 指向容器的第一个元素
    vector<int>::iterator itEnd = arr.end();     //结束迭代器 指向容器的最后一个元素的下一个位置
    //遍历容器 并打印
    //第一种方式
    while (itBegin != itEnd)
    {
        cout << *itBegin << " "; //通过迭代器访问容器中的数据
        itBegin++;
    }
    cout << endl;
    cout << "第一种方式" << endl;

    //第二种方式
    for (vector<int>::iterator it = itBegin; it != itEnd; it++)
    {
        cout << *it << " ";
    }
    cout << "第二种方式" << endl;

    //第三种方式
    for_each(arr.begin(), arr.end(), Print);
    cout << endl;
    cout << "第三种方式" << endl;
    for_each(arr.begin(), arr.end(), [](int val) {
        cout << val << " ";
    });
}
/***********
 * vector 中存放自定义数据类型  
 * 自定义数据类型 必须要提供默认构造函数
 */
class Person
{
public:
    string _Name;
    int _Age;
    Person(string name, int age)
    {
        this->_Name = name;
        this->_Age = age;
    }
};

void Test1()
{
    vector<Person> P;
    Person p1("张三", 20);
    Person p2("李四", 30);
    Person p3("王五", 40);
    P.push_back(p1);//将数据存放到容器中
    P.push_back(p2);//将数据存放到容器中
    P.push_back(p3);//将数据存放到容器中
    //遍历容器B 并打印
    for (vector<Person>::iterator it = P.begin(); it != P.end(); it++)
    {
        cout << "姓名：" << (*it)._Name << " 年龄：" << (*it)._Age << endl;
        cout << "姓名：" << it->_Name << " 年龄：" << it->_Age << endl;
    }
    
    for_each(P.begin(), P.end(), [](Person p) {
        cout << "姓名：" << p._Name << " 年龄：" << p._Age << endl;
    });
}
void Test2()
{
    vector<Person*> P2;
    Person p1("lee", 20);
    Person p2("leo", 30);
    Person p3("opo", 40);
    P2.push_back(&p1);//将数据存放到容器中
    P2.push_back(&p2);//将数据存放到容器中
    P2.push_back(&p3);//将数据存放到容器中
    //遍历容器C 并打印
    for (vector<Person*>::iterator it = P2.begin(); it != P2.end(); it++)
    {
        cout << "姓名：" << (*it)->_Name << " 年龄：" << (*it)->_Age << endl;
    }
}
int main()
{
    Test();
    Test1();
    Test2();
    return 0;
}