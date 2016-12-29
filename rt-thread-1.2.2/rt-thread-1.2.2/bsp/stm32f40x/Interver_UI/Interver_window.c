/*
 * 程序清单：窗口演示
 *
 * 这个例子会先创建出一个演示用的container，当点击上面的按钮时会不同的模式创建窗口
 */

#include <rtgui/rtgui.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/window.h>
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/button.h>
#include <string.h>
#include "view.h"
#include "Interver_RTU.h"
#include <rtgui/widgets/radiobox.h>
#include <rtgui/widgets/staticline.h>
#include <rtgui/dc.h>
#include <rtgui/dc_hw.h>
#include <rtgui/widgets/combobox.h>
#include <rtgui/widgets/panel.h>
extern int Current_RTU_STATUS;
static struct rtgui_listbox_item Slave_choice[] =
{
    {"RTU_SLAVE0", RT_NULL},
    {"RTU_SLAVE1", RT_NULL},
    {"RTU_SLAVE2", RT_NULL},
    {"RTU_SLAVE3", RT_NULL},
    {"RTU_SLAVE4", RT_NULL},
};

rtgui_radiobox_t *radiobox,*radiobox1;


static struct rtgui_timer *timer;
static char label_text[100];

extern struct rtgui_win *main_win;
static char *radio_item_v[5] =
{
    "调制比",
    "电压",
    "电流",
    "保留",
    "保留"
};
/*设置radio中的选项*/
static char *radio_item_h[5] =
{
    "1", "5", "10","100","1000"
};
static unsigned int step_data[5]={1,5,10,100,1000};


static void up_onbutton(struct rtgui_object *object, rtgui_event_t *event)
{

	if(rtgui_radiobox_get_selection(radiobox)==0)
	power_data.SET_DATA+=step_data[0];
	else if(rtgui_radiobox_get_selection(radiobox)==1)
	power_data.SET_DATA+=step_data[1];
		else if(rtgui_radiobox_get_selection(radiobox)==2)
	power_data.SET_DATA+=step_data[2];
				else if(rtgui_radiobox_get_selection(radiobox)==3)
	power_data.SET_DATA+=step_data[3];
								else if(rtgui_radiobox_get_selection(radiobox)==4)
	power_data.SET_DATA+=step_data[4];
				
}
static void down_onbutton(struct rtgui_object *object, rtgui_event_t *event)
{

	if((rtgui_radiobox_get_selection(radiobox)==0)&&(power_data.SET_DATA>=step_data[0]))
	power_data.SET_DATA-=step_data[0];
	else if((rtgui_radiobox_get_selection(radiobox)==1)&&(power_data.SET_DATA>=step_data[1]))
	power_data.SET_DATA-=step_data[1];
		else if((rtgui_radiobox_get_selection(radiobox)==2)&&(power_data.SET_DATA>=step_data[2]))
	power_data.SET_DATA-=step_data[2];
				else if((rtgui_radiobox_get_selection(radiobox)==3)&&(power_data.SET_DATA>=step_data[3]))
	power_data.SET_DATA-=step_data[3];
				else if((rtgui_radiobox_get_selection(radiobox)==4)&&(power_data.SET_DATA>=step_data[4]))
	power_data.SET_DATA-=step_data[4];
				
}
int send_flag=0;
static void ok_onbutton(struct rtgui_object *object, rtgui_event_t *event)
{
	if(rtgui_radiobox_get_selection(radiobox1)==0)
		send_flag=1;
}



