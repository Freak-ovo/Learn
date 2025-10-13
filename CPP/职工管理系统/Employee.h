#pragma once

#include <iostream>
#include "Worker.h"
using namespace std;

class Employee : public Worker
{
public:
    // 构造函数
    Employee(int ID, string Name, int DID);
    ~Employee();

    // 显示个人信息
    virtual void ShowInfo();

    // 获取岗位名称
    virtual string GetDeptName();

    int __ID;
    // 职工姓名
    string __Name;
    // 部门编号
    int __DeptID;
};