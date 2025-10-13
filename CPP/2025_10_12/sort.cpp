#include <iostream>   // 用于输入输出
#include <vector>    // 必须包含，否则编译器不认识std::vector
#include <algorithm> // 包含排序算法
using namespace std;
/**
 * @brief 排序算法
 * 功能：对容器中的元素进行排序
 * 参数：
 * sort(beg, end)：对容器中的元素进行排序
 *      beg：容器开始迭代器
 *      end：容器结束迭代器
 *      return：无
 */

void test_sort()
{
    // 创建一个vector容器v1，包含1, 3, 5, 7, 9, 11, 13这7个元素
    vector<int> v1 = {1, 3, 5, 7, 9, 11, 13};
    // 对v1容器中的元素进行排序（默认升序）
    sort(v1.begin(), v1.end());
    // 输出排序后的结果
    cout << "排序后的结果：" << endl;
    for (int i = 0; i < v1.size(); i++)
    {
        cout << v1[i] << " ";
    }
    cout << endl;
}

//random_shuffle
void test_random_shuffle()
{
    // 创建一个vector容器v1，包含1, 3, 5, 7, 9, 11, 13这7个元素
    vector<int> v1 = {1, 3, 5, 7, 9, 11, 13};
    cout << "随机前的数据" << endl;
    for (int i = 0; i < v1.size(); i++)
    {
        cout << v1[i] << " ";
    }
    cout << endl;
    
    // 对v1容器中的元素进行随机打乱
    random_shuffle(v1.begin(), v1.end());
    // 输出打乱后的结果
    cout << "随机打乱后的结果：" << endl;
    for (int i = 0; i < v1.size(); i++)
    {
        cout << v1[i] << " ";
    }
    cout << endl;
}
int main()
{
    test_sort();
    test_random_shuffle();
    return 0;
}