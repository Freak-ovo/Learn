#include <iostream>
#include <set>
using namespace std;

/***********************
 * 对组(pair)
 * 对组是一种容器，它可以存储两个元素，这两个元素可以是不同的类型。
 * 对组的每个元素都有一个唯一的键值，用于标识该元素。
 * 对组的元素是有序的，默认是按照元素的键值进行排序的。
 * 对组的元素是唯一的，不允许重复。
 */
void Test_pair()
{
    pair<int, string> p1(10, "张三");
    cout << "对组1中的元素为：" << endl;
    cout << "第一个元素为：" << p1.first << endl;
    cout << "第二个元素为：" << p1.second << endl;
}

/**************
 * 
 * set 自定义排序
 * 集合(set)可以自定义排序规则，例如按照元素的某个属性进行排序。
 * 自定义排序规则需要在定义集合时指定，例如：set<int, greater<int>> s1;
 * 这表示集合s1中的元素是按照降序排列的。
 *   bool operator<(const int& a, const int& b)
 *   {
 *       return a > b;
 *   }
 * 
 */

class MyCompare
{
public:
    bool operator()(int a, int b)
    {
        return a > b;
    }
};


void Test_set_sort()
{
    set <int, MyCompare> s1;
    s1.insert(10);
    s1.insert(40);
    s1.insert(20);
    s1.insert(10);
    s1.insert(50);
    s1.insert(30);
    // 打印集合元素
    cout << "集合1中的元素为：" << endl;
    for (set<int>::iterator it = s1.begin(); it != s1.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;

}
int main()
{
    Test_pair();
    Test_set_sort();
    return 0;
}