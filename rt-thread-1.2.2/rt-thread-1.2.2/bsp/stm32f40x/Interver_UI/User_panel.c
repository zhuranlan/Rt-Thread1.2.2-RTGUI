#include "view.h"
#include <rtgui/widgets/digtube.h>
#include "Interver_RTU.h"
#include <rtgui/widgets/notebook.h>
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/button.h>
#include <string.h>
#include <GPIO.h>
#include <rtgui/widgets/radiobox.h>
#include <rtgui/widgets/textbox.h>
#define panel_name_user "用户区"
rtgui_radiobox_t *variable;

rtgui_container_t *container_user;
extern int count;
static char label_text[200];
unsigned int data; 
struct rtgui_rect rect;
extern struct rtgui_notebook *the_notebook;
struct rtgui_label *label_user;
static struct rtgui_timer *timer;
unsigned char User_data_name1_flag=0,User_data_name2_flag=0,User_data_name3_flag=0,User_data_name4_flag=0,User_data_name5_flag=0,User_data_name6_flag=0;
 static char *radio_item_v[5] =
{
    "变量一",
    "变量二",
    "变量三",
    "变量四",
    "变量五",
};
unsigned char user_send_data_type=100;
 void GO_TO_USER(void)
 {
	 rtgui_notebook_set_current_by_index(the_notebook,4);
 }
 void  user_channel_1(void)
 {
	   	/*显示通道1的名称*/
	 	 R485_CMD((rt_uint32_t *)&power_data.User_data_n_1A,0,RS485_READ_CMD,RTU_SLAVE0);	
	  count=0;
	  while(ACK_getdata==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.User_data_n_1A,0,RS485_READ_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
		}	 
    ACK_getdata=FALSE;
			
	  R485_CMD((rt_uint32_t *)&power_data.User_data_n_1B,0,RS485_READ_CMD,RTU_SLAVE0);	
	  count=0;
	  while(ACK_getdata==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.User_data_n_1B,0,RS485_READ_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
		}
		if(ACK_getdata==TRUE)
			User_data_name1_flag=1;
    ACK_getdata=FALSE;
		
		
	  R485_CMD((rt_uint32_t *)&power_data.User_data_n_1E,0,RS485_READ_CMD,RTU_SLAVE0);	
	  count=0;
	  while(ACK_getdata==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.User_data_n_1E,0,RS485_READ_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
		}
    ACK_getdata=FALSE;
		
		
	  R485_CMD((rt_uint32_t *)&power_data.User_data_n_1F,0,RS485_READ_CMD,RTU_SLAVE0);	
	  count=0;
	  while(ACK_getdata==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.User_data_n_1F,0,RS485_READ_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
		}
    ACK_getdata=FALSE;
	

   /*获取通道1的数据*/
	  R485_CMD((rt_uint32_t *)&power_data.User_data_ch1,0,RS485_READ_CMD,RTU_SLAVE0);	
	  count=0;
	  while(ACK_getdata==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.User_data_ch1,0,RS485_READ_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
		}
    ACK_getdata=FALSE;
 }
 
 
 
 
 void  user_channel_2(void)
 {
	   	/*显示通道2的名称*/
	 	 R485_CMD((rt_uint32_t *)&power_data.User_data_n_2A,0,RS485_READ_CMD,RTU_SLAVE0);	
	  count=0;
	  while(ACK_getdata==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.User_data_n_2A,0,RS485_READ_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
		}	 
    ACK_getdata=FALSE;
			
	  R485_CMD((rt_uint32_t *)&power_data.User_data_n_2B,0,RS485_READ_CMD,RTU_SLAVE0);	
	  count=0;
	  while(ACK_getdata==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.User_data_n_2B,0,RS485_READ_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
		}

    ACK_getdata=FALSE;
		
		
	  R485_CMD((rt_uint32_t *)&power_data.User_data_n_2E,0,RS485_READ_CMD,RTU_SLAVE0);	
	  count=0;
	  while(ACK_getdata==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.User_data_n_2E,0,RS485_READ_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
		}
    ACK_getdata=FALSE;
		
		
	  R485_CMD((rt_uint32_t *)&power_data.User_data_n_2F,0,RS485_READ_CMD,RTU_SLAVE0);	
	  count=0;
	  while(ACK_getdata==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.User_data_n_2F,0,RS485_READ_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
		}
		if(ACK_getdata==TRUE)
	   User_data_name2_flag=1;
    ACK_getdata=FALSE;
	

   /*获取通道1的数据*/
	  R485_CMD((rt_uint32_t *)&power_data.User_data_ch2,0,RS485_READ_CMD,RTU_SLAVE0);	
	  count=0;
	  while(ACK_getdata==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.User_data_ch2,0,RS485_READ_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
		}
    ACK_getdata=FALSE;
 }
 
 

 
 
 void  user_channel_3(void)
 {
	   	/*显示通道3的名称*/
	 	 R485_CMD((rt_uint32_t *)&power_data.User_data_n_3A,0,RS485_READ_CMD,RTU_SLAVE0);	
	  count=0;
	  while(ACK_getdata==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.User_data_n_3A,0,RS485_READ_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
		}	 
    ACK_getdata=FALSE;
			
	  R485_CMD((rt_uint32_t *)&power_data.User_data_n_3B,0,RS485_READ_CMD,RTU_SLAVE0);	
	  count=0;
	  while(ACK_getdata==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.User_data_n_3B,0,RS485_READ_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
		}

    ACK_getdata=FALSE;
		
		
	  R485_CMD((rt_uint32_t *)&power_data.User_data_n_3E,0,RS485_READ_CMD,RTU_SLAVE0);	
	  count=0;
	  while(ACK_getdata==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.User_data_n_3E,0,RS485_READ_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
		}
    ACK_getdata=FALSE;
		
		
	  R485_CMD((rt_uint32_t *)&power_data.User_data_n_3F,0,RS485_READ_CMD,RTU_SLAVE0);	
	  count=0;
	  while(ACK_getdata==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.User_data_n_3F,0,RS485_READ_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
		}
		if(ACK_getdata==TRUE)
	   User_data_name3_flag=1;
    ACK_getdata=FALSE;
	

   /*获取通道3的数据*/
	  R485_CMD((rt_uint32_t *)&power_data.User_data_ch3,0,RS485_READ_CMD,RTU_SLAVE0);	
	  count=0;
	  while(ACK_getdata==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.User_data_ch3,0,RS485_READ_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
		}
    ACK_getdata=FALSE;
 }
 
 
 void  user_channel_4(void)
 {
	   	/*显示通道4的名称*/
	 	 R485_CMD((rt_uint32_t *)&power_data.User_data_n_4A,0,RS485_READ_CMD,RTU_SLAVE0);	
	  count=0;
	  while(ACK_getdata==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.User_data_n_4A,0,RS485_READ_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
		}	 
    ACK_getdata=FALSE;
			
	  R485_CMD((rt_uint32_t *)&power_data.User_data_n_4B,0,RS485_READ_CMD,RTU_SLAVE0);	
	  count=0;
	  while(ACK_getdata==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.User_data_n_4B,0,RS485_READ_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
		}

    ACK_getdata=FALSE;
		
		
	  R485_CMD((rt_uint32_t *)&power_data.User_data_n_4E,0,RS485_READ_CMD,RTU_SLAVE0);	
	  count=0;
	  while(ACK_getdata==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.User_data_n_4E,0,RS485_READ_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
		}
    ACK_getdata=FALSE;
		
		
	  R485_CMD((rt_uint32_t *)&power_data.User_data_n_4F,0,RS485_READ_CMD,RTU_SLAVE0);	
	  count=0;
	  while(ACK_getdata==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.User_data_n_4F,0,RS485_READ_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
		}
		if(ACK_getdata==TRUE)
	   User_data_name4_flag=1;
    ACK_getdata=FALSE;
	

   /*获取通道1的数据*/
	  R485_CMD((rt_uint32_t *)&power_data.User_data_ch4,0,RS485_READ_CMD,RTU_SLAVE0);	
	  count=0;
	  while(ACK_getdata==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.User_data_ch4,0,RS485_READ_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
		}
    ACK_getdata=FALSE;
 }
 
 
 void  user_channel_5(void)
 {
	   	/*显示通道5的名称*/
	 	 R485_CMD((rt_uint32_t *)&power_data.User_data_n_5A,0,RS485_READ_CMD,RTU_SLAVE0);	
	  count=0;
	  while(ACK_getdata==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.User_data_n_5A,0,RS485_READ_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
		}	 
    ACK_getdata=FALSE;
			
	  R485_CMD((rt_uint32_t *)&power_data.User_data_n_5B,0,RS485_READ_CMD,RTU_SLAVE0);	
	  count=0;
	  while(ACK_getdata==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.User_data_n_5B,0,RS485_READ_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
		}

    ACK_getdata=FALSE;
		
		
	  R485_CMD((rt_uint32_t *)&power_data.User_data_n_5E,0,RS485_READ_CMD,RTU_SLAVE0);	
	  count=0;
	  while(ACK_getdata==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.User_data_n_5E,0,RS485_READ_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
		}
    ACK_getdata=FALSE;
		
		
	  R485_CMD((rt_uint32_t *)&power_data.User_data_n_5F,0,RS485_READ_CMD,RTU_SLAVE0);	
	  count=0;
	  while(ACK_getdata==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.User_data_n_5F,0,RS485_READ_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
		}
		if(ACK_getdata==TRUE)
	   User_data_name5_flag=1;
    ACK_getdata=FALSE;
	

   /*获取通道5的数据*/
	  R485_CMD((rt_uint32_t *)&power_data.User_data_ch5,0,RS485_READ_CMD,RTU_SLAVE0);	
	  count=0;
	  while(ACK_getdata==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.User_data_ch5,0,RS485_READ_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
		}
    ACK_getdata=FALSE;
 }
 
 void  user_channel_6(void)
 {
	   	/*显示通道2的名称*/
	 	 R485_CMD((rt_uint32_t *)&power_data.User_data_n_6A,0,RS485_READ_CMD,RTU_SLAVE0);	
	  count=0;
	  while(ACK_getdata==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.User_data_n_6A,0,RS485_READ_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
		}	 
    ACK_getdata=FALSE;
			
	  R485_CMD((rt_uint32_t *)&power_data.User_data_n_6B,0,RS485_READ_CMD,RTU_SLAVE0);	
	  count=0;
	  while(ACK_getdata==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.User_data_n_6B,0,RS485_READ_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
		}

    ACK_getdata=FALSE;
		
		
	  R485_CMD((rt_uint32_t *)&power_data.User_data_n_6E,0,RS485_READ_CMD,RTU_SLAVE0);	
	  count=0;
	  while(ACK_getdata==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.User_data_n_6E,0,RS485_READ_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
		}
    ACK_getdata=FALSE;
		
		
	  R485_CMD((rt_uint32_t *)&power_data.User_data_n_6F,0,RS485_READ_CMD,RTU_SLAVE0);	
	  count=0;
	  while(ACK_getdata==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.User_data_n_6F,0,RS485_READ_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
		}
		if(ACK_getdata==TRUE)
	   User_data_name6_flag=1;
    ACK_getdata=FALSE;
	

   /*获取通道1的数据*/
	  R485_CMD((rt_uint32_t *)&power_data.User_data_ch6,0,RS485_READ_CMD,RTU_SLAVE0);	
	  count=0;
	  while(ACK_getdata==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.User_data_ch6,0,RS485_READ_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
		}
    ACK_getdata=FALSE;
 }
 
 
 

 
 
