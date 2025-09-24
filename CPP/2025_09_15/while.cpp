#include <iostream>
using namespace std;

int main(){

    int sum = 0;
    for (int i = 1; i <= 9; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            sum = i * j;
            cout << i << " * "<< j << " = " << sum << " ";
        }
        cout << endl;
    }
}