#include <iostream>
using namespace std;

#define PI 3.14
class Cricle
{
//访问权限
//公共权限
public:
//属性
    int M_R;

//行为
    double calculate()
    {
        return 2 * PI * M_R;
    }
};
int main()
{
    //创建具体的圆
    Cricle C1;
    C1.M_R = 5;
    cout << "圆的周长: " << C1.calculate() << endl;
}