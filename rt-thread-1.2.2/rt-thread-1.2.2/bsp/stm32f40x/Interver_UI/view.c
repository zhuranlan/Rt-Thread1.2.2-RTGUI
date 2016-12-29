#include <rtgui/rtgui.h>
#include <rtgui/rtgui_app.h>

#include <rtgui/widgets/container.h>
#include <rtgui/widgets/notebook.h>
#include <rtgui/widgets/button.h>
#include <rtgui/widgets/staticline.h>
#include <rtgui/widgets/box.h>
#include <rtgui/widgets/progressbar.h>
#include "view.h"
#include "time.h"
#include "Interver_RTU.h"
#define panel_name_user "用户区"
#define panel_name_Grid "并网"
extern struct rtgui_notebook *the_notebook;

rtgui_progressbar_t *ram_hbar,*cpu_hbar,*ram_hbar2,*cpu_hbar2,*ram_hbar3,*cpu_hbar3,*ram_hbar4,*cpu_hbar4,*ram_hbar5,*cpu_hbar5,*ram_hbar6,*cpu_hbar6;
extern  rt_size_t mem_size_aligned;
extern rt_size_t used_mem, max_mem;
extern rt_uint8_t  cpu_usage_major , cpu_usage_minor;
static struct rtgui_timer *timer;
static void cpuinformation_update(struct rtgui_timer *timer, void *parameter)
{
	  static char label_text[100];
	  time_t now;
	  struct rtgui_label   *label; 
	  now = time(RT_NULL);
	  label = RTGUI_LABEL(rtgui_get_self_object(AUTO_TIME_ID));
	{
    rt_sprintf(label_text, "%s",ctime(&now));
    rtgui_label_set_text(label, label_text);
    rtgui_widget_update(RTGUI_WIDGET(label));
	}
	
	
		label = RTGUI_LABEL(rtgui_get_self_object(MCU_INFORMATION_ID));
			if(label!=RT_NULL)
		{
    rt_sprintf(label_text, "RAM:%d.%d%CPU:%d%",(1000*used_mem/mem_size_aligned)/10,(1000*used_mem/mem_size_aligned)%10,cpu_usage_major);
    rtgui_label_set_text(label, label_text);
    rtgui_widget_update(RTGUI_WIDGET(label));
		}
		

	  rtgui_progressbar_set_value(ram_hbar, used_mem);
	  rtgui_progressbar_set_value(cpu_hbar, cpu_usage_major);
	
	
	  label = RTGUI_LABEL(rtgui_get_self_object(AUTO_TIME_ID2));
		if(label!=RT_NULL)
		{
    rt_sprintf(label_text, "%s",ctime(&now));
    rtgui_label_set_text(label, label_text);
    rtgui_widget_update(RTGUI_WIDGET(label));
		}
	
	
		label = RTGUI_LABEL(rtgui_get_self_object(MCU_INFORMATION_ID2));
		if(label!=RT_NULL)
		{
    rt_sprintf(label_text, "RAM:%d.%d%CPU:%d%",(1000*used_mem/mem_size_aligned)/10,(1000*used_mem/mem_size_aligned)%10,cpu_usage_major);
    rtgui_label_set_text(label, label_text);
    rtgui_widget_update(RTGUI_WIDGET(label));
		}
		

	  rtgui_progressbar_set_value(ram_hbar2, used_mem);
	  rtgui_progressbar_set_value(cpu_hbar2, cpu_usage_major);
		
	
		label = RTGUI_LABEL(rtgui_get_self_object(AUTO_TIME_ID3));
		if(label!=RT_NULL)
		{
    rt_sprintf(label_text, "%s",ctime(&now));
    rtgui_label_set_text(label, label_text);
    rtgui_widget_update(RTGUI_WIDGET(label));
		}
	
	
		label = RTGUI_LABEL(rtgui_get_self_object(MCU_INFORMATION_ID3));
		if(label!=RT_NULL)
		{
    rt_sprintf(label_text, "RAM:%d.%d%CPU:%d%",(1000*used_mem/mem_size_aligned)/10,(1000*used_mem/mem_size_aligned)%10,cpu_usage_major);
    rtgui_label_set_text(label, label_text);
    rtgui_widget_update(RTGUI_WIDGET(label));
		}
		

	  rtgui_progressbar_set_value(ram_hbar3, used_mem);
	  rtgui_progressbar_set_value(cpu_hbar3, cpu_usage_major);
		
		
		
		
		
		
		label = RTGUI_LABEL(rtgui_get_self_object(AUTO_TIME_ID4));
		if(label!=RT_NULL)
		{
    rt_sprintf(label_text, "%s",ctime(&now));
    rtgui_label_set_text(label, label_text);
    rtgui_widget_update(RTGUI_WIDGET(label));
		}
	
	
		label = RTGUI_LABEL(rtgui_get_self_object(MCU_INFORMATION_ID4));
		if(label!=RT_NULL)
		{
    rt_sprintf(label_text, "RAM:%d.%d%CPU:%d%",(1000*used_mem/mem_size_aligned)/10,(1000*used_mem/mem_size_aligned)%10,cpu_usage_major);
    rtgui_label_set_text(label, label_text);
    rtgui_widget_update(RTGUI_WIDGET(label));
		}
		

	  rtgui_progressbar_set_value(ram_hbar4, used_mem);
	  rtgui_progressbar_set_value(cpu_hbar4, cpu_usage_major);
		
		
		
		
		label = RTGUI_LABEL(rtgui_get_self_object(AUTO_TIME_ID5));
		if(label!=RT_NULL)
		{
    rt_sprintf(label_text, "%s",ctime(&now));
    rtgui_label_set_text(label, label_text);
    rtgui_widget_update(RTGUI_WIDGET(label));
		}
	
	
		label = RTGUI_LABEL(rtgui_get_self_object(MCU_INFORMATION_ID5));
		if(label!=RT_NULL)
		{
    rt_sprintf(label_text, "RAM:%d.%d%CPU:%d%",(1000*used_mem/mem_size_aligned)/10,(1000*used_mem/mem_size_aligned)%10,cpu_usage_major);
    rtgui_label_set_text(label, label_text);
    rtgui_widget_update(RTGUI_WIDGET(label));
		}
		

	  rtgui_progressbar_set_value(ram_hbar5, used_mem);
	  rtgui_progressbar_set_value(cpu_hbar5, cpu_usage_major);
		
		
		label = RTGUI_LABEL(rtgui_get_self_object(AUTO_TIME_ID6));
		if(label!=RT_NULL)
		{
    rt_sprintf(label_text, "%s",ctime(&now));
    rtgui_label_set_text(label, label_text);
    rtgui_widget_update(RTGUI_WIDGET(label));
		}
		
		
		label = RTGUI_LABEL(rtgui_get_self_object(MCU_INFORMATION_ID6));
		if(label!=RT_NULL)
		{
    rt_sprintf(label_text, "RAM:%d.%d%CPU:%d%",(1000*used_mem/mem_size_aligned)/10,(1000*used_mem/mem_size_aligned)%10,cpu_usage_major);
    rtgui_label_set_text(label, label_text);
    rtgui_widget_update(RTGUI_WIDGET(label));
		}
		

	  rtgui_progressbar_set_value(ram_hbar6, used_mem);
	  rtgui_progressbar_set_value(cpu_hbar6, cpu_usage_major);
}



