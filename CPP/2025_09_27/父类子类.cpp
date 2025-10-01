#include <iostream>
using namespace std;

class Base
{
public:
    int P_A;

private:
    int P_B;

protected:
    int P_C;
};

class Son :public Base
{
public:
    void func()
    {
        P_A = 10;//父类的公共权限成员 到子类中依然是公共权限
        P_C = 10;//父类的保护权限成员 到子类中依然是保护权限
        //P_B = 10;//父类中的隐私权限成员 子类不可以访问
    }
};
void Test()
{
    Son S1;
    S1.P_A = 100;
    //S1.P_C 到Son中 P_C是保护权限 类外访问不到
    
}
//保护继承
class Base2
{
public:
    int P_A;

private:
    int P_B;

protected:
    int P_C;
};

class Son2 :protected Base2
{
    public:

    void func()
    {
        P_A = 10;//父类中公共的成员 到子类中变为保护权限
        P_C = 10;//父类中保护成员 到子类中变为保护成员
        //P_B = 10; //父类中私有成员是访问不到的
    }
};

void Test2()
{
    Son2 S2;
    //S2.P_A = 10;//在Son中 P_A变为保护权限 因此类外访问不到
    //S2.P_C = 10;//在Son中 P_C变为保护权限 因此类外访问不到
}

class Base3
{

public:
    int P_A;

private:
    int P_B;

protected:
    int P_C;
};

class Son3 :private Base3
{
public:
    void func()
    {
        P_A = 10;//父类在公共成员 到子类中变为私有成员
        P_C = 10;//父类在保护成员 到子类中变为私有成员
        //P_B = 10;//父类在隐私成员 子类不能访问
    }
};
class GrandSon3 :public Son3
{
public:
    void func()
    {
        //到了Son3中 所有成员变为隐私类 即使是儿子也不能访问不到
       /*  P_A = 10;
        P_C = 10;
        //P_B = 10; */
    }
};
void Test3()
{
    Son2 S3;
    //S2.P_A = 10;//在Son中 P_A变为保护权限 因此类外访问不到
    //S2.P_C = 10;//在Son中 P_C变为保护权限 因此类外访问不到
}