static rt_bool_t _on_show_status(struct rtgui_object *object, struct rtgui_event *event)
{
	static char image_path[128]="/PICTURE/LINKDOWN.HDC ";
	static char image_path2[128]="/PICTURE/LINKUP.HDC ";
	if (event->type == RTGUI_EVENT_PAINT)
	{
    struct rtgui_dc *dc;
    struct rtgui_rect rect;
		struct rtgui_panel *panel;
		struct rtgui_image *image;
		
		panel = RTGUI_PANEL(object);
    rtgui_widget_get_rect(RTGUI_WIDGET(object), &rect);
		

    dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(object));
    if (dc == RT_NULL) return RT_FALSE;
    rtgui_dc_fill_rect(dc, &rect);

		if(Current_RTU_STATUS==0)
		image = rtgui_image_create(image_path, RT_TRUE);
		else if(Current_RTU_STATUS==1)
			image = rtgui_image_create(image_path2, RT_TRUE);
			
		if (image != RT_NULL)
		{
			rtgui_image_blit(image, dc, RT_NULL);
			rtgui_image_destroy(image);
		}
		else
		{
			rt_kprintf("open image:%s failed!\n", image_path);
		}

		rtgui_dc_draw_border(dc, &rect, panel->border_style);
        /* paint on each child */
        rtgui_container_dispatch_event(RTGUI_CONTAINER(panel), event);

        rtgui_dc_end_drawing(dc);
		return RT_FALSE;
	}

	return rtgui_panel_event_handler(object, event);
}
rtgui_container_t *container;
/* 配置控制面板主界面*/
static void update_data(struct rtgui_timer *timer, void *parameter)
{
    struct rtgui_label *label;
	
    label = RTGUI_LABEL(rtgui_get_self_object(VOLTAGE_A_ID));
    rt_sprintf(label_text, "%dV", power_data.ACV_A);
    rtgui_label_set_text(label, label_text);
    rtgui_widget_update(RTGUI_WIDGET(label));
	
	  label = RTGUI_LABEL(rtgui_get_self_object(VOLTAGE_B_ID));
    rt_sprintf(label_text, "%dV", power_data.ACV_B);
    rtgui_label_set_text(label, label_text);
    rtgui_widget_update(RTGUI_WIDGET(label));
	
	
	   label = RTGUI_LABEL(rtgui_get_self_object(VOLTAGE_C_ID));
    rt_sprintf(label_text, "%dV", power_data.ACV_C);
    rtgui_label_set_text(label, label_text);
    rtgui_widget_update(RTGUI_WIDGET(label));
		
		
		
		label = RTGUI_LABEL(rtgui_get_self_object(CURRENT_A_ID));
    rt_sprintf(label_text, "%dMA", power_data.ACC_A);
    /* 设置标签文本并更新控件 */
    rtgui_label_set_text(label, label_text);
    rtgui_widget_update(RTGUI_WIDGET(label));
		
		
		
		label = RTGUI_LABEL(rtgui_get_self_object(CURRENT_B_ID));
    rt_sprintf(label_text, "%dMA", power_data.ACC_B);
    rtgui_label_set_text(label, label_text);
    rtgui_widget_update(RTGUI_WIDGET(label));
		
		
		label = RTGUI_LABEL(rtgui_get_self_object(CURRENT_C_ID));
    rt_sprintf(label_text, "%dMA", power_data.ACC_C);
    rtgui_label_set_text(label, label_text);
    rtgui_widget_update(RTGUI_WIDGET(label));
		
		label = RTGUI_LABEL(rtgui_get_self_object(VOLTAGE_Z_ID));
		rt_sprintf(label_text, "%d.%dV", power_data.DCV_Z/10,power_data.DCV_Z%10);
    rtgui_label_set_text(label, label_text);
		rtgui_widget_update(RTGUI_WIDGET(label));
		
		if(rtgui_radiobox_get_selection(radiobox1)==0)
		{
		label = RTGUI_LABEL(rtgui_get_self_object(SET_DATA_ID));
			if(power_data.SET_DATA%100<=9)
				rt_sprintf(label_text, "%d.%02x%", power_data.SET_DATA/100,power_data.SET_DATA%100);
			else
        rt_sprintf(label_text, "%d.%d%", power_data.SET_DATA/100,power_data.SET_DATA%100);
    /* 设置标签文本并更新控件 */
    rtgui_label_set_text(label, label_text);
		rtgui_widget_update(RTGUI_WIDGET(label));
		}
		else if(rtgui_radiobox_get_selection(radiobox1)==1)
		{
		label = RTGUI_LABEL(rtgui_get_self_object(SET_DATA_ID));
        rt_sprintf(label_text, "%dV", power_data.SET_DATA);
    /* 设置标签文本并更新控件 */
    rtgui_label_set_text(label, label_text);
		rtgui_widget_update(RTGUI_WIDGET(label));
		}
	  else if(rtgui_radiobox_get_selection(radiobox1)==2)
		{
		label = RTGUI_LABEL(rtgui_get_self_object(SET_DATA_ID));
        rt_sprintf(label_text, "%dMA", power_data.SET_DATA);
    /* 设置标签文本并更新控件 */
    rtgui_label_set_text(label, label_text);
		rtgui_widget_update(RTGUI_WIDGET(label));
		}
		
    /*更新从下位机获取的调至比*/
		label = RTGUI_LABEL(rtgui_get_self_object(DUTY_ID));
			if(power_data.Modulation_ratio%100<=9)
				rt_sprintf(label_text, "%d.%02x%", power_data.Modulation_ratio/100,power_data.Modulation_ratio%100);
			else
        rt_sprintf(label_text, "%d.%d%", power_data.Modulation_ratio/100,power_data.Modulation_ratio%100);
    /* 设置标签文本并更新控件 */
    rtgui_label_set_text(label, label_text);
		rtgui_widget_update(RTGUI_WIDGET(label));		


		label = RTGUI_LABEL(rtgui_get_self_object(Temperature_ID));
    rt_sprintf(label_text, "%d℃", power_data.Temperature);
    /* 设置标签文本并更新控件 */
    rtgui_label_set_text(label, label_text);
		rtgui_widget_update(RTGUI_WIDGET(label));
			
					
}
static void Load_Keyboard_sys(rtgui_container_t *win,rt_uint32_t rect_X,rt_uint32_t rect_Y);
rtgui_container_t * Interver_window(void)
{
    
    rtgui_button_t *button;
		struct rtgui_label      *label;
	    struct rtgui_win   *normal_window;
    rtgui_rect_t rect = {30, 40, 150, 80};
		rtgui_combobox_t *box;
    /*创建控制器的面板*/
    container = view("逆变器");

    normal_window = rtgui_win_create(RT_NULL, "",
                                    &rect, RTGUI_WIN_STYLE_DEFAULT);
		 RTGUI_WIDGET_BACKGROUND(normal_window) = white;
	/****************A相电压电流的显示************/
    view_get_rect(container, &rect);
    rect.x1 += 5;
    rect.x2 = rect.x1 + 48;
    rect.y1 -= 40;
    rect.y2 = rect.y1 + 20;	 
    label = rtgui_label_create("电压A:");
	  RTGUI_WIDGET_FOREGROUND(label) = Scope_Channel_Color_ch3;
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(container, RTGUI_WIDGET(label));
		
    rect.x1 += 48;
    rect.x2 = rect.x1 + 52; 
    label = rtgui_label_create("0V");
	  RTGUI_WIDGET_FOREGROUND(label) = Scope_Channel_Color_ch3;
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(container, RTGUI_WIDGET(label));
		 rtgui_object_set_id(RTGUI_OBJECT(label), VOLTAGE_A_ID);
		 
    rect.x1 += 60;
    rect.x2 = rect.x1 + 16*3;
		label = rtgui_label_create("电流A:");
		RTGUI_WIDGET_FOREGROUND(label) = Scope_Channel_Color_ch3;
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(container, RTGUI_WIDGET(label));
		
    rect.x1 += 48;
    rect.x2 = rect.x1 + 52;
		label = rtgui_label_create("0MA");
		RTGUI_WIDGET_FOREGROUND(label) = Scope_Channel_Color_ch3;
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(container, RTGUI_WIDGET(label));
		rtgui_object_set_id(RTGUI_OBJECT(label), CURRENT_A_ID);
		
		/****************B相电压电流的显示************/
		view_get_rect(container, &rect);
    rect.x1 += 5;
    rect.x2 = rect.x1 + 48;
    rect.y1 =rect.y1-10;
    rect.y2 = rect.y1 + 20;
		label = rtgui_label_create("电压B:");
		RTGUI_WIDGET_FOREGROUND(label) = Scope_Channel_Color_ch2;
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(container, RTGUI_WIDGET(label));
		
		
    rect.x1 += 48;
    rect.x2 = rect.x1 + 52;
		label = rtgui_label_create("0V");
		RTGUI_WIDGET_FOREGROUND(label) = Scope_Channel_Color_ch2;
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(container, RTGUI_WIDGET(label));
		rtgui_object_set_id(RTGUI_OBJECT(label), VOLTAGE_B_ID);
		
    rect.x1 += 60;
    rect.x2 = rect.x1 + 16*3;

		label = rtgui_label_create("电流B:");
		RTGUI_WIDGET_FOREGROUND(label) = Scope_Channel_Color_ch2;
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(container, RTGUI_WIDGET(label));
		
    rect.x1 += 48;
    rect.x2 = rect.x1 + 110-16*3;
		label = rtgui_label_create("0MA");
		RTGUI_WIDGET_FOREGROUND(label) = Scope_Channel_Color_ch2;
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(container, RTGUI_WIDGET(label));
		rtgui_object_set_id(RTGUI_OBJECT(label), CURRENT_B_ID);
		
		/****************C相电压电流的显示************/
		view_get_rect(container, &rect);
		rect.x1 += 5;
    rect.x2 = rect.x1 + 48;
    rect.y1 =rect.y1 + 20;
    rect.y2 = rect.y1 + 20;
	
	  label = rtgui_label_create("电压C:");
		RTGUI_WIDGET_FOREGROUND(label) = Scope_Channel_Color_ch1;
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(container, RTGUI_WIDGET(label));
		
		rect.x1 += 48;
    rect.x2 = rect.x1 + 52;
	
	  label = rtgui_label_create("0V");
		RTGUI_WIDGET_FOREGROUND(label) = Scope_Channel_Color_ch1;
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(container, RTGUI_WIDGET(label));
		rtgui_object_set_id(RTGUI_OBJECT(label), VOLTAGE_C_ID);
		
    rect.x1 += 60;
    rect.x2 = rect.x1 + 16*3;
		label = rtgui_label_create("电流C:");
		RTGUI_WIDGET_FOREGROUND(label) =Scope_Channel_Color_ch1;
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(container, RTGUI_WIDGET(label));
		
    rect.x1 += 48;
    rect.x2 = rect.x1 + 52;
		label = rtgui_label_create("0MA");
		RTGUI_WIDGET_FOREGROUND(label) =Scope_Channel_Color_ch1;
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(container, RTGUI_WIDGET(label));
		rtgui_object_set_id(RTGUI_OBJECT(label), CURRENT_C_ID);
		


		/****************直流侧电压电流的显示************/
		
	  view_get_rect(container, &rect);
    rect.x1 += 220;
    rect.x2 = rect.x1 + 90;
    rect.y1 -= 40;
    rect.y2 = rect.y1 + 20;	 
		label = rtgui_label_create( "直流侧电压:");
	  RTGUI_WIDGET_FOREGROUND(label) = black;
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(container, RTGUI_WIDGET(label));		
		
		
    rect.x1 += 100;
    rect.x2 = rect.x1 + 56;
		label = rtgui_label_create( "调制比:");
	  RTGUI_WIDGET_FOREGROUND(label) = black;
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(container, RTGUI_WIDGET(label));
		
		rect.x1 += 70;
    rect.x2 = rect.x1 + 40;
		label = rtgui_label_create( "温度:");
	  RTGUI_WIDGET_FOREGROUND(label) = black;
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(container, RTGUI_WIDGET(label));	
		
		/*直流侧电压显示*/
		view_get_rect(container, &rect);
    rect.x1 += 235;
    rect.x2 = rect.x1 + 90;
    rect.y1=rect.y1-40+20;
    rect.y2 = rect.y1 + 20;	 
		rt_sprintf(label_text, "%d", power_data.DCV_Z);
		label = rtgui_label_create( label_text);
	  RTGUI_WIDGET_FOREGROUND(label) = black;
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(container, RTGUI_WIDGET(label));
		rtgui_object_set_id(RTGUI_OBJECT(label), VOLTAGE_Z_ID);
		
    /*调至比数据显示*/
    rect.x1 += 90;
    rect.x2 = rect.x1 + 48; 
		rt_sprintf(label_text, "%d%", 0); 
		label = rtgui_label_create( label_text);
	  RTGUI_WIDGET_FOREGROUND(label) = black;
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(container, RTGUI_WIDGET(label));
		rtgui_object_set_id(RTGUI_OBJECT(label), DUTY_ID);
		
		/*温度数据显示*/
    rect.x1 += 70;
    rect.x2 = rect.x1 + 90; 
		rt_sprintf(label_text, "%d℃", 0); 
		label = rtgui_label_create( label_text);
	  RTGUI_WIDGET_FOREGROUND(label) = black;
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(container, RTGUI_WIDGET(label));
		rtgui_object_set_id(RTGUI_OBJECT(label), Temperature_ID);
				


	  view_get_rect(container, &rect);
    rect.x1 += 220;
    rect.x2 = rect.x1 + 72;
    rect.y1 -= 0;
    rect.y2 = rect.y1 + 20;	 
		label = rtgui_label_create( "参数设置:");
	  RTGUI_WIDGET_FOREGROUND(label) = black;
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(container, RTGUI_WIDGET(label));	

	  view_get_rect(container, &rect);
    rect.x1 += 235;
    rect.x2 = rect.x1 + 64;
    rect.y1=rect.y1+20;
    rect.y2 = rect.y1 + 20;	 
		rt_sprintf(label_text, "%d", 0); 
		label = rtgui_label_create( label_text);
	  RTGUI_WIDGET_FOREGROUND(label) = black;
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(container, RTGUI_WIDGET(label));
		rtgui_object_set_id(RTGUI_OBJECT(label), SET_DATA_ID);
		

		
    rect.x1 -= 60;
    rect.x2 =rect.x1 + 120;
    rect.y1=rect.y1+30;
    rect.y2 = rect.y1 + 20;
    box = rtgui_combobox_create(Slave_choice, sizeof(Slave_choice) / sizeof(Slave_choice[0]), &rect);
    rtgui_container_add_child(container, RTGUI_WIDGET(box));
		
     rect.x2 =rect.x1 + 84;
    rect.y1 += 20;
    rect.y2 = rect.y1 + 20;	 
		label = rtgui_label_create( "status:");
	  RTGUI_WIDGET_FOREGROUND(label) = black;
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(container, RTGUI_WIDGET(label));	
		{
		  struct rtgui_panel  *image_panel;
      view_get_rect(container, &rect);
			rect.x1 += 175;
			rect.x2 = rect.x1 + 25;
			rect.y1 += 90;
			rect.y2 = rect.y1 + 25;
			
			image_panel = rtgui_panel_create(RTGUI_BORDER_NONE);//RTGUI_BORDER_SIMPLE  RTGUI_BORDER_NONE
			rtgui_widget_set_rect(RTGUI_WIDGET(image_panel), &rect);
			rtgui_object_set_event_handler(RTGUI_OBJECT(image_panel), _on_show_status);
			RTGUI_WIDGET_ALIGN(image_panel) = RTGUI_ALIGN_EXPAND | RTGUI_ALIGN_STRETCH;
			rtgui_container_add_child(RTGUI_CONTAINER(container), RTGUI_WIDGET(image_panel));
		}
   
	 	/****************控制按钮显示部分************/
    view_get_rect(container, &rect);
    rect.x1 += 220;
    rect.x2 = rect.x1 + 60;
    rect.y1 +=110;
		rect.y2 = rect.y1 + 35;	
    button = rtgui_button_create("+");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(container), RTGUI_WIDGET(button));
    rtgui_button_set_onbutton(button, up_onbutton);


    rect.y1 +=40;
    rect.y2 = rect.y1 + 35;	
    button = rtgui_button_create("-");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(container), RTGUI_WIDGET(button));
    rtgui_button_set_onbutton(button, down_onbutton);


    rect.y1 +=40;
    rect.y2 = rect.y1 + 35;	
    button = rtgui_button_create("发送");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(container), RTGUI_WIDGET(button));
    rtgui_button_set_onbutton(button, ok_onbutton);
		
    view_get_rect(container, &rect);
    rect.x1 += 0;
    rect.x2 = rect.x1 + 100;
    rect.y1 =rect.y1+45;
    rect.y2 = rect.y1 + 120;	

    radiobox1 = rtgui_radiobox_create("变量", RTGUI_VERTICAL, radio_item_v, 5);
    rtgui_radiobox_set_selection(radiobox1, 0);
    rtgui_container_add_child(container, RTGUI_WIDGET(radiobox1));
    rtgui_widget_set_rect(RTGUI_WIDGET(radiobox1), &rect);
		
		view_get_rect(container, &rect);
    rect.x1 += 95;
    rect.x2 = rect.x1 +85;
    rect.y1 =rect.y1+45;
    rect.y2 = rect.y1 + 120;	

    radiobox = rtgui_radiobox_create("步进", RTGUI_VERTICAL, radio_item_h, 5);
    rtgui_radiobox_set_selection(radiobox, 0);
    rtgui_container_add_child(container, RTGUI_WIDGET(radiobox));
    rtgui_widget_set_rect(RTGUI_WIDGET(radiobox), &rect);
		
		
		view_get_rect(container, &rect);
    rect.x1 += 10;
    rect.x2 = rect.x1 + 168;
    rect.y1 +=165;
    rect.y2 = rect.y1 + 16;	
		label = rtgui_label_create( "注:调制比参数设置范围:");
	  RTGUI_WIDGET_FOREGROUND(label) = red;
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(container, RTGUI_WIDGET(label));	
		
		
    rect.x2 -=112;
    rect.y1 +=24;
    rect.y2 = rect.y1 + 16;	
		label = rtgui_label_create( "0~10000");
	  RTGUI_WIDGET_FOREGROUND(label) = red;
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(container, RTGUI_WIDGET(label));	

   	/*用于导入键盘界面*/
    Load_Keyboard_sys(container,300,60);

		 /* 创建一个定时器 */
    timer = rtgui_timer_create(20, RT_TIMER_FLAG_PERIODIC, update_data, RT_NULL);
    rtgui_timer_start(timer);

    return container;
}


