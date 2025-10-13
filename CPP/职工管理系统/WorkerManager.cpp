#include "WorkerManager.h" // 包含自定义头文件，声明WorkerManager类
#include <iostream>        // 输入输出流，用于控制台输入输出
#include <fstream>         // 文件流操作，用于读写文件

using namespace std;       // 使用标准命名空间

/**
 * @brief 构造函数实现
 * 
 * 功能：初始化职工管理系统对象，检查数据文件状态并加载已有数据
 * 流程：
 * 1. 检查文件是否存在
 * 2. 如果文件不存在，初始化空系统
 * 3. 如果文件存在但为空，初始化空系统
 * 4. 如果文件存在且有数据，加载数据到内存
 */
WorkerManager::WorkerManager()
{
    // 打开文件进行读取
    ifstream ifs;
    ifs.open(FILENAME, ios::in); // 以输入模式打开文件
    
    // 情况1：文件不存在
    if (!ifs.is_open())
    {
        cout << "文件不存在" << endl;
        // 初始化空系统
        this->__EmpNum = 0;           // 职工数量设为0
        this->__EmpArray = NULL;      // 职工数组指针设为空
        this->__FileIsEmpty = true;   // 标记文件为空
        ifs.close();                  // 关闭文件流
        return;                       // 返回
    }

    // 情况2：文件存在但数据为空
    char ch;
    ifs >> ch;                        // 尝试读取一个字符
    if (ifs.eof())                    // 如果立即到达文件末尾
    {
        cout << "文件为空！" << endl;
        // 初始化空系统
        this->__EmpNum = 0;
        this->__EmpArray = NULL;
        this->__FileIsEmpty = true;
        ifs.close();
        return;
    }

    // 情况3：文件存在且有数据
    int Num = this->Get_EmpNum();     // 获取文件中的职工人数
    cout << "职工人数为：" << Num << endl;
    
    // 初始化成员变量
    this->__EmpNum = Num;                         // 设置职工数量
    this->__EmpArray = new Worker*[this->__EmpNum]; // 动态分配职工指针数组
    this->Init_Emp();                             // 初始化职工数据
    
    // 调试信息：打印所有职工信息（生产环境中可注释掉）
    for (int i = 0; i < this->__EmpNum; i++)
    {
        cout << "职工编号：" << this->__EmpArray[i]->__ID
             << " 姓名：" << this->__EmpArray[i]->__Name
             << " 部门编号:" << this->__EmpArray[i]->__DeptID
             << endl;
    }        
}

/**
 * @brief 统计文件中职工人数
 * 
 * 功能：读取文件并统计职工记录数量
 * 文件格式：每行包含 编号 姓名 部门ID
 * 
 * @return int 返回文件中的职工人数
 */
int WorkerManager::Get_EmpNum()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in); // 以输入模式打开文件

    int ID;        // 临时存储职工编号
    string Name;   // 临时存储职工姓名
    int DID;       // 临时存储部门ID
    int Num = 0;   // 计数器，记录职工人数
    
    // 循环读取文件，每成功读取一行（三个字段）计数加1
    while (ifs >> ID && ifs >> Name && ifs >> DID)
    {
        Num++; // 职工人数增加
    }

    return Num; // 返回总人数
}

/**
 * @brief 添加职工函数实现
 * 
 * 功能：向系统中添加新的职工信息
 * 流程：
 * 1. 获取要添加的职工数量
 * 2. 计算新数组大小并分配内存
 * 3. 将原有数据拷贝到新数组
 * 4. 输入新职工信息并创建对应对象
 * 5. 更新系统状态并保存到文件
 */
