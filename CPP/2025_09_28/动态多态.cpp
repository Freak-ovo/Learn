#include <iostream>
using namespace std;
/*****
 * 动态多态满足的条件
 * 1、有继承关系
 * 2、子类重写父类的虚函数
 * 
 * 动态多态的使用
 * 父类的指针或者引用 执行子类对象
 * 
 * 
 **/
//动物类
class Animal
{
public:
    virtual void Speak()
    {
        cout << "动物在说话" << endl;
    }
};

//猫类
class Cat:public Animal
{
public:
    void Speak()
    {
        cout << "小猫在说话" << endl;

    }
};
class Dog:public Animal
{
public:
    void Speak()
    {
        cout << "小狗在说话" << endl;

    }
};
void DoSpeak(Animal &animal) //Animal &animal = cat
{
    animal.Speak();
}

void Test()
{
    Cat cat;
    DoSpeak(cat);

    Dog dog;
    DoSpeak(dog);
}

int main()
{
    Test();
}