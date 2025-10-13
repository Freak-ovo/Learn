#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <ctime>
using namespace std;

class Person
{
public:
    Person(string name, int score) : _Name(name), _Score(score) {}
    string _Name;
    int _Score;
};

void CreatePerson(vector<Person> &v)
{
    for (int i = 0; i < 5; i++)
    {
        string name = "学生";
        int score = 0;
        name += to_string(i);
        v.push_back(Person(name, score));

    }
}
void ScorePerson(vector<Person> &v)
{
    int seed = static_cast<int>(time(0));
    srand(seed);
    for (vector<Person>::iterator it = v.begin(); it != v.end(); it++)
    {
        deque<int> d;
        for (int i = 0; i < 10; i++)
        {
            int score = rand() % 41 + 60; //60-100
            d.push_back(score);
        }
        cout <<"学生: " << it->_Name << " 评委打分: " << endl;
        for (deque<int>::iterator dit = d.begin(); dit != d.end(); dit++)
        {
            cout << *dit << " ";
        }
        cout << endl; 
        //对得分进行排序
        sort(d.begin(), d.end());
        d.pop_front();//去掉最低分
        d.pop_back();//去掉最高分
        //计算平均分
        int total = 0;
        for (deque<int>::iterator dit = d.begin(); dit != d.end(); dit++)
        {
            total += *dit;
        }
        it->_Score = total / static_cast<int>(d.size());

    }
 
}
void SortPerson(vector<Person> &v)
{

    sort(v.begin(), v.end(), [](const Person &p1, const Person &p2) {
        return p1._Score > p2._Score;
    });
    //计算平均分
    int total = 0;  
    for (vector<Person>::iterator it = v.begin(); it != v.end(); it++)
    {
        total += it->_Score;
        cout << "姓名：" << it->_Name << " 最终得分：" << it->_Score << endl;
    }
    double average = static_cast<double>(total) / v.size();
    cout << "平均分：" << average << endl;  
}

void ShowPerson(vector<Person> &v)
{
    cout << "比赛结果：" << endl;
    for (vector<Person>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << "姓名：" << it->_Name << " 分数：" << it->_Score << endl;
    }
}
int main()
{
    vector<Person> v;
    CreatePerson(v);
    ScorePerson(v);
    SortPerson(v);
    ShowPerson(v);

    


    return 0;
}