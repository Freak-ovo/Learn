#include <stdio.h>

    /* 
     *输入数组长度 
     *输入元素
     *输入删除元素
     *打印被删除的数组元素
     */
int main()
{
    int n = 0;
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    
    int del = 0;
    scanf("%d", &del);
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] != del)
        {
            arr[j] = arr[i];
            j++;
        }
    }
    for (int i = 0; i < j; i++)
    {
        printf("%d ", arr[i]);
    }
    

    return 0;
}