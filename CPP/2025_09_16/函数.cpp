#include <iostream>
using namespace std;
/**
 * C语言函数书写要求综合说明
 * 
 * 1. 函数命名：使用有意义的名称，采用小写字母和下划线组合，清晰表达函数功能
 * 2. 参数列表：明确每个参数的类型和含义，参数名应具有描述性
 * 3. 返回值：确保返回类型与函数功能匹配，无返回值时使用void
 * 4. 函数体：保持函数功能单一，避免过长函数，考虑错误处理
 */


int Sum(int X, int Y)
{
    int Sum = 0;
    Sum = X + Y;
    return Sum;
}
int main()
{
    int a = 10, b = 20, c = 0;
    c = Sum(a, b);
    cout << c << endl;
}