#include <rtgui/widgets/textbox.h>
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
	power_data.SET_DATA=keyboard_data.Value_data_Decimal;
}


static void Softkeyboard_clear(struct rtgui_object *object, rtgui_event_t *event)
{
	  int i;
	  struct rtgui_textbox* text;
    number_key=0;
	  text = RTGUI_TEXTBOX(rtgui_get_self_object(Data_key_board));
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
	
	  text = RTGUI_TEXTBOX(rtgui_get_self_object(Data_key_board));
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
	  text = RTGUI_TEXTBOX(rtgui_get_self_object(Data_key_board));
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
	  text = RTGUI_TEXTBOX(rtgui_get_self_object(Data_key_board));
    

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
	
	  text = RTGUI_TEXTBOX(rtgui_get_self_object(Data_key_board));
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
	  text = RTGUI_TEXTBOX(rtgui_get_self_object(Data_key_board));
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
	
	  text = RTGUI_TEXTBOX(rtgui_get_self_object(Data_key_board));
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
	
	  text = RTGUI_TEXTBOX(rtgui_get_self_object(Data_key_board));
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
	
	  text = RTGUI_TEXTBOX(rtgui_get_self_object(Data_key_board));
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
	
	  text = RTGUI_TEXTBOX(rtgui_get_self_object(Data_key_board));
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
	
	  text = RTGUI_TEXTBOX(rtgui_get_self_object(Data_key_board));
    KeyBoard_Data[number_key]=9+48;
	  if(number_key<=number)
	  number_key++;
		for(i=number_key,j=0;i>0;i--,j++)
    KeyBoard_DataC[number-i+1]=KeyBoard_Data[j];
    rtgui_textbox_set_value(text, KeyBoard_DataC);
    rtgui_widget_update(RTGUI_WIDGET(text));
}


void Load_Keyboard_sys(rtgui_container_t *win,rt_uint32_t rect_X,rt_uint32_t rect_Y)
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
	  rtgui_object_set_id(RTGUI_OBJECT(text), Data_key_board);
	 
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