/* 这个函数用于返回演示视图的对外可用区域 */
void view_get_rect(rtgui_container_t *container, rtgui_rect_t *rect)
{
    RT_ASSERT(container != RT_NULL);
    RT_ASSERT(rect != RT_NULL);

    rtgui_widget_get_rect(RTGUI_WIDGET(container), rect);
    rtgui_widget_rect_to_device(RTGUI_WIDGET(container), rect);
    /* 去除演示标题和下方按钮的区域 */
    rect->y1 += 45;
    rect->y2 -= 35;
}

void view_next(struct rtgui_object *object, struct rtgui_event *event)
{
    rtgui_notebook_set_current_by_index(the_notebook,
                                        (rtgui_notebook_get_current_index(the_notebook) + 1) %
                                        rtgui_notebook_get_count(the_notebook));
}

void view_prev(struct rtgui_object *object, struct rtgui_event *event)
{
    rt_int16_t cur_idx = rtgui_notebook_get_current_index(the_notebook);

    if (cur_idx == 0)
        rtgui_notebook_set_current_by_index(the_notebook,
                                            rtgui_notebook_get_count(the_notebook) - 1);
    else
        rtgui_notebook_set_current_by_index(the_notebook,
                                            --cur_idx);
}


static rt_bool_t dc_event_handler(struct rtgui_object *object, rtgui_event_t *event)
{
    struct rtgui_widget *widget = RTGUI_WIDGET(object);

    /* 仅对PAINT事件进行处理 */
    if (event->type == RTGUI_EVENT_PAINT)
    {
        struct rtgui_dc *dc;
        rtgui_rect_t rect;
			  int i;

        dc = rtgui_dc_begin_drawing(widget);

        if (dc == RT_NULL)
           return RT_FALSE;


        rect.x1 = 0;
				rect.x2 = rect.x1+480;
        rect.y1 = 300;
        rect.y2 = rect.y1+16;
        RTGUI_DC_FC(dc) = RTGUI_RGB(0, 0, 0);
        rtgui_dc_fill_round_rect(dc, &rect, 0);
								

				
        /* 绘图完成 */
        rtgui_dc_end_drawing(dc);
    }
    else
    {
        /* 其他事件，调用默认的事件处理函数 */
        return rtgui_container_event_handler(object, event);
    }
		
		



    return RT_FALSE;
}

