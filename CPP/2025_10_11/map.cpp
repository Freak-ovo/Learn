#include <iostream>
#include <map>
using namespace std;

/*****************
 * 映射(map)
 * 映射是一种容器，它可以存储键值对(key-value pair)，每个键值对都有一个唯一的键(key)，用于标识该元素。
 * 映射的元素是有序的，默认是按照键的升序排列的。
 * 映射的元素是唯一的，不允许重复。
 * 映射的元素可以通过键来访问，例如：map<int, string> m1; m1[10] = "张三";
 * 映射的元素可以通过迭代器来遍历，例如：for (map<int, string>::iterator it = m1.begin(); it != m1.end(); it++)
 * 映射的元素可以通过键来删除，例如：m1.erase(10);
 * 映射的元素可以通过键来查找，例如：map<int, string>::iterator it = m1.find(10);
 * 如果找到，it指向该元素；如果未找到，it指向m1.end()。
 */

void Test_map()
{
    map<int, string> m1;
    m1[10] = "张三";
    m1[40] = "李四";
    m1[20] = "王五";
    m1[10] = "赵六";
    // 打印映射元素
    cout << "映射1中的元素为：" << endl;
    for (map<int, string>::iterator it = m1.begin(); it != m1.end(); it++)
    {
        cout << "键为：" << it->first << "，值为：" << it->second << endl;
    }
    // size
    cout << "映射1中的元素个数为：" << m1.size() << endl;
    // empty
    cout << "映射1是否为空：" << m1.empty() << endl;

    map <int ,string> m2;
    m2.insert(pair<int, string>(25, "leo"));
    // 打印映射元素
    cout << "映射2中的元素为：" << endl;
    for (map<int, string>::iterator it = m2.begin(); it != m2.end(); it++)
    {
        cout << "键为：" << it->first << "，值为：" << it->second << endl;
    }
    // size
    cout << "映射2中的元素个数为：" << m2.size() << endl;
    // empty
    cout << "映射2是否为空：" << m2.empty() << endl;

    // 交换 m1 和 m2 中的元素
    cout << "交换映射1和映射2中的元素后：" << endl;
    m1.swap(m2);
    // 打印映射元素
    cout << "映射1中的元素为：" << endl;
    for (map<int, string>::iterator it = m1.begin(); it != m1.end(); it++)
    {
        cout << "键为：" << it->first << "，值为：" << it->second << endl;
    }
    cout << "映射2中的元素为：" << endl;
    for (map<int ,string>::iterator it = m2.begin(); it != m2.end(); it++)
    {
        cout << "键为：" << it->first << "，值为：" << it->second << endl;
    }

    // 删除操作
    cout << "删除映射m2中的元素20后：" << endl;
    m2.erase(20); 
    // 打印映射元素
    cout << "映射2中的元素为：" << endl;
    for (map<int ,string>::iterator it = m2.begin(); it != m2.end(); it++)
    {
        cout << "键为：" << it->first << "，值为：" << it->second << endl;
    }   

    // 查找m2中是否有元素20
    cout << "查找映射m2中是否有元素20：" << endl;
    map<int ,string>::iterator it = m2.find(25);
    if (it != m2.end()) 
    {
        cout << "找到元素20，键为：" << it->first << "，值为：" << it->second << endl;
    }
    else
    {
        cout << "未找到元素20" << endl;
    }
    
   

}

int main()
{
    Test_map();
    return 0;
}