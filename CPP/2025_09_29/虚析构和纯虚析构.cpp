#include <iostream>
using namespace std;
/****
 * 纯虚析构 需要声明也需要实现
 * 有了纯虚析构之后这个类也属于抽象类无法实例化对象
 * 
 * 虚析构和纯虚析构的共性 
 *  可以解决父类指针释放子类对象
 *  都需要具体函数实现
 * 虚析构和纯虚析构的区别
 *  如果纯虚析构 该类属于抽象类 无法实例化
 */
class Animal
{
public:
    Animal()
    {
        cout << "Animal构造函数调用" << endl;
    }
/*     virtual~Animal()
    {
        cout << "Animal析构函数调用" << endl;
    } */
    //纯虚析构函数
    virtual~Animal() = 0;
    //纯虚函数
    virtual void Speak() = 0;


};
Animal ::~Animal()
{
    cout << "Animal纯虚析构构函数调用" << endl;

}
class Cat :public Animal
{
public:
    Cat(string name)
    {
        cout << "Cat构造函数调用" << endl;
        Name = new string(name);
    }
    virtual void Speak()
    {
        cout << *Name << "小猫在说话" << endl;
    }
    ~Cat()
    {
        if (Name != NULL)
        {
            cout << "Cat析构函数调用" << endl;
            delete Name;
            Name = NULL;
        }
        
    }

    string *Name;
};

void Test()
{
    Animal *animal = new Cat("Tom");
    animal->Speak();
    //父类的指针在析构的时候不会调用子类的析构函数，导致子类如果有堆区的属性，出现内存的泄露
    delete animal;
}

int main()
{
    Test();
}