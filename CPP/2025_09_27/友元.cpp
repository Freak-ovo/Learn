#include <iostream>
using namespace std;

//建筑物
class Building
{
    //GoodGay 全局函数是Building好朋友 可以访问Building中私有成员
    friend void GoodGay(Building &Building);
    friend class GoodGay;
private:
    string BedRoom;
public:
    string SittingRoom;



    Building();
/*     {
        SittingRoom = "客厅";
        BedRoom = " 卧室";
    } */

};

class GoodGay
{

public:
    void visit();
    GoodGay();
    Building *building;//参观函数 访问Building 中的属性
};


//全局函数
/* void GoodGay(Building &Building)
{
    cout << "好基友全局函数 真正访问：" << Building.SittingRoom << endl;

    cout << "好基友全局函数 真正访问：" << Building.BedRoom << endl;

} */



//类外写成员函数
Building :: Building()
{
    SittingRoom = "客厅";
    BedRoom = "卧室";
}

GoodGay :: GoodGay()
{
    //创建建筑物对象
    building = new Building;
}
void GoodGay::visit()
{
    cout << "好基友类真正访问：" << building->SittingRoom << endl;

    cout << "好基友全局函数 真正访问：" << building->BedRoom << endl;

}

void Test()
{
   GoodGay gg;
   gg.visit();
    
}

int main()
{
    Test();
}