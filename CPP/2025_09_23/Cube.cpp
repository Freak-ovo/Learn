#include <iostream>
using namespace std;
class Cube
{
public:
    void SetLength(int L)
    {
        Length = L;
    }
    int GetLeng()
    {
        return Length;
    }
    void SetWright(int W)
    {
        Wright = W;
    }
    int GetWright()
    {
        return Wright;
    }

    void SetHigh(int H)
    {
        High = H;
    }
    int GetHigh()
    {
        return High;
    }

    int CalculateS()
    {
        return 2 * Length * Wright + 2 *Length * High + 2 * Wright * High;
    }
    int CalculateV()
    {
        return Length * Wright * High;
    }

    bool IsSameClass(Cube C)
    {
        if (High == C.GetHigh() && Wright == C.GetLeng() && Length == C.GetWright())
    {
        return true;
    }
    return false;
    }
private:
    int High;
    int Wright;
    int Length;
};

bool IsSame(Cube &C1, Cube &C2)
{
    if (C1.GetHigh() == C2.GetHigh() && C1.GetLeng()== C2.GetLeng() && C1.GetWright() == C2.GetWright())
    {
        return true;
    }
    return false;
}

int main()
{
    Cube C1;
    C1.SetHigh(10);
    C1.SetWright(10);
    C1.SetLength(10);
    cout << "C1 的面积是：" << C1.CalculateS() << endl;
    cout << "C1 的体积是：" << C1.CalculateV() << endl;

    Cube C2;
    C2.SetHigh(10);
    C2.SetWright(10);
    C2.SetLength(10);

    bool Ret = IsSame(C1, C2);
    if (Ret == 1)
    {
        cout << "C1和C2是相等！" << endl;
    }
    else
    {
        cout << "C1和C2是不相等！" << endl;

    }
    
}