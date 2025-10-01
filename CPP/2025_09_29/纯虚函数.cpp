#include <iostream>
using namespace std;
/******
 * 纯虚函数
 * 只要有一个纯虚函数 这个类称为抽象类
 * 
 * 1、抽象类 无法实例化对象
 * 2、抽象类的子类 必须重写父类中的纯虚函数，否则也属于抽象类
 * 
 *  */ 
class Base
{
public:
    //纯虚函数
    virtual void func() = 0;


};

class Son:public Base
{
public:
    //子类 必须重写父类中的纯虚函数，否则也属于抽象类
    virtual void func()
    {
        cout << "func 函数调用" << endl;
    };

};

void Test()
{
/*     Base b;//抽象类 无法实例化对象
    new Base b;//抽象类 无法实例化对象 */

    Son B;//子类 必须重写父类中的纯虚函数，否则也属于抽象类
    
    //多态
    Base *base = new Son;
    base->func();
}

int main()
{
    Test();
}