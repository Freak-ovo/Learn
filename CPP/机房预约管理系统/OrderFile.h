#ifndef ORDERFILE_H
#define ORDERFILE_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include "globalFile.h"


using namespace std;

class OrderFile {
private:
    int _size;  // 预约记录总条数
    // 存储所有预约信息：外层key为记录编号(0开始)，内层为单条预约的键值对
    map<int, map<string, string>> _orderMap;

public:
    // 构造函数：读取文件并解析预约信息
    OrderFile();

    // 析构函数
    ~OrderFile();

    // 获取预约记录总条数
    int getSize();

    // 获取所有预约信息
    map<int, map<string, string>>& getOrderMap();

    // 更新预约信息到文件（覆盖原文件）
    void updateOrder();

    // 新增预约记录（追加到文件和内存）
    void recordOrder(const map<string, string>& newOrder);
};

#endif // ORDERFILE_H