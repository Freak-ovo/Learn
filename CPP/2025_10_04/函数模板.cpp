#include <iostream>
using namespace std;
/*********************
 * 函数模板使用注意事项
 * 
 * template <class T> typename可以替换为class
 * 
 * 1.自动类型推导，必须推导出一致的数据类型T 才可以使用
 * 2.模板必须要确定出T的数据类型，才可以使用
 */

/**
 * @brief 通用交换函数模板
 * 
 * 交换两个相同类型变量的值
 * 
 * @tparam T 数据类型模板参数
 * @param a 第一个变量的引用
 * @param b 第二个变量的引用
 * 
 * @note 支持任意数据类型的交换操作
 */
template <typename T>
void MySwap(T &a, T &b)
{
    T temp = a;  // 临时保存第一个值
    a = b;       // 将第二个值赋给第一个变量
    b = temp;    // 将临时值赋给第二个变量
}

/**
 * @brief 通用数组排序函数模板
 * 
 * 使用选择排序算法对数组进行从大到小排序
 * 
 * @tparam T 数组元素数据类型
 * @param Array 要排序的数组
 * @param Length 数组长度
 * 
 * @note 支持任意可比较数据类型的数组排序
 * @warning 当前实现存在逻辑错误，需要修复
 */
template <class T>
void MySort(T Array[], int Length)
{
    // 外层循环：控制排序轮次，每轮确定一个位置的元素
    for (int i = 0; i < Length; i++)
    {
        int Max = i;  // 记录当前轮次最大值索引
        
        // 内层循环：在未排序部分查找最大值
        for (int j = i + 1; j < Length - 1; j++)
        {
            // 比较逻辑：寻找最大值（当前实现有误）
            if (Array[Max] > Array[j])  // BUG: 应使用 < 比较符
            {
                Max = j;  // 更新最大值索引
            }
        }
        
        // 将找到的最大值交换到当前位置
        if (Max != i)
        {
            // BUG: 交换逻辑错误且类型不匹配
            T Temp;        // 错误：应使用模板类型T
            Temp = Array[i];
            Array[i] = Array[Max];  // 错误：覆盖了最大值
            Array[Max] = Temp;
        }
    }
}

/**
 * @brief 通用数组打印函数模板
 * 
 * 格式化输出数组的所有元素
 * 
 * @tparam T 数组元素数据类型
 * @param Array 要打印的数组
 * @param Length 数组长度
 * 
 * @note 输出格式：元素间用空格分隔，末尾换行
 */
template <class T>
void PrintArray(T Array[], int Length)
{
    cout << "[";
    // 遍历数组并输出每个元素
    for (int i = 0; i < Length - 1; i++)
    {
        cout << Array[i] << " ";
    }
    cout << "]" << endl;  // 输出换行符
}

/**
 * @brief 排序功能测试函数
 * 
 * 演示字符数组的排序功能，包含完整的测试流程
 * 
 * @details
 * - 初始化测试数据
 * - 计算数组长度
 * - 执行排序操作
 * - 输出排序结果
 */
void Test()
{
    char charArray[] = "asdfghjkl";  // 测试数据：乱序字符数组
    int IntArray[] = {1 ,9, 2, 5, 6, 4, 7, 8, 10};  // 测试数据：乱序字符数组

    int Num = sizeof(charArray) / sizeof(charArray[0]);  // 动态计算数组长度
    
    cout << "原始数组: ";
    PrintArray(charArray, Num);
    
    MySort(charArray, Num);  // 执行排序
    
    cout << "排序结果: ";
    PrintArray(charArray, Num);  // 输出排序后数组

    cout << "原始数组: ";
    PrintArray(IntArray, Num);
    
    MySort(IntArray, Num);  // 执行排序
    
    cout << "排序结果: ";
    PrintArray(IntArray, Num);  // 输出排序后数组
}

/**
 * @brief 主函数 - 模板功能演示
 * 
 * 展示函数模板的两种使用方式：
 * 1. 自动类型推导
 * 2. 显式类型指定
 * 
 * @return int 程序退出码
 * 
 * @see MySwap(), Test()
 */
int main()
{
    // ==================== 自动类型推导演示 ====================
    cout << "=== 自动类型推导演示 ===" << endl;
    int a = 10, b = 20;
    
    cout << "交换前 - a: " << a << ", b: " << b << endl;
    MySwap(a, b);  // 编译器自动推导T为int类型
    cout << "交换后 - a: " << a << ", b: " << b << endl;
    
    // ==================== 显式类型指定演示 ====================
    cout << "\n=== 显式类型指定演示 ===" << endl;
    cout << "交换前 - a: " << a << ", b: " << b << endl;
    MySwap<int>(a, b);  // 显式指定模板参数类型
    cout << "交换后 - a: " << a << ", b: " << b << endl;
    
    // ==================== 排序功能测试 ====================
    cout << "\n=== 数组排序功能测试 ===" << endl;
    Test();
    
    return 0;
}