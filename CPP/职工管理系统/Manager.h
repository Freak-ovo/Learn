#pragma once
#include <iostream>
#include "Worker.h"
using namespace std;

class Manager :public Worker
{
public:
    Manager(int ID, string Name, int DID);
    ~Manager();
    //显示个人信息;
    virtual void ShowInfo();

    //获取岗位名称
    virtual string GetDeptName();

};