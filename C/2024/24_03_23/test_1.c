#include <stdio.h>
#include <math.h>

// 计算圆形喇叭天线尺寸
void calculate_horn_antenna_size(double freq_low, double freq_high, double gain_requirement) {
    double c = 3e8; // 光速，单位：m/s
    double lambda_low = c / freq_high; // 最低频率对应的波长
    double lambda_high = c / freq_low; // 最高频率对应的波长
    double aperture_diameter = 2 * lambda_low; // 口径为波长的两倍
    double length = (lambda_high - lambda_low) / 2; // 长度为频率范围波长差的一半

    printf("喇叭口径 (D): %f m\n", aperture_diameter);
    printf("喇叭长度 (L): %f m\n", length);
}

int main() {
    double freq_low = 130e9; // 下限频率，单位：Hz
    double freq_high = 170e9; // 上限频率，单位：Hz
    double gain_requirement = 23; // 增益要求，单位：dBi

    calculate_horn_antenna_size(freq_low, freq_high, gain_requirement);

    return 0;
}
