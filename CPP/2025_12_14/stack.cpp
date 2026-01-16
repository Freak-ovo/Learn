/**
 * @file stack.cpp
 * @brief 栈的顺序存储实现
 * @author Leo
 * @date 2025-12-14
 * @version 1.0
 * @details 本文件实现了一个简单的栈数据结构，支持基本的栈操作如入栈、出栈和查看栈顶元素。
 */

/**
 * @note  栈（stack）是一种后进先出（LIFO, Last In First Out）的数据结构。
 *       栈尾称为栈顶（top），栈头称为栈底（bottom）。 不含元素时，是空栈。
 *       栈的基本操作包括：
 *       - 入栈（push）：将一个元素添加到栈顶。
 *       - 出栈（pop）：移除并返回栈顶元素。
 *       - 查看栈顶元素（top）：返回栈顶元素但不移除。
 *       - 判断栈是否为空（isEmpty）：检查栈是否不包含任何元素。
 *       - 获取栈的长度（getLength）：返回栈中元素的数量。
 */
#include <iostream>
// 新增：包含异常处理所需的头文件
#include <stdexcept>
using namespace std;

class Stack {
private:
    int* data;        // 存储栈元素的数组
    int topIndex;     // 栈顶索引（初始为-1，表示空栈）
    int capacity;     // 栈的容量

public:
    // 构造函数，初始化栈
    Stack(int cap = 100);
    // 析构函数，释放内存
    ~Stack();

    /**
     * @brief 入栈操作
     * @param val 要入栈的元素值
     */
    void Push(int val);

    /**
     * @brief 出栈操作
     */
    void Pop();

    /**
     * @brief 查看栈顶元素
     * @return int 栈顶元素值
     */
    int Top() const;

    /**
     * @brief 获取栈的长度
     * @return int 栈中元素的数量
     */
    int GetLength() const;

    /**
     * @brief 判断栈是否为空
     * @return bool 空返回true
     */
    bool IsEmpty() const;
};

// 构造函数实现：初始化栈的容量、栈顶索引和存储数组
Stack::Stack(int cap) {
    capacity = cap;
    // 初始化栈顶索引为-1，表示空栈
    topIndex = -1;
    // 动态分配内存存储栈元素
    data = new int[capacity];
}

// 析构函数实现：释放动态分配的内存，避免内存泄漏
Stack::~Stack() {
    delete[] data;
    // 防止野指针（可选，增强代码健壮性）
    data = nullptr;
}

// 入栈操作实现
void Stack::Push(int val) {
    // 检查栈是否已满（栈顶索引 >= 容量-1 表示栈满）
    if (topIndex >= capacity - 1) {
        throw std::overflow_error("Push: 栈溢出");
    }
    // 栈顶索引加1，然后赋值
    data[++topIndex] = val;
}

// 出栈操作实现
void Stack::Pop() {
    if (IsEmpty()) {
        throw std::underflow_error("Pop: 栈为空");
    }
    // 栈顶索引减1，逻辑上移除栈顶元素
    topIndex--;
}

// 查看栈顶元素实现
int Stack::Top() const {
    if (IsEmpty()) {
        throw std::underflow_error("Top: 栈为空");
    }
    return data[topIndex];
}

// 获取栈长度实现
int Stack::GetLength() const {
    // 栈顶索引+1即为元素个数（索引从-1开始）
    return topIndex + 1;
}

// 判断栈是否为空实现
bool Stack::IsEmpty() const {
    // 栈顶索引为-1表示空栈
    return topIndex == -1;
}

int main() {
    try {
        Stack myStack;
        myStack.Push(10);
        myStack.Push(20);
        myStack.Push(30);

        std::cout << "栈顶元素: " << myStack.Top() << std::endl;
        std::cout << "栈长度: " << myStack.GetLength() << std::endl;

        myStack.Pop();
        std::cout << "出栈后栈顶元素: " << myStack.Top() << std::endl;
        std::cout << "出栈后栈长度: " << myStack.GetLength() << std::endl;

        // 测试空栈出栈（可选，用于验证异常处理）
        // while (!myStack.IsEmpty()) {
        //     myStack.Pop();
        // }
        // myStack.Pop(); // 会抛出异常
    } catch (const std::exception& e) {
        // 捕获并输出异常信息，增强程序健壮性
        std::cerr << "异常信息: " << e.what() << std::endl;
    }

    return 0;
}