void Digit_update(void)
{
	  
	GPIO_OverTurn(LED3_gpio,LED3_pin);
	
  user_channel_1();
	user_channel_2();
	user_channel_3();
	user_channel_4();
	user_channel_5();
	user_channel_6();
	if(user_send_data_type==0)
	{
	 R485_CMD((rt_uint32_t *)&power_data.User_data_ch7,power_data.User_data_ch7,RS485_WRITE_CMD,RTU_SLAVE0);	
	  count=0;
	  while(ACK_GET==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.User_data_ch7,power_data.User_data_ch7,RS485_WRITE_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
		}
    ACK_GET=FALSE;
		user_send_data_type=100;
		
		
		R485_CMD((rt_uint32_t *)&power_data.User_data_setting_1,0,RS485_READ_CMD,RTU_SLAVE0);	
	  count=0;
	  while(ACK_GET==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.User_data_setting_1,0,RS485_READ_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
		}
    ACK_GET=FALSE;
			
	}
	else 	if(user_send_data_type==1)
	{
	 R485_CMD((rt_uint32_t *)&power_data.User_data_ch8,power_data.User_data_ch8,RS485_WRITE_CMD,RTU_SLAVE0);	
	  count=0;
	  while(ACK_GET==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.User_data_ch8,power_data.User_data_ch8,RS485_WRITE_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
		}
    ACK_GET=FALSE;
		user_send_data_type=100;
			
	  R485_CMD((rt_uint32_t *)&power_data.User_data_setting_2,0,RS485_READ_CMD,RTU_SLAVE0);	
	  count=0;
	  while(ACK_GET==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.User_data_setting_2,0,RS485_READ_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
		}
    ACK_GET=FALSE;
		
	
	}
	else 	if(user_send_data_type==2)
	{
	 R485_CMD((rt_uint32_t *)&power_data.User_data_ch9,power_data.User_data_ch9,RS485_WRITE_CMD,RTU_SLAVE0);	
	  count=0;
	  while(ACK_GET==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.User_data_ch9,power_data.User_data_ch9,RS485_WRITE_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
		}
    ACK_GET=FALSE;
		user_send_data_type=100;
		
		
	  R485_CMD((rt_uint32_t *)&power_data.User_data_setting_3,0,RS485_READ_CMD,RTU_SLAVE0);	
	  count=0;
	  while(ACK_GET==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.User_data_setting_3,0,RS485_READ_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
		}
    ACK_GET=FALSE;
	
	}
	
		else 	if(user_send_data_type==3)
	{
	 R485_CMD((rt_uint32_t *)&power_data.User_data_ch10,power_data.User_data_ch10,RS485_WRITE_CMD,RTU_SLAVE0);	
	  count=0;
	  while(ACK_GET==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.User_data_ch10,power_data.User_data_ch10,RS485_WRITE_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
		}
    ACK_GET=FALSE;
		user_send_data_type=100;
		
		
	  R485_CMD((rt_uint32_t *)&power_data.User_data_setting_4,0,RS485_READ_CMD,RTU_SLAVE0);	
	  count=0;
	  while(ACK_GET==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.User_data_setting_4,0,RS485_READ_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
		}
    ACK_GET=FALSE;
	
	}
	
		else 	if(user_send_data_type==4)
	{
	 R485_CMD((rt_uint32_t *)&power_data.User_data_ch11,power_data.User_data_ch11,RS485_WRITE_CMD,RTU_SLAVE0);	
	  count=0;
	  while(ACK_GET==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.User_data_ch11,power_data.User_data_ch11,RS485_WRITE_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
		}
    ACK_GET=FALSE;
		user_send_data_type=100;
		
		
	  R485_CMD((rt_uint32_t *)&power_data.User_data_setting_5,0,RS485_READ_CMD,RTU_SLAVE0);	
	  count=0;
	  while(ACK_GET==FALSE&&count<10)
		{
			R485_CMD((rt_uint32_t *)&power_data.User_data_setting_5,0,RS485_READ_CMD,RTU_SLAVE0);	
		  rt_thread_delay(2);
			count++;
		}
    ACK_GET=FALSE;
	
	}
	
		
}
static void cpuinformation_update(struct rtgui_timer *timer, void *parameter)
{  
	  struct rtgui_textbox* text;
	if(rtgui_notebook_get_current_index(the_notebook)==4)
	{
	
	    /*用户数据通道 1*/
			if(User_data_name1_flag==1)
			{
		  label_user = RTGUI_LABEL(rtgui_get_self_object(USER_DATA_NAME_1));
	    rt_sprintf(label_text, "%c%c%c%c%c%c%c%c",  power_data.User_data_n_1A&0xff,(power_data.User_data_n_1A>>8)&0xff,
	                                                power_data.User_data_n_1B&0xff,(power_data.User_data_n_1B>>8)&0xff,
	                                                power_data.User_data_n_1E&0xff,(power_data.User_data_n_1E>>8)&0xff,
	                                                power_data.User_data_n_1F&0xff,(power_data.User_data_n_1F>>8)&0xff);
			if(label_text!=RT_NULL)
	    rt_sprintf(label_text,"%s:",label_text);
				
      rtgui_label_set_text(label_user, label_text);
      rtgui_widget_update(RTGUI_WIDGET(label_user));
		  }
		else
		{
		label_user = RTGUI_LABEL(rtgui_get_self_object(USER_DATA_NAME_1));
		rt_sprintf(label_text,"RT_NULL:",label_text);
		rtgui_label_set_text(label_user, label_text);
    rtgui_widget_update(RTGUI_WIDGET(label_user));
		}
		
		label_user = RTGUI_LABEL(rtgui_get_self_object(USER_DATA_1));
    rt_sprintf(label_text, "%d", power_data.User_data_ch1);
    rtgui_label_set_text(label_user, label_text);
    rtgui_widget_update(RTGUI_WIDGET(label_user));
	
	
	
		    /*用户数据通道 2*/
			if(User_data_name2_flag==1)
			{
		  label_user = RTGUI_LABEL(rtgui_get_self_object(USER_DATA_NAME_2));
	    rt_sprintf(label_text, "%c%c%c%c%c%c%c%c",  power_data.User_data_n_2A&0xff,(power_data.User_data_n_2A>>8)&0xff,
	                                                power_data.User_data_n_2B&0xff,(power_data.User_data_n_2B>>8)&0xff,
	                                                power_data.User_data_n_2E&0xff,(power_data.User_data_n_2E>>8)&0xff,
	                                                power_data.User_data_n_2F&0xff,(power_data.User_data_n_2F>>8)&0xff);
			if(label_text!=RT_NULL)
	    rt_sprintf(label_text,"%s:",label_text);
				
      rtgui_label_set_text(label_user, label_text);
      rtgui_widget_update(RTGUI_WIDGET(label_user));
		  }
		else
		{
		label_user = RTGUI_LABEL(rtgui_get_self_object(USER_DATA_NAME_2));
		rt_sprintf(label_text,"RT_NULL:",label_text);
		rtgui_label_set_text(label_user, label_text);
    rtgui_widget_update(RTGUI_WIDGET(label_user));
		}
		
		label_user = RTGUI_LABEL(rtgui_get_self_object(USER_DATA_2));
    rt_sprintf(label_text, "%d", power_data.User_data_ch2);
    rtgui_label_set_text(label_user, label_text);
    rtgui_widget_update(RTGUI_WIDGET(label_user));
		
		
		
		
		
		    /*用户数据通道 3*/
			if(User_data_name3_flag==1)
			{
		  label_user = RTGUI_LABEL(rtgui_get_self_object(USER_DATA_NAME_3));
	    rt_sprintf(label_text, "%c%c%c%c%c%c%c%c",  power_data.User_data_n_3A&0xff,(power_data.User_data_n_3A>>8)&0xff,
	                                                power_data.User_data_n_3B&0xff,(power_data.User_data_n_3B>>8)&0xff,
	                                                power_data.User_data_n_3E&0xff,(power_data.User_data_n_3E>>8)&0xff,
	                                                power_data.User_data_n_3F&0xff,(power_data.User_data_n_3F>>8)&0xff);
			if(label_text!=RT_NULL)
	    rt_sprintf(label_text,"%s:",label_text);
				
      rtgui_label_set_text(label_user, label_text);
      rtgui_widget_update(RTGUI_WIDGET(label_user));
		  }
		else
		{
		label_user = RTGUI_LABEL(rtgui_get_self_object(USER_DATA_NAME_3));
		rt_sprintf(label_text,"RT_NULL:",label_text);
		rtgui_label_set_text(label_user, label_text);
    rtgui_widget_update(RTGUI_WIDGET(label_user));
		}
		
		label_user = RTGUI_LABEL(rtgui_get_self_object(USER_DATA_3));
    rt_sprintf(label_text, "%d", power_data.User_data_ch3);
    rtgui_label_set_text(label_user, label_text);
    rtgui_widget_update(RTGUI_WIDGET(label_user));
		
		
		
				    /*用户数据通道 4*/
			if(User_data_name4_flag==1)
			{
		  label_user = RTGUI_LABEL(rtgui_get_self_object(USER_DATA_NAME_4));
	    rt_sprintf(label_text, "%c%c%c%c%c%c%c%c",  power_data.User_data_n_4A&0xff,(power_data.User_data_n_4A>>8)&0xff,
	                                                power_data.User_data_n_4B&0xff,(power_data.User_data_n_4B>>8)&0xff,
	                                                power_data.User_data_n_4E&0xff,(power_data.User_data_n_4E>>8)&0xff,
	                                                power_data.User_data_n_4F&0xff,(power_data.User_data_n_4F>>8)&0xff);
			if(label_text!=RT_NULL)
	    rt_sprintf(label_text,"%s:",label_text);
				
      rtgui_label_set_text(label_user, label_text);
      rtgui_widget_update(RTGUI_WIDGET(label_user));
		  }
		else
		{
		label_user = RTGUI_LABEL(rtgui_get_self_object(USER_DATA_NAME_4));
		rt_sprintf(label_text,"RT_NULL:",label_text);
		rtgui_label_set_text(label_user, label_text);
    rtgui_widget_update(RTGUI_WIDGET(label_user));
		}
		
		label_user = RTGUI_LABEL(rtgui_get_self_object(USER_DATA_4));
    rt_sprintf(label_text, "%d", power_data.User_data_ch4);
    rtgui_label_set_text(label_user, label_text);
    rtgui_widget_update(RTGUI_WIDGET(label_user));
		
		
				    /*用户数据通道 5*/
			if(User_data_name5_flag==1)
			{
		  label_user = RTGUI_LABEL(rtgui_get_self_object(USER_DATA_NAME_5));
	    rt_sprintf(label_text, "%c%c%c%c%c%c%c%c",  power_data.User_data_n_5A&0xff,(power_data.User_data_n_5A>>8)&0xff,
	                                                power_data.User_data_n_5B&0xff,(power_data.User_data_n_5B>>8)&0xff,
	                                                power_data.User_data_n_5E&0xff,(power_data.User_data_n_5E>>8)&0xff,
	                                                power_data.User_data_n_5F&0xff,(power_data.User_data_n_5F>>8)&0xff);
			if(label_text!=RT_NULL)
	    rt_sprintf(label_text,"%s:",label_text);
				
      rtgui_label_set_text(label_user, label_text);
      rtgui_widget_update(RTGUI_WIDGET(label_user));
		  }
		else
		{
		label_user = RTGUI_LABEL(rtgui_get_self_object(USER_DATA_NAME_5));
		rt_sprintf(label_text,"RT_NULL:",label_text);
		rtgui_label_set_text(label_user, label_text);
    rtgui_widget_update(RTGUI_WIDGET(label_user));
		}
		
		label_user = RTGUI_LABEL(rtgui_get_self_object(USER_DATA_5));
    rt_sprintf(label_text, "%d", power_data.User_data_ch5);
    rtgui_label_set_text(label_user, label_text);
    rtgui_widget_update(RTGUI_WIDGET(label_user));
		
		
		
				    /*用户数据通道 6*/
			if(User_data_name6_flag==1)
			{
		  label_user = RTGUI_LABEL(rtgui_get_self_object(USER_DATA_NAME_6));
	    rt_sprintf(label_text, "%c%c%c%c%c%c%c%c",  power_data.User_data_n_6A&0xff,(power_data.User_data_n_6A>>8)&0xff,
	                                                power_data.User_data_n_6B&0xff,(power_data.User_data_n_6B>>8)&0xff,
	                                                power_data.User_data_n_6E&0xff,(power_data.User_data_n_6E>>8)&0xff,
	                                                power_data.User_data_n_6F&0xff,(power_data.User_data_n_6F>>8)&0xff);
			if(label_text!=RT_NULL)
	    rt_sprintf(label_text,"%s:",label_text);
				
      rtgui_label_set_text(label_user, label_text);
      rtgui_widget_update(RTGUI_WIDGET(label_user));
		  }
		else
		{
		label_user = RTGUI_LABEL(rtgui_get_self_object(USER_DATA_NAME_6));
		rt_sprintf(label_text,"RT_NULL:",label_text);
		rtgui_label_set_text(label_user, label_text);
    rtgui_widget_update(RTGUI_WIDGET(label_user));
		}
		
		label_user = RTGUI_LABEL(rtgui_get_self_object(USER_DATA_6));
    rt_sprintf(label_text, "%d", power_data.User_data_ch6);
    rtgui_label_set_text(label_user, label_text);
    rtgui_widget_update(RTGUI_WIDGET(label_user));
		
		
		

		

	  text = RTGUI_TEXTBOX(rtgui_get_self_object(USER_DATA_SETTING_1));
    rt_sprintf(label_text,"%d",power_data.User_data_setting_1);
    rtgui_textbox_set_value(text, label_text);
    rtgui_widget_update(RTGUI_WIDGET(text));
		
		
		text = RTGUI_TEXTBOX(rtgui_get_self_object(USER_DATA_SETTING_2));
    rt_sprintf(label_text,"%d",power_data.User_data_setting_2);
    rtgui_textbox_set_value(text, label_text);
    rtgui_widget_update(RTGUI_WIDGET(text));
		
		
		text = RTGUI_TEXTBOX(rtgui_get_self_object(USER_DATA_SETTING_3));
    rt_sprintf(label_text,"%d",power_data.User_data_setting_3);
    rtgui_textbox_set_value(text, label_text);
    rtgui_widget_update(RTGUI_WIDGET(text));
		
		
		text = RTGUI_TEXTBOX(rtgui_get_self_object(USER_DATA_SETTING_4));
    rt_sprintf(label_text,"%d",power_data.User_data_setting_4);
    rtgui_textbox_set_value(text, label_text);
    rtgui_widget_update(RTGUI_WIDGET(text));
		
		
		
		text = RTGUI_TEXTBOX(rtgui_get_self_object(USER_DATA_SETTING_5));
    rt_sprintf(label_text,"%d",power_data.User_data_setting_5);
    rtgui_textbox_set_value(text, label_text);
    rtgui_widget_update(RTGUI_WIDGET(text));
			
	}
		
}
static void Load_Keyboard_user(rtgui_container_t *win,rt_uint32_t rect_X,rt_uint32_t rect_Y);
rtgui_container_t * User_panel(void)
{	
	  struct rtgui_digitfont digitfont;
	  struct rtgui_textbox* text;
		struct rtgui_label      *label;
	  
	  container_user = view("用户区");
		if (container_user == RT_NULL)
    return RT_NULL;
	
    view_get_rect(container_user, &rect);
    rect.x1 += 5;
    rect.x2 = rect.x1 + 72;
    rect.y1 -= 40;
    rect.y2 = rect.y1 + 20;	 
	  label_user = rtgui_label_create("RT_NULL:");
	  RTGUI_WIDGET_FOREGROUND(label_user) = Scope_Channel_Color_ch3;
    rtgui_widget_set_rect(RTGUI_WIDGET(label_user), &rect);
    rtgui_container_add_child(container_user, RTGUI_WIDGET(label_user));
	  rtgui_object_set_id(RTGUI_OBJECT(label_user), USER_DATA_NAME_1);
		
    rect.x1 += 78;
    rect.x2 = rect.x1 + 52; 
    label_user = rtgui_label_create("65536");
	  RTGUI_WIDGET_FOREGROUND(label_user) = Scope_Channel_Color_ch3;
    rtgui_widget_set_rect(RTGUI_WIDGET(label_user), &rect);
    rtgui_container_add_child(container_user, RTGUI_WIDGET(label_user));
		rtgui_object_set_id(RTGUI_OBJECT(label_user), USER_DATA_1);
			 
    rect.x1 += 60;
    rect.x2 = rect.x1 + 72;
		label_user = rtgui_label_create("RT_NULL:");
		RTGUI_WIDGET_FOREGROUND(label_user) = Scope_Channel_Color_ch3;
    rtgui_widget_set_rect(RTGUI_WIDGET(label_user), &rect);
    rtgui_container_add_child(container_user, RTGUI_WIDGET(label_user));
		rtgui_object_set_id(RTGUI_OBJECT(label_user), USER_DATA_NAME_2);
		
    rect.x1 += 78;
    rect.x2 = rect.x1 + 52;
		label_user = rtgui_label_create("65536");
		RTGUI_WIDGET_FOREGROUND(label_user) = Scope_Channel_Color_ch3;
    rtgui_widget_set_rect(RTGUI_WIDGET(label_user), &rect);
    rtgui_container_add_child(container_user, RTGUI_WIDGET(label_user));
    rtgui_object_set_id(RTGUI_OBJECT(label_user), USER_DATA_2);
			
		view_get_rect(container_user, &rect);
    rect.x1 += 5;
    rect.x2 = rect.x1 + 72;
    rect.y1 =rect.y1-10;
    rect.y2 = rect.y1 + 20;
		label_user = rtgui_label_create("RT_NULL:");
		RTGUI_WIDGET_FOREGROUND(label_user) = Scope_Channel_Color_ch2;
    rtgui_widget_set_rect(RTGUI_WIDGET(label_user), &rect);
    rtgui_container_add_child(container_user, RTGUI_WIDGET(label_user));
		rtgui_object_set_id(RTGUI_OBJECT(label_user), USER_DATA_NAME_3);
				
    rect.x1 += 78;
    rect.x2 = rect.x1 + 52;
		label_user = rtgui_label_create("65536");
		RTGUI_WIDGET_FOREGROUND(label_user) = Scope_Channel_Color_ch2;
    rtgui_widget_set_rect(RTGUI_WIDGET(label_user), &rect);
    rtgui_container_add_child(container_user, RTGUI_WIDGET(label_user));
		rtgui_object_set_id(RTGUI_OBJECT(label_user), USER_DATA_3);
		
    rect.x1 += 60;
    rect.x2 = rect.x1 + 72;
    label_user = rtgui_label_create("RT_NULL:");
		RTGUI_WIDGET_FOREGROUND(label_user) = Scope_Channel_Color_ch2;
    rtgui_widget_set_rect(RTGUI_WIDGET(label_user), &rect);
    rtgui_container_add_child(container_user, RTGUI_WIDGET(label_user));
		rtgui_object_set_id(RTGUI_OBJECT(label_user), USER_DATA_NAME_4);
		
    rect.x1 += 78;
    rect.x2 = rect.x1 + 52;
		label_user = rtgui_label_create("65536");
		RTGUI_WIDGET_FOREGROUND(label_user) = Scope_Channel_Color_ch2;
    rtgui_widget_set_rect(RTGUI_WIDGET(label_user), &rect);
    rtgui_container_add_child(container_user, RTGUI_WIDGET(label_user));
		rtgui_object_set_id(RTGUI_OBJECT(label_user), USER_DATA_4);
		
		view_get_rect(container_user, &rect);
		rect.x1 += 5;
    rect.x2 = rect.x1 + 72;
    rect.y1 +=20;
    rect.y2 = rect.y1 + 20;
	
	  label_user = rtgui_label_create("RT_NULL:");
		RTGUI_WIDGET_FOREGROUND(label_user) = Scope_Channel_Color_ch1;
    rtgui_widget_set_rect(RTGUI_WIDGET(label_user), &rect);
    rtgui_container_add_child(container_user, RTGUI_WIDGET(label_user));
	  rtgui_object_set_id(RTGUI_OBJECT(label_user), USER_DATA_NAME_5);
		
		rect.x1 += 78;
    rect.x2 = rect.x1 + 52;
	
	  label_user = rtgui_label_create("65536");
		RTGUI_WIDGET_FOREGROUND(label_user) = Scope_Channel_Color_ch1;
    rtgui_widget_set_rect(RTGUI_WIDGET(label_user), &rect);
    rtgui_container_add_child(container_user, RTGUI_WIDGET(label_user));
		rtgui_object_set_id(RTGUI_OBJECT(label_user), USER_DATA_5);
		
    rect.x1 += 60;
    rect.x2 = rect.x1 + 72;
		label_user = rtgui_label_create("RT_NULL:");
		RTGUI_WIDGET_FOREGROUND(label_user) =Scope_Channel_Color_ch1;
    rtgui_widget_set_rect(RTGUI_WIDGET(label_user), &rect);
    rtgui_container_add_child(container_user, RTGUI_WIDGET(label_user));
		rtgui_object_set_id(RTGUI_OBJECT(label_user), USER_DATA_NAME_6);
		
    rect.x1 += 78;
    rect.x2 = rect.x1 + 52;
		label_user = rtgui_label_create("65536");
		RTGUI_WIDGET_FOREGROUND(label_user) =Scope_Channel_Color_ch1;
    rtgui_widget_set_rect(RTGUI_WIDGET(label_user), &rect);
    rtgui_container_add_child(container_user, RTGUI_WIDGET(label_user));
		rtgui_object_set_id(RTGUI_OBJECT(label_user), USER_DATA_6);
		
		
		
			
	  rect.y1 += 30;
    rect.y2 = rect.y1 + 20;
		RTGUI_WIDGET_FOREGROUND(label_user) =Scope_Channel_Color_ch1;
	  text = rtgui_textbox_create("RT_NULL", RTGUI_TEXTBOX_SINGLE);
    rtgui_widget_set_rect(RTGUI_WIDGET(text), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(container_user), RTGUI_WIDGET(text));
	  rtgui_object_set_id(RTGUI_OBJECT(text), USER_DATA_SETTING_1);
		
		
	  rect.y1 += 30;
    rect.y2 = rect.y1 + 20;
		RTGUI_WIDGET_FOREGROUND(label_user) =Scope_Channel_Color_ch1;
	  text = rtgui_textbox_create("RT_NULL", RTGUI_TEXTBOX_SINGLE);
    rtgui_widget_set_rect(RTGUI_WIDGET(text), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(container_user), RTGUI_WIDGET(text));
	  rtgui_object_set_id(RTGUI_OBJECT(text), USER_DATA_SETTING_2);
		
		
		rect.y1 += 30;
    rect.y2 = rect.y1 + 20;
		RTGUI_WIDGET_FOREGROUND(label_user) =Scope_Channel_Color_ch1;
	  text = rtgui_textbox_create("RT_NULL", RTGUI_TEXTBOX_SINGLE);
    rtgui_widget_set_rect(RTGUI_WIDGET(text), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(container_user), RTGUI_WIDGET(text));
	  rtgui_object_set_id(RTGUI_OBJECT(text), USER_DATA_SETTING_3);
		
		
		rect.y1 += 30;
    rect.y2 = rect.y1 + 20;
		RTGUI_WIDGET_FOREGROUND(label_user) =Scope_Channel_Color_ch1;
	  text = rtgui_textbox_create("RT_NULL", RTGUI_TEXTBOX_SINGLE);
    rtgui_widget_set_rect(RTGUI_WIDGET(text), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(container_user), RTGUI_WIDGET(text));
	  rtgui_object_set_id(RTGUI_OBJECT(text), USER_DATA_SETTING_4);
		
		
		rect.y1 += 30;
    rect.y2 = rect.y1 + 20;
		RTGUI_WIDGET_FOREGROUND(label_user) =Scope_Channel_Color_ch1;
	  text = rtgui_textbox_create("RT_NULL", RTGUI_TEXTBOX_SINGLE);
    rtgui_widget_set_rect(RTGUI_WIDGET(text), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(container_user), RTGUI_WIDGET(text));
	  rtgui_object_set_id(RTGUI_OBJECT(text), USER_DATA_SETTING_5);
		
		
		rect.x1 -=75;
		rect.x2 =rect.x1+55;
		rect.y1 -=160;	
		rect.y1 += 40;
    rect.y2 = rect.y1 + 20;
		RTGUI_WIDGET_FOREGROUND(label_user) =Scope_Channel_Color_ch1;
	  label = rtgui_label_create("变量一:");
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(container_user), RTGUI_WIDGET(label));
		
	  rect.y1 += 30;
    rect.y2 = rect.y1 + 20;
		RTGUI_WIDGET_FOREGROUND(label_user) =Scope_Channel_Color_ch1;
		label = rtgui_label_create("变量二:");
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(container_user), RTGUI_WIDGET(label));


		rect.y1 += 30;
    rect.y2 = rect.y1 + 20;
		RTGUI_WIDGET_FOREGROUND(label_user) =Scope_Channel_Color_ch1;
		label = rtgui_label_create("变量三:");
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(container_user), RTGUI_WIDGET(label));

		
		
		rect.y1 += 30;
    rect.y2 = rect.y1 + 20;
		RTGUI_WIDGET_FOREGROUND(label_user) =Scope_Channel_Color_ch1;
		label = rtgui_label_create("变量四:");
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(container_user), RTGUI_WIDGET(label));	
		
		rect.y1 += 30;
    rect.y2 = rect.y1 + 20;
		RTGUI_WIDGET_FOREGROUND(label_user) =Scope_Channel_Color_ch1;
		label = rtgui_label_create("变量五:");
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(container_user), RTGUI_WIDGET(label));
		
		view_get_rect(container_user, &rect);
    rect.x1 += 0;
    rect.x2 = rect.x1 + 100;
    rect.y1 =rect.y1+45;
    rect.y2 = rect.y1 + 120;	

    variable = rtgui_radiobox_create("变量设置", RTGUI_VERTICAL, radio_item_v, 5);
    rtgui_radiobox_set_selection(variable, 0);
    rtgui_container_add_child(container_user, RTGUI_WIDGET(variable));
    rtgui_widget_set_rect(RTGUI_WIDGET(variable), &rect);
		
		view_get_rect(container_user, &rect);
    rect.x1 += 10;
    rect.x2 = rect.x1 + 168;
    rect.y1 +=165;
    rect.y2 = rect.y1 + 16;	
		label = rtgui_label_create( "注:变量设置范围:");
	  RTGUI_WIDGET_FOREGROUND(label) = red;
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(container_user, RTGUI_WIDGET(label));	
			
    rect.x2 -=112;
    rect.y1 +=24;
    rect.y2 = rect.y1 + 16;	
		label = rtgui_label_create( "0~65536");
	  RTGUI_WIDGET_FOREGROUND(label) = red;
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(container_user, RTGUI_WIDGET(label));	
		
		/*用于导入键盘界面*/
    Load_Keyboard_user(container_user,300,60);
		
	  timer = rtgui_timer_create(50, RT_TIMER_FLAG_PERIODIC, cpuinformation_update, RT_NULL);
	  rtgui_timer_start(timer);		
	  return container_user;
}


