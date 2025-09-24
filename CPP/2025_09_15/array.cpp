#include <iostream>
using namespace std;

int main(){

    int arr[] = {10, 20, 30, 40, 50};
    int a = 0;
    int Start = 0;
    int end = sizeof(arr) / sizeof(arr[0]) - 1;
    int length = 0;
    cout << arr << endl;
    cout << &arr[0] << endl;
    cout << &arr[1] << endl;

    length = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < 5; i++)
    {
        cout << arr[i];
    }
    cout << endl;
    for (int i = 0; i < 2; i++)
    {
        a = arr[i];
        arr[i] = arr[end - i];
        arr[end - i] = a;
    }
    for (int i = 0; i < 5; i++)
    {
        cout << arr[i];
    }
    

}