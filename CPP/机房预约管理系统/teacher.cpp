#include "teacher.h"


// 教师类菜单
void TeacherMenu(Identity* &teacher){

    
    while (true)
    {
        // 显示教师操作菜单
        teacher->operMenu();

        Teacher *teacher = (Teacher*)teacher;
        // 教师操作
        int choice = 0;
        cin >> choice;

        switch (choice)
        {
        case 1:
            // 查看所有预约
            teacher->viewAllReservations();
            break;
        case 2:
            // 审核预约
            teacher->approveReservation();
            break;
        case 3:
            // 退出教师操作菜单
            cout << "退出教师操作菜单" << endl;
            cout << "感谢使用教师操作菜单" << endl;
            delete teacher;
            system("pause");
            system("cls");
            return;
        default:
            // 输入错误提示
            cout << "输入错误，请重新输入" << endl;
            break;
        }

    }
    


}

// 教师类 默认构造函数
Teacher::Teacher() {    
}
// 教师类 析构函数
Teacher::~Teacher() {
}
// 教师类 有参构造函数
Teacher::Teacher(int id, string name, string pwd) {
    _Id = id;
    _Name = name;
    _Pwd = pwd;
    _teaId = id;
}
// 显示教师操作菜单
void Teacher::operMenu() {
    cout << "欢迎使用教师操作菜单" << endl;
    cout << "1. 查看所有预约" << endl;
    cout << "2. 审核预约" << endl;
    cout << "3. 退出" << endl;
}

// 查看所有预约
void Teacher::viewAllReservations() {
    cout << "查看所有预约" << endl;
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
    // 检查是否有预约记录
    if (vOrder.empty()) {
        cout << "==================" << endl;
        cout << "当前没有预约记录。" << endl;
        cout << "==================" << endl;
        return;
    }
    // 输出预约记录
    cout << "预约记录序号\t\t预约时间\t\t预约人姓名\t\t预约人学号\t\t预约人手机号\t\t预约人邮箱\t\t预约人班级\t\t预约人预约类型" << endl;
    for (int i = 0; i < vOrder.size(); i++) {
        cout << i + 1 << "\t\t" << vOrder[i] << endl;
    }

}

// 审核预约
void Teacher::approveReservation() {
    cout << "审核预约" << endl;
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
    // 检查是否有预约记录
    if (vOrder.empty()) {
        cout << "==================" << endl;
        cout << "当前没有预约记录。" << endl;
        cout << "==================" << endl;
        return;
    }
    // 输出预约记录
    cout << "预约记录序号\t\t预约时间\t\t预约人姓名\t\t预约人学号\t\t预约人手机号\t\t预约人邮箱\t\t预约人班级\t\t预约人预约类型" << endl;
    for (int i = 0; i < vOrder.size(); i++) {
        cout << i + 1 << "\t\t" << vOrder[i] << endl;
    }
    // 审核预约
    cout << "请输入要审核的预约记录序号：" << endl;
    int index;
    cin >> index;
    if (index < 1 || index > vOrder.size()) {
        cout << "==================" << endl;
        cout << "输入的序号无效，请重新输入。" << endl;
        cout << "==================" << endl;
        return;
    }
    // 审核预约
    cout << "请输入审核结果（1：同意，2：拒绝）：" << endl;
    int result;
    cin >> result;
    if (result != 1 && result != 2) {
        cout << "==================" << endl;
        cout << "输入的结果无效，请重新输入。" << endl;
        cout << "==================" << endl;
        return;
    }
    // 更新预约记录
    if (result == 1) {
        cout << "==================" << endl;
        cout << "预约已同意。" << endl;
        cout << "==================" << endl;
    } else {
        cout << "==================" << endl;
        cout << "预约已拒绝。" << endl;
        cout << "==================" << endl;
    }
    // 更新预约记录文件
    ofstream ofs(Order_File); // 直接在构造函数中打开文件
    if (!ofs.is_open()) {
        cout << "==================" << endl;
        cout << "文件打开失败，请检查文件名。" << endl;
        cout << "==================" << endl;
        return;
    }
    for (int i = 0; i < vOrder.size(); i++) {
        ofs << vOrder[i] << endl;

    }

    ofs.close();
    



    // 提示用户审核完成
    cout << "==================" << endl;
    cout << "审核完成。" << endl;
    cout << "==================" << endl;
    return;



    
}
