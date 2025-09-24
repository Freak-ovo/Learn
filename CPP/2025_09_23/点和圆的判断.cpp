#include <iostream>
using namespace std;
#include "Circle.h"
#include "Point.h"
/* class Point
{
public:
    void SetX(int x)
    {
        X = x;
    }
    int GetX()
    {
        return X;
    }

    void SetY(int y)
    {
        Y = y;
    }
    int GetY()
    {
        return Y;
    }
private:
    int X;
    int Y;

}; */
/* class Circle
{
public:


    void SetR(int r)
    {
        R = r;
    }

    int GetR()
    {
        return R;
    }

    void SetCenter(Point center)
    {
        Center = center;
    }
    Point GetCenter()
    {
        return Center;
    }

private:
    int R;
    Point Center;
}; */

//判断圆心
void IsInCircle(Circle &C, Point &P)
{
    //计算2点之间的距离²
    int Distance = 
        (C.GetCenter().GetX() - P.GetX()) * (C.GetCenter().GetX() - P.GetX()) +
        (C.GetCenter().GetY() - P.GetY()) * (C.GetCenter().GetY() - P.GetY());
    //R的²
    int R_Distance = C.GetR() * C.GetR();

    if (Distance == R_Distance)
    {
        cout << "点在圆上！" << endl;
    }
    else if(Distance < R_Distance)
    {
        cout << "点在圆内！" << endl;
    }
    else if(Distance > R_Distance)
    {
        cout << "点在圆外！" << endl;
    }
}

int main()
{
    //创建圆
    Circle C;
    C.SetR(10);
    Point Center;
    Center.SetX(10);
    Center.SetY(0);
    C.SetCenter(Center);

    //创建点
    Point P;
    P.SetX(10);
    P.SetY(10);

    //判断关系
    IsInCircle(C, P);
}