#include "student.h"
#include <iomanip>  // 添加这一行，包含setw函数所在的头文件

// 学生菜单
void StudentMenu(Identity * &student) {
    //
    while (true)
    {
        // 显示学生操作菜单
        student->operMenu();

        Student* stu = static_cast<Student*>(student);
        // 接收用户输入
        int choice;
        cout << "请输入您的选择: ";
        cin >> choice;

        switch (choice) {
        case 1: // 申请预约
            stu->applyReservation();
            system("pause");
            system("cls");
            break;
        case 2: // 查看自身预约信息
            stu->viewSelfReservationInfo();
            system("pause");
            system("cls");
            break;
        case 3: // 查看所有人的预约
            stu->viewAllReservations();
            system("pause");
            system("cls");
            break;
        case 4: // 取消预约
            stu->cancelReservation();
            system("pause");
            system("cls");
            break;
        case 0: // 返回上一级
            cout << "返回上一级菜单" << endl;
            system("pause");
            system("cls");
            return;
        default:
            cout << "==================" << endl;
            cout << "无效的选择，请重新输入。" << endl;
            cout << "==================" << endl;
            break;
        }
    }
    
}



// 学生类 默认构造函数
Student::Student() {

}

// 学生类 析构函数
Student::~Student() {

}

// 初始化机房容器
void Student::InitVectorRoom(){

    ifstream ifs;
    ifs.open(ComputerRoom_File, ios::in);
    if (!ifs.is_open()) {
        cout << "文件打开失败" << endl;
        return;
    }

    ComputerRoom room;
    while (ifs >> room._RoomId >> room._Capacity >> room._Status) {
        _vRoom.push_back(room);
    }
    ifs.close();
    
}

//有参构造(学号、姓名、密码)
Student::Student(int id, string name, string pwd) {  
    _stuId = id;
    _Name = name;
    _Pwd = pwd;

    // 初始化机房容器
    InitVectorRoom();
}
// 显示学生操作菜单
void Student::operMenu() {
    cout << "1. 申请预约" << endl;
    cout << "2. 查看自身预约信息" << endl;
    cout << "3. 查看所有人的预约" << endl;
    cout << "4. 取消预约" << endl;
    cout << "0. 返回上一级" << endl;
}

