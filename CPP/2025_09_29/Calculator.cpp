#include <iostream>
using namespace std;

class Calculator
{
public:
    int Num1;
    int Num2;

    int GetResult(string oper)
    {
        if (oper == "+")
        {
            return Num1 + Num2;
        }
        else if (oper == "-")
        {
            return Num1 - Num2;
        }
        else if (oper == "*")
        {
            return Num1 * Num2;
        }

        else if (oper == "/")
        {
            return Num1 / Num2;
        }
    }
};

void Test()
{
    Calculator c;
    c.Num1 = 10;
    c.Num2 = 10;

    cout << c.Num1 << " + " << c.Num2 << " = " << c.GetResult("+") << endl;
    cout << c.Num1 << " - " << c.Num2 << " = " << c.GetResult("-") << endl;
    cout << c.Num1 << " * " << c.Num2 << " = " << c.GetResult("*") << endl;
    cout << c.Num1 << " / " << c.Num2 << " = " << c.GetResult("/") << endl;
}

/***************************
 * 不用多态 下次扩展就得动源码
 * 在实际开发中 提倡开闭原则
 * 开闭原则：对扩展进行开放，对修改进行关闭
 * 
 * 利用的多态的好处
 * 1、组织结构清晰
 * 2、可读性强
 * 3、
 *  */ 
//使用多态来实现计算器
//实现计算器的抽象类

class AbstractCalculator
{
public:
    int Num1;
    int Num2;
    virtual int GetResult()
    {
        return 0;
    }
};

//加法计算器类
class AddCalculator:public AbstractCalculator
{
public:
    int GetResult()
    {
        return Num1 + Num2;
    }
};

//减法的计算器类
class SubCalculator:public AbstractCalculator
{
public:
    int GetResult()
    {
        return Num1 - Num2;
    }
};
//乘法的计算器类
class MulCalculator:public AbstractCalculator
{
public:
    int GetResult()
    {
        return Num1 * Num2;
    }
};

void test()
{
    //多态使用条件
    //父类指针或引用指向子类

    //加法运算
    AbstractCalculator *abc = new AddCalculator;
    abc->Num1 = 10;
    abc->Num2 = 20;
    cout << abc->Num1 << " + " << abc->Num2 << " = " << abc->GetResult() << endl;
    //用完删除
    delete abc;
        //加法运算
    abc = new SubCalculator;
    abc->Num1 = 10;
    abc->Num2 = 20;
    cout << abc->Num1 << " - " << abc->Num2 << " = " << abc->GetResult() << endl;
    //用完删除
    delete abc;
}
int main()
{
    test();
}