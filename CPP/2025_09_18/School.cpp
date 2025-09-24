#include <iostream>
#include <string>
#include <ctime>
using namespace std;

struct Student
{
    string Sname;
    int age;
    int score;
};

struct Teacher
{
    int Id;
    string Tname;
    int age;
    struct Student Sarray[5];
};

void AllocateSpace(struct Teacher Tarray[], int length)
{
    string NameSeed = "ABCDE";
    for (int i = 0; i < length; i++)
    {
        Tarray[i].Tname = "Teacher_";
        Tarray[i].Tname += NameSeed[i];


        for (int j = 0; j < 5; j++)
        {
            int Radom = rand() % 61 + 40;
            Tarray[i].Sarray[j].Sname = "Student_";
            Tarray[i].Sarray[j].Sname += NameSeed[j];
            Tarray[i].Sarray[j].score = Radom;

        }
        
    }
    
}


void printfInfo(struct Teacher Tarray[], int length)
{
    for (int i = 0; i < length; i++)
    {
        cout << "老师姓名：" << Tarray[i].Tname << endl;
        for (int j = 0; j < 5; j++)
        {
            cout << "\t学生姓名：" << Tarray[i].Sarray[j].Sname 
                 << " 考试分数：" << Tarray[i].Sarray[j].score << endl;
        }
        
    }
    
}
int main()
{
    srand((unsigned int)time(NULL));
    struct Teacher Tarray[3];
    int length = sizeof(Tarray) / sizeof(Tarray[0]);
    AllocateSpace(Tarray, length);

    printfInfo(Tarray, length);

}