static unsigned char KeyBoard_Data[20]="0000000";
static unsigned char KeyBoard_DataC[20]="0000000";
extern struct power_parameter power_data;
static int number=6;
static int number_key=0;

static struct Key_board_Value
	{
  rt_uint32_t Value_data_Decimal;
  };

static struct Key_board_Value keyboard_data;
static void Softkeyboard_ok(struct rtgui_object *object, rtgui_event_t *event)
{
	int i,j;
	keyboard_data.Value_data_Decimal=0;
	
	keyboard_data.Value_data_Decimal+=(KeyBoard_DataC[number]-48);
	keyboard_data.Value_data_Decimal+=(KeyBoard_DataC[number-1]-48)*10;
	keyboard_data.Value_data_Decimal+=(KeyBoard_DataC[number-2]-48)*100;
	keyboard_data.Value_data_Decimal+=(KeyBoard_DataC[number-3]-48)*1000;
	keyboard_data.Value_data_Decimal+=(KeyBoard_DataC[number-4]-48)*10000;
	keyboard_data.Value_data_Decimal+=(KeyBoard_DataC[number-5]-48)*100000;
	keyboard_data.Value_data_Decimal+=(KeyBoard_DataC[number-6]-48)*1000000;
	if(rtgui_radiobox_get_selection(variable)==0)
	power_data.User_data_ch7=keyboard_data.Value_data_Decimal;
	else if(rtgui_radiobox_get_selection(variable)==1)
	power_data.User_data_ch8=keyboard_data.Value_data_Decimal;
	else if(rtgui_radiobox_get_selection(variable)==2)
	power_data.User_data_ch9=keyboard_data.Value_data_Decimal;
		else if(rtgui_radiobox_get_selection(variable)==3)
	power_data.User_data_ch10=keyboard_data.Value_data_Decimal;
			else if(rtgui_radiobox_get_selection(variable)==4)
	power_data.User_data_ch11=keyboard_data.Value_data_Decimal;
	
	user_send_data_type=rtgui_radiobox_get_selection(variable);
}


