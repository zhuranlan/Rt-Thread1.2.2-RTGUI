#include "view.h"
#include <rtgui/dc.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/slider.h>
#include <rtgui/image_hdc.h>
#include <rtgui/widgets/combobox.h>
#include <rtgui/dc.h>
#include <rtgui/dc_hw.h>
#include <rtgui/widgets/container.h>

#include <rtgui/rtgui.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/window.h>
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/button.h>
#include <string.h>
#include "view.h"
#include <rtgui/widgets/staticline.h>
#include <rtgui/widgets/notebook.h>
#include <rtgui/widgets/textview.h>
#include "time.h"
#include <rtgui/widgets/radiobox.h>
#include <rtgui/widgets/panel.h>
#include "mylcd.h"
#include <rtgui/widgets/textbox.h>
#include "Interver_RTU.h"
#include <rtgui/widgets/progressbar.h>
#include <rtgui/widgets/checkbox.h>
#include <rtgui/widgets/scrollbar.h>
#include "arm_math.h"
#include "messagedialog.h"
extern q15_t store_data[8192];
extern void GO_TO_Scope(void);
rtgui_container_t *container_scope_setting;
extern rtgui_checkbox_t *ch1_checkbox,*ch2_checkbox,*ch3_checkbox,*ch1_checkbox_1,*ch2_checkbox_1,*ch3_checkbox_1;
rtgui_combobox_t *box_ch1,*box_ch2,*box_ch3;
extern struct rtgui_notebook *the_notebook;
rtgui_radiobox_t *radiobox_f;
rtgui_radiobox_t *sample_count_ch1,*sample_count_ch2,*sample_count_ch3;
extern char * rt_kprintf_float(double data);
static rtgui_messagedialog_t *msgboox;
static struct rtgui_listbox_item Sope_data_choice[] =
{
    {"电压A", RT_NULL},
    {"电压B", RT_NULL},
		{"电压C", RT_NULL},
    {"电流A", RT_NULL},
    {"电流B", RT_NULL},
    {"电流C", RT_NULL}, 
    {"用户1", RT_NULL}, 
		{"用户2", RT_NULL},
};
static char *radio_item_f[6] =
{
	  "1KHZ",
    "2KHZ",
    "4KHZ",
    "5KHZ",
    "10KHZ",
	  "20KHZ",	
};
static char *radio_item_count[4] =
{
	   "0",
    "2048",
    "4096",
    "8192",
};

//#define warning_icon   "/SD/warning.bmp"

 void GO_TO_Scope_Setting(void)
 {
	 rtgui_notebook_set_current_by_index(the_notebook,3);
 }
