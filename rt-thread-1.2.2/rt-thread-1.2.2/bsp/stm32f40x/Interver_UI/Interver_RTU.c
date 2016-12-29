#include "Interver_RTU.h"
#include "stm32f4xx_usart.h"
#include <rtgui/rtgui_system.h>
#include <GPIO.h>
#include <rtgui/widgets/notebook.h>
#include "arm_math.h"
extern q15_t store_data[8192];
extern struct rtgui_notebook *the_notebook;
static rt_device_t device, write_device; 
/* �����̵߳Ľ��ջ�����*/ 
rt_uint8_t uart_rx_buffer[15]; 
static char rx_buffer[15]; 
int RTU_STATUS=1;
int Current_RTU_STATUS=0;
extern int send_flag;
int count;
extern int store_data_number;
extern void Digit_update(void);
void AMD_2587_RDELAY(void)
{
	unsigned int us;
	us=2800;
	while(us--);
}
void the_note_book_1(void)
{
{  
	GPIO_OverTurn(LED3_gpio,LED3_pin);
  R485_CMD((rt_uint32_t *)&power_data.ACC_A,0,RS485_READ_CMD,RTU_SLAVE0);
		count=0;
	 while(ACK_getdata==FALSE&&count<10)
		{
			//rt_kprintf("move here point FLASE!\n");
			R485_CMD((rt_uint32_t *)&power_data.ACC_A,0,RS485_READ_CMD,RTU_SLAVE0);
		  rt_thread_delay(2);
			count++;
			RTU_STATUS=0;
		}
	 ACK_getdata=FALSE;
		
R485_CMD((rt_uint32_t *)&power_data.ACC_B,2,RS485_READ_CMD,RTU_SLAVE0);
		count=0;
	 while(ACK_getdata==FALSE&&count<10)
		{
			//rt_kprintf("move here point FLASE!\n");
	R485_CMD((rt_uint32_t *)&power_data.ACC_B,2,RS485_READ_CMD,RTU_SLAVE0);
		  rt_thread_delay(2);
			count++;
			RTU_STATUS=0;
		}
	 ACK_getdata=FALSE;
		
		
R485_CMD((rt_uint32_t *)&power_data.ACC_C,0,RS485_READ_CMD,RTU_SLAVE0);	
		count=0;
	 while(ACK_getdata==FALSE&&count<10)
		{
			//rt_kprintf("move here point FLASE!\n");
			R485_CMD((rt_uint32_t *)&power_data.ACC_C,0,RS485_READ_CMD,RTU_SLAVE0);
		  rt_thread_delay(2);
			count++;
			RTU_STATUS=0;
		}
	 ACK_getdata=FALSE;
	
R485_CMD((rt_uint32_t *)&power_data.ACV_A,0,RS485_READ_CMD,RTU_SLAVE0);	
		count=0;
	 while(ACK_getdata==FALSE&&count<10)
		{
			//rt_kprintf("move here point FLASE!\n");
			R485_CMD((rt_uint32_t *)&power_data.ACV_A,0,RS485_READ_CMD,RTU_SLAVE0);
		  rt_thread_delay(2);
			count++;
			RTU_STATUS=0;
		}
	 ACK_getdata=FALSE;
		
   R485_CMD((rt_uint32_t *)&power_data.ACV_B,0,RS485_READ_CMD,RTU_SLAVE0);	
		count=0;
	 while(ACK_getdata==FALSE&&count<10)
		{
			//rt_kprintf("move here point FLASE!\n");
			R485_CMD((rt_uint32_t *)&power_data.ACV_B,0,RS485_READ_CMD,RTU_SLAVE0);
		  rt_thread_delay(2);
			count++;
			RTU_STATUS=0;
		}
	 ACK_getdata=FALSE;
		
R485_CMD((rt_uint32_t *)&power_data.ACV_C,0,RS485_READ_CMD,RTU_SLAVE0);	
	 count=0;
	 while(ACK_getdata==FALSE&&count<10)
		{
			//rt_kprintf("move here point FLASE!\n");
			R485_CMD((rt_uint32_t *)&power_data.ACV_C,0,RS485_READ_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
			RTU_STATUS=0;
		}
	 ACK_getdata=FALSE;
		
  R485_CMD((rt_uint32_t *)&power_data.Modulation_ratio,0,RS485_READ_CMD,RTU_SLAVE0);	
	 count=0;
	 while(ACK_getdata==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.Modulation_ratio,0,RS485_READ_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
			RTU_STATUS=0;
		}
	 ACK_getdata=FALSE;
		
		
R485_CMD((rt_uint32_t *)&power_data.DCV_Z,0,RS485_READ_CMD,RTU_SLAVE0);	
	 count=0;
	 while(ACK_getdata==FALSE&&count<10)
		{
			//rt_kprintf("move here point FLASE!\n");
			R485_CMD((rt_uint32_t *)&power_data.DCV_Z,0,RS485_READ_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
			RTU_STATUS=0;
		}
	  ACK_getdata=FALSE;
		
		
				
    R485_CMD((rt_uint32_t *)&power_data.Temperature,0x01,RS485_READ_CMD,RTU_SLAVE0);	
		count=0;
	  while(ACK_getdata==FALSE&&count<10)
		{
			//rt_kprintf("move here point FLASE!\n");
			R485_CMD((rt_uint32_t *)&power_data.Temperature,0x01,RS485_READ_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
			RTU_STATUS=0;
		}
	  ACK_getdata=FALSE;
		
		
		if(send_flag==1)
		{
	  power_data.SET_DUTY=power_data.SET_DATA;
	  R485_CMD((rt_uint32_t *)&power_data.SET_DUTY,power_data.SET_DUTY,RS485_WRITE_CMD,RTU_SLAVE0);
	  send_flag=0;		
			
			/*Ҫ��ӻ�д������*/
	   while(ACK_GET==FALSE&&count<10)
		{
			//rt_kprintf("move here point FLASE write cmd!\n");
			R485_CMD((rt_uint32_t *)&power_data.SET_DUTY,power_data.SET_DUTY,RS485_WRITE_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
			RTU_STATUS=0;
		}
	  ACK_GET=FALSE;
		}
		/*ˢ���������*/
		if(Current_RTU_STATUS!=RTU_STATUS&&the_notebook!=RT_NULL)
		{
		if(RTU_STATUS==0&&rtgui_notebook_get_current_index(the_notebook)==1)
		  {
			Current_RTU_STATUS=RTU_STATUS;

		  rtgui_notebook_set_current_by_index(the_notebook,
                                        1);	
		  }
		else if(RTU_STATUS==1&&rtgui_notebook_get_current_index(the_notebook)==1)
		  {
		  Current_RTU_STATUS=RTU_STATUS;

	    rtgui_notebook_set_current_by_index(the_notebook,
                                        1);		
		  }
	  }
    RTU_STATUS=1;

	}	
}




void the_note_book_2(void)
{
	extern unsigned int start_getdata_flag,start_loaddata_flag,load_data_count_ch1,load_data_count_ch2,load_data_count_ch3;
	int i;
	unsigned int temp;

	if(start_getdata_flag==1)
	{ 
		/*������Ҫ�����ĵ���*/
		R485_CMD((rt_uint32_t *)&power_data.ch1_data_length,power_data.ch1_data_length,RS485_WRITE_CMD,RTU_SLAVE0);
		count=0;
		while(ACK_GET==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.ch1_data_length,power_data.ch1_data_length,RS485_WRITE_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
			RTU_STATUS=0;
		}
		ACK_GET=FALSE;
		
				R485_CMD((rt_uint32_t *)&power_data.ch2_data_length,power_data.ch2_data_length,RS485_WRITE_CMD,RTU_SLAVE0);
		count=0;
		while(ACK_GET==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.ch2_data_length,power_data.ch2_data_length,RS485_WRITE_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
			RTU_STATUS=0;
		}
		ACK_GET=FALSE;
		
		
		R485_CMD((rt_uint32_t *)&power_data.ch3_data_length,power_data.ch3_data_length,RS485_WRITE_CMD,RTU_SLAVE0);
		count=0;
		while(ACK_GET==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.ch3_data_length,power_data.ch3_data_length,RS485_WRITE_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
			RTU_STATUS=0;
		}
		ACK_GET=FALSE;
		
		/*д�����Ƶ��*/
		R485_CMD((rt_uint32_t *)&power_data.DSP_Sampling_f,power_data.DSP_Sampling_f,RS485_WRITE_CMD,RTU_SLAVE0);
		count=0;
		while(ACK_GET==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.DSP_Sampling_f,power_data.DSP_Sampling_f,RS485_WRITE_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
			RTU_STATUS=0;
		}
		ACK_GET=FALSE;
		
		/*�ȴ�Ƶ�ʽ�ȥ*/
		rt_thread_delay(10);
		
		/*д�����ͨ��������*/
	  power_data.store_data_types=0;
	  power_data.store_data_types=(power_data.store_data_types|(scope_setting.ch1_choice|scope_setting.ch2_choice<<1|scope_setting.ch3_choice<<2))&0x000F;

		power_data.store_data_types=power_data.store_data_types+(scope_setting.ch1_combox<<4);//+(scope_setting.ch1_combox<<8)+(scope_setting.ch1_combox<<12);
		temp=(scope_setting.ch2_combox<<4)<<4;

		power_data.store_data_types=power_data.store_data_types+temp;
		temp=((scope_setting.ch3_combox<<4)<<4)<<4;

		power_data.store_data_types=power_data.store_data_types+temp;
		
		
    R485_CMD((rt_uint32_t *)&power_data.store_data_types,power_data.store_data_types,RS485_WRITE_CMD,RTU_SLAVE0);
	  count=0;
		while(ACK_GET==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.store_data_types,power_data.store_data_types,RS485_WRITE_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
			RTU_STATUS=0;
		}
		ACK_GET=FALSE;

		
		
	  
		start_getdata_flag=0;
		load_data_count_ch1=0;
	}
	else if(start_loaddata_flag==1)
	{
		
		if(scope_setting.ch1_choice==1)
		{
		i=0;
		load_data_count_ch1=0;
		for(i=0;i<power_data.ch1_data_length;i++)
		{
		GPIO_OverTurn(LED3_gpio,LED3_pin);
		R485_CMD(((rt_uint32_t *)&power_data+i),0,Load_data_ch1,RTU_SLAVE0);
		count=0;
		
	  while(ACK_getdata==FALSE&&count<10)
		{
			R485_CMD(((rt_uint32_t *)&power_data+i),0,Load_data_ch1,RTU_SLAVE0);
		  rt_thread_delay(2);
			count++;
			RTU_STATUS=0;
		}
		if(ACK_getdata==TRUE)
		load_data_count_ch1++;
	 ACK_getdata=FALSE;
	}
   }
		
	 
	 		if(scope_setting.ch2_choice==1)
		{
		i=0;
		load_data_count_ch2=0;
		for(i=power_data.ch1_data_length;i<power_data.ch1_data_length+power_data.ch2_data_length;i++)
		{
		GPIO_OverTurn(LED3_gpio,LED3_pin);
		R485_CMD(((rt_uint32_t *)&power_data+i),0,Load_data_ch2,RTU_SLAVE0);
		count=0;
		
	  while(ACK_getdata==FALSE&&count<10)
		{
			R485_CMD(((rt_uint32_t *)&power_data+i),0,Load_data_ch2,RTU_SLAVE0);
		  rt_thread_delay(2);
			count++;
			RTU_STATUS=0;
		}
		if(ACK_getdata==TRUE)
		load_data_count_ch2++;
	 ACK_getdata=FALSE;
	}
}
	
		
		if(scope_setting.ch3_choice==1)
		{
		i=0;
		load_data_count_ch3=0;
		for(i=(power_data.ch1_data_length+power_data.ch2_data_length);i<(power_data.ch1_data_length+power_data.ch2_data_length+power_data.ch3_data_length);i++)
		{
		GPIO_OverTurn(LED3_gpio,LED3_pin);
		R485_CMD(((rt_uint32_t *)&power_data+i),0,Load_data_ch3,RTU_SLAVE0);
		count=0;
		
	  while(ACK_getdata==FALSE&&count<10)
		{
			R485_CMD(((rt_uint32_t *)&power_data+i),0,Load_data_ch3,RTU_SLAVE0);
		  rt_thread_delay(2);
			count++;
			RTU_STATUS=0;
		}
		if(ACK_getdata==TRUE)
		load_data_count_ch3++;
	 ACK_getdata=FALSE;
	}
}
   
		
		start_loaddata_flag=0;
	}
	else
		rt_thread_delay(10);
		
}

void the_note_book_user(void)
{
	 Digit_update();
}
void RTU_CMD_thread_entry(void* parameter) 
{
		/*Ĭ�ϲ�������*/
	power_data.ch1_data_length=2048;
	power_data.ch2_data_length=2048;
	power_data.ch3_data_length=2048;
	power_data.DSP_Sampling_f=2000;
	
  scope_setting.ch1_choice=1;
	
	while(1)
{
if(the_notebook!=RT_NULL)
	{
if(rtgui_notebook_get_current_index(the_notebook)==1)
	  the_note_book_1();
else if(rtgui_notebook_get_current_index(the_notebook)==2)
	  the_note_book_2();
else if(rtgui_notebook_get_current_index(the_notebook)==4)
   the_note_book_user();
else
	  {
		rt_thread_delay(10);
	  }
  }
else
{
		rt_thread_delay(10);
}
}
}


struct power_parameter power_data={0};
/*
*ͨѶЭ�� RTUģʽ
*����λ  ��ַ   ���ܴ���  ���ݵ�ַ��λ ���ݵ�ַ��λ     ��ַCRCУ��0    ��ַCRCУ��1      ���ݸ�λ   ���ݵ�λ  ��ַCRCУ��2     ��ַCRCУ��3     ����ĩ
*0x55    0x01    0x03:��    ADDRH        ADDRL           CRC_0           CRC_1            DATAH     DATAL        CRC_2            CRC_3         0xAA
*                0x06:д
*                0xff:ACK
*
*/

/*����ĳ�������ARM����DSP�ڴ���д����*/
/* aadr:���ڻ�ȡ���ͱ����ĵ�ַ
 * data:����Ҫ�������ݵ���ֵ
 * channel:ѡ���͵�ͨ��
 * ���Ͱ��� ��
 * R485_Write((rt_uint32_t *)&power_data.SET_DUTY,power_data.SET_DUTY,RTU_MASTER);
 * ��ע��ͨ������
*/

void R485_CMD(rt_uint32_t * addr,rt_uint16_t data,rt_uint8_t cmd_function,rt_uint8_t RTU_Addr)
{	
 unsigned char R485[12]={0x55,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xAA};
 int i;
 
  rt_uint8_t  ADDRH;
	rt_uint8_t  ADDRL;
	rt_uint32_t Addr;
	rt_uint8_t DATAH;
	rt_uint8_t DATAL;
	unsigned char CRC_0,CRC_1,CRC_2,CRC_3;
	rt_uint32_t crc;
  rt_uint32_t* a,*b;

		/*Ŀ���ַ���ϱ��ص�ַ����*/
	R485[1]=RTU_Addr|(Local_rtu_addr<<4);
		/*���ù��ܴ���*/
		R485[2]=cmd_function;
	/*��ȡ���ݽṹ���ͷ��ַ*/
	a= (rt_uint32_t*)&power_data;
	/*��ȡĿ�����ݵĵ�ַ*/
	b= addr;

	/*��ȡƫ�Ƶ�ַ*/
	Addr=b-a;
	
	ADDRL=Addr;
	ADDRH=Addr>>8;
	R485[3]=ADDRH;
	R485[4]=ADDRL;
	DATAL=data;
	DATAH=data>>8;
	R485[7]=DATAH;
	R485[8]=DATAL;

	
	crc=CRC_Check_Bit(&R485[0],12);
	CRC_0=crc&0xFF;
	CRC_1=(crc>>8)&0x0000FF;
	CRC_2=((crc>>8)>>8)&0x00FF;
	CRC_3=(((crc>>8)>>8)>>8)&0xFF;
	R485[5]=CRC_0&0XFF;
	R485[6]=CRC_1&0XFF;
	R485[9]=CRC_2&0XFF;
	R485[10]=CRC_3&0XFF;
  RS485_1_DE;		
	rt_device_write(device, 0, 
           &R485, 12); 
					 i=2700;//2700  200MHZ
					 while(i--);

	RS485_1_RE;
	ACK_TARGET=RTU_Addr;
	ACK_TARGET_CMD=cmd_function;
  rt_thread_delay(2);//�ȴ�һ��ʱ�� �����Ȼ��ACKӦ��  ������ʱ�� ��������

}




/*��ȡ����λ�����͹��������� ���н���*/
/* R485:���յ�������
 * length�����ݳ���
 * 
 * ���Ͱ��� ��
 *          
 *����CRCУ��
 * ��ע��ͨ������
*/
void R485_Read(rt_uint8_t R485[64],rt_uint8_t length)
{
	rt_uint16_t  addr,data,ADDRH,ADDRL,DATAH,DATAL;
	rt_uint32_t crc;
  rt_uint8_t CRC_0,CRC_1,CRC_2,CRC_3;
	
	 crc=CRC_Check_Bit(&R485[0],12);
   CRC_0=crc;
   CRC_1=crc>>8;
   CRC_2=(crc>>8)>>8;
   CRC_3=((crc>>8)>>8)>>8;

	/*ֻ���ܷ��͵���RTU�ĵ�ַ*/
   if(CRC_0==R485[5]&&CRC_1==R485[6]&&CRC_2==R485[9]&&CRC_3==R485[10])
		{  
			if ((R485[1]&0x0F)==Local_rtu_addr)
			{
			if(R485[2]==0x06)/*д���ݽ���*/
			  {
					ADDRH=R485[3]<<8;
					ADDRL=R485[4];
					DATAH=R485[7]<<8;
					DATAL=R485[8];
					/*�ó�����*/
					data=DATAH|DATAL;
					/*�����ַ*/
					addr=ADDRH|ADDRL;
					/*���ݸ�ֵ*/
					*((unsigned int*)&power_data+addr)=data;
					if(ACK_TARGET==(R485[1]>>4))//��ӻ���ȡ���� �Է���Ӧ
          ACK_getdata=TRUE;		
          //rt_kprintf("move here point4!\n");					
	      }
				else if(R485[2]==Load_data_ch1)
				{
					ADDRH=R485[3]<<8;
					ADDRL=R485[4];
					DATAH=R485[7]<<8;
					DATAL=R485[8];
					/*�ó�����*/
					data=DATAH|DATAL;
					/*�����ַ*/
					addr=ADDRH|ADDRL;
					/*���ݸ�ֵ*/
					store_data[addr]=data;//����Ӧ�����ݷ���store_data�еȴ�����
					if(ACK_TARGET==(R485[1]>>4))//��ӻ���ȡ���� �Է���Ӧ
          ACK_getdata=TRUE;		
				}
				else if(R485[2]==Load_data_ch2)
				{
					ADDRH=R485[3]<<8;
					ADDRL=R485[4];
					DATAH=R485[7]<<8;
					DATAL=R485[8];
					/*�ó�����*/
					data=DATAH|DATAL;
					/*�����ַ*/
					addr=ADDRH|ADDRL;
					/*���ݸ�ֵ*/
					store_data[addr]=data;//����Ӧ�����ݷ���store_data�еȴ�����
					if(ACK_TARGET==(R485[1]>>4))//��ӻ���ȡ���� �Է���Ӧ
          ACK_getdata=TRUE;		
				}
				else if(R485[2]==Load_data_ch3)
				{
					ADDRH=R485[3]<<8;
					ADDRL=R485[4];
					DATAH=R485[7]<<8;
					DATAL=R485[8];
					/*�ó�����*/
					data=DATAH|DATAL;
					/*�����ַ*/
					addr=ADDRH|ADDRL;
					/*���ݸ�ֵ*/
					store_data[addr]=data;//����Ӧ�����ݷ���store_data�еȴ�����
					if(ACK_TARGET==(R485[1]>>4))//��ӻ���ȡ���� �Է���Ӧ
          ACK_getdata=TRUE;		
				}
			else if((R485[2]==0XFF)&&(ACK_TARGET==(R485[1]>>4)))//������ӻ�����ָ��  �Է���Ӧ
				{
					ACK_GET=TRUE;
					rt_kprintf("move here point3!\n");
				}

		  }
		}
}



/*
*�����嵥
*��usart1ʹ���жϽ���  ����Ϣ�ж���������ݵĽ���
*/

/* UART������Ϣ�ṹ*/ 
struct rx_msg 
{ 
  rt_device_t dev; 
  rt_size_t size; 
}; 
/*���ڽ�����Ϣ����Ϣ�ж�*/ 
static rt_mq_t rx_mq; 

 
/* ���ݵ���ص�����*/ 
static rt_err_t uart_input(rt_device_t dev, rt_size_t size) 
{ 
  struct rx_msg msg; 
  msg.dev = dev; 
  msg.size = size; 
 
  /* ������Ϣ����Ϣ�ж���*/ 
  rt_mq_send(rx_mq, &msg, sizeof(struct rx_msg)); 
 
  return RT_EOK; 
} 


static	int i;
void device_thread_entry(void* parameter) 
{ 
  struct rx_msg msg; 
  rt_err_t result = RT_EOK; 

 
  /* ����ϵͳ�еĴ���1�豸*/ 
  device = rt_device_find("uart1");


  if (device!= RT_NULL) 
  { 
    /* ���ûص����������豸*/ 
    rt_device_set_rx_indicate(device, uart_input); 
    rt_device_open(device, RT_DEVICE_OFLAG_RDWR|RT_DEVICE_FLAG_INT_RX); 
  } 

  /* ����д�豸Ϊuart1�豸 */ 
  write_device = device; 
	

	{
  rt_err_t result;
  static rt_uint8_t rtu_stack[ 1024 ] __attribute__((at(0X10000000+1024*1)));
  static struct rt_thread RTU;
	result = rt_thread_init(&RTU,
		                    "RTU_CMD",
		                    RTU_CMD_thread_entry, 
							RT_NULL,
		                    &rtu_stack[0],
							sizeof(rtu_stack),
							30,
							5
							);

	if (result == RT_EOK)
        rt_thread_startup(&RTU);
  }

  while (1) 
  { 
    /* ����Ϣ�ж��ж�ȡ��Ϣ*/ 
    result = rt_mq_recv(rx_mq, &msg,  
      sizeof(struct rx_msg),1); 

    /* �ɹ��յ���Ϣ*/ 
    if (result == RT_EOK) 
  { 
     rt_uint32_t rx_length; 
   rx_length = (sizeof(uart_rx_buffer) - 1) > 
      msg.size ? msg.size : sizeof(uart_rx_buffer) - 1; 
     /* ��ȡ��Ϣ*/ 
     rx_length = rt_device_read(msg.dev, 0, 
      &uart_rx_buffer[0], rx_length); 
     uart_rx_buffer[rx_length] = '\0'; 
 
      /* ��DSP�������ݽ��д���*/ 
     if (write_device != RT_NULL)
			 {
				 {

						 rx_buffer[i]=uart_rx_buffer[0]; 
					 if(rx_buffer[0]==0x55)
						 {
						 i++;
			        if(i==12)
			        {
			        R485_Read(&rx_buffer[0],rx_length);
			    	  i=0;
			        }
					  }
		     }
		  }
    } 
  } 
} 
 

static struct rt_messagequeue s_your_mq;//��Ϣ�жӿ��ƿᰮ����
static char s_msg_pool[512];//��Ϣ��
static rt_uint8_t usart_stack[ 1024 ] __attribute__((at(0X10000000+1024*31)));
static struct rt_thread usart;
int uart_application_init(void)
{
	rt_err_t result;
  rt_mq_init(&s_your_mq,"RTU",&s_msg_pool[0],sizeof(struct rx_msg),sizeof(s_msg_pool),RT_IPC_FLAG_FIFO);
  rx_mq =&s_your_mq;//��rx_mq��ָ��s_your_mq

	
	result = rt_thread_init(&usart,
		                    "usart_devt",
		                    device_thread_entry, 
							RT_NULL,
		                    &usart_stack[0],
							sizeof(usart_stack),
							13,
							5
							);

	if (result == RT_EOK)
        rt_thread_startup(&usart);
	
  return 0;

}

char float_text[100];
char * rt_kprintf_float(double data)
{
	unsigned int inter;
	unsigned int f1,f2,f3,f4,f5,f6,f7,f8;
	unsigned char i;
for(i=0;i<100;i++)
	float_text[i]=0;
 if(data>=0)
 {
	inter=(int)data;
	data=10*(data-inter);
	f1=data;
	data=10*(data-f1);
	f2=data;
	data=10*(data-f2);
	f3=data;
	data=10*(data-f3);
	f4=data;
	data=10*(data-f4);
	f5=data;
	data=10*(data-f5);
	f6=data;
	data=10*(data-f6);
	 //rt_sprintf(float_text, "%d.%d%d%d%d%d%d",inter,f1,f2,f3,f4,f5,f6);
	  rt_sprintf(float_text, "%d.%d%d%d",inter,f1,f2,f3);
 }
 else
 {
	 data=-data;
	inter=(int)data;
	data=10*(data-inter);
	f1=data;
	data=10*(data-f1);
	f2=data;
	data=10*(data-f2);
	f3=data;
	data=10*(data-f3);
	f4=data;
	data=10*(data-f4);
	f5=data;
	data=10*(data-f5);
	f6=data;
	data=10*(data-f6);
	 //rt_sprintf(float_text, "-%d.%d%d%d%d%d%d",inter,f1,f2,f3,f4,f5,f6);
	 rt_sprintf(float_text, "-%d.%d%d%d",inter,f1,f2,f3);
 }

  
	return float_text ;
}