static void Softkeyboard_clear(struct rtgui_object *object, rtgui_event_t *event)
{
	  int i;
	  struct rtgui_textbox* text;
    number_key=0;
	  text = RTGUI_TEXTBOX(rtgui_get_self_object(Data_key_board_user));
	  for(i=0;i<number+1;i++)
	{
    KeyBoard_Data[i]=0+48;
		KeyBoard_DataC[i]=0+48;
	}
    rtgui_textbox_set_value(text, KeyBoard_DataC);
    rtgui_widget_update(RTGUI_WIDGET(text));
}

static void Softkeyboard_num_0(struct rtgui_object *object, rtgui_event_t *event)
{
	  struct rtgui_textbox* text;
	  int i,j;
	
	  text = RTGUI_TEXTBOX(rtgui_get_self_object(Data_key_board_user));
    KeyBoard_Data[number_key]=0+48;
	  if(number_key<=number&&number_key!=0)
	  number_key++;
		for(i=number_key,j=0;i>0;i--,j++)
    KeyBoard_DataC[number-i+1]=KeyBoard_Data[j];
    rtgui_textbox_set_value(text, KeyBoard_DataC);
    rtgui_widget_update(RTGUI_WIDGET(text));
		
}

static void Softkeyboard_num_1(struct rtgui_object *object, rtgui_event_t *event)
{
	  struct rtgui_textbox* text;
    int i,j;
	  text = RTGUI_TEXTBOX(rtgui_get_self_object(Data_key_board_user));
    KeyBoard_Data[number_key]=1+48;
	  if(number_key<=number)
	  number_key++;
		for(i=number_key,j=0;i>0;i--,j++)
    KeyBoard_DataC[number-i+1]=KeyBoard_Data[j];
    rtgui_textbox_set_value(text, KeyBoard_DataC);
    rtgui_widget_update(RTGUI_WIDGET(text));
}