static void Return_Scope_onbutton(struct rtgui_object *object, rtgui_event_t *event)
{
	GO_TO_Scope();
}


 
static void save_onbutton(struct rtgui_object *object, rtgui_event_t *event)
{
	struct rtgui_listbox_item *get_select;
	struct rtgui_label  *label;
	rtgui_image_t *icon;
	static char label_text[100];
	rtgui_dialog_result_t result;	
	rtgui_rect_t rect;
	int i;
	float temp,temp2,orig_temp1,orig_temp2,orig_temp3;
	/*存储上次配置的数据*/
	orig_temp1=power_data.ch1_data_length;
	orig_temp2=power_data.ch2_data_length;
	orig_temp3=power_data.ch3_data_length;
	/*存储需要采样的点数*/
		if(rtgui_radiobox_get_selection(sample_count_ch1)==0)
	power_data.ch1_data_length=0;	
		else if(rtgui_radiobox_get_selection(sample_count_ch1)==1)
	power_data.ch1_data_length=2048;		
		else if(rtgui_radiobox_get_selection(sample_count_ch1)==2)
	power_data.ch1_data_length=4096;
				else if(rtgui_radiobox_get_selection(sample_count_ch1)==3)
	power_data.ch1_data_length=8192;
		
		if(rtgui_radiobox_get_selection(sample_count_ch2)==0)
	power_data.ch2_data_length=0;	
		else if(rtgui_radiobox_get_selection(sample_count_ch2)==1)
	power_data.ch2_data_length=2048;		
		else if(rtgui_radiobox_get_selection(sample_count_ch2)==2)
	power_data.ch2_data_length=4096;
				else if(rtgui_radiobox_get_selection(sample_count_ch2)==3)
	power_data.ch2_data_length=8192;
		
		
		if(rtgui_radiobox_get_selection(sample_count_ch3)==0)
	power_data.ch3_data_length=0;	
		else if(rtgui_radiobox_get_selection(sample_count_ch3)==1)
	power_data.ch3_data_length=2048;		
		else if(rtgui_radiobox_get_selection(sample_count_ch3)==2)
	power_data.ch3_data_length=4096;
				else if(rtgui_radiobox_get_selection(sample_count_ch3)==3)
	power_data.ch3_data_length=8192;
	
	/*存储DSP采样频率*/
	if(rtgui_radiobox_get_selection(radiobox_f)==0)
	power_data.DSP_Sampling_f=1000;
	else if(rtgui_radiobox_get_selection(radiobox_f)==1)
	power_data.DSP_Sampling_f=2000;	
	else if(rtgui_radiobox_get_selection(radiobox_f)==2)
	power_data.DSP_Sampling_f=4000;		
	else if(rtgui_radiobox_get_selection(radiobox_f)==3)
	power_data.DSP_Sampling_f=5000;					
	else if(rtgui_radiobox_get_selection(radiobox_f)==4)
	power_data.DSP_Sampling_f=10000;
		else if(rtgui_radiobox_get_selection(radiobox_f)==5)
	power_data.DSP_Sampling_f=20000;
	
	
		if((power_data.ch3_data_length+power_data.ch2_data_length+power_data.ch1_data_length)<=8192)
	{		
	label = RTGUI_LABEL(rtgui_get_self_object(SIMPLE_TIME_CH1));
	temp=(float)power_data.DSP_Sampling_f;
	temp2=(float)power_data.ch1_data_length;
  rt_sprintf(label_text, "%sS",rt_kprintf_float(temp2*(1/temp)));
  rtgui_label_set_text(label, label_text);
  rtgui_widget_update(RTGUI_WIDGET(label));
				
	label = RTGUI_LABEL(rtgui_get_self_object(SIMPLE_TIME_CH2));
  temp=(float)power_data.DSP_Sampling_f;
	temp2=(float)power_data.ch2_data_length;
  rt_sprintf(label_text, "%sS",rt_kprintf_float(temp2*(1/temp)));
  rtgui_label_set_text(label, label_text);
  rtgui_widget_update(RTGUI_WIDGET(label));
				
	label = RTGUI_LABEL(rtgui_get_self_object(SIMPLE_TIME_CH3));
  temp=(float)power_data.DSP_Sampling_f;
	temp2=(float)power_data.ch3_data_length;
  rt_sprintf(label_text, "%sS",rt_kprintf_float(temp2*(1/temp)));
  rtgui_label_set_text(label, label_text);
  rtgui_widget_update(RTGUI_WIDGET(label));
		
//	RTGUI_RECT(rect, 130, 110, 220, 100);
//	msgboox = rtgui_messagedialog_create(RT_NULL, "Successful Configuration!!", "Message",
//                                        &rect, RTGUI_MB_FLAG_YESNO, RT_NULL);
//	result = rtgui_messagedialog_show(msgboox);
//	rtgui_messagedialog_destroy(msgboox);
	}
	else
	{
	power_data.ch1_data_length=orig_temp1;
	power_data.ch2_data_length=orig_temp2;
	power_data.ch3_data_length=orig_temp3;
		
	label = RTGUI_LABEL(rtgui_get_self_object(SIMPLE_TIME_CH1));
	temp=(float)power_data.DSP_Sampling_f;
	temp2=(float)power_data.ch1_data_length;
  rt_sprintf(label_text, "%sS",rt_kprintf_float(temp2*(1/temp)));
  rtgui_label_set_text(label, label_text);
  rtgui_widget_update(RTGUI_WIDGET(label));
				
	label = RTGUI_LABEL(rtgui_get_self_object(SIMPLE_TIME_CH2));
  	temp=(float)power_data.DSP_Sampling_f;
	temp2=(float)power_data.ch2_data_length;
  rt_sprintf(label_text, "%sS",rt_kprintf_float(temp2*(1/temp)));
  rtgui_label_set_text(label, label_text);
  rtgui_widget_update(RTGUI_WIDGET(label));
				
	label = RTGUI_LABEL(rtgui_get_self_object(SIMPLE_TIME_CH3));
  temp=(float)power_data.DSP_Sampling_f;
	temp2=(float)power_data.ch3_data_length;
  rt_sprintf(label_text, "%sS",rt_kprintf_float(temp2*(1/temp)));
  rtgui_label_set_text(label, label_text);
  rtgui_widget_update(RTGUI_WIDGET(label));
	
	RTGUI_RECT(rect, 130, 110, 220, 100);
//	icon = rtgui_image_create(warning_icon, RT_FALSE);
	msgboox = rtgui_messagedialog_create(RT_NULL, "Configuration Failed!!", "Waring",
                                        &rect, RTGUI_MB_FLAG_OK, RT_NULL);
	result = rtgui_messagedialog_show(msgboox);
	rtgui_messagedialog_destroy(msgboox);
	}
	
	
	
	/*存储示波器选中的通道*/
  scope_setting.ch1_choice=rtgui_checkbox_get_checked(ch1_checkbox);
  scope_setting.ch2_choice=rtgui_checkbox_get_checked(ch2_checkbox);
  scope_setting.ch3_choice=rtgui_checkbox_get_checked(ch3_checkbox);
	
	
	/*存储每个通道需要传输的数据类型*/
	get_select=(rtgui_combox_get_select(box_ch1));
	for(i=0;i<(sizeof(Sope_data_choice) / sizeof(Sope_data_choice[0]));i++)
	{
	if(strcmp(get_select->name,Sope_data_choice[i].name)==0)
	{
		scope_setting.ch1_combox=i;
	}
  }
	
	get_select=(rtgui_combox_get_select(box_ch2));
	for(i=0;i<(sizeof(Sope_data_choice) / sizeof(Sope_data_choice[0]));i++)
	{
	if(strcmp(get_select->name,Sope_data_choice[i].name)==0)
	{
		scope_setting.ch2_combox=i;
		//rt_kprintf("scope_setting.ch2_combox:%d \n",i);
	}
  }
	
	get_select=(rtgui_combox_get_select(box_ch3));
	for(i=0;i<(sizeof(Sope_data_choice) / sizeof(Sope_data_choice[0]));i++)
	{
	if(strcmp(get_select->name,Sope_data_choice[i].name)==0)
		scope_setting.ch3_combox=i;
  }

	for(i=0;i<8192;i++)
	store_data[i]=0;
}




