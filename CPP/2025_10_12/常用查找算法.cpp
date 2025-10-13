#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;
/**
 * @brief 常用查找算法
 * 功能：查找容器中是否存在指定的元素
 * 返回值：如果找到元素，返回该元素的迭代器；如果未找到元素，返回容器的结束迭代器
 * 参数：
 * find(beg, end, val)：查找容器中是否存在指定的元素val
 *      beg：容器开始迭代器
 *      end：容器结束迭代器
 *      val：要查找的元素
 *      return：如果找到元素，返回该元素的迭代器；如果未找到元素，返回容器的结束迭代器
 * 
 * find_if(beg, end, op)：查找容器中是否存在满足条件的元素
 *      beg：容器开始迭代器
 *      end：容器结束迭代器
 *      op：要执行的操作（函数对象）
 *      return：如果找到元素，返回该元素的迭代器；如果未找到元素，返回容器的结束迭代器
 * 
 * adjacent_find(beg, end, op)：查找容器中是否存在相邻的两个元素满足条件
 *      beg：容器开始迭代器
 *      end：容器结束迭代器
 *      op：要执行的操作（函数对象）
 *      return：如果找到元素，返回该元素的迭代器；如果未找到元素，返回容器的结束迭代器
 * 
 * binary_search(beg, end, val)：在有序容器中查找是否存在指定的元素val
 *      beg：容器开始迭代器
 *      end：容器结束迭代器
 *      val：要查找的元素
 *      return：如果找到元素，返回true；如果未找到元素，返回false
 *
 * count(beg, end, val)：统计容器中等于指定元素val的元素个数
 *      beg：容器开始迭代器
 *      end：容器结束迭代器
 *      val：要统计的元素
 *      return：容器中等于指定元素val的元素个数
 * 
 * count_if(beg, end, op)：统计容器中满足条件的元素个数
 *      beg：容器开始迭代器
 *      end：容器结束迭代器
 *      op：要执行的操作（函数对象）
 *      return：容器中满足条件的元素个数
 * 
 */


class Person
{
public:
    string _name;
    int _age;
    Person(string name, int age) : _name(name), _age(age) {}
    bool operator==(const Person& other) const {
    return _name == other._name;
}
};
void test_find()
{
    vector<int> v1;
    // 创建容器v1并初始化
    for (int i = 0; i < 10; i++)
    {
        v1.push_back(i);
    }
    // 查找 容器中是否存在元素5
    cout << "------------------" << endl;
    cout << "1.查找容器v1中是否存在元素5"<< endl;
    vector<int>::iterator it = find(v1.begin(), v1.end(), 5);
    if (it != v1.end())
    {
        cout << "容器v1中存在元素5" << endl;
    }
    else
    {
        cout << "容器v1中不存在元素5" << endl;
    }

    // 创建自定义类型
    vector<Person> v2;
    // 创建容器v2并初始化
    for (int i = 0; i < 10; i++)
    {
        v2.push_back(Person("张三" + to_string(i), 18 + i));
    }
    // 查找 容器中是否存在元素"张三3"
    cout << "------------------" << endl;
    cout << "2.查找容器v2中是否存在元素\"张三3\""<< endl;
    vector<Person>::iterator it2 = find(v2.begin(), v2.end(), Person("张三3", 0));
    if (it2 != v2.end())
    {
        cout << "容器v2中存在元素\"张三3\"" << endl;
    }
    else
    {
        cout << "容器v2中不存在元素\"张三3\"" << endl;
    }
}

//find_if
void test_find_if()
{
    vector<int> v2;
    // 创建容器v2并初始化
    for (int i = 0; i < 10; i++)
    {
        v2.push_back(i);
    }
    // 查找 容器中是否存在大于5的元素
    cout << "------------------" << endl;
    cout << "3.查找容器v2中是否存在大于5的元素"<< endl;
    vector<int>::iterator it = find_if(v2.begin(), v2.end(), bind2nd(greater<int>(), 5));//查找大于5的元素
    if (it != v2.end())
    {
        cout << "容器v2中存在大于5的元素" << endl;
    }
    else
    {
        cout << "容器v2中不存在大于5的元素" << endl;
    }
}
int main()
{
    test_find();
    test_find_if();
    return 0;
}