void WorkerManager::Add_Emp()
{
    cout << "请输入添加职工的数量：" << endl;

    int AddNum = 0; // 保存用户输入的添加数量
    cin >> AddNum;

    // 验证输入数量是否有效
    if (AddNum > 0)
    {
        // 步骤1：计算新空间大小
        int NewSize = this->__EmpNum + AddNum; // 新空间大小 = 原来人数 + 新增人数

        // 步骤2：开辟新空间
        Worker **newSpace = new Worker *[NewSize];

        // 步骤3：将原有数据拷贝到新空间
        if (this->__EmpArray != NULL)
        {
            for (int i = 0; i < this->__EmpNum; i++)
            {
                newSpace[i] = this->__EmpArray[i]; // 拷贝指针
            }
        }

        // 步骤4：输入新职工信息
        for (int i = 0; i < AddNum; i++)
        {
            int ID;        // 职工编号
            string Name;   // 职工姓名
            int DSelect;   // 部门选择

            // 获取职工基本信息
            cout << "请输入第 " << i + 1 << " 个新职工编号：" << endl;
            cin >> ID;
            cout << "请输入第 " << i + 1 << " 个新职工姓名：" << endl;
            cin >> Name;
            
            // 选择岗位类型
            cout << "请选择该员工的岗位：" << endl;
            cout << "1.员工" << endl;
            cout << "2.经理" << endl;
            cout << "3.老板" << endl;
            cin >> DSelect;

            // 根据选择创建不同类型的职工对象
            Worker *worker = NULL;
            switch (DSelect)
            {
            case 1: // 普通员工
                worker = new Employee(ID, Name, 1);
                break;
            case 2: // 经理
                worker = new Manager(ID, Name, 2);
                break;
            case 3: // 老板
                worker = new Boss(ID, Name, 3);
                break;
            default: // 无效选择
                break;
            }

            // 将新职工添加到数组的相应位置
            newSpace[this->__EmpNum + i] = worker;
        }

        // 步骤5：清理和更新
        delete[] this->__EmpArray;    // 释放原有数组空间
        this->__EmpArray = newSpace;  // 指向新数组
        this->__EmpNum = NewSize;     // 更新职工人数
        this->__FileIsEmpty = false;  // 标记文件不为空
        
        cout << "成功添加" << AddNum << "名新职工" << endl;
        this->Save(); // 保存数据到文件
    }
    else
    {
        cout << "输入错误，请输入正确的人数！" << endl; // 输入验证失败
    }

    // 用户交互：暂停并清屏
    system("pause");
    system("cls");
}

//修改员工
void WorkerManager::Modify_Emp()
{
    if (this->__FileIsEmpty)
    {
        cout << "文件不存在或记录为空！" << endl;
    } 
    else
    {
        cout << "请输入修改职工的编号！" << endl;
        int ID;
        cin >> ID;

        int Ret = this->IsExist(ID);
        if (Ret != -1)
        {
            //查找到编号的职工
            delete this->__EmpArray[Ret];

            int NewID = 0;
            string NewName = "";
            int NewDSelect = 0;
            cout << "查找到编号：" << ID << "请输入新职工号：" << endl;
            cin >> NewID;
            cout << "请输入新的姓名：" << endl;
            cin >> NewName;
            cout << "请输入新的岗位：" << endl;
            cout << "1.员工" << endl;
            cout << "2.经理" << endl;
            cout << "3.老板" << endl;
            cin >> NewDSelect;

            Worker *worker = NULL;
            switch (NewDSelect)
            {
            case 1: // 普通员工
                worker = new Employee(NewID, NewName, 1);
                break;
            case 2: // 经理
                worker = new Manager(NewID, NewName, 2);
                break;
            case 3: // 老板
                worker = new Boss(NewID, NewName, 3);
                break;
            default:
                break;
            }

            //更新数据
            this->__EmpArray[Ret] = worker;
            cout << "修改成功！" << endl;
            //保存到文件中
            this->Save();
        }
        else
        {
            cout << "修改失败，查无此人！" << endl;
        }
        
    }
    system("pause");
    system("cls");
}

/**
 * @brief 保存数据到文件函数实现
 * 
 * 功能：将当前职工数据保存到文件中
 * 文件格式：每行保存一个职工的信息（编号 姓名 部门ID）
 * 用途：数据持久化，确保程序关闭后数据不丢失
 */
