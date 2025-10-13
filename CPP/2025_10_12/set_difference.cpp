#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * @brief 集合差集排序算法
 * 功能：将第一个容器中不在第二个容器中的元素复制到另一个容器中
 * 参数：
 * set_difference(beg1, end1, beg2, end2, dest)：将第一个容器中不在第二个容器中的元素复制到另一个容器中
 *      beg1：第一个容器开始迭代器
 *      end1：第一个容器结束迭代器
 *      beg2：第二个容器开始迭代器
 *      end2：第二个容器结束迭代器
 *      dest：目标容器开始迭代器
 *      return：无
 */


void test_set_difference()
{
    // 创建两个vector容器v1和v2，分别包含1, 3, 5, 7, 9, 11, 13这7个元素
    vector<int> v1 = {1, 3, 5, 7, 9, 11, 13};
    vector<int> v2 = {2, 4, 6, 8, 10, 12, 14};
    // 输出v1和v2的原始数据
    cout << "v1的原始数据：" << endl;
    for (int i = 0; i < v1.size(); i++)
    {
        cout << v1[i] << " ";
    }
    cout << endl;
    cout << "v2的原始数据：" << endl;
    for (int i = 0; i < v2.size(); i++)
    {
        cout << v2[i] << " ";
    }
    cout << endl;
    // 创建一个空容器v3，用于存储差集结果
    vector<int> v3(v1.size() + v2.size());
     // 调用set_difference函数将v1中不在v2中的元素复制到v3中
    set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
    // 输出差集结果
    cout << "v1和v2的差集结果：" << endl;
    for (int i = 0; i < v3.size(); i++)
    {
        cout << v3[i] << " ";
    }
    cout << endl;

}
int main()
{
    test_set_difference();
    return 0;
}