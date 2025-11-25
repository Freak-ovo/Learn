#pragma once
#include <iostream>
using namespace std;
#include "speaker.h"
#include <vector>
#include <map>


//设计演讲比赛管理类
class SpeechManager
{
public:
    //构造函数
    SpeechManager();

    //初始化容器和属性
    void InitSpeechManager();

    //ShowMenu 显示菜单
    void ShowMenu();

    //退出功能
    void ExitSystem();

    //演讲比赛
    void SpeechCompetition();

    //创建选手
    void CreateSpeaker();
    //析构函数
    ~SpeechManager();



    //成员属性
    //保存第一轮的演讲者的编号
    vector<int> _v1;


    //第一轮晋级的选手 的编号
    vector<int> _v2;

    //胜出的前三名的编号
    vector<int> _v3;

    //存放编号 和 具体选手 的映射关系
    map<int, Speaker> _mapSpeaker;

    //存放比赛轮数
    int _SpeechRound;
};