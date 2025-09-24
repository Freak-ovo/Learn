#include <iostream>
#include <string>
using namespace std;

struct Student
{
    string name;
    int age;
    int score;
};

struct Teacher
{
    int id;
    string name;
    int age;
    struct Student Stu;
};


void PrintStudent(struct Student No1)
{
    cout << "函数打印结构体" << endl;
    cout << " 姓名: " << No1.name
         << " 年龄: " << No1.age
         << " 得分: " << No1.score << endl;
}

void PrintStudent_Point(struct Student *No1)
{
    cout << "函数打印指针结构体" << endl;
    cout << " 姓名: " << No1->name
         << " 年龄: " << No1->age
         << " 得分: " << No1->score << endl;
}

int main()
{
    struct Student No1;
    No1.name = "李明";
    No1.age = 18;
    No1.score = 150;

    struct Student No2 = {"张三", 19, 140};

    struct Student StuArray[3] = {
        {"王二", 20, 145},
        {"小黑", 19, 139},
        {"赵四", 19, 139},
    };

    StuArray[2].score = 145;

    for (int i = 0; i < 3; i++)
    {
        cout << " 姓名: " << StuArray[i].name
             << " 年龄: " << StuArray[i].age
             << " 得分: " << StuArray[i].score << endl;
    }

    Student *p = &No1;
    cout << " 姓名: " << p->name
         << " 年龄: " << p->age
         << " 得分: " << p->score << endl;

    Teacher T1;
    T1.id = 001;
    T1.name = "jobs";
    T1.age = 45;
    T1.Stu.name = "cook";
    T1.Stu.age = 38;
    T1.Stu.score = 100;

    cout << " 导师姓名: " << T1.name
         << " 导师编号: " << T1.id
         << " 导师年龄: " << T1.age << endl
         << " 导师学生姓名: " << T1.Stu.name
         << " 导师学生年龄: " << T1.Stu.age
         << " 导师学生得分: " << T1.Stu.score << endl;

    PrintStudent(No1);
    PrintStudent_Point(&No2);
}