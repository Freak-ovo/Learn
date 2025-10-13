#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

/**
 * @brief transform 算法
 * 功能：对容器中的每个元素执行指定操作并将结果存储到另一个容器中
 * 返回值：void
 * 参数：
 *      beg：容器开始迭代器
 *      end：容器结束迭代器
 *      op：要执行的操作（函数对象）
 */
// 函数对象
class Transform
{
public:
    int operator()(int val)
    {
        return val * 2;
    }
};

void test_transform()
{
    vector<int> v;
    // 创建容器v并初始化
    for (int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }

    // 创建目标容器w
    vector<int> w;
    w.resize(v.size()); // 开辟空间
    // 利用transform 算法 对容器v中的每个元素执行操作并将结果存储到容器w中
    transform(v.begin(), v.end(), w.begin(), Transform()); // 利用lambda表达式 对容器v中的每个元素执行操作并将结果存储到容器w中
    // 打印容器w中的元素
    cout << "容器w中的元素：" << endl;
    for (vector<int>::iterator it = w.begin(); it != w.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;

    // 利用for_each 算法 打印容器w中的元素
    cout << "容器w中的元素：" << endl;
    for_each(w.begin(), w.end(), [](int val){cout << val << " ";});
    cout << endl;
}

int main()
{
    test_transform();
    return 0;
}