void WorkerManager::Save()
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out); // 以输出模式打开文件

    // 检查文件是否成功打开
    if (!ofs.is_open())
    {
        cout << "文件打开失败！" << endl;
        return;
    }

    // 遍历职工数组，将每个职工的信息写入文件
    for (int i = 0; i < this->__EmpNum; i++)
    {
        ofs << this->__EmpArray[i]->__ID << " "
            << this->__EmpArray[i]->__Name << " "
            << this->__EmpArray[i]->__DeptID << endl;
    }

    ofs.close(); // 关闭文件流
    cout << "数据已成功保存到文件！" << endl;
}

/**
 * @brief 显示菜单函数实现
 * 
 * 功能：在控制台输出格式化的菜单界面
 * 菜单选项说明：
 * 0-退出系统，1-添加职工，2-显示职工，3-删除职工
 * 4-修改职工，5-查找职工，6-排序，7-清空数据
 * 设计：清晰的分层结构，便于用户理解和操作
 */
void WorkerManager::Show_Menu()
{
    // 输出菜单顶部边框
    cout << "**************************" << endl;

    // 输出系统标题
    cout << "欢迎使用职工管理系统！" << endl;

    // 输出各个功能选项
    cout << "0.退出管理程序" << endl; // 安全退出整个系统
    cout << "1.添加职工信息" << endl; // 添加新的职工记录
    cout << "2.显示职工信息" << endl; // 显示所有职工信息列表
    cout << "3.删除离职职工" << endl; // 根据编号删除职工记录
    cout << "4.修改职工信息" << endl; // 根据编号修改职工信息
    cout << "5.查找职工信息" << endl; // 按编号或姓名搜索职工
    cout << "6.按照编号排序" << endl; // 对职工按编号进行排序
    cout << "7.清空所有文档" << endl; // 清空所有数据（危险操作）

    // 输出菜单底部边框
    cout << "**************************" << endl;

    // 输出空行，使菜单显示更清晰
    cout << endl;
}

/**
 * @brief 退出系统函数实现
 * 
 * 功能：安全退出职工管理系统
 * 流程：显示退出信息→暂停→退出程序
 * 设计：友好的退出体验，给用户确认时间
 */
void WorkerManager::ExitSystem()
{
    cout << "欢迎下次使用！" << endl;
    system("pause"); // 暂停，等待用户按键
    exit(0);         // 退出程序
}

/**
 * @brief 初始化职工数据
 * 
 * 功能：从文件读取数据并初始化职工对象数组
 * 流程：
 * 1. 打开文件
 * 2. 逐行读取数据
 * 3. 根据部门ID创建对应类型的职工对象
 * 4. 将对象存入数组
 * 5. 关闭文件
 */
void WorkerManager::Init_Emp()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in); // 以输入模式打开文件
    
    int ID;        // 临时存储职工编号
    string Name;   // 临时存储职工姓名
    int DID;       // 临时存储部门ID
    int Index = 0; // 数组索引
    
    // 循环读取文件直到结束
    while (ifs >> ID && ifs >> Name && ifs >> DID)
    {
        Worker *worker = NULL; // 创建职工指针

        // 根据部门ID创建不同类型的职工对象
        if (DID == 1) // 普通员工
        {
            worker = new Employee(ID, Name, DID);
        }
        else if (DID == 2) // 经理
        {
            worker = new Manager(ID, Name, DID);
        }
        else // 老板（部门ID为3或其他）
        {
            worker = new Boss(ID, Name, DID);
        }
        
        // 将职工对象存入数组并递增索引
        this->__EmpArray[Index] = worker;
        Index++;
    }
    
    // 关闭文件
    ifs.close();
}

/**
 * @brief 显示所有职工信息
 * 
 * 功能：在控制台显示系统中所有职工的信息
 * 特点：利用多态机制，自动调用相应职工类型的显示方法
 * 流程：
 * 1. 检查系统是否为空
 * 2. 遍历数组调用每个职工的ShowInfo方法
 */