static void Softkeyboard_num_2(struct rtgui_object *object, rtgui_event_t *event)
{
	  struct rtgui_textbox* text;
	  int i,j;
	  text = RTGUI_TEXTBOX(rtgui_get_self_object(Data_key_board_user));
    

		KeyBoard_Data[number_key]=2+48;
	  if(number_key<=number)
	  number_key++;
		for(i=number_key,j=0;i>0;i--,j++)
    KeyBoard_DataC[number-i+1]=KeyBoard_Data[j];
    rtgui_textbox_set_value(text, KeyBoard_DataC);
    rtgui_widget_update(RTGUI_WIDGET(text));
}

static void Softkeyboard_num_3(struct rtgui_object *object, rtgui_event_t *event)
{
	  struct rtgui_textbox* text;
	  int i,j;
	
	  text = RTGUI_TEXTBOX(rtgui_get_self_object(Data_key_board_user));
    KeyBoard_Data[number_key]=3+48;
	  if(number_key<=number)
	  number_key++;
		for(i=number_key,j=0;i>0;i--,j++)
    KeyBoard_DataC[number-i+1]=KeyBoard_Data[j];
    rtgui_textbox_set_value(text, KeyBoard_DataC);
    rtgui_widget_update(RTGUI_WIDGET(text));
}

