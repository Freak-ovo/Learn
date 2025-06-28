#include <stdio.h>
#include <math.h>
double waveguide_width(char* mode);
// 计算波导宽度和高度
void calculate_waveguide_dimensions(double freq, double epsilon_r, char* mode) {
    double c = 3e8; // 光速，单位：m/s
    double lambda = c / freq; // 波长，单位：m
    double lambda_c = 2 * waveguide_width(mode); // 截止波长，单位：m
    double a = lambda / sqrt(epsilon_r) / (1.651 / 2);
    double b = 0.8255 / 2 / lambda_c;

    printf("波导宽度: %f m\n", a);
    printf("波导高度: %f m\n", b);
}

// 根据模式返回波导宽度
double waveguide_width(char* mode) {
    if (strcmp(mode, "TE") == 0) {
        return 1.71;
    } else if (strcmp(mode, "TM") == 0) {
        return 2.61;
    } else {
        printf("不支持的波导模式\n");
        return 0;
    }
}

int main() {
    double freq = 150e9; // 波导工作频率，单位：Hz
    double epsilon_r = 2.2; // 波导介电常数
    char mode[] = "TE"; // TE或TM模式

    calculate_waveguide_dimensions(freq, epsilon_r, mode);

    return 0;
}
