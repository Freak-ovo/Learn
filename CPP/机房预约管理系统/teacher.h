#pragma once
#include <iostream>
using namespace std;

#include "identity.h"
#include "globalFile.h"
#include "OrderFile.h"
#include "ComputerRoom.h"
#include "Student.h"

// 教师类菜单
void TeacherMenu(Identity* &teacher);
// 教师类 继承自 身份类
class Teacher : public Identity {
public:


    // 教师类 默认构造函数
    Teacher();
    // 教师类 析构函数
    ~Teacher();

    // 教师类 有参构造函数
    Teacher(int id, string name, string pwd);
    // 显示教师操作菜单
    void operMenu();

    // 查看所有预约
    void viewAllReservations();

    // 审核预约
    void approveReservation();

     int _teaId; // 教师号

};