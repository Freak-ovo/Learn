#include <stdio.h>
int IsLeapYear(int year); // 函数声明

int main()
{
    int year = 0;
    for (year = 2020; year <= 2050; year++)
    {
        if (IsLeapYear(year))
        {
            printf("%d ", year);
        }
    }

    return 0;
}

int IsLeapYear(int year)
{
    if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}