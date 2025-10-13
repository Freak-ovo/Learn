#include "Boss.h"
#include <iostream>  // 添加iostream头文件，确保cout和endl可用

using namespace std;

/**
 * @brief Boss类构造函数
 * @param ID 职工编号
 * @param Name 职工姓名
 * @param DID 部门编号（对于Boss类，此参数可能不需要，因为部门固定）
 */
Boss::Boss(int ID, string Name, int DID)
{
    this->__ID = ID;
    this->__Name = Name;
    this->__DeptID = 3;  // 修正：老板的部门编号应该固定为3，忽略传入的DID参数
}

/**
 * @brief 显示老板的个人信息
 * 
 * 功能：在控制台输出老板的详细信息
 * 输出格式：职工编号、姓名、部门名称和岗位职责
 */
void Boss::ShowInfo()
{
    cout << "职工编号：" << this->__ID
         << "\t职工姓名：" << this->__Name
         << "\t部门编号：" << this->GetDeptName()
         << "\t岗位职责：管理公司所有事务！" << endl;  // 修正：错别字"事物"改为"事务"
}

/**
 * @brief 获取部门名称
 * @return string 返回部门名称字符串"老板"
 * 
 * 功能：返回老板的部门名称
 * 注意：Boss类的部门名称固定为"老板"
 */
string Boss::GetDeptName()
{
    return string("老板");
}