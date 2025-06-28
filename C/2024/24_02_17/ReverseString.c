

#include<stdio.h>
#include<string.h>
// 交换2个大小相等的数组
/* ************************************************

int main()
{

    int arr1[] = {1, 3, 5, 7, 9};
    int arr2[] = {2, 4, 6, 8, 0};

    int sz = sizeof(arr1) / sizeof(arr1[0]);

    for (int i = 0; i < sz; i++)
    {
        int temp = arr1[i];
        arr1[i] = arr2[i];
        arr2[i] = temp;
    }
    
    for (int i =0; i < sz; i++)
    {
        printf("%d ", arr1[i]);
    }

    printf("\n");

    for (int i =0; i < sz; i++)
    {
        printf("%d ", arr2[i]);
    }

    return 0;
} 
******************************************************/
/*
将数组元素逆序

int main()
{
    char arr[] = "abcdef";
    int sz = sizeof(arr) / sizeof(arr[0]);

    int left = 0, right = sz -2;
    int right = strlen(arr) - 1;
    while (left < right)
    {
        char temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;
        left++;
        right--;
    }
    printf("%s\n", arr);
    return 0;
}


 */

/* 函数实现
char ReverseString(char *string)
{
    int left = 0;
    int right = strlen(string) - 1;
    while (left < right)
    {
        char temp = string[left];
        string[left] = string[right];
        string[right] = temp;
        left++;
        right--;
    }
} */

/* 获取字符串长度 */
int ArrayStrlen(char *str)
{
    int count = 0;
    while (*str != '\0')
    {
        count++;
        str++;
    }
    return count;
}


/* 递归实现 */
char ReverseString(char *string)
{
    char temp = *string;//1。将数组首元素存放到temp
    int len = ArrayStrlen(string);//获取数组长度
    *string = *(string + len -1);//2.将数组最后一位元素 放置到第一位
    *(string + len -1) = '\0';//3.将数组最后一位元素替换为\0 （结束符）
    if (ArrayStrlen(string + 1) >= 2)//判断数组剩余元素是否大于2个 大于二交换
    {
        ReverseString(string + 1);//递归调用
    }
    *(string + len -1) = temp;//将数组最后一位替换temp中的第一位元素
}

int main()
{
    char arr[] = "abcdef";
    ReverseString(arr);
    printf("%s\n", arr);
}