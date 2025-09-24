#include <iostream>
using namespace std;

int *func()
{
    // 利用new关键字 可以将数据开辟到堆区
    // new返回值是该数据类型的指针
    // 堆区的数据由程序员开辟 和释放
    // 释放堆区的数据关键字是 delete
    int *p = new int(10);
    return p;
}

void task_1()
{
    int *p = func();
    cout << *p << endl;
    cout << *p << endl;
    delete p; // 释放 p
    cout << *p << endl;
}

// 堆区利用new开辟数组
void task_02()
{
    // 创建10整型数据的数组，在堆区
    int *array = new int[10];
    for (int i = 0; i < 10; i++)
    {
        array[i] = i;
    }
    for (int i = 0; i < 10; i++)
    {
        cout << array[i] << " ";
    }
    // 释放堆区数组
    delete[] array;
}
int main()
{
    task_1();
    task_02();
}