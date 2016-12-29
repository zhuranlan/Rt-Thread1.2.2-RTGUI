/*
 * 程序清单：DC操作演示
 *
 * 这个例子会在创建出的view上进行DC操作的演示
 */

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
extern void Analysis__onbutton(struct rtgui_object *object, rtgui_event_t *event);
rtgui_scrollbar_t *scope_hbar,*scope_vbar;
struct scope scope_setting={0};
static struct rtgui_timer *timer_update,*timer_close,*scrollbar_update;
unsigned int start_getdata_flag=0,start_loaddata_flag=0;
unsigned int load_data_count_ch1=0,load_data_count_ch2=0,load_data_count_ch3;
q15_t store_data[8192]  __attribute__((at(0X10000000+1024*32)))={0};
q15_t turn_data_temp[8192] __attribute__((at(0X10000000+1024*12)))={0};


rtgui_progressbar_t *loaddata_hbar;
extern struct rtgui_notebook *the_notebook;
struct rtgui_win *setscope_win;
rtgui_checkbox_t *ch1_checkbox,*ch2_checkbox,*ch3_checkbox,*ch1_checkbox_1,*ch2_checkbox_1,*ch3_checkbox_1;
rtgui_slider_t *scope_slider_v,*scope_slider_h;
int current_scrollbar_valve=0,current_scrollbar_valve_v_ch1=0,current_scrollbar_valve_v_ch2=0,current_scrollbar_valve_v_ch3;
unsigned char complete_flag_ch1=0,complete_flag_ch2=0,complete_flag_ch3=0;
char label_text[200];
unsigned int rate_ch1=10,rate_ch2=10,rate_ch3=10;
int X_Step_ch1=1,X_Step_ch2=1,X_Step_ch3=1,X_LITTLE_ch1=1,X_LITTLE_ch2=1,X_LITTLE_ch3=1;
int Y_middle_ch1=120,Y_middle_ch2=120,Y_middle_ch3=120;
extern unsigned char FFT_Open_flag;
extern void dc_fft_event_handler(struct rtgui_dc *analyze_dc);
extern char * rt_kprintf_float(double data);
static struct rtgui_listbox_item Sope_data_choice[] =
{
    {"电压A", RT_NULL},
    {"电压B", RT_NULL},
		{"电压C", RT_NULL},
    {"电流A", RT_NULL},
    {"电流B", RT_NULL},
    {"电流C", RT_NULL}, 
    {"直流电压", RT_NULL}, 
};



rtgui_radiobox_t *scope_radiobox;

void GO_TO_Scope(void)
{
	rtgui_notebook_set_current_by_index(the_notebook,2);
}


