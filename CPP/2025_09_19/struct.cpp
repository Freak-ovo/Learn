#include <iostream>
#include <string>
#include <ctime>
using namespace std;

struct Hero
{
    string Name;
    int Age;
    string Sex;
};
void BubbleSort(struct Hero HeroArray[], int Length)
{
    for (int i = 0; i < Length; i++)
    {
        for (int j = 0; j < Length - i - 1; j++)
        {
            if (HeroArray[j].Age > HeroArray[j + 1].Age)
            {
                struct Hero Temp = HeroArray[j];
                HeroArray[j] = HeroArray[j + 1];
                HeroArray[j + 1] = Temp;
            }
            
        }
        
    }
    
}


void PrintfHero(struct Hero HeroArray[], int Length)
{
    cout << "排序后" << endl;
    for (int i = 0; i < Length; i++)
    {
        cout << "姓名：" << HeroArray[i].Name 
             << " 年龄：" << HeroArray[i].Age
             << " 性别：" << HeroArray[i].Sex << endl;

    }
}
int main()
{
    struct Hero HeroArray[5] = {
        {"刘备", 20 , "男"},
        {"张飞", 19 , "男"},
        {"关羽", 21 , "男"},
        {"马超", 22 , "男"},
        {"貂蝉", 18 , "女"},

    };
    int Length = sizeof(HeroArray) / sizeof(HeroArray[0]);

    cout << "排序前" << endl;
    for (int i = 0; i < Length; i++)
    {
        cout << "姓名：" << HeroArray[i].Name 
             << " 年龄：" << HeroArray[i].Age
             << " 性别：" << HeroArray[i].Sex << endl;

    }
    BubbleSort(HeroArray, Length);

    PrintfHero(HeroArray, Length);
    
    
}