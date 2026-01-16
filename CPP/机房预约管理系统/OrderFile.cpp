#include "OrderFile.h"

// 构造函数：读取文件并解析预约信息
OrderFile::OrderFile() {
    _size = 0;  // 初始化记录数为0

    // 打开预约文件（只读模式）
    ifstream ifs;
    ifs.open(Student_Order_File, ios::in);
    if (!ifs.is_open()) {
        cout << "【错误】预约文件打开失败，请检查文件是否存在！" << endl;
        return;
    }

    // 临时变量：存储从文件读取的单条记录字段
    int id;             // 预约记录ID
    string stuId;       // 学生学号
    string stuName;     // 学生姓名
    string day;         // 预约日期（格式："日期: 2025-11-10"）
    string roomId;      // 机房号（格式："机房号: 101"）
    string startHour;   // 开始时间（格式："开始时间: 09:00"）
    string endHour;     // 结束时间（格式："结束时间: 11:00"）
    string status;      // 审核状态（格式："状态: 待审核"）

    // 循环读取文件中的每条记录（按空格分隔字段）
    while (ifs >> id >> stuId >> stuName >> day >> roomId >> startHour >> endHour >> status) {
        // 临时存储单条预约的键值对
        map<string, string> singleOrder;

        // 解析"日期"字段（分割键和值）
        int pos = day.find(": ");  // 查找分隔符": "的位置
        if (pos != string::npos) {  // 找到分隔符才解析（修正原逻辑错误）
            string key = day.substr(0, pos);       // 键："日期"
            string value = day.substr(pos + 2);    // 值："2025-11-10"（跳过": "）
            singleOrder.insert(make_pair(key, value));
        }

        // 解析"开始时间"字段
        pos = startHour.find(": ");
        if (pos != string::npos) {
            string key = startHour.substr(0, pos);
            string value = startHour.substr(pos + 2);
            singleOrder.insert(make_pair(key, value));
        }

        // 解析"结束时间"字段
        pos = endHour.find(": ");
        if (pos != string::npos) {
            string key = endHour.substr(0, pos);
            string value = endHour.substr(pos + 2);
            singleOrder.insert(make_pair(key, value));
        }

        // 解析"学生学号"字段
        pos = stuId.find(": ");
        if (pos != string::npos) {
            string key = stuId.substr(0, pos);
            string value = stuId.substr(pos + 2);
            singleOrder.insert(make_pair(key, value));
        }

        // 解析"学生姓名"字段
        pos = stuName.find(": ");
        if (pos != string::npos) {
            string key = stuName.substr(0, pos);
            string value = stuName.substr(pos + 2);
            singleOrder.insert(make_pair(key, value));
        }

        // 解析"机房号"字段
        pos = roomId.find(": ");
        if (pos != string::npos) {
            string key = roomId.substr(0, pos);
            string value = roomId.substr(pos + 2);
            singleOrder.insert(make_pair(key, value));
        }

        // 解析"审核状态"字段
        pos = status.find(": ");
        if (pos != string::npos) {
            string key = status.substr(0, pos);
            string value = status.substr(pos + 2);
            singleOrder.insert(make_pair(key, value));
        }

        // 将单条记录存入总容器（键为记录编号）
        _orderMap.insert(make_pair(_size, singleOrder));
        _size++;  // 记录数+1
    }

    ifs.close();  // 关闭文件
}

// 析构函数：无需手动释放资源（map自动管理）
OrderFile::~OrderFile() {}

// 获取预约记录总条数
int OrderFile::getSize() {
    return _size;
}

// 获取所有预约信息（返回引用，方便外部修改）
map<int, map<string, string>>& OrderFile::getOrderMap() {
    return _orderMap;
}

// 更新预约信息到文件（覆盖原文件，保持内存与文件一致）
void OrderFile::updateOrder() {
    if (_size == 0) {
        cout << "【提示】暂无预约记录，无需更新！" << endl;
        return;
    }

    // 打开文件（覆盖写入模式）
    ofstream ofs;
    ofs.open(Student_Order_File, ios::out | ios::trunc);
    if (!ofs.is_open()) {
        cout << "【错误】更新文件打开失败！" << endl;
        return;
    }

    // 遍历所有预约记录，写入文件
    for (int i = 0; i < _size; i++) {
        // 从内存中读取字段（键需与解析时一致）
        auto& order = _orderMap[i];
        // 按格式写入：ID 学号 姓名 日期 机房号 开始时间 结束时间 状态
        ofs << i + 1 << " "  // 预约ID（从1开始）
            << "学号: " << order["学号"] << " "
            << "姓名: " << order["姓名"] << " "
            << "日期: " << order["日期"] << " "
            << "机房号: " << order["机房号"] << " "
            << "开始时间: " << order["开始时间"] << " "
            << "结束时间: " << order["结束时间"] << " "
            << "状态: " << order["状态"] << endl;
    }

    ofs.close();  // 关闭文件
    cout << "【成功】预约记录已更新到文件！" << endl;
}

// 新增预约记录（追加到文件和内存）
void OrderFile::recordOrder(const map<string, string>& newOrder) {
    // 1. 追加到文件（以追加模式打开）
    ofstream ofs;
    ofs.open(Student_Order_File, ios::out | ios::app);
    if (!ofs.is_open()) {
        cout << "【错误】新增记录时文件打开失败！" << endl;
        return;
    }

    // 写入新记录（ID为当前总条数+1）
    ofs << _size + 1 << " "
        << "学号: " << newOrder.at("学号") << " "
        << "姓名: " << newOrder.at("姓名") << " "
        << "日期: " << newOrder.at("日期") << " "
        << "机房号: " << newOrder.at("机房号") << " "
        << "开始时间: " << newOrder.at("开始时间") << " "
        << "结束时间: " << newOrder.at("结束时间") << " "
        << "状态: " << newOrder.at("状态") << endl;  // 新增记录默认状态为"待审核"
    ofs.close();

    // 2. 同步到内存
    _orderMap.insert(make_pair(_size, newOrder));
    _size++;  // 记录数+1

    cout << "【成功】新预约记录已保存！" << endl;
}