#include<stdio.h>
int main(){
    
    char ch = '\0';
    while((ch = getchar()) != EOF){
        if(ch < '\0' || ch > '9')//读取数字
            continue;
        putchar(ch);
    }

    return 0;
}