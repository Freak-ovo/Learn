#include <iostream>
using namespace std;

#include <vector>
#include <algorithm>

/**
 * @brief 谓词
 * 谓词是一个返回值为bool类型的函数对象
 * 一元谓词：只有一个参数
 * 二元谓词：有两个参数
 */

 
class GreaterFive
{
public:
    //一元谓词 ：只有一个参数
    bool operator()(int a)
    {
        return a > 5;
    }

    // 二元谓词：有两个参数
    bool operator()(int a, int b)
    {
        return a > b;
    }
};
void Test_Predicate()
{
    cout << "Test_Predicate调用:" << endl;
    vector<int> v;
    for (int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }
    
    // 查找第一个大于5的元素
    //find_if算法：查找第一个符合条件的元素
    vector<int>::iterator it = find_if(v.begin(), v.end(), GreaterFive());
    cout << "查找第一个大于5的元素：" << endl;
    if (it != v.end())
    {
        cout << "第一个大于5的元素为：" << *it << endl;
    }
    else
    {
        cout << "未找到大于5的元素" << endl;
    }
    // 二元谓词：有两个参数
    bool ret = GreaterFive()(10, 5);
    cout << "10是否大于5：" << endl;
    if (ret)
    {
        cout << "10大于5" << endl;
    }
    else
    {
        cout << "10不大于5" << endl;
    }
}

int main()
{
    Test_Predicate();
    return 0;
}