rt_bool_t dc_event_handler(struct rtgui_object *object, rtgui_event_t *event)
{
  uint32_t i,j;
	q15_t  middle=0;
	q15_t MAX,MIN;
	float M=0;
	 
  struct rtgui_widget *widget = RTGUI_WIDGET(object);


    /* 仅对PAINT事件进行处理 */
    if (event->type == RTGUI_EVENT_PAINT)
    {	
        struct rtgui_dc *dc;
        rtgui_rect_t rect;
        //q15_t *turn_data_temp;
			   //turn_data_temp= (q15_t *) rt_malloc(store_data_number);
        /*
         * 因为用的是demo view，上面本身有一部分控件，所以在绘图时先要让demo view
         * 先绘图
         */
        rtgui_container_event_handler(RTGUI_OBJECT(widget), event);

        /************************************************************************/
        /* 下面的是DC的操作                                                     */
        /************************************************************************/

        /* 获得控件所属的DC */
        dc = rtgui_dc_begin_drawing(widget);
        /* 如果不能正常获得DC，返回（如果控件或父控件是隐藏状态，DC是获取不成功的） */
        if (dc == RT_NULL)
           return RT_FALSE;

        /* 获得demo view允许绘图的区域 */
        view_get_logic_rect(RTGUI_CONTAINER(widget), &rect);
				if(FFT_Open_flag==1)
				{
        dc_fft_event_handler(dc);
					
				}
				else if(FFT_Open_flag==0)
				{
					
        /* 画一个圆角矩形 示波器的底色*/	
        rect.x1 = 0;
				rect.x2 = rect.x1+360;
        rect.y1 = 0;
        rect.y2 = rect.y1+240;
        RTGUI_DC_FC(dc) = RTGUI_RGB(0, 0, 0);
        rtgui_dc_fill_round_rect(dc, &rect, 0);
				
				/*绘制示波器格子线*/
				RTGUI_DC_FC(dc) = RTGUI_RGB(105, 105, 105);
				for(i=0;i<6;i++)
        rtgui_dc_draw_hline(dc, 0, 360, 40+40*i);
				
				for(i=0;i<9;i++)
				rtgui_dc_draw_vline(dc,40*i,0,250);
				

        				
		    if(scope_setting.ch1_choice==1&&complete_flag_ch1==1)		
		  {   
				for(i=0;i<8192;i++)
				turn_data_temp[i]=0;
				
				for(i=0;i<power_data.ch1_data_length;i++)
				turn_data_temp[i]=store_data[i];
		
			
				
				arm_max_q15(turn_data_temp, power_data.ch1_data_length, &MAX, &i); 
				arm_min_q15(turn_data_temp, power_data.ch1_data_length, &MIN, &i);

				if(MIN<0)
				{
					for(i=0;i<power_data.ch1_data_length;i++)
					{
					turn_data_temp[i] =turn_data_temp[i]-MIN;
					}
				}
//				rt_kprintf("MAX:%d\n",MAX);
//			  rt_kprintf("MIN:%d\n",MIN);

				
//					for(i=0;i<power_data.ch1_data_length;i++)
//				{
//					M=turn_data_temp[i]*(3000/MAX);
//					rt_kprintf("turn_data_temp[%d]=%s \n",i,rt_kprintf_float(turn_data_temp[i]));
//					turn_data_temp[i] =(unsigned int)M;
//					rt_kprintf("turn_data_temp[%d]=%s \n",i,rt_kprintf_float(turn_data_temp[i]));
//				}
		
				
			
				
				arm_max_q15(turn_data_temp, power_data.ch1_data_length, &MAX, &i); 
				arm_min_q15(turn_data_temp, power_data.ch1_data_length, &MIN, &i);
//				rt_kprintf("MAX:%d\n",MAX);
//			  rt_kprintf("MIN:%d\n",MIN);
				
				middle=(MIN+MAX)/2;

//				rt_kprintf("middle:%d\n",i,middle);
				for(i=0;i<power_data.ch1_data_length;i++)
				{
					if(turn_data_temp[i]>middle)
					turn_data_temp[i]=Y_middle_ch1+(turn_data_temp[i]-middle)/rate_ch1;
					else
					turn_data_temp[i]=Y_middle_ch1-(-turn_data_temp[i]+middle)/rate_ch1;
					
					if(turn_data_temp[i]>Y_middle_ch1)
						turn_data_temp[i]=Y_middle_ch1-(turn_data_temp[i]-Y_middle_ch1);
					else
						turn_data_temp[i]=Y_middle_ch1+(-turn_data_temp[i]+Y_middle_ch1);		
         //rt_kprintf("[%d]%s \n",i,rt_kprintf_float(turn_data_temp[i]));
				}
				
			  RTGUI_DC_FC(dc) = Scope_Channel_Color_ch1;
			  j=0;
				for(i=current_scrollbar_valve*4;i<(current_scrollbar_valve*4+359*X_LITTLE_ch1);i+=X_LITTLE_ch1)
				{

					if(i+1-X_Step_ch1<1600)
					if(turn_data_temp[i-X_Step_ch1]<=250&&turn_data_temp[i+1-X_Step_ch1]<=250&&j<360&&(i+X_LITTLE_ch1)<1600)
					rtgui_dc_draw_line(dc,j,turn_data_temp[i],j+X_Step_ch1,turn_data_temp[i+X_LITTLE_ch1]);
					j+=X_Step_ch1;	
				}			
				
	  }
			

		
	  if(scope_setting.ch2_choice==1&&complete_flag_ch2==1)						
		{   

				for(i=0;i<8192;i++)
				turn_data_temp[i]=0;
			 middle=0;

				for(i=power_data.ch1_data_length;i<(power_data.ch2_data_length+power_data.ch1_data_length);i++)
				turn_data_temp[i-power_data.ch1_data_length]=store_data[i];
				
				arm_max_q15(turn_data_temp, power_data.ch2_data_length, &MAX, &i); 
				arm_min_q15(turn_data_temp, power_data.ch2_data_length, &MIN, &i);
				if(MIN<0)
				{
					for(i=0;i<power_data.ch2_data_length;i++)
					turn_data_temp[i] =turn_data_temp[i]-MIN;
				}
				
//				 arm_max_q15(turn_data_temp, power_data.ch2_data_length, &MAX, &i); 

//					for(i=0;i<store_data_number;i++)
//					turn_data_temp[i] =turn_data_temp[i]*(3000/MAX);
				

				arm_max_q15(turn_data_temp, power_data.ch2_data_length, &MAX, &i); 
				arm_min_q15(turn_data_temp, power_data.ch2_data_length, &MIN, &i);
				
				
				middle=(MIN+MAX)/2;


				for(i=0;i<power_data.ch2_data_length;i++)
				{
					if(turn_data_temp[i]>middle)
					turn_data_temp[i]=Y_middle_ch2+(turn_data_temp[i]-middle)/rate_ch2;
					else
					turn_data_temp[i]=Y_middle_ch2-(-turn_data_temp[i]+middle)/rate_ch2;
					
					if(turn_data_temp[i]>Y_middle_ch2)
						turn_data_temp[i]=Y_middle_ch2-(turn_data_temp[i]-Y_middle_ch2);
					else
						turn_data_temp[i]=Y_middle_ch2+(-turn_data_temp[i]+Y_middle_ch2);						
				}
			
			
			 j=0;
			 RTGUI_DC_FC(dc) = Scope_Channel_Color_ch2;
			
				for(i=current_scrollbar_valve*4;i<(current_scrollbar_valve*4+359*X_LITTLE_ch2);i+=X_LITTLE_ch2)
				{

					if(i+1-X_Step_ch2<1600)
					if(turn_data_temp[i-X_Step_ch2]<=250&&turn_data_temp[i+1-X_Step_ch2]<=250&&j<360&&(i+X_LITTLE_ch2)<1600)
					rtgui_dc_draw_line(dc,j,turn_data_temp[i],j+X_Step_ch2,turn_data_temp[i+X_LITTLE_ch2]);
					j+=X_Step_ch2;	
				}	
	  }
		
		
			  if(scope_setting.ch3_choice==1&&complete_flag_ch3==1)		
		{   
							for(i=0;i<8192;i++)
				turn_data_temp[i]=0;
			   middle=0;

				for(i=(power_data.ch2_data_length+power_data.ch1_data_length);i<(power_data.ch3_data_length+power_data.ch2_data_length+power_data.ch1_data_length);i++)
				turn_data_temp[i-(power_data.ch2_data_length+power_data.ch1_data_length)]=store_data[i];
				
				arm_max_q15(turn_data_temp, power_data.ch3_data_length, &MAX, &i); 
				arm_min_q15(turn_data_temp, power_data.ch3_data_length, &MIN, &i);
				if(MIN<0)
				{
					for(i=0;i<power_data.ch3_data_length;i++)
					turn_data_temp[i] =turn_data_temp[i]-MIN;
				}
				
//				 arm_max_q15(turn_data_temp, power_data.ch3_data_length, &MAX, &i); 
//					for(i=0;i<store_data_number;i++)
//					turn_data_temp[i] =turn_data_temp[i]*(3000/MAX);

				
			
			
				arm_max_q15(turn_data_temp, power_data.ch3_data_length, &MAX, &i); 
				arm_min_q15(turn_data_temp, power_data.ch3_data_length, &MIN, &i);
				
				
				middle=(MIN+MAX)/2;


				for(i=0;i<power_data.ch3_data_length;i++)
				{
					if(turn_data_temp[i]>middle)
					turn_data_temp[i]=Y_middle_ch3+(turn_data_temp[i]-middle)/rate_ch3;
					else
					turn_data_temp[i]=Y_middle_ch3-(-turn_data_temp[i]+middle)/rate_ch3;
					
					if(turn_data_temp[i]>Y_middle_ch3)
						turn_data_temp[i]=Y_middle_ch3-(turn_data_temp[i]-Y_middle_ch3);
					else
						turn_data_temp[i]=Y_middle_ch3+(-turn_data_temp[i]+Y_middle_ch3);		
				
				}
				
			j=0;
			 RTGUI_DC_FC(dc) = Scope_Channel_Color_ch3;
			 for(i=current_scrollbar_valve*4;i<(current_scrollbar_valve*4+359*X_LITTLE_ch3);i+=X_LITTLE_ch3)
				{
					if(i+1-X_Step_ch3<1600)
					if(turn_data_temp[i-X_Step_ch3]<=250&&turn_data_temp[i+1-X_Step_ch3]<=250&&j<360&&(i+X_LITTLE_ch3)<1600)
					rtgui_dc_draw_line(dc,j,turn_data_temp[i],j+X_Step_ch3,turn_data_temp[i+X_LITTLE_ch3]);
					j+=X_Step_ch3;	
				}	
	  }
		//rt_free(turn_data_temp);//释放RAM


/*在这里添加数值的显示*/
		
		rect.x1=0;
		//rect.x2=rect.x2+100;
		rect.y1=0;
		rect.y2=rect.y1+16;
		if(scope_setting.ch1_choice==1&&power_data.ch1_data_length>0)
		{
							for(i=0;i<8192;i++)
				turn_data_temp[i]=0;

		for(i=0;i<power_data.ch1_data_length;i++)
		turn_data_temp[i]=store_data[i];
			MAX=0;
			MIN=0;
			
		arm_max_q15(turn_data_temp, power_data.ch1_data_length, &MAX, &i); 
		arm_min_q15(turn_data_temp, power_data.ch1_data_length, &MIN, &i);

		RTGUI_DC_FC(dc) = Scope_Channel_Color_ch1;
		rt_sprintf(label_text, "MAX:%d",MAX); 
		rect.x2=rect.x2+sizeof(label_text)*8;
		rtgui_dc_draw_text(dc, label_text, &rect);
			
		rect.y1+=16;
		rect.y2=rect.y1+16;
		rt_sprintf(label_text, "MIN:%d",MIN); 
		rect.x2=rect.x2+sizeof(label_text)*8;
		rtgui_dc_draw_text(dc, label_text, &rect);
		}
		
    if(scope_setting.ch2_choice==1&&power_data.ch2_data_length>0)
		{
		for(i=0;i<8192;i++)
		turn_data_temp[i]=0;
		for(i=power_data.ch1_data_length;i<(power_data.ch2_data_length+power_data.ch1_data_length);i++)
		turn_data_temp[i-power_data.ch1_data_length]=store_data[i];
		arm_max_q15(turn_data_temp, power_data.ch2_data_length, &MAX, &i); 
		arm_min_q15(turn_data_temp, power_data.ch2_data_length, &MIN, &i);
		rect.y1+=16;
		rect.y2=rect.y1+16;
		RTGUI_DC_FC(dc) = Scope_Channel_Color_ch2;
		rt_sprintf(label_text, "MAX:%d",MAX); 
		rect.x2=rect.x2+sizeof(label_text)*8;
		rtgui_dc_draw_text(dc, label_text, &rect);
			
		rect.y1+=16;
		rect.y2=rect.y1+16;
		rt_sprintf(label_text, "MIN:%d",MIN); 
		rect.x2=rect.x2+sizeof(label_text)*8;
		rtgui_dc_draw_text(dc, label_text, &rect);
		}
		
		if(scope_setting.ch3_choice==1&&power_data.ch3_data_length>0)
		{
		for(i=0;i<8192;i++)
		turn_data_temp[i]=0;
		for(i=(power_data.ch1_data_length+power_data.ch2_data_length);i<(power_data.ch1_data_length+power_data.ch2_data_length+power_data.ch3_data_length);i++)
		turn_data_temp[i-(power_data.ch1_data_length+power_data.ch2_data_length)]=store_data[i];
		arm_max_q15(turn_data_temp, power_data.ch3_data_length, &MAX, &i); 
		arm_min_q15(turn_data_temp, power_data.ch3_data_length, &MIN, &i);	
		rect.y1+=16;
		rect.y2=rect.y1+16;
		RTGUI_DC_FC(dc) = Scope_Channel_Color_ch3;
		rt_sprintf(label_text, "MAX:%d",MAX); 
		rect.x2=rect.x2+sizeof(label_text)*8;
		rtgui_dc_draw_text(dc, label_text, &rect);
			
		rect.y1+=16;
		rect.y2=rect.y1+16;
		rt_sprintf(label_text, "MIN:%d",MIN); 
		rect.x2=rect.x2+sizeof(label_text)*8;
		rtgui_dc_draw_text(dc, label_text, &rect);
		}
		
	  
	}
				
        /* 绘图完成 */
        rtgui_dc_end_drawing(dc);
    }
    else
    {
        /* 其他事件，调用默认的事件处理函数 */
        return rtgui_container_event_handler(object, event);
			  rt_kprintf("move here \n");
    }
		


    return RT_FALSE;
}