static void Softkeyboard_num_4(struct rtgui_object *object, rtgui_event_t *event)
{
	  struct rtgui_textbox* text;
	  int i,j;
	  text = RTGUI_TEXTBOX(rtgui_get_self_object(Data_key_board_user));
    KeyBoard_Data[number_key]=4+48;
	  if(number_key<=number)
	  number_key++;
		for(i=number_key,j=0;i>0;i--,j++)
    KeyBoard_DataC[number-i+1]=KeyBoard_Data[j];
    rtgui_textbox_set_value(text, KeyBoard_DataC);
    rtgui_widget_update(RTGUI_WIDGET(text));
}

static void Softkeyboard_num_5(struct rtgui_object *object, rtgui_event_t *event)
{
	  struct rtgui_textbox* text;
	  int i,j;
	
	  text = RTGUI_TEXTBOX(rtgui_get_self_object(Data_key_board_user));
    KeyBoard_Data[number_key]=5+48;
	  if(number_key<=number)
	  number_key++;
		for(i=number_key,j=0;i>0;i--,j++)
    KeyBoard_DataC[number-i+1]=KeyBoard_Data[j];
    rtgui_textbox_set_value(text, KeyBoard_DataC);
    rtgui_widget_update(RTGUI_WIDGET(text));
}

