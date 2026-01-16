#pragma once

#include <iostream>
using namespace std;

// 身份基类 
class Identity {
public:
    virtual void operMenu() = 0; // Pure virtual function for displaying the operation menu
    virtual ~Identity() {} // Virtual destructor

    // 用户名
    string _Name;
    // 密码
    string _Pwd;

    int _Id; // 用户ID


};