#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;
/**
 * @brief 算术仿函数
 * 功能：实现四则运算
 * 其中negate是一元运算 取反
 * 二元运算 plus 加法
 * 二元运算 minus 减法
 * 二元运算 multiplies 乘法
 * 二元运算 divides 除法
 */

 // 一元运算 取反
 // negate 取反
void test_negate()
{
    negate<int> n;
    cout << "----------------------------"<< endl;
    cout << "negate 取反：" << n(5) << endl;
    cout << "negate 取反：" << n(-5) << endl;
}

// 二元运算 加法
// plus 加法
void test_plus()
{
    plus<int> p;
    cout << "----------------------------"<< endl;
    cout << "plus 加法：" << p(5, 3) << endl;
}

int main()
{
    test_negate();
    test_plus();
    return 0;
}