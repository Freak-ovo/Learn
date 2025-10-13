#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;
/**
 * @brief 关系仿函数
 * 功能：实现关系运算
 *  返回值：bool类型
 * 其中equal_to 等于
 * not_equal_to 不等于
 * greater 大于
 * greater_equal 大于等于
 * less 小于
 * less_equal 小于等于
 * 
 */

// 二元运算 等于
// equal_to 等于
void test_equal_to()
{
    equal_to<int> e;
    cout << "----------------------------"<< endl;
    cout << "equal_to 等于：" << e(5, 3) << endl;
}

// 二元运算 不等于
// not_equal_to 不等于
void test_not_equal_to()
{
    not_equal_to<int> ne;
    cout << "----------------------------"<< endl;
    cout << "not_equal_to 不等于：" << ne(5, 3) << endl;
}

// 二元运算 大于
// greater 大于
void test_greater()
{
    greater<int> g;
    cout << "----------------------------"<< endl;
    cout << "greater 大于：" << g(5, 3) << endl;
}

// 二元运算 大于等于
// greater_equal 大于等于
void test_greater_equal()
{
    greater_equal<int> ge;
    cout << "----------------------------"<< endl;
    cout << "greater_equal 大于等于：" << ge(5, 3) << endl;
}

// 二元运算 小于
// less 小于
void test_less()
{
    less<int> l;
    cout << "----------------------------"<< endl;
    cout << "less 小于：" << l(5, 3) << endl;
}

// 二元运算 小于等于
// less_equal 小于等于
void test_less_equal()
{
    less_equal<int> le;
    cout << "----------------------------"<< endl;
    cout << "less_equal 小于等于：" << le(5, 3) << endl;
}
void test_greater_sort()
{
    vector<int> v;
    v.push_back(10);
    v.push_back(40);
    v.push_back(20);
    v.push_back(30);
    v.push_back(50);
    cout << "----------------------------"<< endl;
    cout << "greater 排序：" << endl;
    sort(v.begin(), v.end(), greater<int>());
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}
int main()
{
    test_equal_to();
    test_not_equal_to();
    test_greater();
    test_greater_equal();
    test_less();
    test_less_equal();
    test_greater_sort();
    return 0;
}