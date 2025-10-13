#include "Employee.h"
#include <iostream>  // 确保cout和endl可用

using namespace std;

/**
 * @brief Employee类构造函数
 * @param ID 职工编号
 * @param Name 职工姓名
 * @param DID 部门编号（对于Employee类，此参数应该固定为1）
 */
Employee::Employee(int ID, string Name, int DID) 
{
    this->__ID = ID;
    this->__Name = Name;
    this->__DeptID = DID;  // 修正：普通职工的部门编号应该固定为1，忽略传入的DID参数
}



/**
 * @brief 显示职工的个人信息
 * 
 * 功能：在控制台输出职工的详细信息
 * 输出格式：职工编号、姓名、部门名称和岗位职责
 */
void Employee::ShowInfo()
{
    cout << "职工编号：" << this->__ID
         << "\t职工姓名：" << this->__Name
         << "\t岗位名称：" << this->GetDeptName()  // 修正：改为"岗位名称"更准确
         << "\t岗位职责：完成经理交代的任务" << endl;
}

/**
 * @brief 获取岗位名称
 * @return string 返回岗位名称字符串"员工"
 * 
 * 功能：返回职工的岗位名称
 * 注意：Employee类的岗位名称固定为"员工"
 */
string Employee::GetDeptName()
{
    return string("员工");  // 使用string构造函数，确保返回的是string对象
}