static void Softkeyboard_num_6(struct rtgui_object *object, rtgui_event_t *event)
{
	  struct rtgui_textbox* text;
	  int i,j;
	
	  text = RTGUI_TEXTBOX(rtgui_get_self_object(Data_key_board_user));
    KeyBoard_Data[number_key]=6+48;
	  if(number_key<=number)
	  number_key++;
		for(i=number_key,j=0;i>0;i--,j++)
    KeyBoard_DataC[number-i+1]=KeyBoard_Data[j];
    rtgui_textbox_set_value(text, KeyBoard_DataC);
    rtgui_widget_update(RTGUI_WIDGET(text));
}

static void Softkeyboard_num_7(struct rtgui_object *object, rtgui_event_t *event)
{
	  struct rtgui_textbox* text;
	  int i,j;
	
	  text = RTGUI_TEXTBOX(rtgui_get_self_object(Data_key_board_user));
    KeyBoard_Data[number_key]=7+48;
	  if(number_key<=number)
	  number_key++;
		for(i=number_key,j=0;i>0;i--,j++)
    KeyBoard_DataC[number-i+1]=KeyBoard_Data[j];
    rtgui_textbox_set_value(text, KeyBoard_DataC);
    rtgui_widget_update(RTGUI_WIDGET(text));
}
static void Softkeyboard_num_8(struct rtgui_object *object, rtgui_event_t *event)
{
	  struct rtgui_textbox* text;
	  int i,j;
	
	  text = RTGUI_TEXTBOX(rtgui_get_self_object(Data_key_board_user));
    KeyBoard_Data[number_key]=8+48;
	  if(number_key<=number)
	  number_key++;
		for(i=number_key,j=0;i>0;i--,j++)
    KeyBoard_DataC[number-i+1]=KeyBoard_Data[j];
    rtgui_textbox_set_value(text, KeyBoard_DataC);
    rtgui_widget_update(RTGUI_WIDGET(text));
}

