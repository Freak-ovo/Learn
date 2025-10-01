#include <iostream>
using namespace std;

// 抽象不同的零件类

// 抽象CPU类 - 定义CPU的接口
class CPU
{
public:
    // 纯虚函数，计算功能
    virtual void Calculate() = 0;
};

// 抽象显卡类 - 定义显卡的接口
class VideoCard
{
public:
    // 纯虚函数，显示功能
    virtual void Dispaly() = 0;  // 注意：原代码此处有拼写错误，应为Display
};

// 抽象内存类 - 定义内存的接口
class Memory
{
public:
    // 纯虚函数，存储功能
    virtual void Storage() = 0;
};

// 电脑类 - 组合CPU、显卡和内存
class Computer
{
public:
    // 构造函数，接收三个零件的指针
    Computer(CPU *cpu, VideoCard *vc, Memory *men)
    {
        Cpu = cpu;
        Vc = vc;
        Men = men;
    }
    
    // 电脑工作函数，调用各零件的功能
    void Work()
    {
        // 让各模块工作，调用对应的接口
        Cpu->Calculate();  // CPU进行计算
        Vc->Dispaly();     // 显卡进行显示
        Men->Storage();    // 内存进行存储
    }
    // 析构函数，释放所有零件资源
    ~Computer()
    {
        // 释放CPU资源
        if (Cpu != NULL)
        {
            delete Cpu;
            Cpu = NULL;  // 避免野指针
        }
        
        // 释放显卡资源
        if (Vc != NULL)
        {
            delete Vc;
            Vc = NULL;  // 避免野指针
        }
        
        // 释放内存资源
        if (Men != NULL)
        {
            delete Men;
            Men = NULL;  // 避免野指针
        }
    }
    
private:
    CPU *Cpu;         // CPU指针
    VideoCard *Vc;    // 显卡指针
    Memory *Men;      // 内存指针
};

// Intel厂商的零件实现

// Intel CPU - 继承自CPU基类
class IntelCPU : public CPU
{
public:
    // 实现计算功能
    virtual void Calculate()
    {
        cout << "Intel的CPU开始工作" << endl;
    }
};

// Intel显卡 - 继承自VideoCard基类（原代码错误地继承了CPU）
class IntelVideoCard : public VideoCard
{
public:
    // 实现显示功能
    virtual void Dispaly()
    {
        cout << "Intel的VideoCard开始工作" << endl;
    }
};

// Intel内存 - 继承自Memory基类
class IntelMemory : public Memory
{
public:
    // 实现存储功能
    virtual void Storage()
    {
        cout << "Intel的Memory开始工作" << endl;
    }
};
// AMD CPU - 继承自CPU基类
class AMDCPU : public CPU
{
public:
    // 实现计算功能
    virtual void Calculate()
    {
        cout << "AMD的CPU开始工作" << endl;
    }
};
// Nvidia显卡 - 继承自VideoCard基类
class NvidiaVideoCard : public VideoCard
{
public:
    // 实现显示功能
    virtual void Dispaly()
    {
        cout << "Nvidia的VideoCard开始工作" << endl;
    }
};

// Samsung内存 - 继承自Memory基类
class SamsungMemory : public Memory
{
public:
    // 实现存储功能
    virtual void Storage()
    {
        cout << "Samsung的Memory开始工作" << endl;
    }
};



// 测试函数
void Test()
{
    // 第一台电脑的零件
    CPU *intelCpu = new IntelCPU;               // 创建Intel CPU
    VideoCard *intelVideoCard = new IntelVideoCard;  // 创建Intel显卡
    Memory *intelMemory = new IntelMemory;      // 创建Intel内存
    
    // 创建第一台电脑
    cout << "第一台电脑" << endl;
    Computer *mark = new Computer(intelCpu, intelVideoCard, intelMemory);
    mark->Work();  // 让电脑工作

    // 第二台电脑的零件
    CPU *amdCPU = new AMDCPU;               // 创建Intel CPU
    VideoCard *nvidiaVideoCard = new NvidiaVideoCard;  // 创建Intel显卡
    Memory *samsungMemory = new SamsungMemory;      // 创建Intel内存
    
    // 创建第二台电脑
    cout << "第二台电脑" << endl;
    Computer *Lenovo = new Computer(amdCPU, nvidiaVideoCard, samsungMemory);
    Lenovo->Work();  // 让电脑工作
    // 创建第三台电脑
    cout << "第三台电脑" << endl;
    Computer *Legion = new Computer(new IntelCPU, nvidiaVideoCard, samsungMemory);
    Legion->Work();  // 让电脑工作
    
    // 释放资源
    delete mark;
    delete Lenovo;
    delete Legion;

}

int main()
{
    Test();  // 执行测试
    return 0;  // 标准主函数返回值
}