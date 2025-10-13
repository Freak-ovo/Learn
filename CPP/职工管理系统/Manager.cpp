#include "Manager.h"

Manager::Manager(int ID, string Name, int DID)
{
    this->__ID = ID;
    this->__Name = Name;
    this->__DeptID = DID;
}

//显示个人信息;
void Manager::ShowInfo()
{
    cout << "职工编号：" << this->__ID
         << "\t职工姓名：" << this->__Name
         << "\t部门编号：" << this->GetDeptName()
         << "\t岗位职责： 完成老板交代的任务并且下发任务给普通员工" << endl;

}

//获取岗位名称
string Manager::GetDeptName()
{
    return string("经理");
}
