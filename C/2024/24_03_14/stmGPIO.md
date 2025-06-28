## GPIO使用教程
1. GPIO寄存器配置（General-purposeinput/output）
   - 开启时钟	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC,ENABLE);开始RCC时钟
   - 配置端口
    ```
    GPIO_InitTypeDef  GPIO_InitStructure;//结构体变量定义
    GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_x); //选择IO口
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//输出模式
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50M
    ```
   - 初始化端口 GPIO_Init(GPIOA,&GPIO_InitStructure);
   - 
1. 端口配置
    | 模式名称 | 性质 | 特征 | 代码 |
    | :--: | :--: | :--: | :--: |
    | 浮空输入 | 数字输入 | 可读取引脚电平，若引脚悬空，则电平不确定 | GPIO_Mode_IN_FLOATING |
    | 上拉输入 | 数字输入 |可读取引脚电平，内部连接上拉电阻，悬空时默认高电平 | GPIO_Mode_IPU |
    | 下拉输入 | 数字输入 | 可读取引脚电平，内部连接下拉电阻，悬空时默认低电平 |GPIO_Mode_IPD |
    | 模拟输入 | 模拟输入 | GPIO无效，引脚直接接入内部ADC| GPIO_Mode_AIN|
    | 开漏输出 | 数字输出 | 可输出引脚电平，高电平为高阻态，低电平接VSS | GPIO_Mode_Out_OD |
    | 推挽输出 | 数字输出 | 可输出引脚电平，高电平接VDD，低电平接VSS | GPIO_Mode_Out_PP |
    | 复用开漏输出 | 数字输出 | 由片上外设控制，高电平为高阻态，低电平接VSS | GPIO_Mode_AF_OD |
    | 复用推挽输出 | 数字输出 | 由片上外设控制，高电平接VDD，低电平接VSS |GPIO_Mode_AF_PP |