static void close_timer_data(struct rtgui_timer *timer, void *parameter)
{
    if (timer_update != RT_NULL)
    {
        /* 停止并删除定时器 */
        rtgui_timer_stop(timer_update);
        rtgui_timer_destory(timer_update);

        timer_update = RT_NULL;
  }
}


static void update_data(struct rtgui_timer *timer, void *parameter)
{
	
	struct rtgui_label *label;
	if(load_data_count_ch1>0)
	{
		RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(loaddata_hbar)) = Scope_Channel_Color_ch1;
  		if(power_data.ch1_data_length==4096)
  rtgui_progressbar_set_value(loaddata_hbar, load_data_count_ch1/2);
		else if(power_data.ch1_data_length==8192)
			rtgui_progressbar_set_value(loaddata_hbar, load_data_count_ch1/4);
		else
				rtgui_progressbar_set_value(loaddata_hbar, load_data_count_ch1);
		
		
	if(load_data_count_ch1<power_data.ch1_data_length)
	{
	label = RTGUI_LABEL(rtgui_get_self_object(LOADDATA_PRO_ID));
	rt_sprintf(label_text, "CH1:%d%", 100*load_data_count_ch1/power_data.ch1_data_length);
  rtgui_label_set_text(label, label_text);
	rtgui_widget_update(RTGUI_WIDGET(label));
	}
	else if(load_data_count_ch1==power_data.ch1_data_length)
	{
		complete_flag_ch1=1;
	load_data_count_ch1=0;	
	label = RTGUI_LABEL(rtgui_get_self_object(LOADDATA_PRO_ID));
	rt_sprintf(label_text, "OK!!");
  rtgui_label_set_text(label, label_text);
	rtgui_widget_update(RTGUI_WIDGET(label));
	//rtgui_notebook_set_current_by_index(the_notebook,2);
		GO_TO_Scope();
		
			
	}
}
	else if(load_data_count_ch2>0)
	{
		RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(loaddata_hbar)) = Scope_Channel_Color_ch2;
		if(power_data.ch2_data_length==4096)
  rtgui_progressbar_set_value(loaddata_hbar, load_data_count_ch2/2);
		else if(power_data.ch2_data_length==8192)
			rtgui_progressbar_set_value(loaddata_hbar, load_data_count_ch2/4);
		else
				rtgui_progressbar_set_value(loaddata_hbar, load_data_count_ch2);
	if(load_data_count_ch2<power_data.ch2_data_length)
	{
	label = RTGUI_LABEL(rtgui_get_self_object(LOADDATA_PRO_ID));
	rt_sprintf(label_text, "CH2:%d%", 100*load_data_count_ch2/power_data.ch2_data_length);
  rtgui_label_set_text(label, label_text);
	rtgui_widget_update(RTGUI_WIDGET(label));
	}
	else if(load_data_count_ch2==power_data.ch2_data_length)
	{
  complete_flag_ch2=1;
	load_data_count_ch2=0;	
	label = RTGUI_LABEL(rtgui_get_self_object(LOADDATA_PRO_ID));
	rt_sprintf(label_text, "OK!!");
  rtgui_label_set_text(label, label_text);
	rtgui_widget_update(RTGUI_WIDGET(label));	
	//rtgui_notebook_set_current_by_index(the_notebook,2);	
		GO_TO_Scope();
	
	}
}
	
	else if(load_data_count_ch3>0)
	{
		RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(loaddata_hbar)) = Scope_Channel_Color_ch3;
		
		if(power_data.ch3_data_length==4096)
  rtgui_progressbar_set_value(loaddata_hbar, load_data_count_ch3/2);
		else if(power_data.ch3_data_length==8192)
			rtgui_progressbar_set_value(loaddata_hbar, load_data_count_ch3/4);
		else
				rtgui_progressbar_set_value(loaddata_hbar, load_data_count_ch3);
			
	if(load_data_count_ch3<power_data.ch3_data_length)
	{
	label = RTGUI_LABEL(rtgui_get_self_object(LOADDATA_PRO_ID));
	rt_sprintf(label_text, "CH3:%d%", 100*load_data_count_ch3/power_data.ch3_data_length);
  rtgui_label_set_text(label, label_text);
	rtgui_widget_update(RTGUI_WIDGET(label));
		
	}
	else if(load_data_count_ch3==power_data.ch3_data_length)
	{
		complete_flag_ch3=1;
	 load_data_count_ch3=0;	
	label = RTGUI_LABEL(rtgui_get_self_object(LOADDATA_PRO_ID));
	rt_sprintf(label_text, "OK!!");
  rtgui_label_set_text(label, label_text);
	rtgui_widget_update(RTGUI_WIDGET(label));
	//rtgui_notebook_set_current_by_index(the_notebook,2);	
		GO_TO_Scope();
 
	}
	else if(load_data_count_ch1==0&&load_data_count_ch2==0&&load_data_count_ch3==0)
	{
		//rtgui_notebook_set_current_by_index(the_notebook,2);	
  timer_close = rtgui_timer_create(0, RT_TIMER_FLAG_ONE_SHOT, close_timer_data, RT_NULL);
  rtgui_timer_start(timer_close);

	}
}
		
}
void start_loaddata_(void)
{
  start_loaddata_flag=1;
  /* 创建一个定时器 */
  timer_update = rtgui_timer_create(40, RT_TIMER_FLAG_PERIODIC, update_data, RT_NULL);
  rtgui_timer_start(timer_update);
}
static void start_getdata_onbutton(struct rtgui_object *object, rtgui_event_t *event)
{
	int count;
	struct rtgui_label *label;
	start_getdata_flag=1;
	//char label_text[100];
	count=0;
	while(start_getdata_flag==1&&count<20)
	{
		count++;
		rt_thread_delay(2);
	}
	if(start_getdata_flag==0)
	{
	label = RTGUI_LABEL(rtgui_get_self_object(LOADDATA_PRO_ID));
	rt_sprintf(label_text, "READY!!");
  rtgui_label_set_text(label, label_text);
	rtgui_widget_update(RTGUI_WIDGET(label));
		
	/*发出指令开始上传数据*/
  start_loaddata_();
	}
		
}

