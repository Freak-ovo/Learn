#include <stdio.h>
#include <math.h>

// 计算波导尺寸
void calculate_waveguide_size(double freq_low, double freq_high, double gain_requirement) {
    double lambda_low = 3e8 / freq_high; // 最低频率对应的波长
    double lambda_high = 3e8 / freq_low; // 最高频率对应的波长
    double width = lambda_low / 2; // 波导宽度为波长的一半
    double height = lambda_high / 2; // 波导高度为波长的一半

    printf("波导宽度: %f mm\n", width*100);
    printf("波导高度: %f mm\n", height*100);
}

int main() {
    double freq_low = 130e9; // 下限频率，单位：Hz
    double freq_high = 170e9; // 上限频率，单位：Hz
    double gain_requirement = 23; // 增益要求，单位：dB

    calculate_waveguide_size(freq_low, freq_high, gain_requirement);

    return 0;
}
