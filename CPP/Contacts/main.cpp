#include <iostream>
#include <string>  // 注意这里应该用<string>而不是<string.h>

using namespace std;

#define MAX 1000

// 显示菜单
void ShowMenu()
{
    cout << "1.添加联系人" << endl;
    cout << "2.显示联系人" << endl;
    cout << "3.删除联系人" << endl;
    cout << "4.查找联系人" << endl;
    cout << "5.修改联系人" << endl;
    cout << "6.清空联系人" << endl;
    cout << "0.退出通讯录" << endl;
}

// 联系人结构体
struct Person
{
    string Name;
    string Sex;
    int Age;
    string Phone;
    string Address;
};

// 通讯录结构体
struct AddressBooks
{
    struct Person PersonArray[MAX];
    int Size;
};

// 添加联系人
void AddPerson(AddressBooks* Abs)
{
    if (Abs->Size >= MAX)  // 这里修改为>=更准确
    {
        cout << "通讯录已满，无法添加！" << endl;
        return;
    }
    
    string Name;
    cout << "请输入姓名：" << endl;
    cin >> Name;
    Abs->PersonArray[Abs->Size].Name = Name;

    cout << "请输入性别：" << endl;
    cout << "请输入：男 / 女" << endl;  // 添加提示信息
    while (true)
    {
        string Sex;
        cin >> Sex;
        if (Sex == "男" || Sex == "女")
        {
            Abs->PersonArray[Abs->Size].Sex = Sex;
            break;
        }
        else
        {
            cout << "输入错误，请重新输入性别（男/女）：" << endl;
        }
    }

    int Age;
    cout << "请输入年龄：" << endl;
    cin >> Age;
    Abs->PersonArray[Abs->Size].Age = Age;

    string Phone;
    cout << "请输入手机号：" << endl;
    cin >> Phone;
    Abs->PersonArray[Abs->Size].Phone = Phone;

    string Address;
    cout << "请输入地址：" << endl;
    cin >> Address;
    Abs->PersonArray[Abs->Size].Address = Address;

    // 更新通讯录人数
    Abs->Size++;
    cout << "添加成功！" << endl;

    system("pause");
    system("cls");
}

// 显示所有联系人
void ShowPerson(AddressBooks *Abs)
{
    if (Abs->Size == 0)
    {
        cout << "当前的记录为空！" << endl;
    }
    else
    {
        for (int i = 0; i < Abs->Size; i++)
        {
            cout << "姓名：" << Abs->PersonArray[i].Name << "\t";
            cout << "性别：" << Abs->PersonArray[i].Sex << "\t";
            cout << "年龄：" << Abs->PersonArray[i].Age << "\t";
            cout << "电话：" << Abs->PersonArray[i].Phone << "\t";
            cout << "地址：" << Abs->PersonArray[i].Address << endl;
        }
    }
    system("pause");
    system("cls");
}

// 查找联系人是否存在，存在返回索引，不存在返回-1
int isExist(AddressBooks* Abs, string Name)
{
    for (int i = 0; i < Abs->Size; i++)
    {
        if (Abs->PersonArray[i].Name == Name)
        {
            return i;
        }
    }
    return -1;
}

// 删除联系人
void DeletePerson(AddressBooks* Abs)
{
    cout << "请输入您想要删除的联系人：" << endl;
    
    string Name;
    cin >> Name;
    int Ret = isExist(Abs, Name);
    if (Ret != -1)
    {
        for (int i = Ret; i < Abs->Size - 1; i++)  // 这里修改循环条件，防止越界
        {
            Abs->PersonArray[i] = Abs->PersonArray[i + 1];
        } 
        Abs->Size--;
        cout << "删除成功！" << endl;
    }
    else
    {
        cout << "未找到此人！" << endl;
    }
    system("pause");
    system("cls");
}

// 查找联系人
void FindPerson(AddressBooks* Abs)
{
    cout << "请输入您想要查找的联系人：" << endl;
    string Name;
    cin >> Name;
    int Ret = isExist(Abs, Name);
    if (Ret != -1)
    {
        cout << "姓名：" << Abs->PersonArray[Ret].Name << "\t";
        cout << "性别：" << Abs->PersonArray[Ret].Sex << "\t";
        cout << "年龄：" << Abs->PersonArray[Ret].Age << "\t";
        cout << "电话：" << Abs->PersonArray[Ret].Phone << "\t";
        cout << "地址：" << Abs->PersonArray[Ret].Address << endl;
    }
    else
    {
        cout << "未找到该联系人！" << endl;
    }
    system("pause");
    system("cls");
}

// 修改联系人信息
void ModifyPerson(AddressBooks* Abs)
{
    cout << "请输入您需要修改的联系人" << endl;
    string Name;
    cin >> Name;
    int Ret = isExist(Abs, Name);
    if (Ret != -1)
    {
        string newName;
        cout << "请输入姓名：" << endl;
        cin >> newName;
        Abs->PersonArray[Ret].Name = newName;

        cout << "请输入性别：" << endl;
        while (true)
        {
            string Sex;
            cin >> Sex;
            if (Sex == "男" || Sex == "女")
            {
                Abs->PersonArray[Ret].Sex = Sex;
                break;
            }
            else
            {
                cout << "请输入正确的性别（男/女）" << endl;  // 修正错别字"真确"为"正确"
            }
        }

        cout << "请输入年龄：" << endl;
        int Age = 0;
        cin >> Age;
        Abs->PersonArray[Ret].Age = Age;

        cout << "请输入手机号码：" << endl;
        string phone;
        cin >> phone;
        Abs->PersonArray[Ret].Phone = phone;

        cout << "请输入地址：" << endl;
        string Address;
        cin >> Address;
        Abs->PersonArray[Ret].Address = Address;

        cout << "修改成功！" << endl;
    }
    else  // 添加else，避免找到联系人后仍显示此消息
    {
        cout << "没有该用户信息" << endl;
    }
    system("pause");
    system("cls");
}

// 清空联系人
void CleanPerson(AddressBooks *Abs)
{
    Abs->Size = 0;
    cout << "通讯录已清空" << endl;
    system("pause");
    system("cls");
}

int main()
{
    // 创建通讯录结构体变量
    AddressBooks Abs;  // 在C++中可以省略struct关键字
    Abs.Size = 0;

    int Select = 0;
    
    while (true)
    {
        ShowMenu();
        cin >> Select;
        switch (Select)
        {
            case 1:     // 添加联系人
                AddPerson(&Abs);
                break;
            case 2:     // 显示联系人
                ShowPerson(&Abs);
                break;
            case 3:     // 删除联系人
                DeletePerson(&Abs);
                break;
            case 4:     // 查找联系人
                FindPerson(&Abs);
                break;
            case 5:     // 修改联系人
                ModifyPerson(&Abs);
                break;
            case 6:     // 清空联系人
                CleanPerson(&Abs);
                break;
            case 0:     // 退出通讯录
                cout << "欢迎下次使用!" << endl;
                system("pause");
                return 0;
                break;
            default:
                break;
        }
    }

    system("pause");
    return 0;
}
