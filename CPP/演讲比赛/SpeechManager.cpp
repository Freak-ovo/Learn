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
// 抽签
void SpeechManager::DrawSpeaker(){

    cout << "第" << this->_SpeechRound << "轮抽签" << endl;
    cout << "----------------" << endl;
    cout << "抽签结果如下：" << endl;
    // 第一轮比赛 随机抽签
    if (this->_SpeechRound == 1)
    {
        
        random_shuffle(this->_v1.begin(), this->_v1.end());
        for (vector<int>::iterator it = _v1.begin(); it != _v1.end(); it++){
            cout << *it << " ";
            cout << endl;
        }
    }
    // 第二轮比赛 按照上一轮的晋级的顺序抽签
    else {
        random_shuffle(this->_v2.begin(), this->_v2.end());
        for (vector<int>::iterator it = _v2.begin(); it != _v2.end(); it++){
            cout << *it << " ";
            cout << endl;
        }
    
    }
    cout <<"----------------" << endl;

    system("pause");


}


// 比赛
void SpeechManager::SpeechContest(){

    // 比赛
    cout << "第" << this->_SpeechRound << "轮比赛" << endl;
    cout << "----------------" << endl;
    cout << "比赛结果如下：" << endl;

    // 准备容器 存放小组的容器
    multimap<double, int, greater<double>> groupScore;
    // 存放比赛选手的容器
    vector<int> v;
    // 记录人员个数
    int num = 0;
    if (this->_SpeechRound == 1)
    {
        v = this->_v1;
    }
    else {
        v = this->_v2;
    }
    
    // 遍历所有的选手进行比赛
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++){
        cout << "编号: " << *it << " 姓名: " << this->_mapSpeaker[*it]._Name << " 成绩: " << this->_mapSpeaker[*it]._Score[this->_SpeechRound - 1] << endl;
        
        // 评委打分
        deque<double> d;
        // 5个评委打分
        for (int i = 0; i < 5; i++){
            double score = (rand() % 40 + 60);
            d.push_back(score);
        }
        // 排序
        sort(d.begin(), d.end());
        // 去掉最高分和最低分
        d.pop_back();
        d.pop_front();
        // 计算平均分
        double sum = 0;
        sum = accumulate(d.begin(), d.end(), 0.0); // 计算评委打分的总和
        double avg = sum / d.size(); // 计算评委打分的平均分

        // 打印平均分
        cout << "编号: " << *it << " 姓名: " << this->_mapSpeaker[*it]._Name << " 平均分: " << avg << endl;
    
        // 赋值给选手
        this->_mapSpeaker[*it]._Score[this->_SpeechRound - 1] = avg;
    
        // 将打分数据 存放入小组容器中
        groupScore.insert(make_pair(avg, *it));
        num++;
    }
    
    // 根据轮次确定晋级人数
    int advanceCount = 0;
    if (this->_SpeechRound == 1) {
        advanceCount = 5; // 第一轮选出前5名
        cout << "第一轮比赛晋级前5名：" << endl;
    } else {
        advanceCount = 3; // 第二轮选出前3名
        cout << "第二轮比赛晋级前3名（最终获胜者）：" << endl;
    }
    
    // 所有选手评分完成后，再取出相应数量的选手放入晋级容器
    int count = 0;
    for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count < advanceCount; it++, count++){
        if (this->_SpeechRound == 1){
            this->_v2.push_back((*it).second);
            cout << "编号: " << (*it).second << " 姓名: " << this->_mapSpeaker[(*it).second]._Name << " 成绩: " << (*it).first << endl;
        }
        else {
            this->_v3.push_back((*it).second);
            cout << "编号: " << (*it).second << " 姓名: " << this->_mapSpeaker[(*it).second]._Name << " 成绩: " << (*it).first << endl;
        }
    }
    
    cout << "第" << this->_SpeechRound << "轮比赛完毕！" << endl;
    cout << "----------------" << endl;
    system("pause");
}
// 实现开始比赛函数
void SpeechManager::StartSpeechCompetition(){
    cout << "开始演讲比赛" << endl;
    // 开始比赛的具体实现
    // 第一轮比赛
    // 1. 随机抽签
    this->_SpeechRound = 1;
    this->DrawSpeaker();

    // 2. 比赛
    this->SpeechContest();

    // 3. 显示晋级选手
    this->ShowScore();

    // 4. 继续下一轮比赛
    this->_SpeechRound++;

    // 第二轮比赛
    // 1. 随机抽签
    this->DrawSpeaker();
    // 2. 比赛
    this->SpeechContest();
    // 3. 显示最终得分
    this->ShowScore();

    // 4. 存储记录
    this->StoreRecord();
}

