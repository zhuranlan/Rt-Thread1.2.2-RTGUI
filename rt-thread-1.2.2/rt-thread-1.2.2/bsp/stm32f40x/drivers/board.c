/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009 RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      first implementation
 */

#include <rthw.h>
#include <rtthread.h>

#include "stm32f4xx.h"
#include "board.h"

/**
 * @addtogroup STM32
 */

/*@{*/

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures Vector Table base location.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{
#ifdef  VECT_TAB_RAM
	/* Set the Vector Table base location at 0x20000000 */
	NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);
#else  /* VECT_TAB_FLASH  */
	/* Set the Vector Table base location at 0x08000000 */
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
#endif

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	#ifdef RT_USING_LWIP
	 /* 对enc28j60的中断管脚进行配置 */

{
    NVIC_InitTypeDef NVIC_InitStructure;
    /* Enable the EXTI0 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

{
    /* PD6 touch INT */
    {
        GPIO_InitTypeDef GPIO_InitStructure;
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
			
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
        GPIO_Init(GPIOD,&GPIO_InitStructure);
    }
		  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource6);

    /* Configure  EXTI  */
   {
    EXTI_InitTypeDef EXTI_InitStructure;

    /* Configure  EXTI  */
    EXTI_InitStructure.EXTI_Line = EXTI_Line6;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//Falling下降沿 Rising上升

     /* enable */
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;

    EXTI_Init(&EXTI_InitStructure);
    EXTI_ClearITPendingBit(EXTI_Line6);
    }
	}
	 #endif
}

/*******************************************************************************
 * Function Name  : SysTick_Configuration
 * Description    : Configures the SysTick for OS tick.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void  SysTick_Configuration(void)
{
	RCC_ClocksTypeDef  rcc_clocks;
	rt_uint32_t         cnts;

	RCC_GetClocksFreq(&rcc_clocks);

	cnts = (rt_uint32_t)rcc_clocks.HCLK_Frequency / RT_TICK_PER_SECOND;
	cnts = cnts / 8;

	SysTick_Config(cnts);
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
}

/**
 * This is the timer interrupt service routine.
 *
 */
void SysTick_Handler(void)
{
	/* enter interrupt */
	rt_interrupt_enter();

	rt_tick_increase();

	/* leave interrupt */
	rt_interrupt_leave();
}

/**
 * This function will initial STM32 board.
 */
void rt_hw_board_init()
{

	/* NVIC Configuration */
	NVIC_Configuration();

	/* Configure the SysTick */
	SysTick_Configuration();

	rt_hw_usart_init();
#ifdef RT_USING_CONSOLE
	rt_console_set_device(CONSOLE_DEVICE);
#endif
}

/*@}*/
