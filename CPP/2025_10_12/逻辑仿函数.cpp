#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;
/**
 * @brief 逻辑仿函数
 * 功能：实现逻辑运算
 * 返回值：bool类型
 * 其中logical_and 与
 * logical_or 或
 * logical_not 非
 */

void test_logical_and()
{
    logical_and<int> la;
    cout << "----------------------------"<< endl;
    cout << "logical_and 与：" << la(5, 3) << endl;
}
void test_logical_or()
{
    logical_or<int> lo;
    cout << "----------------------------"<< endl;
    cout << "logical_or 或：" << lo(5, 3) << endl;
}
void test_logical_not()
{
    logical_not<int> ln;
    cout << "----------------------------"<< endl;
    cout << "logical_not 非：" << ln(5) << endl;
}

void test_logical_swap()
{
    vector<bool> v;
    v.push_back(true);
    v.push_back(false);
    v.push_back(true);
    v.push_back(false);
    cout << "----------------------------"<< endl;
    cout << "logical_swap 交换：" << endl;
    cout << "交换前v容器中的元素：" << endl;
    for (vector<bool>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
    // 利用逻辑非 将容器v中的元素取反并移动到w容器
    vector<bool> w;
    w.resize(v.size()); // 开辟空间
    transform(v.begin(), v.end(), w.begin(), logical_not<bool>()); // 利用逻辑非 将容器v中的元素取反并移动到w容器
    cout << "交换后w容器中的元素：" << endl;
    for (vector<bool>::iterator it = w.begin(); it != w.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}

int main()
{
    test_logical_and();// 与
    test_logical_or();// 或
    test_logical_not();// 非
    test_logical_swap();// 交换
    return 0;
}
