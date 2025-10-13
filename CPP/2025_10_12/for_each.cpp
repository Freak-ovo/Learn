#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;


/**
 * @brief for_each 算法
 * 功能：对容器中的每个元素执行指定操作
 * 返回值：void
 * 参数：
 *      beg：容器开始迭代器
 *      end：容器结束迭代器
 *      op：要执行的操作（函数对象）
 */

class Print
{
public:
    void operator()(int val)
    {
        cout << val << " ";
    }
};
void test_for_each()
{
    vector<int> v;
    //创建容器v并初始化
    for (int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }
    // 利用for_each 算法 对容器v中的每个元素执行打印操作
    cout << "利用for_each 算法 对容器v中的每个元素执行打印操作：" << endl;
    for_each(v.begin(), v.end(), [](int val){cout << val << " ";}); // 利用lambda表达式 对容器v中的每个元素执行打印操作
    cout << endl;
    // 利用for_each 算法 对容器v中的每个元素执行打印操作
    cout << "利用for_each 算法 对容器v中的每个元素执行打印操作：" << endl;// 利用函数对象 对容器v中的每个元素执行打印操作
    for_each(v.begin(), v.end(), Print());
    cout << endl;
}

int main()
{
    test_for_each();
    return 0;
}