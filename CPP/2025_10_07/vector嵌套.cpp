#include <iostream>
#include <vector>
#include <algorithm> //C++11新特性 范围for循环
using namespace std;

/************
 * vector 嵌套  二维数组
 *  vector< vector<int> > v;
 *  大容器中 每个元素都是一个小容器
 *  小容器中 每个元素都是int类型数据
 * 
 */
void Test()
{
    //大容器中<小容器>
    vector< vector<int> > v;
    
    //创建三个小容器
    vector<int> v1;
    vector<int> v2;
    vector<int> v3;

    //向小容器中添加数据
    for (int i = 0; i < 3; i++) 
    {
        
        v1.push_back(i);
        v2.push_back(i+1);
        v3.push_back(i+2);
    }

    //将小容器添加到大容器中
    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);

    //通过大容器遍历小容器
    for (vector< vector<int>>::iterator it = v.begin(); it != v.end(); it++)
    {
        //(*it)就是小容器
        for (vector<int>::iterator it2 = (*it).begin(); it2 != (*it).end(); it2++)
        {
            cout << *it2 << " ";
        }
        cout << endl;
    }

}

int main()
{
    Test();
    return 0;
}