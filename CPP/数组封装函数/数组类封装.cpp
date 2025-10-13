#include <iostream>
using namespace std;
#include "MyArray.hpp"

/**
 * @brief 测试MyArray类的构造函数、拷贝构造函数和赋值运算符重载
 * 
 * 该函数创建了三个MyArray对象，展示了类的不同构造方式和赋值操作
 * 包括普通构造、拷贝构造和赋值运算符的使用
 */
void Test()
{
    // 创建容量为5的整型数组（调用普通构造函数）
    MyArray<int> Array1(5);
    
    // 通过Array1拷贝创建新数组Array2（调用拷贝构造函数，进行深拷贝）
    MyArray<int> Array2(Array1);
    
    // 创建容量为100的整型数组
    MyArray<int> Array3(100);
    
    // 将Array1赋值给Array3（调用赋值运算符重载，进行深拷贝）
    Array3 = Array1;

}
int main()
{
    Test();
}