void WorkerManager::Show_Emp()
{
    // 检查系统是否为空
    if (this->__FileIsEmpty)
    {
        cout << "文件不存在或记录为空！" << endl;
        return;
    }
    else
    {
        // 遍历所有职工并显示信息
        for (int i = 0; i < this->__EmpNum; i++)
        {
            // 利用多态调用相应职工类型的显示接口
            this->__EmpArray[i]->ShowInfo();
        }
    }
    
    // 用户交互：暂停并清屏
    system("pause");
    system("cls");
}

/**
 * @brief 删除职工函数实现
 * 
 * 功能：根据职工编号删除指定的职工记录
 * 流程：
 * 1. 检查系统是否为空
 * 2. 获取要删除的职工编号
 * 3. 检查职工是否存在
 * 4. 如果存在，执行删除操作
 * 5. 更新系统状态并保存
 */
void WorkerManager::Delete_Emp()
{
    // 检查系统是否为空
    if (this->__FileIsEmpty)
    {
        cout << "文件不存在或记录为空！" << endl;
    }
    else
    {
        // 获取要删除的职工编号
        cout << "请输入想要删除的职工编号：" << endl;
        int ID = 0;
        cin >> ID;

        // 检查职工是否存在
        int Index = this->IsExist(ID);

        if (Index != -1) // 职工存在，执行删除
        {
            // 修复：先释放要删除的职工对象内存
            delete this->__EmpArray[Index];
            
            // 将后面的元素前移，覆盖要删除的元素
            for (int i = Index; i < this->__EmpNum - 1; i++)
            {
                this->__EmpArray[i] = this->__EmpArray[i + 1];
            }
            
            this->__EmpNum--; // 更新职工数量
            
            // 如果删除后数组为空，重置相关状态
            if (this->__EmpNum == 0)
            {
                delete[] this->__EmpArray;
                this->__EmpArray = NULL;
                this->__FileIsEmpty = true;
            }
            
            this->Save();     // 保存到文件
            cout << "删除成功!" << endl;
        }
        else
        {
            cout << "删除失败，未找到该职工！" << endl;
        } 
    }
    
    // 用户交互：暂停并清屏
    system("pause");
    system("cls");
}

/**
 * @brief 判断职工是否存在
 * 
 * 功能：根据职工编号查找职工在数组中的位置
 * 
 * @param ID 要查找的职工编号
 * @return int 如果找到返回职工在数组中的索引，否则返回-1
 */
int WorkerManager::IsExist(int ID)
{
    int Index = -1; // 初始化为-1，表示未找到
    
    // 修复后的正确循环条件：遍历所有职工
    for (int i = 0; i < this->__EmpNum; i++)
    {
        if (this->__EmpArray[i]->__ID == ID)
        {
            Index = i; // 记录找到的位置
            break;     // 找到后立即退出循环
        }
    }
    
    return Index; // 返回结果：找到返回索引，未找到返回-1
}

//查找职工
void WorkerManager::Find_Emp()
{
    if (this->__FileIsEmpty)
    {
        cout << "文件不存在，或者记录为空！" << endl;
    }
    else
    {
        cout << "请输入查找的方式：" << endl;
        cout << "1.按照职工编号查找 " << endl;
        cout << "2.按照职工姓名查找 " << endl;
        
        int Select = 0;
        cin >> Select;
        if (Select = 1)
        {
            int ID;
            cout << "请输入查找的职工编号：" << endl;
            cin >> ID;
            int Ret = IsExist(ID);
            if (Ret != -1)
            {
                cout << "查找成功！" << endl;
                this->__EmpArray[Ret]->ShowInfo();
            }
            else
            {
                cout << "查找失败，查无此人！" << endl;
                
            }
        }
        else if (Select = 2)
        {
            //按照姓名
            string Name;
            cout << "请输入查找的姓名：" << endl;
            cin >> Name;
            //加入判断是否查到的标志
            bool flag = false;
            
            for (int i = 0; i < __EmpNum; i++)
            {
                if (this->__EmpArray[i]->__Name == Name)
                {
                    cout << "查找成功， 职工编号为：" << this->__EmpArray[i]->__ID << endl;
                    cout << "职工信息如下：" << endl;
                    this->__EmpArray[i]->ShowInfo();
                    flag = true;
                }
                
            }
            if (flag == false)
            {
                cout << "查找失败！" << endl;
            }
            
        }
        else
        {
            cout << "输入的选项有误！ "  << endl;
        }
        
        

    }
    system("pause");
    system("cls");
}


