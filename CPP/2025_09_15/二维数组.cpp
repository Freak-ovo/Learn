#include <iostream>
using namespace std;

int main()
{

    int sum= 0;
    int arr[3][3] = {
        {100, 100, 100},
        {90, 50, 100},
        {60, 70, 80},
    };

    string name[] = {"张三", "李四", "王五"};
    
    for (int i = 0; i < 3; i++)
    {
        sum = 0;
        for (int j = 0; j < 3; j++)
        {
            sum += arr[i][j];      
        }
        cout << name[i] << "的总分是：";
        cout << sum << endl;
    }


}