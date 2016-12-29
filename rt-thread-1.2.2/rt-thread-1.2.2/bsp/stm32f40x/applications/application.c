/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
  * 2016-04-09     Ran      
 */
 /*Stm32F4_CCMRAM的使用记录 共64K*/
/*************0~1024*4***********************/
/*touch_deriver       512*/
/*watch_dog           512*/
/*rtu                 1024*/
/*system_gui          1024*2*/ //server.c
/*total=4K*/
/*************1024*4~1024*28***********************/
/*analyse_data*/
/*fftOutput_f32    1024*8*/
/*turn_data_temp    8192*2=1024*16*/
/*total=24K*/
/*************1024*28~1024*31***********************/
/*application_gui    1024*3*/
/*total=4K*/
/*************1024*31~1024*32***********************/
/*RTU主机代码        1024*/
/*total=1K*/
/*************1024*32~1024*64***********************/
/*data*/
/*store_data    8192*2=16k*/
/*fftInput_f32  2048*4=8k*/
/*total=24K*/

/*ftpd*  1024*4=4k*/
/*ftp_session */



//USE_STDPERIPH_DRIVER,STM32F4XX,ARM_MATH_CM4, __FPU_PRESENT = 1,__FPU_USED =1,__CC_ARM


/**
 * @addtogroup STM32
 */
/*@{*/


#include "stm32f4xx.h"
#include <board.h>
#include <rtthread.h>
#include  "GPIO.h"
extern __IO uint16_t ADC3ConvertedValue[2];
void Iwatchdog_init(void);
extern void rt_platform_init(void);
void rt_init_thread_entry(void* parameter)
{	
	
	rt_platform_init();
  Iwatchdog_init();
}

void Iwatchdog_Feed(void* parameter)
{
	/*初始化看门狗*/
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//使能写入PR与RLR
  IWDG_SetPrescaler(IWDG_Prescaler_128);  //写入PR预分频
  IWDG_SetReload(1000);  //写入RLR
  IWDG_Enable();//KR写入0xCCCC
	rt_kprintf("Iwatch Dog Init ok ! \n");
	while(1)
	{
	IWDG_ReloadCounter();
  rt_thread_delay(200);
	GPIO_OverTurn(LED4_gpio,LED4_pin);

//	rt_kprintf("DC3ConvertedValue[0] :%d \n",ADC3ConvertedValue[0]);
//	rt_kprintf("DC3ConvertedValue[1] :%d \n",ADC3ConvertedValue[1]);
	}
	
}


int rt_application_init()
{
    rt_thread_t init_thread;

#if (RT_THREAD_PRIORITY_MAX == 32)
    init_thread = rt_thread_create("init",
                                   rt_init_thread_entry, RT_NULL,
                                   2048, 8, 20);
#else
    init_thread = rt_thread_create("init",
                                   rt_init_thread_entry, RT_NULL,
                                   2048, 80, 20);
#endif
	

	    if (init_thread != RT_NULL)
        rt_thread_startup(init_thread);

	
    return 0;
}
static rt_uint8_t watchdog_stack[ 512 ] __attribute__((at(0X10000000+512)));
static struct rt_thread watchdog;
void Iwatchdog_init(void)
{
	rt_err_t result;
	
		result = rt_thread_init(&watchdog,
		                    "watch_dog",
		                    Iwatchdog_Feed, 
							RT_NULL,
		                    &watchdog_stack[0],
							sizeof(watchdog_stack),
							13,
							5
							);

	if (result == RT_EOK)
        rt_thread_startup(&watchdog);
}


/*@}*/
