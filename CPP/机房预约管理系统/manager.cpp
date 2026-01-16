#include "manager.h"

void ManagerMenu(Identity* &manager) {
    while (true)
    {
        cout << "====管理员菜单====" << endl;
        // 显示管理员操作菜单
        manager->operMenu();

        // 将父类指针转换为管理员类指针
        Manager* mgr = static_cast<Manager*>(manager);

        // 接收用户输入
        int choice;
        cout << "请输入您的选择: ";
        cin >> choice;
        switch (choice)
        {
        case 1: // 添加账号
            mgr->addAccount();
            break;
        case 2: // 查看账号
            mgr->viewAccounts();
            break;
        case 3: // 查看机房信息
            mgr->viewRoomInfo();
            break;
        case 4: // 清空预约信息
            mgr->clearReservations();
            break;
        case 0: // 退出
            cout << "==================" << endl;
            cout << "退出管理员菜单" << endl;
            cout << "注销管理员登录" << endl;
            cout << "注销成功！" << endl;
            cout << "==================" << endl;
            // 注销管理员登录
            delete manager;
            manager = NULL;
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

// 查看学生信息
void PrintStudentInfo(const vector<Student>& vStu) {
    cout << "学生信息如下: " << endl;
    for (vector<Student>::const_iterator it = vStu.begin(); it != vStu.end(); ++it) {
        cout << "学号: " << it->_Id << "\t"
             << "姓名: " << it->_Name << "\t"
             << "密码: " << it->_Pwd << endl;
    }
}

// 查看教师信息
void PrintTeacherInfo(const vector<Teacher>& vTea) {
    cout << "教师信息如下: " << endl;
    for (vector<Teacher>::const_iterator it = vTea.begin(); it != vTea.end(); ++it) {
        cout << "教师号: " << it->_Id << "\t"
             << "姓名: " << it->_Name << "\t"
             << "密码: " << it->_Pwd << endl;
    }
}
// 管理员类 默认构造函数
Manager::Manager() {
    
}
// 管理员类 析构函数
Manager::~Manager() {
}
// 管理员类 有参构造函数
Manager::Manager(string name, string pwd) {
    // 初始化用户名和密码
    _Name = name;
    _Pwd = pwd;

    // 初始化容器
    this->InitVectorAccount();
    
    // 初始化机房信息
    this->InitVectorRoom();
}
// 显示管理员操作菜单
void Manager::operMenu() {
    cout << "欢迎使用管理员操作菜单" << endl;
    cout << "1. 添加账号" << endl;
    cout << "2. 查看账号" << endl;
    cout << "3. 查看机房信息" << endl;
    cout << "4. 清空预约信息" << endl;
    cout << "0. 退出" << endl;
}

// 添加账号
void Manager::addAccount() {
    cout << "添加账号" << endl;
    cout << "==================" << endl;
    cout << "1. 添加学生账号" << endl;
    cout << "2. 添加教师账号" << endl;
    cout << "0. 返回" << endl;
    cout << "==================" << endl;


    // 接收用户输入
    int choice;
    ofstream ofs;       // 输出文件流对象

    int id;         // 学号/教师号
    string name;    // 用户名
    string pwd;     // 密码
    // 提示用户输入选择
    cout << "==================" << endl;
    cout << "请输入您的选择: ";
    cin >> choice;
    switch (choice)
    {
    case 1: // 添加学生账号
        cout << "==================" << endl;
        cout << "添加学生账号" << endl;
        cout << "==================" << endl;
        

        // 打开文件
        ofs.open(Student_File, ios::out | ios::app);
        if (!ofs.is_open()) {
            cout << "==================" << endl;
            cout << "文件打开失败，请检查文件名。" << endl;
            cout << "==================" << endl;
            return;
        }

        // 提示用户输入学号、用户名和密码
        cout << "请输入学号: ";
        cin >> id;
        if (this->checkRepeat(id, 1)) {
            cout << "==================" << endl;
            cout << "学号已存在，请重新输入。" << endl;
            cout << "==================" << endl;
            system("pause");
            system("cls");
            break;
        }
        cout << "请输入用户名: ";
        cin >> name;
        cout << "请输入密码: ";
        cin >> pwd;
        // 写入文件
        ofs << id << " " << name << " " << pwd << endl;
        // 关闭文件
        ofs.close();
        cout << "==================" << endl;
        cout << "学生账号添加成功！" << endl;
        cout << "==================" << endl;
        this->InitVectorAccount();
        system("pause");
        system("cls");
        break;
        
    case 2: // 添加教师账号
        cout << "==================" << endl;
        cout << "添加教师账号" << endl;
        cout << "==================" << endl;


        // 打开文件
        ofs.open(Teacher_File, ios::out | ios::app);
        if (!ofs.is_open()) {
            cout << "==================" << endl;
            cout << "文件打开失败，请检查文件名。" << endl;
            cout << "==================" << endl;
            return;
        }
        // 提示用户输入教师号、用户名和密码
        cout << "请输入教师号: ";
        cin >> id;
        if (this->checkRepeat(id, 2)) {
            cout << "==================" << endl;
            cout << "教师号已存在，请重新输入。" << endl;
            cout << "==================" << endl;
            system("pause");
            system("cls");
            break;
        }
        cout << "请输入用户名: ";
        cin >> name;
        cout << "请输入密码: ";
        cin >> pwd;
        // 写入文件
        ofs << id << " " << name << " " << pwd << endl;
        // 关闭文件
        ofs.close();
        cout << "==================" << endl;
        cout << "教师账号添加成功！" << endl;
        cout << "==================" << endl;
        this->InitVectorAccount();
        system("pause");
        system("cls");
        break;
    case 0: // 返回
        cout << "返回管理员菜单" << endl;
        break;
    default:
        cout << "==================" << endl;
        cout << "无效的选择，请重新输入。" << endl;
        cout << "==================" << endl;
        break;
    }
}
// 去除重复账号信息
void Manager::InitVectorAccount() {

    // 读取学生账号信息
    ifstream ifsStu;
    ifsStu.open(Student_File, ios::in);
    if (!ifsStu.is_open()) {
        cout << "==================" << endl;
        cout << "文件打开失败，请检查文件名。" << endl;
        cout << "==================" << endl;
        return;
    }
    
    // 初始化学生账号容器
    vStu.clear();
    // 初始化教师账号容器
    vTea.clear();

    Student stu;
    while (ifsStu >> stu._Id && ifsStu >> stu._Name && ifsStu >> stu._Pwd) {
        // 将学生对象添加到学生账号容器中
        vStu.push_back(stu);
    }
    // 读取教师账号信息
    ifstream ifsTea;
    ifsTea.open(Teacher_File, ios::in);
    if (!ifsTea.is_open()) {
        cout << "==================" << endl;
        cout << "文件打开失败，请检查文件名。" << endl;
        cout << "==================" << endl;
        return;
    }
    // 查看学生数量
    cout << "学生数量为: " << vStu.size() << endl;
    // 关闭文件
    ifsStu.close();

    // 初始化教师账号容器
    Teacher tea;
    while (ifsTea >> tea._Id && ifsTea >> tea._Name && ifsTea >> tea._Pwd) {
        // 将教师对象添加到教师账号容器中
        vTea.push_back(tea);
    }
    // 查看教师数量
    cout << "教师数量为: " << vTea.size() << endl;
    // 关闭文件
    ifsTea.close();
}

// 初始化机房容器
void Manager::InitVectorRoom() {
    // 获取机房信息
    ifstream ifs;
    ifs.open(ComputerRoom_File, ios::in);
    if (!ifs.is_open()) {
        cout << "==================" << endl;
        cout << "文件打开失败，请检查文件名。" << endl;
        cout << "==================" << endl;
        return;
    }
    // 初始化机房容器
    vRoom.clear();
    ComputerRoom room;
    while (ifs >> room._RoomId && ifs >> room._Capacity && ifs >> room._Status) {
        // 将机房对象添加到机房容器中
        vRoom.push_back(room);
    }

    cout << "机房数量为: " << vRoom.size() << endl;
    ifs.close();
}
// 查看机房信息
void Manager::viewRoomInfo() {
    cout << "查看机房信息" << endl;
    cout << "==================" << endl;
    // 查看机房数量
    cout << "机房数量为: " << vRoom.size() << endl;
    // 查看机房信息
    PrintComputerRoomInfo(vRoom);
    system("pause");
    system("cls");
}
// 检测重复账号
bool Manager::checkRepeat(int id, int type){
    if (type == 1) { // 学生
        for (vector<Student>::iterator stu = vStu.begin(); stu != vStu.end(); ++stu) {
            if (stu->_Id == id) {
                return true;
            }
        }
    }
    else if (type == 2) { // 教师
        for (vector<Teacher>::iterator tea = vTea.begin(); tea != vTea.end(); ++tea) {
            if (tea->_Id == id) {
                return true;
            }
        }
    }
    return false;
}

// 查看账号
void Manager::viewAccounts() {
    cout << "查看账号" << endl;
    cout << "==================" << endl;
    cout << "1. 查看学生账号" << endl;
    cout << "2. 查看教师账号" << endl;
    cout << "0. 返回" << endl;
    cout << "==================" << endl;
    // 接收用户输入
    int choice;
    cout << "请输入您的选择: ";
    cin >> choice;
    switch (choice) {
    case 1: // 查看学生账号
        PrintStudentInfo(vStu);
        system("pause");
        system("cls");
        break;
    case 2: // 查看教师账号
        PrintTeacherInfo(vTea);
        system("pause");
        system("cls");
        break;
    case 0: // 返回
        cout << "返回管理员菜单" << endl;
        break;
    default:
        cout << "==================" << endl;
        cout << "无效的选择，请重新输入。" << endl;
        cout << "==================" << endl;
        break;
    }
}

void PrintComputerRoomInfo(const vector<ComputerRoom>& vRoom) {
    cout << "机房信息如下: " << endl;
    for (vector<ComputerRoom>::const_iterator it = vRoom.begin(); it != vRoom.end(); ++it) {
        cout << "机房编号: " << it->_RoomId << "\t"
             << "机房容量: " << it->_Capacity << "\t"
             << "机房状态: " << (it->_Status == 0 ? "空闲" : "占用") << endl;
    }
}

// 清空预约信息
void Manager::clearReservations() {
    cout << "清空预约信息" << endl;
    cout << "==================" << endl;
    // 清空预约信息
    ofstream ofs(Order_File, ios::trunc);
    ofs.close();
    cout << "预约信息已清空" << endl;
    system("pause");
    system("cls");
}

