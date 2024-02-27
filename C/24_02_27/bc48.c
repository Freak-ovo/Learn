#include <stdio.h>

/* 
    字母大小写转换


 */

int main()
{
    char ch = 0;


    while(scanf("%c", &ch) != EOF)
    {

        if (ch >= 'a' && ch <= 'z')
        {
            printf("%c\n", ch - 32);
        }
        else
        {
            printf("%c\n", ch + 32);
        }
        getchar();//处理\n
    }

    return 0;
}