static void Softkeyboard_num_9(struct rtgui_object *object, rtgui_event_t *event)
{
	  struct rtgui_textbox* text;
	  int i,j;
	
	  text = RTGUI_TEXTBOX(rtgui_get_self_object(Data_key_board_user));
    KeyBoard_Data[number_key]=9+48;
	  if(number_key<=number)
	  number_key++;
		for(i=number_key,j=0;i>0;i--,j++)
    KeyBoard_DataC[number-i+1]=KeyBoard_Data[j];
    rtgui_textbox_set_value(text, KeyBoard_DataC);
    rtgui_widget_update(RTGUI_WIDGET(text));
}


void Load_Keyboard_user(rtgui_container_t *win,rt_uint32_t rect_X,rt_uint32_t rect_Y)
{
		rtgui_button_t *button;
    rtgui_rect_t rect;  
//	  rtgui_label_t *label;
	  struct rtgui_textbox* text;

		rect.x1=rect_X+45;
		rect.y1=rect_Y+10;
		rect.x2 = rect.x1+60;
    rect.y2 = rect.y1 + 25;
    text = rtgui_textbox_create("0000000", RTGUI_TEXTBOX_SINGLE);
    rtgui_widget_set_rect(RTGUI_WIDGET(text), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(text));
	  rtgui_object_set_id(RTGUI_OBJECT(text), Data_key_board_user);
	 
    rect.x1 = rect_X;
		rect.y1 = rect_Y;
		rect.x2 = rect.x1 + 35;
    rect.y2 = rect.y1 + 35;
	
    rect.x2 = rect.x1 + 35;
		rect.y1 += 40;
    rect.y2 = rect.y1 + 35;
		button = rtgui_button_create("1");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
		rtgui_button_set_onbutton(button, Softkeyboard_num_1);

    rect.x1 += 40;
    rect.x2 = rect.x1+35;
		button = rtgui_button_create("2");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
		rtgui_button_set_onbutton(button, Softkeyboard_num_2);
		
		rect.x1 += 40;
    rect.x2 = rect.x1+35;
		button = rtgui_button_create("3");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
		rtgui_button_set_onbutton(button, Softkeyboard_num_3);
		
		rect.x1 += 40;
    rect.x2 = rect.x1+35;
		button = rtgui_button_create("A");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
		
		rect.x1 = rect_X;
    rect.x2 = rect.x1+35;
		rect.y1 += 40;
    rect.y2 = rect.y1 + 35;
		button = rtgui_button_create("4");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
		rtgui_button_set_onbutton(button, Softkeyboard_num_4);
		
		rect.x1 += 40;
    rect.x2 = rect.x1+35;
		button = rtgui_button_create("5");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
		rtgui_button_set_onbutton(button, Softkeyboard_num_5);
		
		rect.x1 += 40;
    rect.x2 = rect.x1+35;
		button = rtgui_button_create("6");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
		rtgui_button_set_onbutton(button, Softkeyboard_num_6);
		
				rect.x1 += 40;
    rect.x2 = rect.x1+35;
		button = rtgui_button_create("B");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
		
		
		rect.x1 = rect_X;
    rect.x2 = rect.x1+35;
		rect.y1 += 40;
    rect.y2 = rect.y1 + 35;
		button = rtgui_button_create("7");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
		rtgui_button_set_onbutton(button, Softkeyboard_num_7);
		
		rect.x1 += 40;
    rect.x2 = rect.x1+35;
		button = rtgui_button_create("8");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
		rtgui_button_set_onbutton(button, Softkeyboard_num_8);
		
		rect.x1 += 40;
    rect.x2 = rect.x1+35;
		button = rtgui_button_create("9");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
		rtgui_button_set_onbutton(button, Softkeyboard_num_9);
		
		rect.x1 += 40;
    rect.x2 = rect.x1+35;
		button = rtgui_button_create("C");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
		
		
		rect.x1 = rect_X;
    rect.x2 = rect.x1+35;
		rect.y1 += 40;
    rect.y2 = rect.y1 + 35;
		button = rtgui_button_create("F");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
		
	  rect.x1 += 40;
    rect.x2 = rect.x1+35;
		button = rtgui_button_create("0");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
		rtgui_button_set_onbutton(button, Softkeyboard_num_0);
		
		rect.x1 += 40;
    rect.x2 = rect.x1+35;
		button = rtgui_button_create("E");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
		
	  rect.x1 += 40;
    rect.x2 = rect.x1+35;
		button = rtgui_button_create("D");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
		
		
		rect.x1 = rect_X;
    rect.x2 = rect.x1+75;
		rect.y1 += 40;
    rect.y2 = rect.y1 + 35;
		button = rtgui_button_create("Clear");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
		rtgui_button_set_onbutton(button, Softkeyboard_clear);
		
		rect.x1 += 80;
    rect.x2 = rect.x1+75;
		button = rtgui_button_create("Ok");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
	  rtgui_button_set_onbutton(button, Softkeyboard_ok);
}