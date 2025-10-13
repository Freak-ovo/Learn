#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;
/*
This is a simple example of using a deque (double-ended queue) in C++.
*/

/********************
 * Deque Example   *
 * 
 * This example demonstrates the basic operations of a deque, including
 * insertion, deletion, and traversal.
 * deque 构造函数 
 * deque是一个双端队列，它可以在队头和队尾进行插入和删除操作。 
 * 
 * deque的基本操作包括：
 * 1. push_front()：在队头插入元素
 * 2. push_back()：在队尾插入元素
 * 3. pop_front()：从队头删除元素
 * 4. pop_back()：从队尾删除元素
 * 5. front()：访问队头元素
 * 6. back()：访问队尾元素
 */
void Test_Deque()
{
    deque<int> dq;
    // 插入元素
    for (int i = 0; i < 10; i++)
    {
        dq.push_back(i);
    }
    
    cout << "Deque elements: ";
    for (int i : dq)
    {
        cout << i << " ";
    }
    cout << endl;
    for (deque<int>::iterator it = dq.begin();it != dq.end(); it++)
    {
        dq.pop_front();
    }
}


/*************
 * deque 赋值操作
 * 1. assign()：赋值操作
 * 2. operator=：赋值操作
 * 3. swap()：交换操作
 */
void Test_deque_PushFront()
{
    deque<int> dq_front;
    // 插入元素
    for (int i = 0; i < 10; i++)
    {
        dq_front.push_front(i);
    }
    cout << "Deque_front elements: ";
    for (int i : dq_front)
    {
        cout << i << " ";
    }
    cout << endl;
    
    deque<int> dq_1;
    dq_1.assign(dq_front.begin(), dq_front.end());
    cout << "Deque_1 elements after assign from Deque_front: ";
    for (int i : dq_1)
    {
        cout << i << " ";
    }
    cout << endl;
    deque<int> dq_2;
    dq_2 = dq_front;
    cout << "Deque_2 elements after assign from Deque_front: ";
    for (int i : dq_2)
    {
        cout << i << " ";
    }
    cout << endl;   

}

/***
 * deque 容器大小 
 * 1. size()：返回deque中元素的个数
 * 2. max_size()：返回deque能容纳的最大元素个数 
 * 3. empty()：判断deque是否为空
 * 4. resize()：改变deque的大小
 * 5. clear()：清空deque
 */
void Test_deque_Size()
{
    deque<int> dq;
    // 插入元素
    for (int i = 0; i < 10; i++)
    {
        dq.push_back(i);
    }
    cout << "Deque size: " << dq.size() << endl;
    cout << "Deque max size: " << dq.max_size() << endl;
    cout << "Is Deque empty? " << (dq.empty() ? "Yes" : "No") << endl;
    dq.resize(5);
    cout << "Deque size after resize to 5: " << dq.size() << endl;
    dq.clear();
    cout << "Deque size after clear: " << dq.size() << endl;
}

void Test_deque_sort()
{
    deque<int> dq_sort;
    // 插入元素
    dq_sort.push_back(3);
    dq_sort.push_back(1); 
    dq_sort.push_back(2);
    dq_sort.push_back(4);
    dq_sort.push_back(5);
    dq_sort.push_back(6);
    cout << "Deque_sort elements before sort: ";
    // 遍历元素
    for (int i : dq_sort)
    {
        cout << i << " ";
    }
    cout << endl;
    // 排序 升序
    sort(dq_sort.begin(), dq_sort.end());
    cout << "Deque_sort elements after sort: ";
    for (int i : dq_sort)
    {
        cout << i << " ";
    }
    cout << endl;
}
int main()
{
    Test_Deque();
    Test_deque_PushFront();
    Test_deque_Size();
    Test_deque_sort();
    return 0;
}