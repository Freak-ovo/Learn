#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#include "identity.h"
#include "globalFile.h"
#include "student.h"
#include "teacher.h"
#include "ComputerRoom.h"

void ManagerMenu(Identity* &manager);
void InitVectorRoom();
void InitVectorAccount();
void PrintStudentInfo(const vector<Student>& vStu);
void PrintTeacherInfo(const vector<Teacher>& vTea);
void PrintComputerRoomInfo(const vector<ComputerRoom>& vRoom);

// 管理员类 继承自 身份类
class Manager : public Identity {
public:
    // 管理员类 默认构造函数
    Manager();

    // 管理员类 析构函数
    ~Manager();

    // 管理员类 有参构造函数
    Manager(string name, string pwd);

    // 显示管理员操作菜单
    void operMenu();

    // 添加账号
    void addAccount();

    // 查看账号
    void viewAccounts();

    // 查看机房信息
    void viewRoomInfo();

    // 清空预约信息
    void clearReservations();

    // 去除重复账号信息
    void InitVectorAccount();
    // 初始化机房信息
    void InitVectorRoom();

    // 学生账号容器
    vector<Student> vStu;

    // 教师账号容器
    vector<Teacher> vTea;
    // 检测重复账号
    bool checkRepeat(int id, int type);

    // 创建机房容器
    vector<ComputerRoom> vRoom;


};