int enter_update_flag_h,enter_update_flag_v_ch1=0,enter_update_flag_v_ch2=0,enter_update_flag_v_ch3=0;
extern unsigned int current_scrollbar_valve_fft;
extern rt_uint32_t get_scrollbar_pos(rtgui_scrollbar_t* bar);
static void scrollbar_t(struct rtgui_timer *timer, void *parameter)
{
	int temp;
	if(FFT_Open_flag==0)
	{
	if(current_scrollbar_valve!=get_scrollbar_pos(scope_hbar)&&enter_update_flag_h==0)
	{
		enter_update_flag_h=1;
		current_scrollbar_valve=get_scrollbar_pos(scope_hbar);
		GO_TO_Scope();
		//rtgui_notebook_set_current_by_index(the_notebook,2);
		//rt_kprintf("current_scrollbar_valve:%d \n",current_scrollbar_valve); 
		enter_update_flag_h=0;
	}
	
	if(rtgui_checkbox_get_checked(ch1_checkbox_1)==1)
	if(current_scrollbar_valve_v_ch1!=get_scrollbar_pos(scope_vbar)&&enter_update_flag_v_ch1==0)
	{
		enter_update_flag_v_ch1=1;
		temp=get_scrollbar_pos(scope_vbar);
		
		if(current_scrollbar_valve_v_ch1>temp)
      Y_middle_ch1-=current_scrollbar_valve_v_ch1-temp;
	  else
      Y_middle_ch1+=-current_scrollbar_valve_v_ch1+temp;
		
//		if(current_scrollbar_valve_v>92)
//		Y_middle_ch1+=(current_scrollbar_valve_v-92);
//		else 
//			Y_middle_ch1-=(92-current_scrollbar_valve_v);
		
		//rtgui_notebook_set_current_by_index(the_notebook,2);
		GO_TO_Scope();
		//rt_kprintf("current_scrollbar_valve_v:%d \n",current_scrollbar_valve_v); 
		current_scrollbar_valve_v_ch1=temp;
		enter_update_flag_v_ch1=0;
	}
	
	
		if(rtgui_checkbox_get_checked(ch2_checkbox_1)==1)
	if(current_scrollbar_valve_v_ch2!=get_scrollbar_pos(scope_vbar)&&enter_update_flag_v_ch2==0)
	{
		enter_update_flag_v_ch2=1;
		temp=get_scrollbar_pos(scope_vbar);
		
		if(current_scrollbar_valve_v_ch2>temp)
      Y_middle_ch2-=current_scrollbar_valve_v_ch2-temp;
	  else
      Y_middle_ch2+=-current_scrollbar_valve_v_ch2+temp;
		
		//rtgui_notebook_set_current_by_index(the_notebook,2);
		GO_TO_Scope();

		current_scrollbar_valve_v_ch2=temp;
		enter_update_flag_v_ch2=0;
	}
	
	
	if(rtgui_checkbox_get_checked(ch3_checkbox_1)==1)
	if(current_scrollbar_valve_v_ch3!=get_scrollbar_pos(scope_vbar)&&enter_update_flag_v_ch3==0)
	{
		enter_update_flag_v_ch3=1;
		temp=get_scrollbar_pos(scope_vbar);
		
		if(current_scrollbar_valve_v_ch3>temp)
      Y_middle_ch3-=current_scrollbar_valve_v_ch3-temp;
	  else
      Y_middle_ch3+=-current_scrollbar_valve_v_ch3+temp;
		
		//rtgui_notebook_set_current_by_index(the_notebook,2);
		GO_TO_Scope();

		current_scrollbar_valve_v_ch3=temp;
		enter_update_flag_v_ch3=0;
	}
}
	

}




