#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
/**
 * @brief 复制排序算法
 * 功能：将容器中的元素复制到另一个容器中
 * 参数：
 * copy(beg, end, dest)：将容器中的元素复制到另一个容器中
 *      beg：容器开始迭代器
 *      end：容器结束迭代器
 *      dest：目标容器开始迭代器
 *      return：无
 */
void test_copy()
{
    // 创建一个vector容器v1，包含1, 3, 5, 7, 9, 11, 13这7个元素
    vector<int> v1 = {1, 3, 5, 7, 9, 11, 13};
    // 创建一个空容器v2，用于存储复制后的结果
    vector<int> v2(v1.size());
    // 调用copy函数将v1容器中的元素复制到v2容器中
    copy(v1.begin(), v1.end(), v2.begin());
    // 输出复制后的结果
    cout << "复制后的结果：" << endl;
    for (int i = 0; i < v2.size(); i++)
    {
        cout << v2[i] << " ";
    }
    cout << endl;
}
int main()
{
    test_copy();
    return 0;
}