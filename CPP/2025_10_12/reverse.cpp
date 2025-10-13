#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
/**
 * @brief 反转排序算法
 * 功能：将容器中的元素反转排序
 * 参数：
 * reverse(beg, end)：将容器中的元素反转排序
 *      beg：容器开始迭代器
 *      end：容器结束迭代器
 *      return：无
 */
void test_reverse()
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
    // 调用reverse函数将v1容器中的元素反转排序
    reverse(v1.begin(), v1.end());
    // 输出反转排序后的结果
    cout << "反转排序后的结果：" << endl;
    for (int i = 0; i < v1.size(); i++)
    {
        cout << v1[i] << " ";
    }
    cout << endl;
}
int main()
{
    test_reverse();
    return 0;
}