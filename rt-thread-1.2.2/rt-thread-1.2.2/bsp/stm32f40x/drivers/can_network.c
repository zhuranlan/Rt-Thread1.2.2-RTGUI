#include <rtthread.h>
#include <stm32f4xx.h>

/* CAN1的引脚，时钟定义 */
#define CANx                       CAN1
#define CAN_CLK                    RCC_APB1Periph_CAN1
#define CAN_RX_PIN                 GPIO_Pin_11
#define CAN_TX_PIN                 GPIO_Pin_12
#define CAN_GPIO_TX_PORT           GPIOA
#define CAN_GPIO_TX_CLK            RCC_AHB1Periph_GPIOA
#define CAN_GPIO_RX_PORT           GPIOA
#define CAN_GPIO_RX_CLK            RCC_AHB1Periph_GPIOA
#define CAN_AF_PORT                GPIO_AF_CAN1
#define CAN_RX_SOURCE              GPIO_PinSource11
#define CAN_TX_SOURCE              GPIO_PinSource12

/* 定义全局变量 */
CanTxMsg g_tCanTxMsg;	/* 用于发送 */
CanRxMsg g_tCanRxMsg;	/* 用于接收 */

/* 仅允许本文件内调用的函数声明 */
static void can_Init(void);
static void can_NVIC_Config(void);
static void SendCanMsg(void);

/*
*********************************************************************************************************
*	函 数 名: can
*	功能说明: CAN初始化
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void can_INIT(void)
{	
	
	can_Init();				/* 初始化STM32 CAN硬件 */
	can_NVIC_Config();		/* 配置CAN中断 */

}

/*
*********************************************************************************************************
*	函 数 名: SendCanMsg
*	功能说明: 发送一包数据
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
static void SendCanMsg(void)
{
    CAN_Transmit(CAN1, &g_tCanTxMsg);	
}

/*
*********************************************************************************************************
*	函 数 名: can_Init
*	功能说明: 配置CAN硬件
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
static void can_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	CAN_InitTypeDef        CAN_InitStructure;
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;

	/* CAN GPIOs 配置*/
	/* 使能GPIO时钟 */
	RCC_AHB1PeriphClockCmd(CAN_GPIO_TX_CLK|CAN_GPIO_RX_CLK, ENABLE);

	/* 引脚映射为CAN功能  */
	GPIO_PinAFConfig(CAN_GPIO_RX_PORT, CAN_RX_SOURCE, CAN_AF_PORT);
	GPIO_PinAFConfig(CAN_GPIO_TX_PORT, CAN_TX_SOURCE, CAN_AF_PORT); 

	/* 配置 CAN RX 和 TX 引脚 */
	GPIO_InitStructure.GPIO_Pin = CAN_RX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(CAN_GPIO_RX_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = CAN_TX_PIN;
	GPIO_Init(CAN_GPIO_TX_PORT, &GPIO_InitStructure);

	/* CAN配置*/  
	/* 使能CAN时钟 */
	RCC_APB1PeriphClockCmd(CAN_CLK, ENABLE);

	/* 复位CAN寄存器 */
	CAN_DeInit(CANx);
	
	/*
		TTCM = time triggered communication mode
		ABOM = automatic bus-off management 
		AWUM = automatic wake-up mode
		NART = no automatic retransmission
		RFLM = receive FIFO locked mode 
		TXFP = transmit FIFO priority		
	*/
	CAN_InitStructure.CAN_TTCM = DISABLE;			/* 禁止时间触发模式（不生成时间戳), T  */
	CAN_InitStructure.CAN_ABOM = DISABLE;			/* 禁止自动总线关闭管理 */
	CAN_InitStructure.CAN_AWUM = DISABLE;			/* 禁止自动唤醒模式 */
	CAN_InitStructure.CAN_NART = DISABLE;			/* 禁止仲裁丢失或出错后的自动重传功能 */
	CAN_InitStructure.CAN_RFLM = DISABLE;			/* 禁止接收FIFO加锁模式 */
	CAN_InitStructure.CAN_TXFP = DISABLE;			/* 禁止传输FIFO优先级 */
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;	/* 设置CAN为正常工作模式 */
	
	/* 
		CAN 波特率 = RCC_APB1Periph_CAN1 / Prescaler / (SJW + BS1 + BS2);
		
		SJW = synchronisation_jump_width 
		BS = bit_segment
		
		本例中，设置CAN波特率为500Kbps		
		CAN 波特率 = 420000000 / 2 / (1 + 12 + 8) / = 1 MBps		
	*/
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
	CAN_InitStructure.CAN_BS1 = CAN_BS1_6tq;
	CAN_InitStructure.CAN_BS2 = CAN_BS2_8tq;
	CAN_InitStructure.CAN_Prescaler = 2;
	CAN_Init(CANx, &CAN_InitStructure);
	
	/* 设置CAN滤波器0 */
	CAN_FilterInitStructure.CAN_FilterNumber = 0;		/* 滤波器序号，0-13，共14个滤波器 */
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;		/* 滤波器模式，设置ID掩码模式 */
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;	/* 32位滤波 */
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;					/* 掩码后ID的高16bit */
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;					/* 掩码后ID的低16bit */
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;				/* ID掩码值高16bit */
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;				/* ID掩码值低16bit */
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FIFO0;		/* 滤波器绑定FIFO 0 */
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;				/* 使能滤波器 */
	CAN_FilterInit(&CAN_FilterInitStructure);

	/* 填充发送参数， 也可以再每次发送的时候填 */
	g_tCanTxMsg.StdId = 0x321;
	g_tCanTxMsg.ExtId = 0x01;
	g_tCanTxMsg.RTR = CAN_RTR_DATA;
	g_tCanTxMsg.IDE = CAN_ID_STD;
	g_tCanTxMsg.DLC = 1;
}     

/*
*********************************************************************************************************
*	函 数 名: can_NVIC_Config
*	功能说明: 配置CAN中断
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/  
static void can_NVIC_Config(void)
{
	NVIC_InitTypeDef  NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	/* CAN FIFO0 消息接收中断使能 */ 
	CAN_ITConfig(CANx, CAN_IT_FMP0, ENABLE);	
}

/*
*********************************************************************************************************
*	函 数 名: can_ISR
*	功能说明: CAN中断服务程序. 这个函数在 stm32f4xx_it.c中被调用
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/ 
void can_ISR(void)
{
	 /* enter interrupt */
   rt_interrupt_enter();
	
	CAN_Receive(CANx, CAN_FIFO0, &g_tCanRxMsg);
	if ((g_tCanRxMsg.StdId == 0x321) && (g_tCanRxMsg.IDE == CAN_ID_STD) && (g_tCanRxMsg.DLC == 1))
	{
		// g_tCanRxMsg.Data[0];	/* 数据缓冲区第1个字节表示LED序号 */

	}
	    /* leave interrupt */
    rt_interrupt_leave();
}

/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/
