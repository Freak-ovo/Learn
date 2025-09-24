#include <iostream>
using namespace std;


void ShowValue(const int &val)
{
    cout << "val = " << val << endl;
}
int main()
{
    //加入const ref 变为只读 不能修改
    const int & ref = 10;//引用必须引用一块合法的空间
    int a = 10;
    ShowValue(a);
}