// 显示得分
void SpeechManager::ShowScore(){
    cout << "第" << this->_SpeechRound << "轮比赛得分如下：" << endl;
    vector<int> v;
    
    // 根据轮次选择要显示的选手容器
    if (this->_SpeechRound == 1){
        v = this->_v1; // 第一轮显示所有参赛选手
    } else {
        v = this->_v2; // 第二轮显示第一轮晋级的选手
    }
    
    // 显示当前轮次所有选手的得分
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++){
        cout << "编号: " << *it << " 姓名: " << this->_mapSpeaker[*it]._Name << " 成绩: " << this->_mapSpeaker[*it]._Score[this->_SpeechRound - 1] << endl;
    }
    
    // 显示晋级选手
    cout << "----------------" << endl;
    cout << "晋级选手如下：" << endl;
    vector<int> advancedV;
    
    if (this->_SpeechRound == 1){
        advancedV = this->_v2; // 第一轮晋级选手在_v2中
    } else {
        advancedV = this->_v3; // 第二轮晋级（最终胜出）的选手在_v3中
    }
    
    for (vector<int>::iterator it = advancedV.begin(); it != advancedV.end(); it++){
        cout << "编号: " << *it << " 姓名: " << this->_mapSpeaker[*it]._Name << " 成绩: " << this->_mapSpeaker[*it]._Score[this->_SpeechRound - 1] << endl;
    }
    
    cout << "----------------" << endl;
    system("pause");
    system("cls");
    this->ShowMenu();
}

// 存储记录
void SpeechManager::StoreRecord(){
    // 存储记录的具体实现
    cout << "----------------" << endl;
    cout << "正在存储记录..." << endl;

    // TODO: 实现存储记录的功能
    
    // 打开文件，写入记录
    ofstream ofs("speech_records.txt", ios::out | ios::app);
    if (!ofs.is_open()) {
        cout << "文件打开失败，无法存储记录" << endl;
        return;
    }

    // 写入记录

    for (vector<int>::iterator it = this->_v3.begin(); it != this->_v3.end(); it++)
    {
        static int i = 1;
        ofs << "第" << i++ << "名：" << "编号: " << *it << " 姓名: " << this->_mapSpeaker[*it]._Name << " 成绩: " << this->_mapSpeaker[*it]._Score[this->_SpeechRound - 1] << endl;

    }

    // 关闭文件
    ofs.close();
    cout << "记录存储完毕！" << endl;

    cout << "本届比赛完毕，感谢大家的参与！" << endl;
    system("pause");
    system("cls");
    this->ShowMenu();
}
// 读取记录
void SpeechManager::loadRecord() {
    // 读取记录的具体实现
    cout << "----------------" << endl;
    cout << "正在读取记录..." << endl;

    // TODO: 实现读取记录的功能
    
    // 打开文件，读取记录
    ifstream ifs("speech_records.txt", ios::in);
    if (!ifs.is_open()) {
        cout << "文件打开失败，无法读取记录" << endl;
        return;
    }
    else if (ifs.peek() == EOF) {
        cout << "记录文件为空，无记录可读" << endl;
        ifs.close();
        return;
    }
    // 读取记录
    string line;
    while (getline(ifs, line)) {
        // 输出读取的记录
        cout << line << endl;
    }

    // 关闭文件
    ifs.close();
    cout << "记录读取完毕！" << endl;
}

// 清空记录
void SpeechManager::ClearRecord(){
    // 清空记录的具体实现
    cout << "----------------" << endl;
    cout << "确认清空记录吗？(1: 是, 0: 否)" << endl;
    int confirm = 0;
    cin >> confirm;
    if (confirm == 0) {
        cout << "取消清空记录" << endl;
        return;
    }
    else if (confirm == 1){

        cout << "正在清空记录..." << endl;

        ofstream ofs("speech_records.txt", ios::out | ios::trunc);
        if (!ofs.is_open()) {
            cout << "文件打开失败，无法清空记录" << endl;
            return;
        }
        ofs.close();
        cout << "记录清空完毕！" << endl;
    }
    else {
        cout << "无效选择，取消清空记录" << endl;
        
        this->ShowMenu();
    }
    
}
// 实现析构函数
SpeechManager::~SpeechManager() {
    // 析构函数的具体实现

}

// 主函数，程序入口
int main() {
    
    SpeechManager manager;


    //测试创建选手
/*     for (map<int, Speaker>::iterator it = manager._mapSpeaker.begin(); it != manager._mapSpeaker.end(); it++)
    {
        cout << "编号: " << it->first << " 姓名: " << it->second._Name << endl;
    }
     */
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
            manager.StartSpeechCompetition();
            break;
        case 2:
            cout << "查看记录" << endl;
            manager.loadRecord();
            break;
        case 3:
            cout << "清空记录" << endl;
            manager.ClearRecord();
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