#include <iostream>
using namespace std;

int main(){

    int arr[] = {4, 2, 8, 0, 5, 7, 1, 3, 9, 12, 14, 13, 10, 11};
    int Star = 0;
    int End = sizeof(arr) / sizeof(arr[0]) - 1;

    for (int i = 0; i <= End; i++)
    {
        cout << arr[i];
        cout << " ";
    }
    cout << endl;
    
    // 冒泡排序
    for (int i = 0; i <= End; i++) { // 外层循环控制轮数
        bool swapped = false; // 优化：检查是否发生交换
        
        for (int j = 0; j <= End - i - 1; j++) { // 内层循环进行相邻元素比较
            if (arr[j] > arr[j + 1]) {
                // 交换元素
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        
        // 如果没有发生交换，说明数组已经有序，提前结束
        if (!swapped) {
            break;
        }
    }
    for (int i = 0; i <= End; i++)
    {
        cout << arr[i];
        cout << " ";

    }
    cout << endl;


}