/*         ʹ��˵��
 *��������������λ������λ���������ݴ��佻���ı��������ļ�
 *���ļ��еĴ���������ýṹ��ķ�ʽ
 *
  * Change Logs:
 * Date           Author       Notes
 * 2015-12-02     Ran     first implementation
 */
#ifndef __POWER_PARAMETER_H__
#define __POWER_PARAMETER_H__
#include "CRC_Check.h"
#include "rtthread.h"
#define Scope_Channel_Color_ch1 RTGUI_RGB(0, 0, 255)
#define Scope_Channel_Color_ch2 RTGUI_RGB(255, 0, 255)
#define Scope_Channel_Color_ch3 RTGUI_RGB(255, 0, 0)
#define MCU_MESSAGE_Color       RTGUI_RGB(34, 139, 34);

#define RS485_READ_CMD 0x03
#define RS485_WRITE_CMD 0x06
#define Load_data_ch1 0xFE
#define Load_data_ch2 0xFD
#define Load_data_ch3 0xFC
/*������RTU��Ԫ��ַ*/
#define RTU_MASTER 0
#define RTU_SLAVE0 1
#define RTU_SLAVE1 2
#define RTU_SLAVE2 3
#define RTU_SLAVE3 4
#define RTU_SLAVE4 5
#define RTU_SLAVE5 6
#define RTU_SLAVE6 7
#define RTU_SLAVE7 8
#define RTU_SLAVE8 9

#define Local_rtu_addr RTU_MASTER



struct power_parameter                       
{                                                   	
 rt_uint32_t ACV_A;                       /*A�ཻ����ѹ*/           
 rt_uint32_t ACV_B;                       /*B�ཻ����ѹ*/           
 rt_uint32_t ACV_C;                       /*C�ཻ����ѹ*/           
 rt_uint32_t ACC_A;                       /*A�ཻ������*/           
 rt_uint32_t ACC_B;                       /*B�ཻ������*/           
 rt_uint32_t ACC_C;                       /*C�ཻ������*/
 rt_uint32_t User_data_ch1;
 rt_uint32_t User_data_ch2;
 rt_uint32_t User_data_ch3;
 rt_uint32_t User_data_ch4;
 rt_uint32_t User_data_ch5;
 rt_uint32_t User_data_ch6;
 rt_uint32_t User_data_ch7;
 rt_uint32_t User_data_ch8;
 rt_uint32_t User_data_ch9;
 rt_uint32_t User_data_ch10;
 rt_uint32_t User_data_ch11;
 rt_uint32_t User_data_setting_1;
 rt_uint32_t User_data_setting_2;
 rt_uint32_t User_data_setting_3;
 rt_uint32_t User_data_setting_4;
 rt_uint32_t User_data_setting_5;
 rt_uint32_t DCV_Z;                       /*ֱ�����ѹ*/
 rt_uint32_t SET_DATA;                    /*��������*/
 rt_uint32_t SET_DUTY;                    /*ռ�ձȲ���*/
 rt_uint32_t Modulation_ratio;            /*�����������*/
 rt_uint32_t Temperature;                 /*������¶�*/
 rt_uint32_t store_data_types;
 rt_uint32_t ch1_data_length;
 rt_uint32_t ch2_data_length;
 rt_uint32_t ch3_data_length;
 rt_uint32_t DSP_Sampling_f;           /*DSP�Ĳ���Ƶ��*/
 rt_uint32_t User_data_n_1A;
 rt_uint32_t User_data_n_1B;
 rt_uint32_t User_data_n_1E;
 rt_uint32_t User_data_n_1F;
 
 rt_uint32_t User_data_n_2A;
 rt_uint32_t User_data_n_2B;
 rt_uint32_t User_data_n_2E;
 rt_uint32_t User_data_n_2F;
 
 rt_uint32_t User_data_n_3A;
 rt_uint32_t User_data_n_3B;
 rt_uint32_t User_data_n_3E;
 rt_uint32_t User_data_n_3F;
 
 rt_uint32_t User_data_n_4A;
 rt_uint32_t User_data_n_4B;
 rt_uint32_t User_data_n_4E;
 rt_uint32_t User_data_n_4F;
 
 rt_uint32_t User_data_n_5A;
 rt_uint32_t User_data_n_5B;
 rt_uint32_t User_data_n_5E;
 rt_uint32_t User_data_n_5F;
 
 rt_uint32_t User_data_n_6A;
 rt_uint32_t User_data_n_6B;
 rt_uint32_t User_data_n_6E;
 rt_uint32_t User_data_n_6F;
};
extern struct power_parameter power_data;



void R485_CMD(rt_uint32_t * addr,rt_uint16_t data,rt_uint8_t cmd_function,rt_uint8_t RTU_Addr);
void R485_Read(rt_uint8_t R485[64],rt_uint8_t length);/*�����ȡ��������*/
int uart_application_init(void);/*�̳߳�ʼ��*/
//void R485_CMD(rt_uint32_t *addr,rt_uint32_t RTU_Addr);/*���ڶ�ȡDSP������*/
 

struct scope
{
	rt_uint32_t ch1_choice;
	rt_uint32_t ch2_choice;
	rt_uint32_t ch3_choice;
	rt_uint32_t ch1_combox;
	rt_uint32_t ch2_combox;
	rt_uint32_t ch3_combox;
	
};



extern struct scope scope_setting;


#endif