void WorkerManager::Sort_Emp()
{
    if (this->__FileIsEmpty)
    {
        cout << "文件不存在！" << endl;
        system("pause");
        system("cls");
        return; // 提前返回，避免进入else分支
    }
    
    cout << "请选择排序方式：" << endl;
    cout << "1.按照职工号进行升序排列" << endl;
    cout << "2.按照职工号进行降序排列" << endl;

    int Select = 0;
    cin >> Select;
    
    // 增加输入验证
    if (Select != 1 && Select != 2)
    {
        cout << "输入错误，请选择1或2！" << endl;
        system("pause");
        system("cls");
        return;
    }
    
    for (int i = 0; i < __EmpNum; i++)
    {
        int MinOrMax = i;
        for (int j = i + 1; j < this->__EmpNum; j++)
        {
            if (Select == 1) // 升序
            {
                if (this->__EmpArray[MinOrMax]->__ID > this->__EmpArray[j]->__ID)
                {
                    MinOrMax = j;
                }
            }
            else // 降序
            {
                if (this->__EmpArray[MinOrMax]->__ID < this->__EmpArray[j]->__ID)
                {
                    MinOrMax = j;
                }
            }
        }
        
        // 交换数据
        if (i != MinOrMax)
        {
            Worker* Temp = this->__EmpArray[i];
            this->__EmpArray[i] = this->__EmpArray[MinOrMax];
            this->__EmpArray[MinOrMax] = Temp;
        }
    }
    
    cout << "排序成功！排序后的结果为：" << endl;
    this->Show_Emp(); // 先显示再保存，确保显示的是排序后的数据
    this->Save();     // 确保Save()方法正确实现了保存逻辑
    
    system("pause");
    system("cls");
}


//清空文件
void WorkerManager::Clean_File()
{
    cout << "确认清空？" << endl;
    cout << "1.确定" << endl;
    cout << "2.返回" << endl;

    int Select = 0;
    cin >> Select;

    if (Select == 1)
    {
        ofstream ofs;
        ofs.open(FILENAME, ios::trunc);
        ofs.close();

        if (this->__EmpArray != NULL)
        {
            for (int i = 0; i < this->__EmpNum; i++)
            {
                delete this->__EmpArray[i];
                this->__EmpArray[i] = NULL;
            }
            delete[] this->__EmpArray;
            this->__EmpArray = NULL;
            this->__EmpNum = 0;
            this->__FileIsEmpty = true;
        }
        cout << "清空成功！ " << endl;
    }   
    system("pause");
    system("cls");

}
    

/**
 * @brief 析构函数实现
 * 
 * 功能：在对象销毁前执行清理操作，防止内存泄漏
 * 流程：
 * 1. 检查职工数组是否为空
 * 2. 释放每个职工对象的内存
 * 3. 释放职工指针数组的内存
 * 4. 将指针设为NULL防止悬空指针
 * 
 * 设计原则：遵循RAII原则，确保资源正确释放
 */
WorkerManager::~WorkerManager()
{
    // 检查职工数组是否为空
    if (this->__EmpArray != NULL)
    {
        // 先释放每个Worker对象
        for (int i = 0; i < this->__EmpNum; i++)
        {
            delete this->__EmpArray[i]; // 释放每个职工对象
        }
        
        // 再释放指针数组
        delete[] this->__EmpArray; 
        this->__EmpArray = NULL; // 防止悬空指针
    }

    cout << "职工管理系统清理完成！" << endl; // 提示清理成功
}