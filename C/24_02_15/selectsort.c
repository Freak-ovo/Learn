#include <stdio.h>
#define MAX 9


int main()
{
    int num[MAX];
    int len = -1;
    while (scanf("%d", &num[++len]) != EOF);//EOF是一个预定义的宏，表示文件结束符Ctrl+z


    printf("\n");
    for (int i = 0; i < len; i++)
    {
        printf("%d ", num[i]);
    }
    printf("\n");

    for (int i = 0; i < len-1; i++)
    {
        int num_smallest = num[i];//假设数组第i个元素最小
        int location_smallest = i;//数组最小值的位号
        for (int j = i+1; j<len; j++)
        {
            //company num[j] and num_smallest. j=i+1 j是数组元素i的后一位
            if (num[j] < num_smallest)//判断后一位小于前一位 则跟新最小值与位号
            {
                num_smallest = num[j];
                location_smallest = j;
            }
        }
        //swap num_smallest [num]
        if (location_smallest != i)
        {
            int temp = num[i];
            num[i]= num[location_smallest];
            num[location_smallest] = temp;
        }
    for (int k = 0; k < len; k++)
    {
        if (k == i)
        {
            printf("\033[47;31m%d\033[0m ", num[k]);
        }
        else if (k == location_smallest)
        {
            printf("\033[47;34m%d\033[0m ", num[k]);
        }
        else
        {
            printf("%d ", num[k]);
        }
    }
    printf("\n");
    }
    

    printf("\n");
    for (int i = 0; i < len; i++)
    {
        printf("%d ", num[i]);
    }

    return 0;
}
