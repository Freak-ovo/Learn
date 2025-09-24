#include "stm32f10x.h"                  // Device header
#include "Delay.h"

uint8_t Key_Num;
/**
  * 函    数：按键初始化
  * 参    数：无
  * 返 回 值：无
  */
void Key_Init(void)
{
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_4| GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);						
}

/**
  * 函    数：按键获取键码
  * 参    数：无
  * 返 回 值：按下按键的键码值，范围：0~2，返回0代表没有按键按下
  * 注意事项：此函数是阻塞式操作，当按键按住不放时，函数会卡住，直到按键松手
  */
uint8_t Key_GetNum(void)
{
	uint8_t Temp;

	if (Key_Num)
	{
		Temp = Key_Num;
		Key_Num = 0;
		return Temp;
	}
	else
	{
		return 0;
	}
	
}

uint8_t Key_GetState(void)
{
	
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6) == 0)			//读PB1输入寄存器的状态，如果为0，则代表按键1按下
	{
		return 1;
	}
	
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) == 0)			//读PB11输入寄存器的状态，如果为0，则代表按键2按下
	{
		return 2;
	}

	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) == 0)			//读PB11输入寄存器的状态，如果为0，则代表按键2按下
	{
		return 3;
	}
	
	else
	{
		return 0;			//返回键码值，如果没有按键按下，所有if都不成立，则键码为默认值0	
	}
	

}

/**
 * @brief 按键状态扫描与事件检测函数
 * 
 * 本函数通过周期性采样实现按键消抖，并检测按键按下事件（上升沿触发）。
 * 通常由定时器中断（如1ms定时器）周期性调用。
 * 
 * 功能特点：
 * 1. 每20次调用采样一次按键状态（实现软件消抖）
 * 2. 检测按键从无到有的状态变化（上升沿）
 * 3. 检测到按键事件时更新全局变量 KeyNum
 * 
 * 工作流程：
 *  调用次数不足20次 -> 仅计数
 *  调用满20次 -> 采样按键状态 -> 检测状态变化 -> 更新按键值
 * 
 * 全局依赖：
 *  - KeyNum: 全局按键值变量（0表示无按键，非0表示按键编号）
 *  - Key_GetState(): 外部按键状态获取函数
 * 
 * 注意：
 *  1. 需定期调用（推荐1-10ms调用周期）
 *  2. 消抖时间 = 20 × 调用间隔（如1ms调用则消抖20ms）
 *  3. KeyNum 需在主循环中及时处理并清零
 */
void Key_Tick(void)
{
    // 静态局部变量（保持状态）
    static uint8_t Count = 0;          // 采样计数器（用于消抖）
    static uint8_t CurrentState = 0;   // 当前按键状态（0:无按键）
    static uint8_t PreState = 0;       // 前次按键状态（用于状态比较）

    // 增加调用计数
    Count++;
    
    // 达到采样周期（20次调用）
    if (Count >= 20)
    {
        Count = 0;  // 重置计数器
        
        // 状态更新
        PreState = CurrentState;         // 保存前次状态
        CurrentState = Key_GetState();   // 获取当前按键状态
        
        /**
         * 按键事件检测（上升沿触发）：
         * 条件：前次无按键(0) && 当前有按键(非0)
         * 说明：检测到按键按下事件
         */
        if ((CurrentState != 0) && (PreState == 0))
        {
            // 更新全局按键值（使用当前状态而非前次状态）
            Key_Num = CurrentState;  // 保存实际按下的按键编号
        }

    }
}

