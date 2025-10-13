#include <iostream>
#include <list>
using namespace std;
/************
 * list 列表
 * 列表是一个双向循环链表
 * 列表允许在任意位置进行快速插入和删除操作
 * 列表不支持随机访问，只能通过迭代器进行遍历
 * 列表常用接口
 * 构造函数：
 *     list<T> lst; // 定义一个列表，存储 T 类型的数据
 * 赋值操作：
 *     list& operator=(const list &lst); // 赋值运算符重载
 * 数据存储：
 *     push_back(elem); // 元素 elem 入队
 *     pop_back(); // 队头元素出队
 *     front(); // 返回队头元素
 *     back(); // 返回队尾元素
 * 大小操作：
 *     empty(); // 判断列表是否为空
 *     size(); // 返回列表中元素的个数
 ****************************************/

/*********************
 * list 链表
 * 优点
 * 1. 列表允许在任意位置进行快速插入和删除操作
 * 缺点
 * 1. 列表不支持随机访问，只能通过迭代器进行遍历
 * 2. 列表遍历效率较低
 * 3. 列表占用的空间较大，每个节点需要额外的空间存储指针
 * 
 * 双向循环列表
 * 链表存储方式并不是连续的内存空间，而是通过指针将节点连接起来
 * 每个节点占用的内存空间大小是固定的，不依赖于列表中元素的个数
 * list中迭代器只支持前移和后移操作，不支持随机访问
 * 每个节点包含一个指向前一个节点的指针和一个指向后一个节点的指针
 * 列表的头节点的前一个节点指向尾节点，尾节点的后一个节点指向头节点
 * 列表的遍历从头节点的下一个节点开始，遍历到尾节点的前一个节点
 * 
 * 
 * 
 ****************************************/



//list 赋值运算符重载
void Test_list_Assign()
{
    
    list<int> lst;// 定义一个列表，存储 int 类型的数据
    // 入队
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    lst.push_back(4);
    lst.push_back(5);
    
    //遍历
    cout << "列表1中的元素为：" << endl;
    for (list<int>::iterator it = lst.begin(); it != lst.end(); it++)
    {
        cout << *it << " ";// 遍历列表中的元素
    }
    cout << endl;

    //区间构造
    list<int> lst2(lst.begin(), lst.end());// 区间构造
    cout << "列表2中的元素为：" << endl;
    for (list<int>::iterator it = lst2.begin(); it != lst2.end(); it++)
    {
        cout << *it << " ";// 遍历列表2中的元素
    }
    cout << endl;

    //拷贝构造
    list<int> lst3(lst2);// 拷贝构造
    cout << "列表3中的元素为：" << endl;
    for (list<int>::iterator it = lst3.begin(); it != lst3.end(); it++)
    {
        cout << *it << " ";// 遍历列表3中的元素
    }
    cout << endl;
    
    //n个elem
    list<int> lst4(5, 100);// 5个 100
    cout << "列表4中的元素为：" << endl;
    for (list<int>::iterator it = lst4.begin(); it != lst4.end(); it++)
    {
        cout << *it << " ";// 遍历列表4中的元素
    }
    cout << endl;
}


//list 交换
void Test_list_Swap()
{
    list <int> lst5(5, 100);// 5个 100
    cout << "列表5中的元素为：" << endl;
    for (list<int>::iterator it = lst5.begin(); it != lst5.end(); it++)
    {
        cout << *it << " ";// 遍历列表5中的元素
    }
    cout << endl;

    list<int> lst6(5, 200);// 5个 200
    cout << "列表6中的元素为：" << endl;
    for (list<int>::iterator it = lst6.begin(); it != lst6.end(); it++)
    {
        cout << *it << " ";// 遍历列表6中的元素
    }
    cout << endl;
    //交换
    lst5.swap(lst6);// 交换 lst5 和 lst6
    cout << "交换后列表5中的元素为：" << endl;
    for (list<int>::iterator it = lst5.begin(); it != lst5.end(); it++)
    {
        cout << *it << " ";// 遍历列表5中的元素
    }
    cout << endl;
    cout << "交换后列表6中的元素为：" << endl;
    for (list<int>::iterator it = lst6.begin(); it != lst6.end(); it++)
    {
        cout << *it << " ";// 遍历列表6中的元素
    }
    cout << endl;
}

//list 大小操作
// empty(); // 判断列表是否为空
// size(); // 返回列表中元素的个数
void Test_list_size()
{
    list<int> lst7(5, 300);// 5个 300
    cout << "列表7中的元素为：" << endl;
    for (list<int>::iterator it = lst7.begin(); it != lst7.end(); it++)
    {
        cout << *it << " ";// 遍历列表7中的元素
    }
    cout << endl;
    cout << "列表7的大小为：" << lst7.size() << endl;
    
    //重新制定大小
    // resize(num); // 重新制定大小为 num
    lst7.resize(10);// 重新制定大小为 10
    cout << "重新制定大小后的列表7中的元素为：" << endl;
    for (list<int>::iterator it = lst7.begin(); it != lst7.end(); it++)
    {
        cout << *it << " ";// 遍历列表7中的元素
    }
    cout << endl;
    cout << "重新制定大小后的列表7的大小为：" << lst7.size() << endl;
    lst7.resize(2);// 重新制定大小为 2
    cout << "重新制定大小后的列表7中的元素为：" << endl;
    for (list<int>::iterator it = lst7.begin(); it != lst7.end(); it++)
    {
        cout << *it << " ";// 遍历列表7中的元素
    }
    cout << endl;
    cout << "重新制定大小后的列表7的大小为：" << lst7.size() << endl;
}

//list 插入和删除
void Test_list_delete()
{
    list<int> lst8(5, 400);// 5个 400
    cout << "列表8中的元素为：" << endl;
    for (list<int>::iterator it = lst8.begin(); it != lst8.end(); it++)
    {
        cout << *it << " ";// 遍历列表8中的元素
    }
    cout << endl;
    cout << "列表8的大小为：" << lst8.size() << endl;
    //删除
    lst8.pop_back();// 删除尾节点
    cout << "删除尾节点后的列表8中的元素为：" << endl;
    for (list<int>::iterator it = lst8.begin(); it != lst8.end(); it++)
    {
        cout << *it << " ";// 遍历列表8中的元素
    }
    cout << endl;
    cout << "删除尾节点后的列表8的大小为：" << lst8.size() << endl;
}

//list 插入
void Test_list_insert()
{
    list<int> lst9(5, 500);// 5个 500
    cout << "列表9中的元素为：" << endl;
    for (list<int>::iterator it = lst9.begin(); it != lst9.end(); it++)
    {
        cout << *it << " ";// 遍历列表9中的元素
    }
    cout << endl;
    cout << "列表9的大小为：" << lst9.size() << endl;
    //插入
    lst9.insert(++lst9.begin(), 600);// 在第二个位置插入 600
    cout << "插入后的列表9中的元素为：" << endl;
    for (list<int>::iterator it = lst9.begin(); it != lst9.end(); it++)
    {
        cout << *it << " ";// 遍历列表9中的元素
    }
    cout << endl;
    cout << "插入后的列表9的大小为：" << lst9.size() << endl;
}
int main()
{
    Test_list_Assign();
    Test_list_Swap();
    Test_list_size();
    Test_list_delete();
    Test_list_insert();
    return 0;
}