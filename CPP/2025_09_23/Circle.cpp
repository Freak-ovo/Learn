#include "Circle.h"
#include "Point.h"
void Circle::SetR(int r)
{
    R = r;
}

int Circle::GetR()
{
    return R;
}

void Circle::SetCenter(Point center)
{
    Center = center;
}
Point Circle::GetCenter()
{
    return Center;
}

