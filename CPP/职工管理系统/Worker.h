#pragma once  // 防止头文件被重复包含

#include <iostream>   // 输入输出流
#include <fstream>    // 文件流，用于文件读写操作
using namespace std;  // 使用标准命名空间

class Worker
{
public:
    //显示个人信息;
    virtual void ShowInfo() = 0;

    //获取岗位名称
    virtual string GetDeptName() = 0;
    //职工编号
    int __ID;
    //职工姓名
    string __Name;
    //部门编号
    int __DeptID;
};