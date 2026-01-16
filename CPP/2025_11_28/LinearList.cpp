/**
 * @file LinearList.cpp
 * @author leo
 * @brief 基于顺序存储的线性表（C++类封装版）
 * @details 该类实现了线性表的基本操作，包括插入、删除、查找等。
 * @version 1.0
 * @date 2025-11-28
 */
/**
 * @note 线性表是一种基本的数据结构，支持元素的顺序存储和访问。
 *       线性表是n 个具有相同特性的数据元素的有限序列（n≥0）
 */
#include <iostream>
#include <vector>
#include <stdexcept>

/**
 * @brief std::vector<int> data：作为顺序表的底层存储容器。
            vector是 C++ 标准库中的动态数组，支持随机访问、自动扩容，天然适配顺序表 “连续存储、随机访问” 的特性。
            将其设为private是为了封装性：外部无法直接修改存储数据，必须通过类的成员函数操作，保证数据安全。

           int length：记录线性表的当前元素个数。虽然vector本身提供size()方法获取元素个数，但这里单独维护length有两个目的：
            1.更直观体现线性表的 “长度” 属性（符合数据结构教材中对线性表的定义）；
            2.避免频繁调用vector::size()（尽管性能影响可忽略，但教学场景下更清晰）。
            注意：length需与data.size()始终保持一致（通过插入 / 删除操作同步更新）。 
 */
class LinearList {
private:
    std::vector<int> data; // 底层存储（私有，外部不可直接访问）
    int length;            // 线性表当前长度

public:
    /**
     * @brief 构造函数：创建空线性表
     */
    LinearList() : length(0) {}

    /**
     * @brief 构造函数：用元素集合初始化线性表
     * @param elements 初始化元素
     * @details  接收一个vector<int>类型的参数elements，通过初始化列表：
                将data直接赋值为elements（底层是vector的拷贝构造）；
                将length设为elements.size()（与初始元素个数一致）。
                作用：快速用一组已知元素初始化线性表。
                例如：LinearList myList({1, 2, 3}) 即可创建一个包含1,2,3三个元素的线性表。
     */
    LinearList(const std::vector<int>& elements) 
        : data(elements), length(elements.size()) {}

    /**
     * @brief 插入元素到指定位置
     * @param pos 插入位置（0 ~ length）
     * @param val 插入值
     */
    void insert(int pos, int val) {
        if (pos < 0 || pos > length) {
            throw std::out_of_range("insert: 位置非法");
        }
        data.insert(data.begin() + pos, val);
        length++;
    }

    /**
     * @brief 删除指定位置的元素
     * @param pos 删除位置（0 ~ length-1）
     */
    void remove(int pos) {
        if (isEmpty()) {
            throw std::runtime_error("remove: 线性表为空");
        }
        if (pos < 0 || pos >= length) {
            throw std::out_of_range("remove: 位置非法");
        }
        data.erase(data.begin() + pos);
        length--;
    }

    /**
     * @brief 查找元素值
     * @param val 查找值
     * @return int 第一个匹配位置，未找到返回-1
     */
    int find(int val) const {
        for (int i = 0; i < length; ++i) {
            if (data[i] == val) {
                return i;
            }
        }
        return -1;
    }

    /**
     * @brief 判断线性表是否为空
     * @return bool 空返回true
     */
    bool isEmpty() const {
        return length == 0;
    }

    /**
     * @brief 获取线性表长度
     * @return int 当前元素个数
     */
    int getLength() const {
        return length;
    }

    /**
     * @brief 遍历输出线性表元素
     */
    void traverse() const {
        std::cout << "线性表元素: ";
        for (int elem : data) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    try {
        // 用元素初始化线性表
        LinearList myList({1, 2, 3, 4, 5});
        myList.traverse(); // 输出初始元素
        std::cout << "当前长度: " << myList.getLength() << std::endl;

        // 插入元素
        myList.insert(2, 6);
        myList.traverse();
        std::cout << "插入后长度: " << myList.getLength() << std::endl;

        // 删除元素
        myList.remove(4);
        myList.traverse();
        std::cout << "删除后长度: " << myList.getLength() << std::endl;

        // 查找元素
        int pos = myList.find(3);
        std::cout << "元素3的位置: " << pos << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "错误: " << e.what() << std::endl;
    }

    return 0;
}