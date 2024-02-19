#include <stdio.h>

int main()
{
    int n = 0;
    printf("enter array size:");
    scanf("%d", &n);
    int arr[n];

    printf("enter array ment:");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    printf("arry:");
    for (int j = 0; j < n; j++)
    {
        printf("%d ", arr[j]);
    }
    return 0;
}
