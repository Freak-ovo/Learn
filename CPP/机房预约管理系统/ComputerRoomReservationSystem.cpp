#include "ComputerRoomReservationSystem.h"
#include "identity.h"
#include "globalFile.h"
#include "student.h"
#include "teacher.h"
#include "manager.h"
// 编译命令: g++ ComputerRoomReservationSystem.cpp student.cpp teacher.cpp manager.cpp OrderFile.cpp -o ComputerRoomReservationSystem
// ComputerRoomReservationSystem.exe
// 登录验证
void LoginIn(string FileName, int type) {

    Identity* Person = NULL; // 多态指针 指向身份类基类

    // 读文件
    ifstream ifs;
    ifs.open(FileName, ios::in);

    // 判断文件是否打开成功
    if (!ifs.is_open()) {
        cout << "文件不存在，打开失败" << endl;
        ifs.close();
        return;
    }

    // 接收用户输入的账号和密码 和 id
    int id = 0;
    string name;
    string pwd;

    // 判断身份
    if (type == 1) {
        // 学生
        cout << "====学生登录验证====" << endl;

        cout << "请输入您的学号: ";
        cin >> id;

    }
    else if (type == 2) {
        // 教师
        cout << "====教师登录验证====" << endl;

        cout << "请输入您的教师号: ";
        cin >> id;

    }
    else if (type == 3) {
        // 管理员
        cout << "====管理员登录验证====" << endl;
    }
    else {
        cout << "==================" << endl;
        cout << "无效的选择，请重新输入。" << endl;
        cout << "==================" << endl;
        ifs.close();
        return;
    }

    // 输入用户名和密码
    cout << "请输入用户名: ";
    cin >> name;
    cout << "请输入密码: ";
    cin >> pwd;

    // 账号和密码验证
    if (type == 1) {
        // 学生登录验证
        int fId;
        string fName;
        string fPwd;
        // 从文件中读取学生信息
        while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
            if (fId == id && fName == name && fPwd == pwd) {
                cout << "====学生登录成功====" << endl;

                // 创建学生对象
                Person = new Student(id, name, pwd);

                // 登录成功，显示学生菜单
                StudentMenu(Person);

                system("pause");
                system("cls");
                return;
            }

        }
    }
    else if (type == 2) {
        // 教师登录验证
        int fId;
        string fName;
        string fPwd;
        // 从文件中读取教师信息
        while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
            if (fId == id && fName == name && fPwd == pwd) {
                cout << "====教师登录成功====" << endl;
                system("pause");
                system("cls");
                // 创建教师对象
                Person = new Teacher(id, name, pwd);

                // 登录成功，显示教师菜单
                TeacherMenu(Person);

                system("pause");
                system("cls");
                return;
            }
        }
    }
    else if (type == 3) {
        // 管理员登录验证
        string fName;
        string fPwd;
        // 从文件中读取管理员信息
        while (ifs >> fName && ifs >> fPwd) {
            cout << "管理员用户名: " << fName << " 密码: " << fPwd << endl;
            if (fName == name && fPwd == pwd) {
                cout << "====管理员登录成功====" << endl;
                // 创建管理员对象
                Person = new Manager(name, pwd);

                // 登录成功，显示管理员菜单
                ManagerMenu(Person);

                system("pause");
                system("cls");
                return;
            }
        }
    }

    // 验证失败，释放对象

    cout << "验证失败！" << endl;
    system("pause");
    system("cls");
    return;
    
    


}






ComputerRoomReservationSystem::ComputerRoomReservationSystem() {
    // Constructor implementation (if needed)   
    cout << "Welcome to the Computer Room Reservation System!" << endl;
}

void ComputerRoomReservationSystem::mainMenu() {
    cout << "===== Computer Room Reservation System =====" << endl;
    cout << "Please select your identity:" << endl;
    cout << "----------------------------------" << endl;
    cout << "\t\t |       1. 学生代表           |" << endl;
    cout << "\t\t |       2. 教    师           |" << endl;
    cout << "\t\t |       3. 管 理 员           |" << endl;
    cout << "\t\t |       0. 退出系统           |" << endl;
    cout << "----------------------------------" << endl;
}
ComputerRoomReservationSystem::~ComputerRoomReservationSystem() {
    // Destructor implementation (if needed)
    cout << "Exiting the Computer Room Reservation System. Goodbye!" << endl;
}
int main() {
    ComputerRoomReservationSystem computerSystem;
    computerSystem.mainMenu();
    int choice;
    while (true)
    {
        computerSystem.mainMenu();
        cout << "请输入你的选择: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "You selected 学生代表." << endl;
            LoginIn(Student_File, 1); 
            break;
        case 2:
            cout << "You selected 教师." << endl;
            LoginIn(Teacher_File, 2);
            break;
        case 3:
            cout << "You selected 管理员." << endl; 
            LoginIn(Admin_File, 3);
            break;
        case 0:
            cout << "Exiting the system. Goodbye!" << endl;
            system("pause");
            system("cls");
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
            computerSystem.mainMenu();
            break;
        }
    }
    
    return 0;
}   