extern void GO_TO_Scope_Setting(void);
static void set_scope_onbutton(struct rtgui_object *object, rtgui_event_t *event)
{
 GO_TO_Scope_Setting();//跳转到示波器设置页面
}
extern void screenshot(const char *filename);

#define SCREENSHOT_PATH "/SD/SCREEN"
static void Screenshot_onbutton(struct rtgui_object *object, rtgui_event_t *event)
{
	DIR *dir;
	struct rtgui_label *label;
	static char fullpath[256];
	static char path_screen[100];
	int count_file;
	static char all_fille[100]={0};
	int i,j;
	count_file=0;

	dir = opendir(SCREENSHOT_PATH);
	if(dir!=RT_NULL)
		{
		struct dirent* dirent;
		struct stat s;
		
			for(i=0;i<100;i++)
			all_fille[i]=0;
		do
		{
			dirent = readdir(dir);
			/*如果文件夹为空直接截屏存储*/
			if (dirent == RT_NULL) 
				break;
	
			rt_memset(&s, 0, sizeof(struct stat));

			/* build full path for each file */
			rt_sprintf(fullpath, "%s/%s", SCREENSHOT_PATH, dirent->d_name);

			stat(fullpath, &s);
			if ( s.st_mode & DFS_S_IFDIR )
			{
				
			}
			else
			{
				for(i=0;i<100;i++)
				{
				 rt_sprintf(path_screen, "%d.BMP",i);
				  if(strcmp(dirent->d_name,path_screen)==0)
					{
						all_fille[count_file]=i;
						count_file++;
					}	
				}
			}
		} while (dirent != RT_NULL);
		closedir(dir);

		
		label = RTGUI_LABEL(rtgui_get_self_object(LOADDATA_PRO_ID));
    rt_sprintf(label_text, ">>>>>>>>");
    rtgui_label_set_text(label, label_text);
	  rtgui_widget_update(RTGUI_WIDGET(label));
		
		{
		int find_flag=1;
			find_flag=1;
		if(count_file<99)
		{
		for(i=1;i<100;i++)
			{
				if(find_flag==1)
				{
				find_flag=0;
		for(j=0;j<count_file;j++)
				{
		if(all_fille[j]==i)
			find_flag=1;
	      }
				if(find_flag==0)
				{
					rt_sprintf(path_screen, "/SD/SCREEN/%d.BMP",i);
					screenshot(path_screen);	
					label = RTGUI_LABEL(rtgui_get_self_object(LOADDATA_PRO_ID));
        	rt_sprintf(label_text, "Bmp OK!!");
          rtgui_label_set_text(label, label_text);
	        rtgui_widget_update(RTGUI_WIDGET(label));
					
				}
			 }	
	    }
		}
		else
		{
	label = RTGUI_LABEL(rtgui_get_self_object(LOADDATA_PRO_ID));
	rt_sprintf(label_text, "Bmp Failed!!");
  rtgui_label_set_text(label, label_text);
	rtgui_widget_update(RTGUI_WIDGET(label));
		}
		for(i=0;i<100;i++)
		path_screen[i]=0;
	 }
		}
		else 
		{
	label = RTGUI_LABEL(rtgui_get_self_object(LOADDATA_PRO_ID));
	rt_sprintf(label_text, "Bmp Failed!!");
  rtgui_label_set_text(label, label_text);
	rtgui_widget_update(RTGUI_WIDGET(label));
		}
}
static void Y_SUB_onbutton(struct rtgui_object *object, rtgui_event_t *event)
{
	if(FFT_Open_flag==0)
	{
	if(rtgui_checkbox_get_checked(ch1_checkbox_1)==1)
	rate_ch1+=1;
	
  if(rtgui_checkbox_get_checked(ch2_checkbox_1)==1)
	rate_ch2+=1;
		
	if(rtgui_checkbox_get_checked(ch3_checkbox_1)==1)
	rate_ch3+=1;
	

	//rtgui_notebook_set_current_by_index(the_notebook,2);
	GO_TO_Scope();
}
}

