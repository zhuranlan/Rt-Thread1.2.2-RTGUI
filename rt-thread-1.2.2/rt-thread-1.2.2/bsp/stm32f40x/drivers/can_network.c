#include <rtthread.h>
#include <stm32f4xx.h>

/* CAN1�����ţ�ʱ�Ӷ��� */
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

/* ����ȫ�ֱ��� */
CanTxMsg g_tCanTxMsg;	/* ���ڷ��� */
CanRxMsg g_tCanRxMsg;	/* ���ڽ��� */

/* �������ļ��ڵ��õĺ������� */
static void can_Init(void);
static void can_NVIC_Config(void);
static void SendCanMsg(void);

/*
*********************************************************************************************************
*	�� �� ��: can
*	����˵��: CAN��ʼ��
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void can_INIT(void)
{	
	
	can_Init();				/* ��ʼ��STM32 CANӲ�� */
	can_NVIC_Config();		/* ����CAN�ж� */

}

/*
*********************************************************************************************************
*	�� �� ��: SendCanMsg
*	����˵��: ����һ������
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void SendCanMsg(void)
{
    CAN_Transmit(CAN1, &g_tCanTxMsg);	
}

/*
*********************************************************************************************************
*	�� �� ��: can_Init
*	����˵��: ����CANӲ��
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void can_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	CAN_InitTypeDef        CAN_InitStructure;
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;

	/* CAN GPIOs ����*/
	/* ʹ��GPIOʱ�� */
	RCC_AHB1PeriphClockCmd(CAN_GPIO_TX_CLK|CAN_GPIO_RX_CLK, ENABLE);

	/* ����ӳ��ΪCAN����  */
	GPIO_PinAFConfig(CAN_GPIO_RX_PORT, CAN_RX_SOURCE, CAN_AF_PORT);
	GPIO_PinAFConfig(CAN_GPIO_TX_PORT, CAN_TX_SOURCE, CAN_AF_PORT); 

	/* ���� CAN RX �� TX ���� */
	GPIO_InitStructure.GPIO_Pin = CAN_RX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(CAN_GPIO_RX_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = CAN_TX_PIN;
	GPIO_Init(CAN_GPIO_TX_PORT, &GPIO_InitStructure);

	/* CAN����*/  
	/* ʹ��CANʱ�� */
	RCC_APB1PeriphClockCmd(CAN_CLK, ENABLE);

	/* ��λCAN�Ĵ��� */
	CAN_DeInit(CANx);
	
	/*
		TTCM = time triggered communication mode
		ABOM = automatic bus-off management 
		AWUM = automatic wake-up mode
		NART = no automatic retransmission
		RFLM = receive FIFO locked mode 
		TXFP = transmit FIFO priority		
	*/
	CAN_InitStructure.CAN_TTCM = DISABLE;			/* ��ֹʱ�䴥��ģʽ��������ʱ���), T  */
	CAN_InitStructure.CAN_ABOM = DISABLE;			/* ��ֹ�Զ����߹رչ��� */
	CAN_InitStructure.CAN_AWUM = DISABLE;			/* ��ֹ�Զ�����ģʽ */
	CAN_InitStructure.CAN_NART = DISABLE;			/* ��ֹ�ٲö�ʧ��������Զ��ش����� */
	CAN_InitStructure.CAN_RFLM = DISABLE;			/* ��ֹ����FIFO����ģʽ */
	CAN_InitStructure.CAN_TXFP = DISABLE;			/* ��ֹ����FIFO���ȼ� */
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;	/* ����CANΪ��������ģʽ */
	
	/* 
		CAN ������ = RCC_APB1Periph_CAN1 / Prescaler / (SJW + BS1 + BS2);
		
		SJW = synchronisation_jump_width 
		BS = bit_segment
		
		�����У�����CAN������Ϊ500Kbps		
		CAN ������ = 420000000 / 2 / (1 + 12 + 8) / = 1 MBps		
	*/
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
	CAN_InitStructure.CAN_BS1 = CAN_BS1_6tq;
	CAN_InitStructure.CAN_BS2 = CAN_BS2_8tq;
	CAN_InitStructure.CAN_Prescaler = 2;
	CAN_Init(CANx, &CAN_InitStructure);
	
	/* ����CAN�˲���0 */
	CAN_FilterInitStructure.CAN_FilterNumber = 0;		/* �˲�����ţ�0-13����14���˲��� */
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;		/* �˲���ģʽ������ID����ģʽ */
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;	/* 32λ�˲� */
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;					/* �����ID�ĸ�16bit */
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;					/* �����ID�ĵ�16bit */
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;				/* ID����ֵ��16bit */
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;				/* ID����ֵ��16bit */
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FIFO0;		/* �˲�����FIFO 0 */
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;				/* ʹ���˲��� */
	CAN_FilterInit(&CAN_FilterInitStructure);

	/* ��䷢�Ͳ����� Ҳ������ÿ�η��͵�ʱ���� */
	g_tCanTxMsg.StdId = 0x321;
	g_tCanTxMsg.ExtId = 0x01;
	g_tCanTxMsg.RTR = CAN_RTR_DATA;
	g_tCanTxMsg.IDE = CAN_ID_STD;
	g_tCanTxMsg.DLC = 1;
}     

/*
*********************************************************************************************************
*	�� �� ��: can_NVIC_Config
*	����˵��: ����CAN�ж�
*	��    �Σ���
*	�� �� ֵ: ��
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
	
	/* CAN FIFO0 ��Ϣ�����ж�ʹ�� */ 
	CAN_ITConfig(CANx, CAN_IT_FMP0, ENABLE);	
}

/*
*********************************************************************************************************
*	�� �� ��: can_ISR
*	����˵��: CAN�жϷ������. ��������� stm32f4xx_it.c�б�����
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/ 
void can_ISR(void)
{
	 /* enter interrupt */
   rt_interrupt_enter();
	
	CAN_Receive(CANx, CAN_FIFO0, &g_tCanRxMsg);
	if ((g_tCanRxMsg.StdId == 0x321) && (g_tCanRxMsg.IDE == CAN_ID_STD) && (g_tCanRxMsg.DLC == 1))
	{
		// g_tCanRxMsg.Data[0];	/* ���ݻ�������1���ֽڱ�ʾLED��� */

	}
	    /* leave interrupt */
    rt_interrupt_leave();
}

/***************************** ���������� www.armfly.com (END OF FILE) *********************************/
