#include "rtthread.h"
#include "stm32f4xx_conf.h"
#define ADC3_DR_ADDRESS     ((uint32_t)0x4001224C)
__IO uint16_t ADC3ConvertedValue[2];
void ADC3_CH12_DMA_Config(void)
{
  ADC_InitTypeDef       ADC_InitStructure;
  ADC_CommonInitTypeDef ADC_CommonInitStructure;
  DMA_InitTypeDef       DMA_InitStructure;
  GPIO_InitTypeDef      GPIO_InitStructure;

  /* Enable ADC3, DMA2 and GPIO clocks ****************************************/
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2 | RCC_AHB1Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);

  /* DMA2 Stream0 channel0 configuration **************************************/
  DMA_InitStructure.DMA_Channel = DMA_Channel_2;  
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC3_DR_ADDRESS;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&ADC3ConvertedValue;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = 2;//这里天上通道转换结果的数目，两路通道就是2，另外需要修改对应的数组大小
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA2_Stream0, &DMA_InitStructure);
  DMA_Cmd(DMA2_Stream0, ENABLE);

  /* Configure ADC3 Channel12 pin as analog input ******************************/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;//这里初始化你所要用到的引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* ADC Common Init **********************************************************/
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
  ADC_CommonInit(&ADC_CommonInitStructure);

  /* ADC3 Init ****************************************************************/
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	
  ADC_InitStructure.ADC_NbrOfConversion = 2;//这里可以修改到你要的通道数目
  ADC_Init(ADC3, &ADC_InitStructure);

  /* ADC3 regular channel12 configuration *************************************/
  ADC_RegularChannelConfig(ADC3, ADC_Channel_0, 1, ADC_SampleTime_3Cycles);//配置通道1，顺序转换的第一个位置
	ADC_RegularChannelConfig(ADC3, ADC_Channel_1, 2, ADC_SampleTime_3Cycles);//配置通道2，顺序转换的第二个位置，下面可以继续添加。注意修改注释处需要修改的数字

 /* Enable DMA request after last transfer (Single-ADC mode) */
  ADC_DMARequestAfterLastTransferCmd(ADC3, ENABLE);

  /* Enable ADC3 DMA */
  ADC_DMACmd(ADC3, ENABLE);

  /* Enable ADC3 */
  ADC_Cmd(ADC3, ENABLE);
}


void TIM3_Int_Init(u16 arr,u16 psc)
{
       TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
       NVIC_InitTypeDef NVIC_InitStructure;
      
       RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
      
       TIM_TimeBaseInitStructure.TIM_Period = arr; 
       TIM_TimeBaseInitStructure.TIM_Prescaler=psc; 
       TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; 
       TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
      
       TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
      
       TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
      
       NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; 
       NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; 
       NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; 
       NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
       NVIC_Init(&NVIC_InitStructure);
 
      TIM_Cmd(TIM3,ENABLE); 
}