rtgui_container_t *scope_setting_panel(void)
{
	  int i;
	  rtgui_rect_t rect;
	 
	  struct rtgui_label *label_setting;

	  struct rtgui_button *button;
	  char label_text[100];
	  rtgui_font_t *font;
	    
   container_scope_setting = view("参数设置");
	    if (container_scope_setting == RT_NULL)
        return RT_NULL;
	
		view_get_rect(container_scope_setting, &rect);
    rect.x1 += 0;
    rect.x2 = rect.x1 + 480;
    rect.y1 =rect.y1-30;
    rect.y2 = rect.y1 + 45;	
			
   
    radiobox_f = rtgui_radiobox_create("采样频率", RTGUI_HORIZONTAL, radio_item_f, 6);	
		rtgui_widget_set_rect(RTGUI_WIDGET(radiobox_f), &rect);
    rtgui_radiobox_set_selection(radiobox_f, 1);
    rtgui_container_add_child(container_scope_setting, RTGUI_WIDGET(radiobox_f));
   
		
		view_get_rect(RTGUI_CONTAINER(container_scope_setting), &rect);
    rect.x1 += 10;
    rect.x2 =rect.x1 + 100;
    rect.y1 = rect.y1-30+45;
    rect.y2 = rect.y1 + 20;
    box_ch1 = rtgui_combobox_create(Sope_data_choice, sizeof(Sope_data_choice) / sizeof(Sope_data_choice[0]), &rect);
		RTGUI_WIDGET_FOREGROUND(box_ch1) = Scope_Channel_Color_ch1;
    rtgui_container_add_child(RTGUI_CONTAINER(container_scope_setting), RTGUI_WIDGET(box_ch1));
		
    rect.x1 += 110;
    rect.x2 =rect.x1 + 100;
		box_ch2 = rtgui_combobox_create(Sope_data_choice, sizeof(Sope_data_choice) / sizeof(Sope_data_choice[0]), &rect);
		RTGUI_WIDGET_FOREGROUND(box_ch2) = Scope_Channel_Color_ch2;
    rtgui_container_add_child(RTGUI_CONTAINER(container_scope_setting), RTGUI_WIDGET(box_ch2));
		
    rect.x1 += 110;
    rect.x2 =rect.x1 + 100;
		box_ch3 = rtgui_combobox_create(Sope_data_choice, sizeof(Sope_data_choice) / sizeof(Sope_data_choice[0]), &rect);
		RTGUI_WIDGET_FOREGROUND(box_ch3) = Scope_Channel_Color_ch3;
    rtgui_container_add_child(RTGUI_CONTAINER(container_scope_setting), RTGUI_WIDGET(box_ch3));
		
			
		view_get_rect(RTGUI_CONTAINER(container_scope_setting), &rect);
    rect.x1 += 10;
    rect.x2 =rect.x1 + 48;
    rect.y1 =rect.y1 - 30+20+45;
    rect.y2 = rect.y1 + 20;
		ch1_checkbox = rtgui_checkbox_create("CH1", RT_TRUE);
		
	  RTGUI_WIDGET_FOREGROUND(ch1_checkbox) = Scope_Channel_Color_ch1;
    rtgui_widget_set_rect(RTGUI_WIDGET(ch1_checkbox), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(container_scope_setting), RTGUI_WIDGET(ch1_checkbox));
		
		
		rect.x1 += 110;
    rect.x2 =rect.x1 + 48;
    ch2_checkbox = rtgui_checkbox_create("CH2", RT_TRUE);
		
    RTGUI_WIDGET_FOREGROUND(ch2_checkbox) = Scope_Channel_Color_ch2;
    rtgui_widget_set_rect(RTGUI_WIDGET(ch2_checkbox), &rect);
		//rtgui_checkbox_set_checked(ch2_checkbox,RT_FALSE);
    rtgui_container_add_child(RTGUI_CONTAINER(container_scope_setting), RTGUI_WIDGET(ch2_checkbox));
		
		
		rect.x1 += 110;
    rect.x2 =rect.x1 + 48;
    ch3_checkbox = rtgui_checkbox_create("CH3", RT_TRUE);
		
    RTGUI_WIDGET_FOREGROUND(ch3_checkbox) = Scope_Channel_Color_ch3;
    rtgui_widget_set_rect(RTGUI_WIDGET(ch3_checkbox), &rect);
		//rtgui_checkbox_set_checked(ch3_checkbox,RT_FALSE);
    rtgui_container_add_child(RTGUI_CONTAINER(container_scope_setting), RTGUI_WIDGET(ch3_checkbox));
		
		
	  view_get_rect(container_scope_setting, &rect);
    rect.x1 += 0;
    rect.x2 = rect.x1 + 100;
    rect.y1 =rect.y1+60;
    rect.y2 = rect.y1 + 96;	

    sample_count_ch1= rtgui_radiobox_create("采样点数", RTGUI_VERTICAL, radio_item_count, 4);
		RTGUI_WIDGET_FOREGROUND(sample_count_ch1) = Scope_Channel_Color_ch1;
    rtgui_radiobox_set_selection(sample_count_ch1, 1);
    rtgui_container_add_child(container_scope_setting, RTGUI_WIDGET(sample_count_ch1));
    rtgui_widget_set_rect(RTGUI_WIDGET(sample_count_ch1), &rect);
		
	  rect.x1 =rect.x1+110;
    rect.x2 = rect.x1 + 100;		
    sample_count_ch2= rtgui_radiobox_create("采样点数", RTGUI_VERTICAL, radio_item_count, 4);
		RTGUI_WIDGET_FOREGROUND(sample_count_ch2) = Scope_Channel_Color_ch2;
    rtgui_radiobox_set_selection(sample_count_ch2, 1);
    rtgui_container_add_child(container_scope_setting, RTGUI_WIDGET(sample_count_ch2));
    rtgui_widget_set_rect(RTGUI_WIDGET(sample_count_ch2), &rect);
				
	  rect.x1 =rect.x1+110;
    rect.x2 = rect.x1 + 100;	
    sample_count_ch3= rtgui_radiobox_create("采样点数", RTGUI_VERTICAL, radio_item_count, 4);
		RTGUI_WIDGET_FOREGROUND(sample_count_ch3) = Scope_Channel_Color_ch3;
    rtgui_radiobox_set_selection(sample_count_ch3, 1);
    rtgui_container_add_child(container_scope_setting, RTGUI_WIDGET(sample_count_ch3));
    rtgui_widget_set_rect(RTGUI_WIDGET(sample_count_ch3), &rect);
	


	  view_get_rect(RTGUI_CONTAINER(container_scope_setting), &rect);
    rect.x1 += 370;
    rect.x2 = rect.x1 + 100;
    rect.y1 += 30;
    rect.y2 = rect.y1 + 30;
	  button = rtgui_button_create("保存设置");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(container_scope_setting), RTGUI_WIDGET(button));
    rtgui_button_set_onbutton(button, save_onbutton);
		
		rect.y1 += 40;
    rect.y2 = rect.y1 + 30;
    button = rtgui_button_create("返回");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(container_scope_setting), RTGUI_WIDGET(button));
    rtgui_button_set_onbutton(button, Return_Scope_onbutton);
		
		
	  view_get_rect(container_scope_setting, &rect);
    rect.x1 += 10;
    rect.x2 = rect.x1 + 100;
    rect.y1 =rect.y1+60+96;
    rect.y2 = rect.y1 + 20;	
	
	//rt_sprintf(label_text, "maxValue:%s",rt_kprintf_float(maxValue)); 
	  label_setting = rtgui_label_create("采样时间:");
		RTGUI_WIDGET_FOREGROUND(label_setting) = Scope_Channel_Color_ch1;
    rtgui_widget_set_rect(RTGUI_WIDGET(label_setting), &rect);
    rtgui_container_add_child(container_scope_setting, RTGUI_WIDGET(label_setting));
		
		rect.x1 += 110;
    rect.x2 = rect.x1 + 100;
	  label_setting = rtgui_label_create("采样时间:");
		RTGUI_WIDGET_FOREGROUND(label_setting) = Scope_Channel_Color_ch2;
    rtgui_widget_set_rect(RTGUI_WIDGET(label_setting), &rect);
    rtgui_container_add_child(container_scope_setting, RTGUI_WIDGET(label_setting));
		
		
		rect.x1 += 110;
    rect.x2 = rect.x1 + 100;
		label_setting = rtgui_label_create("采样时间:");
		RTGUI_WIDGET_FOREGROUND(label_setting) = Scope_Channel_Color_ch3;
    rtgui_widget_set_rect(RTGUI_WIDGET(label_setting), &rect);
    rtgui_container_add_child(container_scope_setting, RTGUI_WIDGET(label_setting));
		
		view_get_rect(container_scope_setting, &rect);
    rect.x1 += 10;
    rect.x2 = rect.x1 + 100;
    rect.y1 =rect.y1+60+96+20;
    rect.y2 = rect.y1 + 20;	
	
	  //rt_sprintf(label_text, "maxValue:%s",rt_kprintf_float(maxValue)); 
	  label_setting = rtgui_label_create("1.024S");
		RTGUI_WIDGET_FOREGROUND(label_setting) = Scope_Channel_Color_ch1;
    rtgui_widget_set_rect(RTGUI_WIDGET(label_setting), &rect);
    rtgui_container_add_child(container_scope_setting, RTGUI_WIDGET(label_setting));
		rtgui_object_set_id(RTGUI_OBJECT(label_setting), SIMPLE_TIME_CH1);
		
		rect.x1 += 110;
    rect.x2 = rect.x1 + 100;
	  label_setting = rtgui_label_create("1.024S");
		RTGUI_WIDGET_FOREGROUND(label_setting) = Scope_Channel_Color_ch2;
    rtgui_widget_set_rect(RTGUI_WIDGET(label_setting), &rect);
    rtgui_container_add_child(container_scope_setting, RTGUI_WIDGET(label_setting));
		rtgui_object_set_id(RTGUI_OBJECT(label_setting), SIMPLE_TIME_CH2);
				
		rect.x1 += 110;
    rect.x2 = rect.x1 + 100;
		label_setting = rtgui_label_create("1.024S");
		RTGUI_WIDGET_FOREGROUND(label_setting) = Scope_Channel_Color_ch3;
    rtgui_widget_set_rect(RTGUI_WIDGET(label_setting), &rect);
    rtgui_container_add_child(container_scope_setting, RTGUI_WIDGET(label_setting));
		rtgui_object_set_id(RTGUI_OBJECT(label_setting), SIMPLE_TIME_CH3);
		
    return container_scope_setting;
}