// 申请预约
void Student::applyReservation() {
    cout << "申请预约" << endl;
    cout << "==================" << endl;

    cout << "机房开放时间为周一至周五 9:00 至 18:00" << endl;
    cout << "请输入您要预约的时间: \n";
    cout << "1. 周一" << endl;
    cout << "2. 周二" << endl;
    cout << "3. 周三" << endl;
    cout << "4. 周四" << endl;
    cout << "5. 周五" << endl;
    cout << "请输入您要预约的时间: ";
    int day;    // 预约日期
    cin >> day;
    if (day < 1 || day > 5) {
        cout << "==================" << endl;
        cout << "无效的选择，请重新输入。" << endl;
        cout << "==================" << endl;
        return;
    }
    cout << "请输入您要预约的开始时间: ";
    int hour;
    cin >> hour;
    if (hour < 9 || hour > 18) {
        cout << "==================" << endl;
        cout << "无效的选择，请重新输入。" << endl;
        cout << "==================" << endl;
        return;
    }
    cout << "请输入您要预约的结束时间: ";
    int endHour;
    cin >> endHour;
    if (endHour <= hour || endHour > 18) {
        cout << "==================" << endl;
        cout << "无效的选择，请重新输入。" << endl;
        cout << "==================" << endl;
        return;
    }
    
    cout << "请选择您要预约的机房: \n";
    cout << "1号机房的剩余容量为: " << _vRoom[0]._Capacity << endl;
    cout << "2号机房的剩余容量为: " << _vRoom[1]._Capacity << endl;
    cout << "3号机房的剩余容量为: " << _vRoom[2]._Capacity << endl;
    cout << "请输入您要预约的机房: ";

    // 接收用户输入
    int room;
    while (true)
    {
        cin >> room;
        if (room < 1 || room > 3) {
            cout << "==================" << endl;
            cout << "无效的选择，请重新输入。" << endl;
            cout << "==================" << endl;
            continue;
        }
        cout << "您选择的是" << room << "号机房" << "\n" << "预约时间为" << day << "号" << hour << "时" << "至" << endHour << "时" << endl;
        cout << "是否确认预约? (1. 确认 2. 取消)" << endl;
        int confirm;
        cin >> confirm;
        if (confirm == 1) {
            cout << "提交预约成功！正在审核中..." << endl;
            // 写入预约信息文件
            ofstream ofs;
            ofs.open(Order_File, ios::out | ios::app);
            if (!ofs.is_open()) {
                cout << "文件打开失败" << endl;
                return;
            }
            ofs  << "预约日期: " << "周" << day << " 预约时间: " << hour << " 至 " << endHour << "时"  << " 学生学号: " << _stuId << " 学生姓名: " << _Name 
            << " 机房号: " << room << " " << " 审核状态: " << "待审核" << endl;
            ofs.close();
            system("pause");
            system("cls");
            break;
        }
        else if (confirm == 2) {
            cout << "预约取消" << endl;
            system("pause");
            system("cls");
            break;
        }
        else {
            cout << "==================" << endl;
            cout << "无效的选择，请重新输入。" << endl;
            cout << "==================" << endl;
        }
    }
    
}
// 查看自身预约信息
// 改进后的代码
void Student::viewSelfReservationInfo() {
    cout << "查看自身预约信息" << endl;
    cout << "==================" << endl;
    
    // 读取预约信息文件
    ifstream ifs(Order_File); // 直接在构造函数中打开文件
    if (!ifs.is_open()) {
        cout << "==================" << endl;
        cout << "文件打开失败，请检查文件名。" << endl;
        cout << "==================" << endl;
        return;
    }
    
    // 遍历文件内容
    string line;
    string targetId = to_string(_stuId); // 只转换一次，提高效率
    bool foundReservation = false;
    
    while (getline(ifs, line)) {
        // 解析预约信息 - 使用更健壮的方式
        const string prefix = "学生学号: ";
        size_t pos = line.find(prefix);
        if (pos != string::npos) {
            // 提取学号，直到行尾或下一个分隔符（假设学号是数字）
            size_t startPos = pos + prefix.length();
            size_t endPos = line.find_first_not_of("0123456789", startPos);
            string stuId = line.substr(startPos, endPos - startPos);
            
            if (stuId == targetId) {
                cout << line << endl;
                foundReservation = true;
            }
        }
    }
    
    if (!foundReservation) {
        cout << "暂无预约记录" << endl;
    }
    
    // ifs会在作用域结束时自动关闭（RAII原则）
}

// 查看所有人的预约
void Student::viewAllReservations() {
    cout << "==================== 所有预约记录 ====================" << endl;

    // 遍历文件内容
    string line;
    ifstream ifs(Order_File); // 直接在构造函数中打开文件
    if (!ifs.is_open()) {
        cout << "==================" << endl;
        cout << "文件打开失败，请检查文件名。" << endl;
        cout << "==================" << endl;
        return;
    }
    // 打印所有预约记录
    int serialNum = 1;
    while (getline(ifs, line)) {
        cout << setw(2) << serialNum++ << "  | ";
        cout << line << endl;
    }
    ifs.close();
    
}
// 取消预约
void Student::cancelReservation() {
    cout << "==================== 取消预约 ====================" << endl;
    
    // 输出用户预约信息
    this->viewSelfReservationInfo();
    // 接收用户输入
    int serialNum;
    cout << "请输入您要取消的预约记录序号: ";
    cin >> serialNum;

    // 读取预约信息文件
    ifstream ifs(Order_File); // 直接在构造函数中打开文件
    if (!ifs.is_open()) {
        cout << "==================" << endl;
        cout << "文件打开失败，请检查文件名。" << endl;
        cout << "==================" << endl;
        return;
    }
    // 遍历文件内容
    string line;
    vector<string> vOrder;
    while (getline(ifs, line)) {
        vOrder.push_back(line);
    }
    ifs.close();

    // 检查序号是否有效
    if (serialNum < 1 || serialNum > vOrder.size()) {
        cout << "==================" << endl;
        cout << "无效的序号，请重新输入。" << endl;
        cout << "==================" << endl;
        return;
    }
     // 删除指定预约记录
    vOrder.erase(vOrder.begin() + serialNum - 1);
    // 写入更新后的预约信息文件
    ofstream ofs(Order_File, ios::out);
    if (!ofs.is_open()) {
        cout << "文件打开失败" << endl;
        return;
    }
    for (string order : vOrder) {
        ofs << order << endl;
    }
    ofs.close();
    cout << "==================" << endl;
    cout << "预约取消成功" << endl;
    cout << "==================" << endl;
    system("pause");
    system("cls");
    

    

}