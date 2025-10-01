#include <iostream>
using namespace std;

class AbstractDrinking
{
public:

    //饮品名称
    virtual void Name() = 0;
    //煮水
    virtual void Boil() = 0;

    //冲泡
    virtual void Brew() = 0;

    //倒入杯中
    virtual void PourInCup() = 0;

    //加入辅料
    virtual void PutSomeThing() = 0;

    //制作饮品
    void MakeDrink()
    {
        Name();
        Boil();
        Brew();
        PourInCup();
        PutSomeThing();
    }
};

//制作coffee
class Coffee :public AbstractDrinking
{
    //饮品名称
    virtual void Name()
    {
        cout << "Coffee制作" << endl;
    }
   //煮水
    virtual void Boil()
    {
        cout << "煮自来水" << endl;
    }

    //冲泡
    virtual void Brew()
    {
        cout << "冲泡Coffee" << endl;
    }
    //倒入杯中
    virtual void PourInCup()
    {
        cout << "倒入杯中" << endl;

    }
    //加入辅料
    virtual void PutSomeThing()
    {
        cout << "加入牛奶和糖" << endl;

    }
};

//制作奶茶
class MilkTea :public AbstractDrinking
{
    //饮品名称
    virtual void Name()
    {
        cout << "MikeTea制作" << endl;
    }
   //煮水
    virtual void Boil()
    {
        cout << "煮山泉水" << endl;
    }

    //冲泡
    virtual void Brew()
    {
        cout << "冲泡茶叶" << endl;
    }
    //倒入杯中
    virtual void PourInCup()
    {
        cout << "倒入杯中" << endl;

    }
    //加入辅料
    virtual void PutSomeThing()
    {
        cout << "加入牛奶和糖" << endl;

    }
};

//制作函数
void DoWork(AbstractDrinking *Abc)
{
    Abc->MakeDrink();
    delete Abc;
}

void Test()
{
    DoWork(new Coffee);
    cout << "------------------" << endl;
    DoWork(new MilkTea);

}

int main()
{
    Test();
}
