#pragma once  // 防止头文件被重复包含
#include <iostream>   // 输入输出流
#include <fstream>    // 文件流，用于文件读写操作
#include "Worker.h"
#include "Boss.h"
#include "Manager.h"
#include "Employee.h"

#define FILENAME "EmpFile.txt"
using namespace std;  // 使用标准命名空间

/**
 * @brief 职工管理系统类
 * 
 * 功能：管理职工信息的核心类，提供职工信息的增删改查等功能
 */
class WorkerManager
{
public:
    /**
     * @brief 构造函数
     * 
     * 功能：初始化职工管理系统，加载已有数据
     */
    WorkerManager();
    
    /**
     * @brief 显示系统菜单
     * 
     * 功能：在控制台显示职工管理系统的操作菜单
     * 包括：添加、显示、删除、修改、查找、排序、清空等功能选项
     */
    void Show_Menu();
    

    void ExitSystem();
    
    void Add_Emp();

    //保存文件
    void Save();

    bool __FileIsEmpty;

    //统计文件中人数
    int Get_EmpNum();
    //显示职工
    void Show_Emp();
    
    //删除职工
    void Delete_Emp();
    //判断职工是否存在 如果存在返回职工所在数组的位置 不存在返回-1
    int IsExist(int ID);

    //修改员工
    void Modify_Emp();

    //查找职工
    void Find_Emp();

    //排序
    void Sort_Emp();
    //初始化员工

    //清空文件
    void Clean_File();

    void Init_Emp();
    /**
     * @brief 析构函数
     * 
     * 功能：清理系统资源，保存数据到文件
     */
    ~WorkerManager();
    
    // 注意：这里可以继续添加其他成员函数声明
    // 例如：AddWorker(), DeleteWorker(), SaveToFile() 等
public:
    //记录职工人数
    int __EmpNum;
    //职工数组指针
    Worker **__EmpArray;
};