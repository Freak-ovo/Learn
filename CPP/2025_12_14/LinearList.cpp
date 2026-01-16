#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

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
     * @brief 获取指定位置的元素
     * @param pos 位置（0 ~ length-1）
     * @return int 元素值
     */
    int get(int pos) const {
        if (pos < 0 || pos >= length) {
            throw std::out_of_range("get: 位置非法");
        }
        return data[pos];
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

    /**
     * @brief 合并两个线性表
     * @param A 第一个线性表
     * @param B 第二个线性表
     */
void MergeList(LinearList &A, LinearList &B){

    int m = A.getLength();
    int n = B.getLength();

    for (int i = 0; i < n; i++) {
        int e = B.get(i);// Get the i-th element from list B
        // Check if the element is not already in list A
        if (A.find(e) == -1) {
            A.insert(m + i, e);
        }
    }



}


int main() {

    LinearList myList1({7, 5, 3, 11});
    LinearList myList2({2, 6, 3});
    cout << "=====================" << endl;
    cout << "无序线性表合并" << endl;
    cout << "list1的元素: ";
    myList1.traverse();
    cout << "list2的元素: ";
    myList2.traverse();
    cout << "合并后的线性表长度: " << myList1.getLength() << endl;
    MergeList(myList1, myList2);
    myList1.traverse(); 
    cout << "======================" << endl;

}