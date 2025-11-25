#include <iostream>
using namespace std;
#include "SpeechManager.h"  




// 实现构造函数
SpeechManager::SpeechManager() {
    // 构造函数的具体实现
    // 初始化容器和属性
    this->InitSpeechManager();

    //创建12名选手
    this->CreateSpeaker();
}


// 实现初始化容器和属性
void SpeechManager::InitSpeechManager(){
    // 初始化容器和属性的具体实现
    this->_v1.clear();
    this->_v2.clear();
    this->_v3.clear();
    this->_mapSpeaker.clear();


}

// 实现创建选手函数
void SpeechManager::CreateSpeaker(){
    string NameSeed = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < NameSeed.size(); i++)
    {
        Speaker speaker;
        speaker._Name = "选手";
        speaker._Name += NameSeed[i];
        for (int j = 0; j < 2; j++)
        {
            speaker._Score[j] = 0;
        }
        //创建选手编号 并存放在v1容器中
        this->_v1.push_back(i + 10001);
        //将选手编号 和 具体选手 映射关系 存放在map容器中
        this->_mapSpeaker.insert(make_pair(i + 10001, speaker));
    }
    
}



// 实现显示菜单函数
void SpeechManager::ShowMenu() {
    // 清除乱码，使用正确的输出
    cout << "1. 开始比赛" << endl;
    cout << "2. 查看记录" << endl;
    cout << "3. 清空记录" << endl;
    cout << "0. 退出系统" << endl;
}
void SpeechManager::ExitSystem(){
    cout << "确认退出系统吗？(1: 是, 0: 否)" << endl;
    int confirm = 0;
    cin >> confirm;
    if (confirm == 1) {
        cout << "谢谢使用，再见！" << endl;
        exit(0);
    }
    else {
        cout << "已取消退出系统" << endl;
    }
}

// 实现演讲比赛函数
void SpeechManager::SpeechCompetition(){
    cout << "开始演讲比赛" << endl;
    // 演讲比赛的具体实现
    // 
}

// 实现析构函数
SpeechManager::~SpeechManager() {
    // 析构函数的具体实现
}

// 主函数，程序入口
int main() {
    
    SpeechManager manager;


    //测试创建选手
    for (map<int, Speaker>::iterator it = manager._mapSpeaker.begin(); it != manager._mapSpeaker.end(); it++)
    {
        cout << "编号: " << it->first << " 姓名: " << it->second._Name << endl;
    }
    
    manager.CreateSpeaker();

    int choice = 0;
    manager.ShowMenu();
    cout << "请输入您的选择: ";
    cin >> choice;
    while (true)
    {

        switch (choice)
        {
        case 1:
            cout << "开始比赛" << endl;
            manager.SpeechCompetition();
            break;
        case 2:
            cout << "查看记录" << endl;
            break;
        case 3:
            cout << "清空记录" << endl;
            break;
        case 0:
            cout << "退出系统" << endl;
            manager.ExitSystem();
            break;
        default:
            cout << "无效选择，请重新输入" << endl;
            break;
        }

        return 0;
    }
    

}