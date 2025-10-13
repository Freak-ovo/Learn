#pragma once
#include <iostream>
#include "Worker.h"
using namespace std;

class Boss : public Worker
{
public:
    Boss(int ID, string Name, int DID);
    ~Boss();
    // 显示个人信息;
    virtual void ShowInfo();

    // 获取岗位名称
    virtual string GetDeptName();
};