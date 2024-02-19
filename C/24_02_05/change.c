#include<stdio.h>
int main(){
    
    char arr[] = {73,32,99,97,110,32,100,111,32,105,116,33};
    for(int i = 0;arr[i];i++){
        printf("%c",arr[i]);
    }
    
    return 0;
}
/*  sizeof(arr)/sizeof(arr[0]);//计算数组大小
1.sizeof(arr)计算数组总的大小 单位是字节
2.sizeof(arr[0]) 计算数字元素大小 */