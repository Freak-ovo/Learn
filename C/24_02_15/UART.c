/* USART/UART 异步通信配置步骤
 *  1.配置串口工作参数  usart_init
 *  2.串口底层初始化    void HAL_UART_MspInit(UART_HandleTypeDef *huart)
 *  3.开启串口异步接收中断
 *  4.设置中断优先级，使能中断
 *  5.编写中断服务函数
 *  6.串口数据发送
 *  
 * 
 */


//串口初始化函数
// void usart_init(uint32_t baudrate)
// {
//     /*UART 初始化设置*/
//     g_uart1_handle.Instance = USART1;                                       /* USART1 */
//     g_uart1_handle.Init.BaudRate = baudrate;                                  /* 波特率 */
//     g_uart1_handle.Init.WordLength = UART_WORDLENGTH_8B;                      /* 字长为8位数据格式 */
//     g_uart1_handle.Init.StopBits = UART_STOPBITS_1;                           /* 一个停止位 */
//     g_uart1_handle.Init.Parity = UART_PARITY_NONE;                            /* 无奇偶校验位 */
//     g_uart1_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;                      /* 无硬件流控 */
//     g_uart1_handle.Init.Mode = UART_MODE_TX_RX;                               /* 收发模式 */
//     HAL_UART_Init(&g_uart1_handle);                                           /* HAL_UART_Init()会使能UART1 */

//     /* 该函数会开启接收中断：标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量 */
//     /* HAL_UART_Receive_IT(&g_uart1_handle, (uint8_t *)g_rx_buffer, RXBUFFERSIZE);  */
// }
