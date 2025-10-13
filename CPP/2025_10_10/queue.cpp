#include <iostream>
#include <queue>
using namespace std;

/************
 *  queue 队列
 * 先进先出 FIFO(First In First Out)
 *
 * push() 入队                                           pop() 出队
 * 队尾   | 数据元素 | 数据元素 | 数据元素 | 数据元素 | 数据元素 | 队头
 *    ----->------------>------------>--------->--------------->
 * back() 队尾                                             front() 队头
 *
 * 队列容器允许从一端增加元素，从另一端删除元素
 * 队列只有队头和对位才可以被外界使用，因此队列不允许被遍历
 * 队列中进数据称为 入队 push()
 * 队列中出数据称为 出队 pop()
 *
 * 队列常用接口
 * 构造函数：
 *     queue<T> que; // 定义一个队列，存储 T 类型的数据
 * 赋值操作：
 *     queue& operator=(const queue &que); // 赋值运算符重载
 * 数据存储：
 *     push(elem); // 元素 elem 入队
 *     pop(); // 队头元素出队
 *     front(); // 返回队头元素
 *     back(); // 返回队尾元素
 * 大小操作：
 *     empty(); // 判断队列是否为空
 *     size(); // 返回队列中元素的个数
 */

void Test_Queue()
{

    queue<int> que;
    // 入队
    que.push(1);
    que.push(2);
    que.push(3);
    que.push(4);
    que.push(5);

    // 出队
    while (!que.empty())
    {
        cout << "队头元素出队：" << que.front() << endl;
        que.pop();                                  // 队头元素出队
        cout << "队的大小：" << que.size() << endl; // 返回队列中元素的个数
    }
}

class Person 
{
public:
    string _name;
    int _age;
    Person(string name, int age)
    {
        _name = name;
        _age = age;
    }


};

void Test_queue_Person()
{
    queue<Person> que;// 定义一个队列，存储 Person 类型的数据
    // 入队
    que.push(Person("张三", 18));
    que.push(Person("李四", 20));
    que.push(Person("王五", 22));
    que.push(Person("赵六", 24));
    que.push(Person("钱七", 26));

    // 出队
    while (!que.empty())// 只要队列不为空 查看队头 并执行出队操作
    {
        cout << "队头元素出队：" << que.front()._name << " " << que.front()._age << endl;
        que.pop();                                  // 队头元素出队
        cout << "队的大小：" << que.size() << endl; // 返回队列中元素的个数
    }
}


int main()
{
    Test_Queue();
    Test_queue_Person();
    return 0;
}