rtgui_container_t *view(const char *title)
{
	  static char label_text[100];
    struct rtgui_container  *container;
    struct rtgui_label      *label;
    struct rtgui_staticline *line;
    struct rtgui_button     *next_btn, *prev_btn;
    struct rtgui_rect       rect;

	rtgui_font_t *font;

    container = rtgui_container_create();
    if (container == RT_NULL)
        return RT_NULL;

   rtgui_notebook_add(the_notebook, title, RTGUI_WIDGET(container));

		
		/*RAM CPU使用进度条*/
		{
		view_get_rect((container), &rect);
		rt_sprintf(label_text, "RAM:%d.%d%CPU:%d%",(1000*used_mem/mem_size_aligned)/10,(1000*used_mem/mem_size_aligned)%10,cpu_usage_major);
		label = rtgui_label_create( label_text); 
			
		font = rtgui_font_refer("asc", 12);
    RTGUI_WIDGET_FONT(label) = font;
			
    rtgui_container_add_child(container, RTGUI_WIDGET(label));
    rect.x1 += 5;
    rect.x2 = rect.x1 +140;
    rect.y1 = 285;
    rect.y2 = rect.y1 + 15;
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
			
	  if(strcmp(title,"系统")==0)
		rtgui_object_set_id(RTGUI_OBJECT(label),MCU_INFORMATION_ID);
		else  if(strcmp(title,"逆变器")==0)
		rtgui_object_set_id(RTGUI_OBJECT(label),MCU_INFORMATION_ID2);
		else  if(strcmp(title,"分析仪")==0)
		rtgui_object_set_id(RTGUI_OBJECT(label),MCU_INFORMATION_ID3);
				else  if(strcmp(title,"参数设置")==0)
		rtgui_object_set_id(RTGUI_OBJECT(label),MCU_INFORMATION_ID4);
								else  if(strcmp(title,panel_name_user)==0)
		rtgui_object_set_id(RTGUI_OBJECT(label),MCU_INFORMATION_ID5);
																else  if(strcmp(title,panel_name_Grid)==0)
		rtgui_object_set_id(RTGUI_OBJECT(label),MCU_INFORMATION_ID6);
		
	
		rect.x2 = rect.x1 +100;
    rect.y1 = 300;
    rect.y2 = rect.y1 + 18;
		if(strcmp(title,"系统")==0)
		{
    ram_hbar = rtgui_progressbar_create(RTGUI_HORIZONTAL, mem_size_aligned, &rect);
    RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(ram_hbar)) = RTGUI_RGB(34, 139, 34);
    rtgui_container_add_child(container, RTGUI_WIDGET(ram_hbar));
	  rtgui_progressbar_set_value(ram_hbar, used_mem);
		}
		else	if(strcmp(title,"逆变器")==0)
		{
    ram_hbar2 = rtgui_progressbar_create(RTGUI_HORIZONTAL, mem_size_aligned, &rect);
    RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(ram_hbar2)) = RTGUI_RGB(34, 139, 34);
    rtgui_container_add_child(container, RTGUI_WIDGET(ram_hbar2));
	  rtgui_progressbar_set_value(ram_hbar2, used_mem);
		}
				else	if(strcmp(title,"分析仪")==0)
		{
    ram_hbar3 = rtgui_progressbar_create(RTGUI_HORIZONTAL, mem_size_aligned, &rect);
    RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(ram_hbar3)) = RTGUI_RGB(34, 139, 34);;
    rtgui_container_add_child(container, RTGUI_WIDGET(ram_hbar3));
	  rtgui_progressbar_set_value(ram_hbar3, used_mem);
		}
						else	if(strcmp(title,"参数设置")==0)
		{
    ram_hbar4 = rtgui_progressbar_create(RTGUI_HORIZONTAL, mem_size_aligned, &rect);
    RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(ram_hbar4)) = RTGUI_RGB(34, 139, 34);;
    rtgui_container_add_child(container, RTGUI_WIDGET(ram_hbar4));
	  rtgui_progressbar_set_value(ram_hbar4, used_mem);
		}
								else	if(strcmp(title,panel_name_user)==0)
		{
    ram_hbar5 = rtgui_progressbar_create(RTGUI_HORIZONTAL, mem_size_aligned, &rect);
    RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(ram_hbar5)) = RTGUI_RGB(34, 139, 34);;
    rtgui_container_add_child(container, RTGUI_WIDGET(ram_hbar5));
	  rtgui_progressbar_set_value(ram_hbar5, used_mem);
		}
										else	if(strcmp(title,panel_name_Grid)==0)
		{
    ram_hbar6 = rtgui_progressbar_create(RTGUI_HORIZONTAL, mem_size_aligned, &rect);
    RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(ram_hbar6)) = RTGUI_RGB(34, 139, 34);;
    rtgui_container_add_child(container, RTGUI_WIDGET(ram_hbar6));
	  rtgui_progressbar_set_value(ram_hbar5, used_mem);
		}
	
			
    rect.x1 += 105;
    rect.x2 = rect.x1 +100;
		if(strcmp(title,"系统")==0)
		{
    cpu_hbar = rtgui_progressbar_create(RTGUI_HORIZONTAL, 100, &rect);
    RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(cpu_hbar)) = MCU_MESSAGE_Color;
    rtgui_container_add_child(container, RTGUI_WIDGET(cpu_hbar));
	  rtgui_progressbar_set_value(cpu_hbar, cpu_usage_major);	
		}
		else	if(strcmp(title,"逆变器")==0)
		{
    cpu_hbar2 = rtgui_progressbar_create(RTGUI_HORIZONTAL, 100, &rect);
    RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(cpu_hbar2)) = MCU_MESSAGE_Color;
    rtgui_container_add_child(container, RTGUI_WIDGET(cpu_hbar2));
	  rtgui_progressbar_set_value(cpu_hbar2, cpu_usage_major);	
		}
	  else	if(strcmp(title,"分析仪")==0)
		{
    cpu_hbar3 = rtgui_progressbar_create(RTGUI_HORIZONTAL, 100, &rect);
    RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(cpu_hbar3)) =MCU_MESSAGE_Color;
    rtgui_container_add_child(container, RTGUI_WIDGET(cpu_hbar3));
	  rtgui_progressbar_set_value(cpu_hbar3, cpu_usage_major);	
		}
		 else	if(strcmp(title,"参数设置")==0)
		{
    cpu_hbar4 = rtgui_progressbar_create(RTGUI_HORIZONTAL, 100, &rect);
    RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(cpu_hbar4)) = MCU_MESSAGE_Color;
    rtgui_container_add_child(container, RTGUI_WIDGET(cpu_hbar4));
	  rtgui_progressbar_set_value(cpu_hbar4, cpu_usage_major);	
		}
				 else	if(strcmp(title,panel_name_user)==0)
		{
    cpu_hbar5 = rtgui_progressbar_create(RTGUI_HORIZONTAL, 100, &rect);
    RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(cpu_hbar5)) = MCU_MESSAGE_Color;
    rtgui_container_add_child(container, RTGUI_WIDGET(cpu_hbar5));
	  rtgui_progressbar_set_value(cpu_hbar5, cpu_usage_major);	
		}
		
						 else	if(strcmp(title,panel_name_Grid)==0)
		{
    cpu_hbar6 = rtgui_progressbar_create(RTGUI_HORIZONTAL, 100, &rect);
    RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(cpu_hbar6)) = MCU_MESSAGE_Color;
    rtgui_container_add_child(container, RTGUI_WIDGET(cpu_hbar6));
	  rtgui_progressbar_set_value(cpu_hbar5, cpu_usage_major);	
		}

		}
		{
		time_t now;
    now = time(RT_NULL);	
			
		rect.y2=320;
		rect.x2 =480;
		rect.x2 -= 5;
    rect.x1 =rect.x2-192;
   
    rect.y1 =rect.y2-16;

    label = rtgui_label_create(ctime(&now));
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(container), RTGUI_WIDGET(label));
		if(strcmp(title,"系统")==0)
		rtgui_object_set_id(RTGUI_OBJECT(label), AUTO_TIME_ID);
	  else	if(strcmp(title,"逆变器")==0)
		rtgui_object_set_id(RTGUI_OBJECT(label), AUTO_TIME_ID2);
		else	if(strcmp(title,"分析仪")==0)
		rtgui_object_set_id(RTGUI_OBJECT(label), AUTO_TIME_ID3);
		else	if(strcmp(title,"参数设置")==0)
		rtgui_object_set_id(RTGUI_OBJECT(label), AUTO_TIME_ID4);
				else	if(strcmp(title,panel_name_user)==0)
		rtgui_object_set_id(RTGUI_OBJECT(label), AUTO_TIME_ID5);
								else	if(strcmp(title,panel_name_Grid)==0)
		rtgui_object_set_id(RTGUI_OBJECT(label), AUTO_TIME_ID6);
			
		}
		
		{
	   timer = rtgui_timer_create(500, RT_TIMER_FLAG_PERIODIC, cpuinformation_update, RT_NULL);
	   rtgui_timer_start(timer);
		}
		


    /* 获得视图的位置信息(在加入到 notebook 中时，notebook 会自动调整 container
     * 的大小) */
