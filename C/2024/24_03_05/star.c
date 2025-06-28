#include <stdio.h>
int main ()
{

    int len = 0;
    scanf("%d", &len);

    for (int i = 0; i < len; i++)
    {

        for (int j = 0; j < len - 1 - i; j++)
        {
            printf(" ");
        }

        for (int j = 0; j < 2 * i + 1; j++)
        {
            printf("*");
        }

    printf("\n");

    }


    for (int i = len - 2; i >= 0; i--)
    {
        for (int j = 0; j < len - 1 - i; j++)
        {
            printf(" ");
        }

        for (int j = 0; j < 2 * i + 1; j++)
        {
            printf("*");
        }       
        printf("\n");    
    }


    return 0;
}