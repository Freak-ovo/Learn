#pragma once
#include <iostream>
#include "Point.h"
using namespace std;

class Circle
{
public:


    void SetR(int r);


    int GetR();

    void SetCenter(Point center);

    Point GetCenter();

private:
    int R;
    Point Center;
};