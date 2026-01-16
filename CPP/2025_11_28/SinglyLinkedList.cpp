/**
 * @file SinglyLinkedList.cpp
 * @author leo
 * @brief 基于链式存储的单链表（C++类封装版）
 * @details 设计思路
            1. 私有成员：定义节点结构体（数据 + next 指针）、头节点指针、链表长度；
            2. 核心操作：插入（找到前驱节点→修改指针）、删除（找到前驱→修改指针 + 释放节点）、查找（遍历比对）；
            3. 封装性：隐藏节点细节，对外暴露统一接口，保证数据安全。
 * @version 1.0
 * @date 2025-11-28
 */


#include <iostream>
#include <stdexcept>
#include <string>

// 单链表类（带头节点）
class SinglyLinkedList {
private:
    // 节点结构体
    struct Node {
        int data;       // 数据域
        Node* next;     // 指针域：指向下一节点
        Node(int val) : data(val), next(nullptr) {} // 节点构造
    };

    Node* head;         // 头节点（不存储数据）
    int length;         // 链表当前长度

public:
    // 构造函数：初始化头节点
    SinglyLinkedList() : length(0) {
        //new 动态内存分配
        head = new Node(0); // 头节点数据无意义
    }

    // 析构函数：释放所有节点
    //作用：避免内存泄漏，链表销毁时释放所有节点（包括头节点）；
    // 逻辑：从head开始遍历链表，用temp保存当前节点，
    //      移动current到下一个节点后释放temp，
    //      直到current为nullptr（遍历结束）。
    ~SinglyLinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp; // 逐个释放节点
        }
    }

    /**
     * @brief 插入元素到指定位置（0 ≤ pos ≤ length）
     */
    void insert(int pos, int val) {
        if (pos < 0 || pos > length) {
            throw std::out_of_range("insert: 位置非法");
        }

        // 找到插入位置的前驱节点
        Node* prev = head;
        for (int i = 0; i < pos; ++i) {
            prev = prev->next;
        }

        // 创建新节点并插入
        Node* newNode = new Node(val);
        newNode->next = prev->next; // 新节点指向原前驱的后继
        prev->next = newNode;       // 前驱指向新节点
        length++;
    }

    /**
     * @brief 删除指定位置的元素（0 ≤ pos < length）
     */
    void remove(int pos) {
        if (isEmpty()) {
            throw std::runtime_error("remove: 链表为空");
        }
        if (pos < 0 || pos >= length) {
            throw std::out_of_range("remove: 位置非法");
        }

        // 找到删除位置的前驱节点
        Node* prev = head;
        for (int i = 0; i < pos; ++i) {
            prev = prev->next;
        }

        Node* delNode = prev->next; // 待删除节点
        prev->next = delNode->next; // 前驱跳过待删除节点
        delete delNode;             // 释放内存
        length--;
    }

    /**
     * @brief 查找元素位置（返回第一个匹配索引，未找到返回-1）
     */
    int find(int val) const {
        Node* current = head->next; // 跳过头节点，从第一个元素开始
        int index = 0;
        while (current != nullptr) {
            if (current->data == val) {
                return index;
            }
            current = current->next;
            index++;
        }
        return -1;
    }

    /**
     * @brief 判断链表是否为空
     */
    bool isEmpty() const {
        return length == 0;
    }

    /**
     * @brief 获取链表长度
     */
    int getLength() const {
        return length;
    }

    /**
     * @brief 遍历输出链表元素
     */
    void traverse() const {
        std::cout << "单链表元素: ";
        Node* current = head->next;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    // 测试单链表
    try {
        std::cout << "=== 测试单链表 ===" << std::endl;
        SinglyLinkedList sList;
        sList.insert(0, 10);
        sList.insert(1, 20);
        sList.insert(1, 15);
        sList.traverse(); // 输出：10 15 20

        sList.remove(1);
        sList.traverse(); // 输出：10 20
        std::cout << "元素20的位置: " << sList.find(20) << std::endl; // 输出：1
    } catch (const std::exception& e) {
        std::cerr << "单链表错误: " << e.what() << std::endl;
    }


}