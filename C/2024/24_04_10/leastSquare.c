#include <stdio.h>
/*****
 * 
 * 
 * 
 * 
 * 
 * 
 */
// 最小二乘法函数
void leastSquares(int n, double x[], double y[], double *a, double *b) 
{
    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;

    // 计算各种和
    for (int i = 0; i < n; i++) 
    {
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
        sum_x2 += x[i] * x[i];
    }

    // 计算斜率 a 和截距 b
    *a = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x);
    *b = (sum_y - *a * sum_x) / n;
}

int main() 
{
    // 给定的数据点
    double x[] = {1, 2, 3, 4, 5};
    double y[] = {2, 3, 4, 5, 6};

    // 数据点的数量
    int n = sizeof(x) / sizeof(x[0]);

    // 斜率和截距
    double a, b;

    // 计算最小二乘法
    leastSquares(n, x, y, &a, &b);

    // 打印结果
    printf("斜率 a = %lf\n", a);
    printf("截距 b = %lf\n", b);

    return 0;
}
