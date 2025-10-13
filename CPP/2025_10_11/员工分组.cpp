#include <iostream>
#include <map>
#include <vector>
#include <ctime>  // 用于时间种子初始化

using namespace std;

// 定义部门宏（1=策划，2=美术，3=运营）
#define CEHUA 1
#define MEISHU 2
#define YINGYUAN 3

// 员工类：包含姓名和工资
class Worker {
public:
    string _name;
    int _Salary;

    // 带参构造
    Worker(string name, int Salary) : _name(name), _Salary(Salary) {}
    // 默认构造
    Worker() {}
};

// 1. 创建10名员工（姓名+随机工资）
void CreateWorker(vector<Worker>& vWorker) {
    string NameSeed = "ABCDEFGHIJ";  // 姓名后缀
    for (int i = 0; i < 10; i++) {
        Worker worker;
        worker._name = "员工" ;
        worker._name += NameSeed[i];  // 生成“员工A~员工J”
        worker._Salary = rand() % 10000 + 10000;  // 工资范围：10000~19999
        vWorker.push_back(worker);
    }

    // 打印所有员工信息
    cout << "所有员工信息：" << endl;
    for (const auto& worker : vWorker) {
        cout << "姓名：" << worker._name << "  工资：" << worker._Salary << endl;
    }
    cout << endl;
}

// 2. 随机分组：将员工分配到3个部门（1~3）
void setGroup(vector<Worker>& vWorker, multimap<int, Worker>& mmWorker) {
    for (const auto& worker : vWorker) {
        int group = rand() % 3 + 1;  // 随机生成1、2、3（对应3个部门）
        mmWorker.insert(make_pair(group, worker));  // 部门编号为key，员工为value
    }
}

// 3. 按部门打印员工（策划、美术、运营）
void showGroup(multimap<int, Worker>& mmWorker) {
    // -------- 策划部门 --------
    cout << "策划部门（部门编号：" << CEHUA << "）员工：" << endl;
    int cehuaCount = mmWorker.count(CEHUA);  // 策划部门员工数量
    auto pos = mmWorker.find(CEHUA);         // 找到策划部门的起始迭代器
    int index = 0;
    while (pos != mmWorker.end() && index < cehuaCount) {
        cout << "姓名：" << pos->second._name << "  工资：" << pos->second._Salary << endl;
        pos++;
        index++;
    }

    // -------- 美术部门 --------
    cout << "\n美术部门（部门编号：" << MEISHU << "）员工：" << endl;
    int meishuCount = mmWorker.count(MEISHU);
    pos = mmWorker.find(MEISHU);
    index = 0;
    while (pos != mmWorker.end() && index < meishuCount) {
        cout << "姓名：" << pos->second._name << "  工资：" << pos->second._Salary << endl;
        pos++;
        index++;
    }

    // -------- 运营部门 --------
    cout << "\n运营部门（部门编号：" << YINGYUAN << "）员工：" << endl;
    int yingyuanCount = mmWorker.count(YINGYUAN);
    pos = mmWorker.find(YINGYUAN);
    index = 0;
    while (pos != mmWorker.end() && index < yingyuanCount) {
        cout << "姓名：" << pos->second._name << "  工资：" << pos->second._Salary << endl;
        pos++;
        index++;
    }
}

int main() {
    srand((unsigned int)time(NULL));  // 初始化随机数种子（确保每次分组不同）

    vector<Worker> vWorker;            // 存储所有员工的容器
    multimap<int, Worker> mmWorker;    // 按“部门编号→员工”映射的容器（支持同部门多员工）

    CreateWorker(vWorker);   // 创建10名员工
    setGroup(vWorker, mmWorker); // 随机分组
    showGroup(mmWorker);    // 按部门打印员工

    return 0;
}