#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
/**
 * @brief 合并排序算法
 * 功能：将两个有序容器合并为一个有序容器
 * 参数：
 * merge(beg1, end1, beg2, end2, dest)：将两个有序容器合并为一个有序容器
 *      beg1：第一个容器开始迭代器
 *      end1：第一个容器结束迭代器
 *      beg2：第二个容器开始迭代器
 *      end2：第二个容器结束迭代器
 *      dest：合并后的容器开始迭代器
 *      return：无
 */

void test_merge()
{
    // 创建两个有序容器v1和v2
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
    // 创建一个空容器v3，用于存储合并后的结果
    vector<int> v3(v1.size() + v2.size());
    // 调用merge函数将v1和v2合并到v3中
    merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
    // 输出合并后的结果
    cout << "合并后的结果：" << endl;
    for (int i = 0; i < v3.size(); i++)
    {
        cout << v3[i] << " ";
    }
    cout << endl;
}
int main()
{
    test_merge();
    return 0;
}