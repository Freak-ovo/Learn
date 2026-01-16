#pragma once
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

#include "identity.h"
#include "ComputerRoom.h"
#include "globalFile.h"
#include "OrderFile.h"

void StudentMenu(Identity * &student);


// 学生类 继承自 身份类
class Student : public Identity {
public:
    // 学生类 默认构造函数
    Student();
    // 学生类 析构函数
    ~Student();
    // 有参构造函数
    Student(int id, string name, string pwd);
    // 显示学生操作菜单
    virtual void operMenu();

    // 申请预约
    void applyReservation();

    // 查看自身预约信息
    void viewSelfReservationInfo();

    // 查看所有人的预约
    void viewAllReservations();

    // 取消预约
    void cancelReservation();
    

    int _stuId; // 学号

    // 创建机房容器
    vector<ComputerRoom> _vRoom;

    // 初始化机房容器
    void InitVectorRoom();
};