#include <iostream>
#include <set>
using namespace std;

/*****************
 * 多集合(multiset)
 * 多集合是一种容器，它可以存储多个元素，并且元素是有序的。
 * 多集合的每个元素都有一个唯一的键值，用于标识该元素。
 * 多集合的元素是有序的，默认是按照元素的键值进行排序的。
 * 多集合的元素是可以重复的。
 */

void Test_multiset()
{
    multiset<int> ms1;
    ms1.insert(10);
    ms1.insert(40);
    ms1.insert(20);
    ms1.insert(10);
    ms1.insert(50);
    ms1.insert(30);
    // 遍历
    // 打印集合中的元素
    cout << "多集合1中的元素为：" << endl;
    for (multiset<int>::iterator it = ms1.begin(); it != ms1.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}


int main()
{
    Test_multiset();
    return 0;
}