//    rtgui_widget_get_rect(RTGUI_WIDGET(container), &rect);
//    rtgui_widget_rect_to_device(RTGUI_WIDGET(container), &rect);
//   rect.x1 += 5;
//    rect.y1 += 5;
//    rect.x2 = rect.x1 + rt_strlen(title)*8;
//    rect.y2 = rect.y1 + 20;

//   /* 创建标题用的标签 */
//  label = rtgui_label_create(title);
//    /* 设置标签位置信息 */
//    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
//    /* 添加标签到视图中 */
//   rtgui_container_add_child(container, RTGUI_WIDGET(label));

//	
//	rtgui_widget_get_rect(RTGUI_WIDGET(container), &rect);
//	rtgui_widget_rect_to_device(RTGUI_WIDGET(container), &rect);
//   rect.y1 += 20 + 5;
//    rect.y2 = rect.y1 + 2;
//    /* 创建一个水平的 staticline 线 */
//  line = rtgui_staticline_create(RTGUI_HORIZONTAL);
//    /* 设置静态线的位置信息 */
//  rtgui_widget_set_rect(RTGUI_WIDGET(line), &rect);
//   /* 添加静态线到视图中 */
//  rtgui_container_add_child(container, RTGUI_WIDGET(line));
   
//    /* 获得视图的位置信息 */
//    rtgui_widget_get_rect(RTGUI_WIDGET(container), &rect);
//    rtgui_widget_rect_to_device(RTGUI_WIDGET(container), &rect);
//    rect.x2 -= 5;
//    rect.y2 -= 5;
//    rect.x1 = rect.x2 - 100;
//    rect.y1 = rect.y2 - 25;

