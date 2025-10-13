#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
/**
 * @brief 替换排序算法
 * 功能：将容器中的元素替换为指定值
 * 参数：
 * replace(beg, end, old_val, new_val)：将容器中的元素替换为指定值
 *      beg：容器开始迭代器
 *      end：容器结束迭代器
 *      old_val：要替换的旧值
 *      new_val：要替换的新值
 *      return：无
 */

void test_replace()
{
    // 创建一个vector容器v1，包含1, 3, 5, 7, 9, 11, 13这7个元素
    vector<int> v1 = {1, 3, 5, 7, 9, 11, 13};
    // 输出v1的原始数据
    cout << "v1的原始数据：" << endl;
    for (int i = 0; i < v1.size(); i++)
    {
        cout << v1[i] << " ";
    }
    cout << endl;
    // 调用replace函数将v1容器中的元素5替换为100
    replace(v1.begin(), v1.end(), 5, 100);
    // 输出替换后的结果
    cout << "替换后的结果：" << endl;
    for (int i = 0; i < v1.size(); i++)
    {
        cout << v1[i] << " ";
    }
    cout << endl;
}

int main()
{
    test_replace();
    return 0;
}