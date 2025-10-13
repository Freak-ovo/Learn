#include <iostream>
#include <stack>
using namespace std;
/***********
 * 栈 stack
 * 先进后出 FILO(First In Last Out)
 *
 * 栈底   | 数据元素 |
 *       | 数据元素 |
 *       | 数据元素 |
 *       | 数据元素 |
 *       | 数据元素 |
 * 栈顶   | 数据元素 | <-- 栈顶指针 top
 * push()           入栈 pop() 出栈
 * 入栈：top++ 栈顶指针上移 栈顶元素入栈
 * 出栈：top-- 栈顶指针下移 栈顶元素出栈
 * 栈的应用：表达式求值、括号匹配、深度优先搜索等
 * 栈的实现：数组、链表
 * 数组实现：栈顶指针 top 指向栈顶元素
 * 链表实现：栈顶指针 top 指向栈顶节点
 * 栈的时间复杂度：O(1)
 * 栈的空间复杂度：O(n)
 */

 /***********
  * stack 的常用操作
  * good good study, day day up!
  *     stack<int> stk; // 定义一个栈，存储 int 类型的数据
  *     stcak<const stack &stk> // 拷贝构造函数
  * 赋值操作：
  *     stack& operator=(const stack &stk); // 赋值运算符重载
  * 数据存储：
  *     push(elem); // 元素 elem 入栈
  *     pop(); // 栈顶元素出栈
  *     top(); // 返回栈顶元素
  * 大小操作：
  *     empty(); // 判断栈是否为空
  *     size(); // 返回栈中元素的个数
  * 
  * 栈的遍历： 栈不支持遍历
  */

void Test_Stack()
{
    stack<int> stk;// 定义一个栈，存储 int 类型的数据
    stk.push(1); // 元素 1 入栈
    stk.push(2); // 元素 2 入栈
    stk.push(3); // 元素 3 入栈
    stk.push(4); // 元素 4 入栈
    stk.push(5); // 元素 5 入栈
    //只要栈不为空 查看栈顶 并执行出栈操作
    while (!stk.empty())
    {
        cout <<"栈顶元素出栈：" << stk.top() << endl;
        stk.pop(); // 栈顶元素出栈
        
        cout << "栈的大小：" << stk.size() << endl; // 返回栈中元素的个数   
    }
    
    cout << stk.empty() << endl; // 判断栈是否为空，返回 1 表示为空
}

int main()
{
    Test_Stack();
    return 0;
}