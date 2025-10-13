#include <iostream>
#include <set>
using namespace std;
/****************
 * 集合(set)
 * 集合是一种容器，它可以存储唯一的元素，并且元素是有序的。
 * 集合的每个元素都有一个唯一的键值，用于标识该元素。
 * 集合的元素是有序的，默认是按照元素的键值进行排序的。
 * 集合的元素是唯一的，不允许重复。
 */

void Test_set()
{
    set<int> s1;// 定义一个集合，存储 int 类型的数据
    s1.insert(10);
    s1.insert(40);
    s1.insert(20);
    s1.insert(10);
    s1.insert(50);
    s1.insert(30);
    // 遍历
    // 打印集合中的元素
    cout << "集合1中的元素为：" << endl;
    for (set<int>::iterator it = s1.begin(); it != s1.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
    // 判断是否为空
    if (s1.empty())
    {
        cout << "集合1为空" << endl;
    }
    else
    {
        cout << "集合1不为空" << endl;
    }

    //
    set<int> s2;
    s2.insert(2);
    s2.insert(1);
    s2.insert(5);
    s2.insert(4);
    s2.insert(6);
    s2.insert(5);
    // 打印集合中的元素
    cout << "集合s2中的元素为：" << endl;
    for (set<int>::iterator it = s2.begin(); it != s2.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;

    //交换s和s2
    s1.swap(s2);
    // 打印集合1中的元素
    cout << "交换后的集合1中的元素为：" << endl;
    for (set<int>::iterator it = s1.begin(); it != s1.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
    // 打印集合s2中的元素
    cout << "交换后的集合s2中的元素为：" << endl;
    for (set<int>::iterator it = s2.begin(); it != s2.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
    //删除集合1中的第一个元素
    cout << "删除集合1中的第一个元素后为：" << endl;
    s1.erase(s1.begin());
    for (set<int>::iterator it = s1.begin(); it != s1.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
    //清空s2
    cout << "清空集合s2后为：" << endl;
    s2.clear();
    if (s2.empty())
    {
        cout << "集合s2为空" << endl;
    }
    else
    {
        cout << "集合s2不为空" << endl;
    }

    //查找集合1中是否有50
    cout << "集合1中是否有50：" << endl;
    set<int> ::iterator pos = s1.find(50);
    if (pos != s1.end())
    {
        cout << "集合1中存在50" << endl;
        cout << "50的位置为：" << *pos << endl;
    }
    else
    {
        cout << "集合1中不存在50" << endl;
    }   
    set<int> s3;
    s3.insert(30);
    s3.insert(30);
    s3.insert(30);
    //统计集合3中元素的个数
    int num = s3.count(30);
    cout << "集合3中元素30的个数为：" << num << endl;   
}
int main()
{
    Test_set();
    return 0;
}