#include <iostream>
#include "WorkerManager.h" 
#include "Worker.h"
#include "Employee.h" 
#include "Manager.h"
#include "Boss.h"
using namespace std;
//g++ *.cpp -o 职工管理系统 && 职工管理系统.exe
int main()
{

    // 注意：这里使用的类名必须与头文件中定义的类名完全一致
    WorkerManager wm;  
    int choice = 0;     
    
    while (true)
    {
        wm.Show_Menu();
        cout << "请输入您的选择：" << endl;
        cin >> choice;
        
        switch (choice)
        {
        case 0:  // 退出系统
            wm.ExitSystem();
            return 0;
            break;
        case 1:  // 添加职工
            wm.Add_Emp();
            break;
        case 2:  // 显示职工
            wm.Show_Emp();
            break;
        case 3:  // 删除职工
            wm.Delete_Emp();
            break;
        case 4:  // 修改职工
            wm.Modify_Emp();
            break;
        case 5:  // 查找职工
            wm.Find_Emp();
            break;
        case 6:  // 排序
            wm.Sort_Emp();
            break;
        case 7:  // 清空
            wm.Clean_File();
            break;
        default:
            cout << "输入错误，请重新输入！" << endl;
            system("pause");  // 修正拼写
            system("cls");    // 清屏
            break;
        }
    }
    
    return 0;
}