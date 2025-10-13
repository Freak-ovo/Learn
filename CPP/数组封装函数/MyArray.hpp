#pragma once
#include <iostream>
using namespace std;

/**
 * @brief 自定义数组类模板
 * @tparam T 数组元素类型
 * 
 * 实现动态数组的基本功能，包括深拷贝、动态内存管理等
 */
template <class T>
class MyArray
{
private:
    T *PAddress;        // 指针，指向堆区开辟的真实数组
    int __Capacity;     // 数组容量（最大可容纳元素个数）
    int __Size;         // 数组当前大小（实际元素个数）

public:
    /**
     * @brief 构造函数
     * @param Capacity 数组初始容量
     * 
     * 在堆区分配指定容量的数组内存
     */
    MyArray(int Capacity)
    {
        this->__Capacity = Capacity;
        this->__Size = 0;
        // 修复：应该使用 -> 而不是 . 来访问成员
        this->PAddress = new T[this->__Capacity];  // 在堆区分配数组空间
        
        cout << "MyArray构造函数：容量=" << Capacity << endl;
    }

    /**
     * @brief 拷贝构造函数（深拷贝）
     * @param Array 被拷贝的源数组对象
     * 
     * 创建新对象时完全复制源对象的数据和内存空间
     */
    MyArray(const MyArray &Array)
    {
        // 复制基本属性
        this->__Capacity = Array.__Capacity;
        this->__Size = Array.__Size;
        
        // 深拷贝：分配新的内存空间
        this->PAddress = new T[Array.__Capacity];

        // 将Array中的数据逐个拷贝到新数组中
        for (int i = 0; i < this->__Size; i++)
        {
            this->PAddress[i] = Array.PAddress[i];
        }
        
        cout << "MyArray拷贝构造函数：容量=" << __Capacity << "，大小=" << __Size << endl;
    }

    /**
     * @brief 赋值运算符重载（深拷贝）
     * @param Array 被赋值的源数组对象
     * @return MyArray& 返回当前对象的引用，支持链式赋值
     * 
     * 处理对象赋值时的深拷贝，防止内存泄漏和浅拷贝问题
     */
    MyArray& operator=(const MyArray &Array)
    {
        // 检查自赋值：防止 a = a 的情况
        if (this == &Array) {
            return *this;
        }
        
        // 先判断原来堆区是否有数据，如果有则先释放
        // 修复：应该使用 -> 而不是 . 来访问成员
        if (this->PAddress != NULL)
        {
            delete[] this->PAddress;    // 释放原有内存
            this->PAddress = NULL;      // 指针置空，防止悬空指针
            this->__Size = 0;
            this->__Capacity = 0;
        }

        // 深拷贝：复制源对象的属性和数据
        this->__Capacity = Array.__Capacity;
        this->__Size = Array.__Size;
        this->PAddress = new T[Array.__Capacity];
        
        // 将Array中的数据逐个拷贝过来
        for (int i = 0; i < this->__Size; i++)
        {
            this->PAddress[i] = Array.PAddress[i];
        }
        
        cout << "MyArray赋值运算符：容量=" << __Capacity << "，大小=" << __Size << endl;
        return *this;  // 返回当前对象引用，支持链式赋值
    }
    /**
     * @brief 在数组末尾添加元素（尾插法）
     * @param value 要添加的元素值（使用常量引用避免拷贝）
     * 
     * 如果数组已满（当前元素个数大于等于容量），则输出提示信息并返回
     * 如果未满，则将新元素添加到数组末尾，并增加数组当前大小计数
     */
    void Push_Back(const T& value)
    {
        if(this->__Size >= this->__Capacity)
        {
            cout << "数组已满，无法插入新元素" << endl;
            return;
        }
        this->PAddress[this->__Size] = value;
        this->__Size++;
    }
    /**
     * @brief 删除数组末尾的元素（尾删法）
     * 
     * 如果数组为空（当前元素个数小于等于0），则输出提示信息并返回
     * 如果不为空，只需将数组当前大小减1，不需要实际删除元素（通过减小索引范围实现逻辑删除）
     */
    void Pop_Back()
    {
        if(this->__Size <= 0)
        {
            cout << "数组为空，无法删除元素" << endl;
            return;
        }
        this->__Size--;
    }
    /**
     * @brief 重载[]运算符，支持数组下标访问
     * @param index 要访问的元素下标
     * @return T& 返回指定下标位置元素的引用，支持读取和修改操作
     * 
     * 允许通过数组下标语法访问和修改数组中的元素
     * 注意：该实现不进行边界检查，调用者需确保下标在有效范围内
     */
    T& operator[](int index) // 注意：返回类型应该是T&而不是void
    {
        return this->PAddress[index];
    }
    /**
     * @brief 获取数组的容量
     * @return int 返回数组的最大可容纳元素个数
     * 
     * 该函数返回数组在初始化时设定的最大可容纳元素数量，
     * 不考虑当前实际存储的元素个数
     */
    int GetCapacity()
    {
        return this->__Capacity;
    }
    /**
     * @brief 获取数组当前的大小
     * @return int 返回数组中实际存储的元素个数
     * 
     * 该函数返回数组当前实际存储的元素数量，
     * 这个值不会超过数组的容量（__Capacity）
     */
    int GetSize()
    {
        return this->__Size;
    }

    /**
     * @brief 析构函数
     * 
     * 释放堆区分配的内存，防止内存泄漏
     */
    ~MyArray()
    {
        if (this->PAddress != NULL)
        {
            delete[] this->PAddress;    // 释放数组内存
            this->PAddress = NULL;      // 指针置空
            cout << "MyArray析构函数：内存已释放" << endl;
        }
    }

};