static void Y_ADD_onbutton(struct rtgui_object *object, rtgui_event_t *event)
{
	if(FFT_Open_flag==0)
	{
	if(rtgui_checkbox_get_checked(ch1_checkbox_1)==1)
	if(rate_ch1>5)
	rate_ch1-=1;
	
	
	if(rtgui_checkbox_get_checked(ch2_checkbox_1)==1)
	if(rate_ch2>5)
	rate_ch2-=1;
	
	if(rtgui_checkbox_get_checked(ch3_checkbox_1)==1)
	if(rate_ch3>5)
	rate_ch3-=1;

	//rtgui_notebook_set_current_by_index(the_notebook,2);
	GO_TO_Scope();
}
}



static void AUTO_onbutton(struct rtgui_object *object, rtgui_event_t *event)
{
if(FFT_Open_flag==0)
{
	 X_Step_ch1=1;
	 X_Step_ch2=1;
   X_Step_ch3=1;
	 X_LITTLE_ch1=1;
	 X_LITTLE_ch2=1;
	 X_LITTLE_ch3=1;
	Y_middle_ch1=120;
	Y_middle_ch2=120;
	Y_middle_ch3=120;
	rate_ch1=10;
	rate_ch2=10;
	rate_ch3=10;
	current_scrollbar_valve_v_ch1=92;
	current_scrollbar_valve_v_ch2=92;
	current_scrollbar_valve_v_ch3=92;
	rtgui_scrollbar_set_value(scope_hbar,0);
	rtgui_scrollbar_set_value(scope_vbar,37);
	//rtgui_notebook_set_current_by_index(the_notebook,2);
	GO_TO_Scope();
}
}
static void X_SUB_onbutton(struct rtgui_object *object, rtgui_event_t *event)
{
if(FFT_Open_flag==0)
{
	
	if(rtgui_checkbox_get_checked(ch1_checkbox_1)==1)
	{
	if(X_Step_ch1>=2)
	X_Step_ch1-=1;
	else if(X_Step_ch1==1)
		X_LITTLE_ch1+=1;
  }
	
	
	if(rtgui_checkbox_get_checked(ch2_checkbox_1)==1)
	{
	if(X_Step_ch2>=2)
	X_Step_ch2-=1;
		else if(X_Step_ch2==1)
		X_LITTLE_ch2+=1;
	}
	
	if(rtgui_checkbox_get_checked(ch3_checkbox_1)==1)
	{
	if(X_Step_ch3>=2)
	X_Step_ch3-=1;
		else if(X_Step_ch3==1)
		X_LITTLE_ch3+=1;
  }
	//rtgui_notebook_set_current_by_index(the_notebook,2);
	GO_TO_Scope();
}
	
}
static void X_ADD_onbutton(struct rtgui_object *object, rtgui_event_t *event)
{
	if(FFT_Open_flag==0)
	{
		if(rtgui_checkbox_get_checked(ch1_checkbox_1)==1)
		{
	  if(X_LITTLE_ch1==1)
	   X_Step_ch1+=1;
		else if(X_LITTLE_ch1>1)
			X_LITTLE_ch1-=1;
	  }
	
	
	if(rtgui_checkbox_get_checked(ch2_checkbox_1)==1)
	{
		if(X_LITTLE_ch2==1)
	   X_Step_ch2+=1;
		else if(X_LITTLE_ch2>1)
			X_LITTLE_ch2-=1;
		}
	
	if(rtgui_checkbox_get_checked(ch3_checkbox_1)==1)
	{
		if(X_LITTLE_ch3==1)
	    X_Step_ch3+=1;
		else if(X_LITTLE_ch3>1)
			X_LITTLE_ch3-=1;
		}
	
	//rtgui_notebook_set_current_by_index(the_notebook,2);
		GO_TO_Scope();
	}
}
extern unsigned char SAVE_DATA_onbutton(struct rtgui_object *object, rtgui_event_t *event);
extern void FFT_onbutton(struct rtgui_object *object, rtgui_event_t *event);
rtgui_container_t *scope_windows(void)
{
	  int i;
	  rtgui_rect_t rect;
	  struct rtgui_label      *label;
    rtgui_container_t *container_scope;
	  struct rtgui_button *button;
	  char label_text[100];
	  rtgui_font_t *font;
	    

    container_scope = view("分析仪");
		 if (container_scope == RT_NULL)
        return RT_NULL;

    rect.x1 = 385;
    rect.x2 = rect.x1 + 45;
    rect.y1 = 25;
    rect.y2 = rect.y1 + 45;

    button = rtgui_button_create("SET");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(container_scope), RTGUI_WIDGET(button));
    rtgui_button_set_onbutton(button, set_scope_onbutton);
		
		rect.y1 += 45;
    rect.y2 = rect.y1 + 45;
    button = rtgui_button_create("START");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(container_scope), RTGUI_WIDGET(button));
    rtgui_button_set_onbutton(button, start_getdata_onbutton);
		
		rect.y1 += 45;
    rect.y2 = rect.y1 + 45;
    button = rtgui_button_create("X+");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(container_scope), RTGUI_WIDGET(button));
		rtgui_button_set_onbutton(button, X_ADD_onbutton);
		
	  rect.y1 += 45;
    rect.y2 = rect.y1 + 45;
    button = rtgui_button_create("Y+");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(container_scope), RTGUI_WIDGET(button));
		rtgui_button_set_onbutton(button, Y_ADD_onbutton);
		
		 rect.y1 += 45;
    rect.y2 = rect.y1 + 45;
    button = rtgui_button_create("FFT");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(container_scope), RTGUI_WIDGET(button));
		rtgui_button_set_onbutton(button, FFT_onbutton);
		
		
		rect.x1 = 385+45;
    rect.x2 = rect.x1 + 45;
    rect.y1 = 25;
    rect.y2 = rect.y1 + 45;

    button = rtgui_button_create("AUTO");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(container_scope), RTGUI_WIDGET(button));
  
		rtgui_button_set_onbutton(button, AUTO_onbutton);
		
		rect.y1 += 45;
    rect.y2 = rect.y1 + 45;
    button = rtgui_button_create("SAVE");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(container_scope), RTGUI_WIDGET(button));
    rtgui_button_set_onbutton(button, SAVE_DATA_onbutton); 
		
		rect.y1 += 45;
    rect.y2 = rect.y1 + 45;
    button = rtgui_button_create("X-");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(container_scope), RTGUI_WIDGET(button));
    rtgui_button_set_onbutton(button, X_SUB_onbutton);
		
	  rect.y1 += 45;
    rect.y2 = rect.y1 + 45;
    button = rtgui_button_create("Y-");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(container_scope), RTGUI_WIDGET(button));
		rtgui_button_set_onbutton(button, Y_SUB_onbutton);
		
	  rect.y1 += 45;
    rect.y2 = rect.y1 + 45;
    button = rtgui_button_create("截屏");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(container_scope), RTGUI_WIDGET(button));
		rtgui_button_set_onbutton(button, Screenshot_onbutton);
		
		
		
		rect.x1   = 385;
    rect.x2   = rect.x1 + 80;
    rect.y1   =45*5-20;
    rect.y2   = rect.y1 + 30;

    rect.y1 += 44;
    rect.y2 = rect.y1 + 12;
		rt_sprintf(label_text, "RATE:%d%",0); 

		label = rtgui_label_create( label_text);				
		font = rtgui_font_refer("asc", 12);
    RTGUI_WIDGET_FONT(label) = font;
	  RTGUI_WIDGET_FOREGROUND(label) = black;
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(container_scope, RTGUI_WIDGET(label));
		rtgui_object_set_id(RTGUI_OBJECT(label), LOADDATA_PRO_ID);
		
    rect.y1 += 16;
    rect.y2 = rect.y1 + 20;
    loaddata_hbar = rtgui_progressbar_create(RTGUI_HORIZONTAL, 2048, &rect);
    RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(loaddata_hbar)) = Scope_Channel_Color_ch1;
    rtgui_container_add_child(container_scope, RTGUI_WIDGET(loaddata_hbar));
	  rtgui_progressbar_set_value(loaddata_hbar, load_data_count_ch1);
		/*移动X轴*/
	 scope_hbar = rtgui_scrollbar_create(container_scope, 0, 240, 20, 360, RTGUI_HORIZONTAL);
	 rtgui_scrollbar_set_line_step(scope_hbar, 1);
	 rtgui_scrollbar_set_page_step(scope_hbar, 5);
	 rtgui_scrollbar_set_range(scope_hbar, 80);
	 //rtgui_scrollbar_set_value(scope_hbar,10);
	 current_scrollbar_valve=get_scrollbar_pos(scope_hbar);
	 current_scrollbar_valve_fft=get_scrollbar_pos(scope_hbar);
	 //rt_kprintf("%d \n",get_scrollbar_pos(scope_hbar)); 


			/*移动Y轴*/
	 scope_vbar = rtgui_scrollbar_create(container_scope,  360,0, 20, 240, RTGUI_VERTICAL);
	 rtgui_scrollbar_set_line_step(scope_vbar, 1);
	 rtgui_scrollbar_set_page_step(scope_vbar, 5);
	 rtgui_scrollbar_set_range(scope_vbar, 80);
	 //rtgui_scrollbar_set_value(scope_hbar,10);
	 current_scrollbar_valve_v_ch1=92;
	 current_scrollbar_valve_v_ch2=92;
	 current_scrollbar_valve_v_ch3=92;
	 rtgui_scrollbar_set_value(scope_vbar,37);
	
	
    rect.x1 = 310;
    rect.x2 = rect.x1 +50;
    rect.y1 =25;
    rect.y2 = rect.y1 + 20;	
		ch1_checkbox_1 = rtgui_checkbox_create("CH1", RT_FALSE);
		RTGUI_WIDGET_BACKGROUND(ch1_checkbox_1) = black;
	  RTGUI_WIDGET_FOREGROUND(ch1_checkbox_1) = Scope_Channel_Color_ch1;
    rtgui_widget_set_rect(RTGUI_WIDGET(ch1_checkbox_1), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(container_scope), RTGUI_WIDGET(ch1_checkbox_1));
		
		rect.y1 +=20;
    rect.y2 = rect.y1 + 20;	
		ch2_checkbox_1 = rtgui_checkbox_create("CH2", RT_FALSE);
		RTGUI_WIDGET_BACKGROUND(ch2_checkbox_1) = black;
	  RTGUI_WIDGET_FOREGROUND(ch2_checkbox_1) = Scope_Channel_Color_ch2;
    rtgui_widget_set_rect(RTGUI_WIDGET(ch2_checkbox_1), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(container_scope), RTGUI_WIDGET(ch2_checkbox_1));
		
		rect.y1 +=20;
    rect.y2 = rect.y1 + 20;	
		ch3_checkbox_1 = rtgui_checkbox_create("CH3", RT_FALSE);
		RTGUI_WIDGET_BACKGROUND(ch3_checkbox_1) = black;
	  RTGUI_WIDGET_FOREGROUND(ch3_checkbox_1) = Scope_Channel_Color_ch3;
    rtgui_widget_set_rect(RTGUI_WIDGET(ch3_checkbox_1), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(container_scope), RTGUI_WIDGET(ch3_checkbox_1));

		for(i=0;i<(power_data.ch1_data_length+power_data.ch2_data_length+power_data.ch3_data_length);i++)
		store_data[i]=0;

		//rt_kprintf("%d \n",(power_data.ch1_data_length+power_data.ch2_data_length+power_data.ch3_data_length));

     scrollbar_update = rtgui_timer_create(200, RT_TIMER_FLAG_PERIODIC, scrollbar_t, RT_NULL);
     rtgui_timer_start(scrollbar_update);

     rtgui_object_set_event_handler(RTGUI_OBJECT(container_scope), dc_event_handler);
     rtgui_object_set_id(RTGUI_OBJECT(container_scope),SCOPE_PANEL_ID);
     return container_scope;
}
