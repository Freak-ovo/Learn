#include <iostream>
using namespace std;

/* class Java
{
public:
    void Header()
    {
        cout << "首页、 公开课、 登录、注册。。。（公共头部）" << endl;
    }
    
    void Footer()
    {
        cout << "帮助中心、 交流合作、 站内地图。。。（公共底部）" << endl;
    }

    void Left()
    {
        cout << "Java、 python、 C/C++" << endl;
    }
    void Content()
    {
        cout << "Java学科视频" << endl;
    }


};

class CPP
{
public:
    void Header()
    {
        cout << "首页、 公开课、 登录、注册。。。（公共头部）" << endl;
    }
    
    void Footer()
    {
        cout << "帮助中心、 交流合作、 站内地图。。。（公共底部）" << endl;
    }

    void Left()
    {
        cout << "Java、 python、 C/C++" << endl;
    }
    void Content()
    {
        cout << "C++学科视频" << endl;
    }


};

class Python
{
public:
    void Header()
    {
        cout << "首页、 公开课、 登录、注册。。。（公共头部）" << endl;
    }
    
    void Footer()
    {
        cout << "帮助中心、 交流合作、 站内地图。。。（公共底部）" << endl;
    }

    void Left()
    {
        cout << "Java、 python、 C/C++" << endl;
    }
    void Content()
    {
        cout << "Python学科视频" << endl;
    }


};

void Test()
{
    cout << "Java 下载视频页面如下：" << endl;

    Java ja;
    ja.Header();
    ja.Footer();
    ja.Left();
    ja.Content();

    cout << "--------------------" << endl;

    cout << "Python 下载视频页面如下：" << endl;

    Java Python;
    Python.Header();
    Python.Footer();
    Python.Left();
    Python.Content();

    cout << "--------------------" << endl;

    cout << "CPP 下载视频页面如下：" << endl;

    Java CPP;
    CPP.Header();
    CPP.Footer();
    CPP.Left();
    CPP.Content();
}
 */




 /***********************
  *  继承的好处：减少重复代码
  * 语法：class 子类： 继承方式 父类
  * 子类 也称为 派生类
  * 父类 也称为 基类
  * 
  * 
  *  */ 
//继承实现

//公共页面
class BaseUI
{  
public:
    void Header()
    {
        cout << "首页、 公开课、 登录、注册。。。（公共头部）" << endl;
    }
    
    void Footer()
    {
        cout << "帮助中心、 交流合作、 站内地图。。。（公共底部）" << endl;
    }

    void Left()
    {
        cout << "Java、 python、 C/C++" << endl;
    }


};

//Java页面
class Java :public BaseUI
{
public:
    void Content()
    {
        cout << "Java学科视频" << endl;
    }
};
class Cpp :public BaseUI
{
public:
    void Content()
    {
        cout << "C++学科视频" << endl;
    }
};
class Python :public BaseUI
{
public:
    void Content()
    {
        cout << "Python学科视频" << endl;
    }
};

void Test()
{
    cout << "Java 下载视频页面如下：" << endl;

    Java ja;
    ja.Header();
    ja.Footer();
    ja.Left();
    ja.Content();

    cout << "--------------------" << endl;

    cout << "Python 下载视频页面如下：" << endl;

    Python Py;
    Py.Header();
    Py.Footer();
    Py.Left();
    Py.Content();

    cout << "--------------------" << endl;

    cout << "CPP 下载视频页面如下：" << endl;

    Cpp cpp;
    cpp.Header();
    cpp.Footer();
    cpp.Left();
    cpp.Content();
}
int main()
{
    Test();
}
