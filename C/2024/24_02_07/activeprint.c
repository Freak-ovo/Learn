#include <stdio.h>
#include <string.h>

int main()
{
    char arr[] = "aaaaaaaaaaaaaa";
    char pp[] = "################";

    int left = 0;
    int right = strlen(arr) - 1;

    while (left <= right)
    {  
        pp[left] = arr[left];
        printf("%s\n", pp);
        left++;

    }
    printf("%s\n", pp);
    return 0;
}