//    /* 创建"下一个"按钮 */
//    next_btn = rtgui_button_create("下一页");
//    /* 设置onbutton动作到demo_view_next函数 */
//    rtgui_button_set_onbutton(next_btn, view_next);
//    /* 设置按钮的位置信息 */
//    rtgui_widget_set_rect(RTGUI_WIDGET(next_btn), &rect);
//    /* 添加按钮到视图中 */
//    rtgui_container_add_child(container, RTGUI_WIDGET(next_btn));

//    /* 获得视图的位置信息 */
//    rtgui_widget_get_rect(RTGUI_WIDGET(container), &rect);
//    rtgui_widget_rect_to_device(RTGUI_WIDGET(container), &rect);
//    rect.x1 += 5;
//    rect.y2 -= 5;
//    rect.x2 = rect.x1 + 100;
//    rect.y1 = rect.y2 - 25;

//    /* 创建"上一个"按钮 */
//    prev_btn = rtgui_button_create("上一页");
//    /* 设置onbutton动作到demo_view_prev函数 */
//    rtgui_button_set_onbutton(prev_btn, view_prev);
//    /* 设置按钮的位置信息 */
//    rtgui_widget_set_rect(RTGUI_WIDGET(prev_btn), &rect);
//    /* 添加按钮到视图中 */
//    rtgui_container_add_child(container, RTGUI_WIDGET(prev_btn));

    
	 /* 获得视图的位置信息 */
    rtgui_widget_get_rect(RTGUI_WIDGET(container), &rect);
    rtgui_widget_rect_to_device(RTGUI_WIDGET(container), &rect);
    rect.x2 = rect.x2/2+100;
    rect.y2 -= 5;
    rect.x1 = 2*rect.x2/3;
    rect.y1 = rect.y2 - 25;

    /* 返回创建的视图 */
    return container;
}



void view_get_logic_rect(rtgui_container_t *container, rtgui_rect_t *rect)
{
    RT_ASSERT(container != RT_NULL);
    RT_ASSERT(rect != RT_NULL);

    rtgui_widget_get_rect(RTGUI_WIDGET(container), rect);
    /* 去除演示标题和下方按钮的区域 */
    rect->y1 += 45;
    rect->y2 -= 35;
}
