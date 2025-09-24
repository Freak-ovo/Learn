#include <iostream>
using namespace std;
/*************
 * 利用开发人员命令提示工具查看对象模型
 * 跳转 D:
 * 进入文件路径 cd:
 * 查看命令 c1 /d1 reportSingleClassLayout类名称 文件名
 * 
 */
class Base1
{
public:
    int M_A;

protected:
    int M_B;

private:
    int M_C;
};

//公共继承
class Son1 :public Base1
{
public:
    void func()
    {
        M_A = 10;//父类中公共权限成员 到子类中依然是公共权限
        M_B = 10;//父类中保护权限成员 到子类中依然是保护权限
        //M_C = 10;//父类中公共隐私成员 子类不能访问

    }
};

void test()
{
    Son1 s1;
    s1.M_A = 100;
    //s1.M_B = 100;//到son1中 M_B是保护权限 类外访问不到
}

class Base2
{
public:
    int M_A;

protected:
    int M_B;

private:
    int M_C;
};

class Son2 :protected Base2
{
public:
    void func()
    {
        M_A = 100;//父类中公共成员 到子类中变为保护权限
        M_B = 100;//父类中保护成员 到子类中变为保护权限
        //M_C = 100;//父类中的私有成员 子类访问不到
    }
};

//私有继承
class Base3
{
public:
    int M_A;

protected:
    int M_B;

private:
    int M_C;
};

class Son3 :protected Base3
{
public:
    void func()
    {
        M_A = 100;//父类中公共成员 到子类中变为保护权限
        M_B = 100;//父类中保护成员 到子类中变为保护权限
        //M_C = 100;//父类中的私有成员 子类访问不到
    }
};

void test3()
{
    Son3 s1;
    /* s1.M_A = 100; */

}
int main()
{
}
