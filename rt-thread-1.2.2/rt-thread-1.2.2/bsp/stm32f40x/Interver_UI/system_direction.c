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
#include <rtgui/widgets/staticline.h>
#include <rtgui/widgets/notebook.h>
#include <rtgui/widgets/textview.h>
#include "time.h"
#include <rtgui/widgets/radiobox.h>
#include <rtgui/widgets/panel.h>
#include "mylcd.h"
#include <rtgui/widgets/textbox.h>
const char *explain="  本系统是用在使用在逆变器的控制面板，数据传输方式采用RTU模式，通过写读与指令写操作可以完成DSP与ARM的数据交换。使用说明参考程序中的案例。";
 
rtgui_radiobox_t *radiobox_time;
static  char *radio_item_time[6] =
{
    "年",
    "月",
    "日",
    "小时",
    "分钟",
	  "秒"
};
struct time_date
{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
	
};
struct time_date set_timedate={2015,12,17,18,15,00};
static struct rtgui_timer *timer;
static struct rtgui_win *autowin = RT_NULL;


static char window_time_label_text[16];

extern struct rtgui_win *main_win;

              
static void up_onbutton(struct rtgui_object *object, rtgui_event_t *event)
{
		
   struct rtgui_label *label;
	if(rtgui_radiobox_get_selection(radiobox_time)==0)
	{
		set_timedate.year++;
	}
		else if(rtgui_radiobox_get_selection(radiobox_time)==1)
	{
		set_timedate.month++;
		if(set_timedate.month==13)
			set_timedate.month=1;
	}
	
		else if(rtgui_radiobox_get_selection(radiobox_time)==2)
	{
		set_timedate.day++;
		if(set_timedate.day==32)
			set_timedate.day=1;
	}
		else if(rtgui_radiobox_get_selection(radiobox_time)==3)
	{
		set_timedate.hour++;
		if(set_timedate.hour==24)
			set_timedate.hour=0;
			
	}
		else if(rtgui_radiobox_get_selection(radiobox_time)==4)
	{
		set_timedate.minute++;
		if(set_timedate.minute==60)
			set_timedate.minute=0;
	}
		else if(rtgui_radiobox_get_selection(radiobox_time)==5)
	{
		set_timedate.second++;
		if(set_timedate.second==60)
			set_timedate.second=0;
	}
	

    label = RTGUI_LABEL(rtgui_get_self_object(TIMEDATE1_ID));
    rt_sprintf(window_time_label_text,
		"%d年%d月%d日", set_timedate.year,set_timedate.month,set_timedate.day);
    /* 设置标签文本并更新控件 */
    rtgui_label_set_text(label, window_time_label_text);
    rtgui_widget_update(RTGUI_WIDGET(label));
	

    label = RTGUI_LABEL(rtgui_get_self_object(TIMEDATE2_ID));
      rt_sprintf(window_time_label_text,
		"%d:%d:%d",set_timedate.hour,set_timedate.minute,set_timedate.second);
    /* 设置标签文本并更新控件 */
    rtgui_label_set_text(label, window_time_label_text);
    rtgui_widget_update(RTGUI_WIDGET(label));
	
	
		
}
static void down_onbutton(struct rtgui_object *object, rtgui_event_t *event)
{
	   struct rtgui_label *label;
	if(rtgui_radiobox_get_selection(radiobox_time)==0&&set_timedate.year>=0)
	{
		set_timedate.year--;
	}
		else if(rtgui_radiobox_get_selection(radiobox_time)==1)
	{	
		if(set_timedate.month==1)
			set_timedate.month=13;
		set_timedate.month--;

	}
	
		else if(rtgui_radiobox_get_selection(radiobox_time)==2)
	{	
		if(set_timedate.day==1)
			set_timedate.day=32;
		set_timedate.day--;

	}
		else if(rtgui_radiobox_get_selection(radiobox_time)==3)
	{	
		if(set_timedate.hour==0)
			set_timedate.hour=24;
		set_timedate.hour--;
	
			
	}
		else if(rtgui_radiobox_get_selection(radiobox_time)==4)
	{	
		if(set_timedate.minute==0)
			set_timedate.minute=60;
		set_timedate.minute--;

	}
		else if(rtgui_radiobox_get_selection(radiobox_time)==5)
	{	
		if(set_timedate.second==0)
		set_timedate.second=60;
		set_timedate.second--;

	}
	

    label = RTGUI_LABEL(rtgui_get_self_object(TIMEDATE1_ID));
    rt_sprintf(window_time_label_text,
		"%d年%d月%d日", set_timedate.year,set_timedate.month,set_timedate.day);
    /* 设置标签文本并更新控件 */
    rtgui_label_set_text(label, window_time_label_text);
    rtgui_widget_update(RTGUI_WIDGET(label));
	

    label = RTGUI_LABEL(rtgui_get_self_object(TIMEDATE2_ID));
      rt_sprintf(window_time_label_text,
		"%d:%d:%d",set_timedate.hour,set_timedate.minute,set_timedate.second);
    /* 设置标签文本并更新控件 */
    rtgui_label_set_text(label, window_time_label_text);
    rtgui_widget_update(RTGUI_WIDGET(label));
}
static void ok_onbutton(struct rtgui_object *object, rtgui_event_t *event)
{
	extern rt_err_t set_date(rt_uint32_t year, rt_uint32_t month, rt_uint32_t day);
	extern rt_err_t set_time(rt_uint32_t hour, rt_uint32_t minute, rt_uint32_t second);
	set_date(set_timedate.year,set_timedate.month,set_timedate.day);
	set_time(set_timedate.hour,set_timedate.minute,set_timedate.second);
}



/* 触发正常窗口显示   用于修改系统时间 */
static void demo_normal_window_onbutton(struct rtgui_object *object, rtgui_event_t *event)
{
  struct rtgui_win   *normal_window;
    struct rtgui_label *label;
	   rtgui_button_t *button;
    rtgui_rect_t rect = {30, 40, 290, 200};

    normal_window = rtgui_win_create(main_win, "时间设置",
                                     &rect, RTGUI_WIN_STYLE_DEFAULT);
    rtgui_object_set_id(RTGUI_OBJECT(normal_window), NORMAL_WIN_ID);
		
    if (normal_window == RT_NULL)
        return;
		
		rect.x1 += 10;
    rect.x2 = rect.x1 +90;
    rect.y1 =rect.y1+10;
    rect.y2 = rect.y1 + 140;	

    radiobox_time = rtgui_radiobox_create("时间", RTGUI_VERTICAL, radio_item_time, 6);
    rtgui_radiobox_set_selection(radiobox_time, 0);
    rtgui_container_add_child(RTGUI_CONTAINER(normal_window), RTGUI_WIDGET(radiobox_time));
    rtgui_widget_set_rect(RTGUI_WIDGET(radiobox_time), &rect);
		
		
		  view_get_rect(RTGUI_CONTAINER(normal_window), &rect);
    rect.x1 += 120;
    rect.x2 -= 5;
    rect.y1 += 5-40;
    rect.y2 = rect.y1 + 20;

    /* 添加一个文本标签 */

    rt_sprintf(window_time_label_text,
		"%d年%d月%d日", set_timedate.year,set_timedate.month,set_timedate.day);
    label = rtgui_label_create(window_time_label_text);		
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(normal_window),
                              RTGUI_WIDGET(label));
    rtgui_object_set_id(RTGUI_OBJECT(label), TIMEDATE1_ID);
		
		
		view_get_rect(RTGUI_CONTAINER(normal_window), &rect);
		rect.x1 += 140;
    rect.x2 -= 5;
    rect.y1 += 25-40;
    rect.y2 = rect.y1 + 20;

    /* 添加一个文本标签 */
    rt_sprintf(window_time_label_text,
		"%d:%d:%d",set_timedate.hour,set_timedate.minute,set_timedate.second);
    label = rtgui_label_create(window_time_label_text);		
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(normal_window),
                              RTGUI_WIDGET(label));
    rtgui_object_set_id(RTGUI_OBJECT(label), TIMEDATE2_ID);
		
		view_get_rect(RTGUI_CONTAINER(normal_window), &rect);
    rect.x1 += 190;
    rect.x2 = rect.x1 + 60;
    rect.y1 =rect.y1-40+30+30;
    rect.y2 = rect.y1 + 20+15;	
    /* 创建按钮用于显示正常窗口 */
    button = rtgui_button_create("+");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(normal_window), RTGUI_WIDGET(button));
    /* 设置onbutton为demo_win_onbutton函数 */
    rtgui_button_set_onbutton(button, up_onbutton);

    view_get_rect(RTGUI_CONTAINER(normal_window), &rect);
    rect.x1 += 190;
    rect.x2 = rect.x1 + 60;
    rect.y1 =rect.y1-40+10+30*2+40;
    rect.y2 = rect.y1 + 20+15;	
    /* 创建按钮用于显示一个自动关闭的窗口 */
    button = rtgui_button_create("-");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(normal_window), RTGUI_WIDGET(button));
    /* 设置onbutton为demo_autowin_onbutton函数 */
    rtgui_button_set_onbutton(button, down_onbutton);

    view_get_rect(RTGUI_CONTAINER(normal_window), &rect);
    rect.x1 += 120;
    rect.x2 = rect.x1 + 60;
    rect.y1 =rect.y1-40+10+30*2+40;
    rect.y2 = rect.y1 + 20+15;	
    /* 创建按钮用于触发一个模式窗口 */
    button = rtgui_button_create("设置");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(normal_window), RTGUI_WIDGET(button));
    /* 设置onbutton为demo_modalwin_onbutton函数 */
    rtgui_button_set_onbutton(button, ok_onbutton);
		
		    /* 模态显示窗口 */
    rtgui_win_show(normal_window, RT_TRUE);

    /* 删除非自动删除窗口 */
    rtgui_win_destroy(normal_window);

}

///* 获取一个递增的窗口标题 */
//static char *get_win_title()
//{
//    static rt_uint8_t win_no = 0;
//    static char win_title[16];

//    rt_sprintf(win_title, "窗口 %d", ++win_no);
//    return win_title;
//}
 		extern  rt_size_t mem_size_aligned;
    extern rt_size_t used_mem, max_mem;
			extern rt_uint8_t  cpu_usage_major , cpu_usage_minor;
			extern rt_uint32_t total_count ;
/* 关闭对话框时的回调函数 */
static void update_device_information(struct rtgui_timer *timer, void *parameter)
{
	static char label_text[200];
	extern signed short x,y,z,Btn; 
	extern 	unsigned char KEYBOARD_DAT;
	struct rtgui_label *label;

		  #ifdef RT_USING_USB_HOST
		{
     extern unsigned int USB_device_MSGX;

		 label = RTGUI_LABEL(rtgui_get_self_object(USB_HOST_msgx_ID));

    /* 设置标签文本并更新控件 */
  	switch(USB_device_MSGX)
	   {
		case 0:	//USB无连接
    rtgui_label_set_text(label, "USB无连接");
			break;
		case 1:	//USB键盘
			rt_sprintf(label_text, "USB KEYBoard: Value:%02X Char:%c",KEYBOARD_DAT,KEYBOARD_DAT);
			rtgui_label_set_text(label, label_text);	
			break;
		case 2:	//USB鼠标
			rt_sprintf(label_text, "USB Mouse: X:%d Y:%d Z:%d But:%d", x,y,z,Btn);
			rtgui_label_set_text(label, label_text);	
			break; 		
		case 3:	//不支持的USB设备
			rtgui_label_set_text(label, "Unknow USB"); 

			break; 	 
	  }
    rtgui_widget_update(RTGUI_WIDGET(label));		 
   }
		#endif
	 
	 	label = RTGUI_LABEL(rtgui_get_self_object(CPU_Information));
    rt_sprintf(label_text, "cpu_usage_major:%d cpu_usage_minor:%d",cpu_usage_major,cpu_usage_minor);
    rtgui_label_set_text(label, label_text);
    rtgui_widget_update(RTGUI_WIDGET(label));
	 
	 
	  label = RTGUI_LABEL(rtgui_get_self_object(RAM_Information_1));
    rt_sprintf(label_text, "total memory: %d ", mem_size_aligned);
    rtgui_label_set_text(label, label_text);
    rtgui_widget_update(RTGUI_WIDGET(label));

	 	label = RTGUI_LABEL(rtgui_get_self_object(RAM_Information_2));
    rt_sprintf(label_text, "used memory : %d maximum allocated memory: %d",used_mem,max_mem);
    rtgui_label_set_text(label, label_text);
    rtgui_widget_update(RTGUI_WIDGET(label));
	
}

/* AUTO窗口关闭时的事件处理 */
static rt_bool_t auto_window_close(struct rtgui_object *object, struct rtgui_event *event)
{
    if (timer != RT_NULL)
    {
        /* 停止并删除定时器 */
        rtgui_timer_stop(timer);
        rtgui_timer_destory(timer);

        timer = RT_NULL;
    }
    autowin = RT_NULL;

    return RT_TRUE;
}

//static void close_device_window(struct rtgui_object *object, rtgui_event_t *event)
//{
//	    rtgui_win_t *win;

//    /* 获得最顶层控件 */
//    win = RTGUI_WIN(rtgui_widget_get_toplevel(RTGUI_WIDGET(object)));

//    /* 销毁窗口 */
//    rtgui_win_destroy(win);
//}
#include "system_stm32f4xx.h"
/* 触发自动窗口显示 */
static void Deviceman_onbutton(struct rtgui_object *object, rtgui_event_t *event)
{
	  struct rtgui_staticline *line;
    struct rtgui_rect rect = {20, 20, 440, 290};
	  struct rtgui_label      *label;
		extern unsigned int usb_host_msgx;
		static char label_text[100];
		const char *path_flash0="/";
		const char *path_sd="/SD";
		int result;
		struct statfs buffer;
		long long cap;
    if (autowin)
        return;

    autowin = rtgui_win_create(main_win, "设备管理",
                              &rect, RTGUI_WIN_STYLE_DEFAULT | RTGUI_WIN_STYLE_DESTROY_ON_CLOSE);
    if (autowin == RT_NULL)
        return;
   
		view_get_rect(RTGUI_CONTAINER(autowin), &rect);
    rect.x1 += 5;
    rect.x2 = rect.x1 + 76;
    rect.y1 -=40;
    rect.y2 = rect.y1 + 20;	
		label = rtgui_label_create("USB设备:");
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(autowin), RTGUI_WIDGET(label));
		
    rect.x1 += 80;
    rect.x2 = rect.x1 + 300;
		label = rtgui_label_create("DEVICE:");
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(autowin), RTGUI_WIDGET(label));
		

    rect.y1 +=20;
    rect.y2 = rect.y1 + 20;	
		label = rtgui_label_create("HOST:");
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(autowin), RTGUI_WIDGET(label));
		
	
    rect.x1 -= 80;
    rect.x2 = rect.x1 + 96;
    rect.y1 +=20;
    rect.y2 = rect.y1 + 20;	
		label = rtgui_label_create("USB设备检测:");
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(autowin), RTGUI_WIDGET(label));
		
    rect.x2 = rect.x1 + 440;
    rect.y1 +=20;
    rect.y2 = rect.y1 + 20;	
		label = rtgui_label_create("RTT_NULL");
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(autowin), RTGUI_WIDGET(label));
		rtgui_object_set_id(RTGUI_OBJECT(label), USB_HOST_msgx_ID);
		

		rect.y1 +=20 + 5;
    rect.y2 = rect.y1 + 2;
		/* 创建一个水平的 staticline 线 */
   line = rtgui_staticline_create(RTGUI_HORIZONTAL);
    /* 设置静态线的位置信息 */
   rtgui_widget_set_rect(RTGUI_WIDGET(line), &rect);
   /* 添加静态线到视图中 */
   rtgui_container_add_child(RTGUI_CONTAINER(autowin), RTGUI_WIDGET(line));
		
		
    rect.y1 +=5;
    rect.y2 = rect.y1 + 20;	
		rt_sprintf(label_text, "存储设备:");
		label = rtgui_label_create(label_text);		
		rtgui_label_set_text(label, label_text);	
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(autowin), RTGUI_WIDGET(label));

		result = dfs_statfs(path_flash0 ? path_flash0 : RT_NULL, &buffer);
		cap = buffer.f_bsize * buffer.f_bfree / 1024;

    rect.x2 = rect.x1 + 440;
    rect.y1 +=20;
    rect.y2 = rect.y1 + 20;	
		if(result!=0)
		rt_sprintf(label_text, "FLASH: dfs_statfs failed.\n");
		else
		rt_sprintf(label_text, "FLASH:剩余 %d KB",
    (unsigned long)cap, buffer.f_bfree*buffer.f_bsize/1024);
    label = rtgui_label_create(label_text);				
		rtgui_label_set_text(label, label_text);	
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(autowin), RTGUI_WIDGET(label));

		result = dfs_statfs(path_sd ? path_sd : RT_NULL, &buffer);
		cap = buffer.f_bsize * buffer.f_bfree / 1024;

    rect.x2 = rect.x1 + 440;
    rect.y1 +=20;
    rect.y2 = rect.y1 + 20;	
		if(result!=0)
		rt_sprintf(label_text, "TFT_SD: dfs_statfs failed.\n");	
		else	
		rt_sprintf(label_text, "TFT_SD:剩余 %d M",
    (unsigned long)cap/1024, buffer.f_bfree*buffer.f_bsize/1024/1024);

		label = rtgui_label_create(label_text);	
		rtgui_label_set_text(label, label_text);	
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(autowin), RTGUI_WIDGET(label));
		
		rect.y1 +=20 + 5;
    rect.y2 = rect.y1 + 2;
		/* 创建一个水平的 staticline 线 */
		line = rtgui_staticline_create(RTGUI_HORIZONTAL);
		/* 设置静态线的位置信息 */
		rtgui_widget_set_rect(RTGUI_WIDGET(line), &rect);
		/* 添加静态线到视图中 */
		rtgui_container_add_child(RTGUI_CONTAINER(autowin), RTGUI_WIDGET(line));
			
		rect.y1 +=5;
    rect.y2 = rect.y1 +20;
		rt_sprintf(label_text, "CPU: %d Mhz     RT_TICK_PER_SECOND: %d",(PLL_N*PLL_M/8)/PLL_P,RT_TICK_PER_SECOND);
		label = rtgui_label_create(label_text);		
		rtgui_label_set_text(label, label_text);	
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(autowin), RTGUI_WIDGET(label));
		
		{
		rect.y1 +=20;
    rect.y2 = rect.y1 +20;
		rt_sprintf(label_text, "cpu_usage_major:%d cpu_usage_minor:%d",cpu_usage_major,cpu_usage_minor);
		label = rtgui_label_create(label_text);		
		rtgui_label_set_text(label, label_text);	
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(autowin), RTGUI_WIDGET(label));
		rtgui_object_set_id(RTGUI_OBJECT(label), CPU_Information);
		}
		
	  rect.y1 +=20;
    rect.y2 = rect.y1 +20;
		rt_sprintf(label_text, "RAM: ");
		label = rtgui_label_create(label_text);		
		rtgui_label_set_text(label, label_text);	
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(autowin), RTGUI_WIDGET(label));
		
	  rect.y1 +=20;
    rect.y2 = rect.y1 +20;
		rt_sprintf(label_text, "total memory: %d ",mem_size_aligned);
		label = rtgui_label_create(label_text);		
		rtgui_label_set_text(label, label_text);	
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(autowin), RTGUI_WIDGET(label));
		rtgui_object_set_id(RTGUI_OBJECT(label), RAM_Information_1);
			
		rect.y1 +=20;
    rect.y2 = rect.y1 +20;
		rt_sprintf(label_text, "used memory : %d maximum allocated memory: %d",used_mem,max_mem);
		label = rtgui_label_create(label_text);		
		rtgui_label_set_text(label, label_text);	
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(autowin), RTGUI_WIDGET(label));
		rtgui_object_set_id(RTGUI_OBJECT(label), RAM_Information_2);
	
    /* 创建一个定时器 */
    timer = rtgui_timer_create(100, RT_TIMER_FLAG_PERIODIC, update_device_information, RT_NULL);
    rtgui_timer_start(timer);
		
    /* 设置关闭窗口时的动作 */
    rtgui_win_set_onclose(autowin, auto_window_close);
    rtgui_win_show(autowin, RT_FALSE);
}

#include "lwip/opt.h"
#include "lwip/debug.h"
#include "lwip/def.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/sys.h"
#include "lwip/netif.h"
#include "lwip/stats.h"
#include "lwip/tcpip.h"
#include "netif/etharp.h"
#include "netif/ethernetif.h"

//static void Netio_start(struct rtgui_object *object, rtgui_event_t *event)
//{
//	extern void netio_init(void);
//	rt_kprintf("netio server begin...\n");
//	netio_init();
//	rt_kprintf("netio server started!!\n");
//}

//static void Ftpd_start(struct rtgui_object *object, rtgui_event_t *event)
//{
//		#if defined(RT_USING_DFS) && defined(RT_USING_LWIP)
//			{
//		extern void ftpd_start(void);
//		/* start ftp server */
//		rt_kprintf("ftp server begin...\n");
//		ftpd_start();
//		rt_kprintf("ftp server started!!\n");
//		#endif
//			}
//}

//static void Tcpserver_start(struct rtgui_object *object, rtgui_event_t *event)
//{
//		extern void tcpserv(void);
//		/* start tcp server */
//		rt_kprintf("tcp server begin...\n");
//		tcpserv();
//		rt_kprintf("tcp server end!!\n");
//}

//static void Udpserver_start(struct rtgui_object *object, rtgui_event_t *event)
//{
//			extern void udpserv(void);
//		/* start udp server */
//		rt_kprintf("udp server begin...\n");
//		udpserv();
//		rt_kprintf("\n udp server end!!\n");
//}
static void close_window(struct rtgui_object *object, rtgui_event_t *event)
{
    rtgui_win_t *win;

    /* 获得最顶层控件 */
    win = RTGUI_WIN(rtgui_widget_get_toplevel(RTGUI_WIDGET(object)));

    /* 销毁窗口 */
    rtgui_win_destroy(win);
}



//static void Net_Data_Set(struct rtgui_object *object, rtgui_event_t *event)
//{
//	   rtgui_win_t *win;
//    rtgui_label_t *label;
//	  rtgui_button_t *button;  
//    rtgui_rect_t rect = {0, 20, 480, 320};
//    struct rtgui_panel* panel;
//    struct rtgui_textbox* text;
//   struct rtgui_box *box;
// 
//    /* 创建一个窗口 */
//    win = rtgui_win_create(main_win,
//                           "网络参数设置", &rect, RTGUI_WIN_STYLE_DEFAULT);
//		
//		
//    rect.x1 = 350;
//    rect.x2 = rect.x1+100;
//    rect.y1 = 30;
//    rect.y2 = rect.y1 + 30;
//		
//    button = rtgui_button_create("保存");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
//			rtgui_button_set_onbutton(button, Save_net_data);
//		
//		rect.y1 += 35;
//    rect.y2 = rect.y1 + 30;
//		button = rtgui_button_create("放弃");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
//		rtgui_button_set_onbutton(button, Give_up_net_data);

//		 
//		
//		rect.x1 = 5;
//    rect.x2 = rect.x1+48;
//    rect.y1 = 30;
//    rect.y2 = rect.y1 + 20;
//		label = rtgui_label_create("IP:");
//    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(label));
//		
//		rect.x1 +=50;
//    rect.x2 = rect.x1+40;
//    text = rtgui_textbox_create("222", RTGUI_TEXTBOX_SINGLE);
//    rtgui_widget_set_rect(RTGUI_WIDGET(text), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(text));
//		rtgui_object_set_id(RTGUI_OBJECT(text), Text_ip_1);

//		
//		rect.x1 +=50;
//    rect.x2 = rect.x1+40;
//    text = rtgui_textbox_create("24", RTGUI_TEXTBOX_SINGLE);
//    rtgui_widget_set_rect(RTGUI_WIDGET(text), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(text));
//		
//		rect.x1 +=50;
//    rect.x2 = rect.x1+40;
//    text = rtgui_textbox_create("85", RTGUI_TEXTBOX_SINGLE);
//    rtgui_widget_set_rect(RTGUI_WIDGET(text), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(text));
//		
//		rect.x1 +=50;
//    rect.x2 = rect.x1+40;
//    text = rtgui_textbox_create("170", RTGUI_TEXTBOX_SINGLE);
//    rtgui_widget_set_rect(RTGUI_WIDGET(text), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(text));
//		
//		rect.x1 = 5;
//    rect.x2 = rect.x1+48;
//    rect.y1 += 40;
//    rect.y2 = rect.y1 + 20;
//		label = rtgui_label_create("网关:");
//    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(label));

//	
//		
//		rect.x1 = 5;
//    rect.x2 = rect.x1+72;
//    rect.y1 += 40;
//    rect.y2 = rect.y1 + 20;
//		label = rtgui_label_create("子网掩码:");
//    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(label));
//	

//	  /*用于导入键盘界面*/
//    Load_Keyboard(win,240,70);
//		

//    /* 模态显示窗口 */
//    rtgui_win_show(win, RT_TRUE);

//    /* 删除非自动删除窗口 */
//    rtgui_win_destroy(win);
//}

//static void net_manager_onbutton(struct rtgui_object *object, rtgui_event_t *event)
//{
//    rtgui_win_t *win;
//    rtgui_label_t *label;
//	  rtgui_button_t *button;  
//    rtgui_rect_t rect = {10, 20, 440, 300};
//		char label_text[500];
//		char text[500];

// 
//    /* 创建一个窗口 */
//    win = rtgui_win_create(main_win,
//                           "网络管理", &rect, RTGUI_WIN_STYLE_DEFAULT);
//    rect.x1 += 5;
//    rect.x2 = rect.x1+100;
//    rect.y1 += 10;
//    rect.y2 = rect.y1 + 30;
//		
//    button = rtgui_button_create("参数配置");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
//		 rtgui_button_set_onbutton(button, Net_Data_Set);
//		
//		rect.y1 += 35;
//    rect.y2 = rect.y1 + 30;
//		button = rtgui_button_create("Netio");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
//		rtgui_button_set_onbutton(button, Netio_start);
//		 
//		rect.y1 += 35;
//    rect.y2 = rect.y1 + 30;
//		button = rtgui_button_create("Ftpd");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
//		rtgui_button_set_onbutton(button, Ftpd_start);
//		
//		rect.y1 += 35;
//    rect.y2 = rect.y1 + 30;
//		button = rtgui_button_create("Tcpserver");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
//		rtgui_button_set_onbutton(button, Tcpserver_start);

//		rect.y1 += 35;
//    rect.y2 = rect.y1 + 30;
//		button = rtgui_button_create("Udpserver");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
//		rtgui_button_set_onbutton(button, Udpserver_start);
//		
//    rtgui_widget_get_rect(RTGUI_WIDGET(win), &rect);
//		{
//    rt_ubase_t index;
//    struct netif * netif;

//    rt_enter_critical();

//    netif = netif_list;

//    while( netif != RT_NULL )
//    {
//        rt_sprintf(label_text, "network interface: %c%c%s",
//                   netif->name[0],
//                   netif->name[1],
//                   (netif == netif_default)?" (Default)":"");
//			
//		rect.x1 += 140;
//    rect.x2 = rect.x1+400;
//		rect.y1 +=25;
//    rect.y2 = rect.y1 + 20;

//    label = rtgui_label_create(label_text);	
//		rtgui_label_set_text(label, label_text);	
//    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(label));
//			
//    rt_sprintf(label_text,"MTU: %d", netif->mtu);
//		rect.y1+=20;
//    rect.y2 = rect.y1 + 20;	
//		label = rtgui_label_create(label_text);	
//		rtgui_label_set_text(label, label_text);	
//    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(label));
//					
//	  rt_sprintf(label_text, "MAC: %02x %02x %02x %02x %02x %02x", netif->hwaddr[0], netif->hwaddr[1], netif->hwaddr[2], netif->hwaddr[3],netif->hwaddr[4], netif->hwaddr[5]);	
//	  rect.y1+=20;
//    rect.y2 = rect.y1 + 20;	
//		label = rtgui_label_create(label_text);	
//		rtgui_label_set_text(label, label_text);	
//    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(label));
//				
//	/********************本部分代码还没有完成！！！！！！！！！*********************/				
////		rt_sprintf(label_text, "\nFLAGS:");
////		if (netif->flags & NETIF_FLAG_UP) rt_sprintf(label_text, " UP");
////		else rt_sprintf(label_text, " DOWN");
////		if (netif->flags & NETIF_FLAG_LINK_UP) rt_sprintf(label_text, " LINK_UP");
////		else rt_sprintf(label_text, " LINK_DOWN");
////		if (netif->flags & NETIF_FLAG_DHCP) rt_sprintf(label_text, " DHCP");
////		if (netif->flags & NETIF_FLAG_POINTTOPOINT) rt_sprintf(label_text, " PPP");
////		if (netif->flags & NETIF_FLAG_ETHARP) rt_sprintf(label_text, " ETHARP");
////		if (netif->flags & NETIF_FLAG_IGMP) rt_sprintf(label_text, " IGMP");
////		rt_sprintf(label_text, "\n");
//		
//		rt_sprintf(label_text, "ip address: %s", ipaddr_ntoa(&(netif->ip_addr)));
//		rect.y1+=20;
//    rect.y2 = rect.y1 + 20;	
//		label = rtgui_label_create(label_text);	
//		rtgui_label_set_text(label, label_text);	
//    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(label));
//		
//		rt_sprintf(label_text, "gw address: %s", ipaddr_ntoa(&(netif->gw)));
//		rect.y1+=20;
//    rect.y2 = rect.y1 + 20;	
//		label = rtgui_label_create(label_text);	
//		rtgui_label_set_text(label, label_text);	
//    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(label));
//		
//		rt_sprintf(label_text, "net mask  : %s", ipaddr_ntoa(&(netif->netmask)));
//		rect.y1+=20;
//    rect.y2 = rect.y1 + 20;	
//		label = rtgui_label_create(label_text);	
//		rtgui_label_set_text(label, label_text);	
//    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(label));

//		netif = netif->next;
//    }

////#if LWIP_DNS
////    {
////        struct ip_addr ip_addr;

////        for(index=0; index<DNS_MAX_SERVERS; index++)
////        {
////            ip_addr = dns_getserver(index);
////            rt_kprintf("dns server #%d: %s\n", index, ipaddr_ntoa(&(ip_addr)));
////        }
////    }
////#endif /**< #if LWIP_DNS */

//    rt_exit_critical();
//}

//    /* 模态显示窗口 */
//    rtgui_win_show(win, RT_TRUE);

//    /* 删除非自动删除窗口 */
//    rtgui_win_destroy(win);
//}

extern void calibration(void);
static void Calibration_work(struct rtgui_object *object, rtgui_event_t *event)
{
	rm("/SETUP.INI");
	calibration();
}




/* 触发无标题窗口显示    用于显示系统信息*/
static void demo_direction_onbutton(struct rtgui_object *object, rtgui_event_t *event)
{
    rtgui_win_t *win;
    rtgui_button_t *button;  
   struct rtgui_notebook *notebook;
struct rtgui_textview *tv;	
    rtgui_rect_t widget_rect, rect = {0, 0, 220, 160};

    rtgui_rect_moveto(&rect, 40, 40);

    /* 创建一个窗口，风格为无标题及无边框 */
    win = rtgui_win_create(main_win,
                           "no title", &rect, RTGUI_WIN_STYLE_NO_TITLE |
                           RTGUI_WIN_STYLE_DESTROY_ON_CLOSE);
    RTGUI_WIDGET_BACKGROUND(win) = white;

		    /* create a no title notebook that we can switch demo on it easily. */
     notebook = rtgui_notebook_create(&rect,2);
		
	  tv = rtgui_textview_create(explain,&rect);
    rtgui_notebook_add(notebook, "", RTGUI_WIDGET(tv));
    RTGUI_WIDGET_BACKGROUND(tv) = white;

			
    /* 创建一个关闭按钮 */
    widget_rect.x1 = 0;
    widget_rect.y1 = 100;
    widget_rect.x2 = 80;
    widget_rect.y2 = 120;
    rtgui_rect_moveto_align(&rect, &widget_rect, RTGUI_ALIGN_CENTER_HORIZONTAL);
    widget_rect.y1 += 20;
    widget_rect.y2 += 30;
    button = rtgui_button_create("关闭");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &widget_rect);
    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
    rtgui_button_set_onbutton(button, close_window);
		
	   rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(notebook));
     rtgui_win_show(win, RT_FALSE);
}

//static void RTT_THREAD_MANAGE(struct rtgui_object *object, rtgui_event_t *event)
//{
//    rtgui_win_t *win;
//    rtgui_label_t *label;
//	  rtgui_button_t *button;  
//    rtgui_rect_t rect = {10, 20, 440, 300};
//		char label_text[12];
//		char text[12];

// 
//    /* 创建一个窗口 */
//    win = rtgui_win_create(main_win,
//                           "WIFI", &rect, RTGUI_WIN_STYLE_DEFAULT);
//    rect.x1 += 5;
//    rect.x2 = rect.x1+100;
//    rect.y1 += 10;
//    rect.y2 = rect.y1 + 30;
//		
//    button = rtgui_button_create("TCP");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
//		rtgui_button_set_onbutton(button, WIFI_TCP_start);
//		
//		rect.y1 += 35;
//    rect.y2 = rect.y1 + 30;
//		button = rtgui_button_create("UDP");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
//		rtgui_button_set_onbutton(button, WIFI_UDP_start);
//		 
//		rect.y1 += 35;
//    rect.y2 = rect.y1 + 30;
//		button = rtgui_button_create("Ftpd");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
//		//rtgui_button_set_onbutton(button, Ftpd_start);
//		
//		rect.y1 += 35;
//    rect.y2 = rect.y1 + 30;
//		button = rtgui_button_create("CLOSE");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
//		//rtgui_button_set_onbutton(button, Tcpserver_start);

//		rect.y1 += 35;
//    rect.y2 = rect.y1 + 30;
//		button = rtgui_button_create("重启WIFI");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
//		rtgui_button_set_onbutton(button, WIFI_Restart_start);
//		
//    rtgui_widget_get_rect(RTGUI_WIDGET(win), &rect);


//    /* 模态显示窗口 */
//    rtgui_win_show(win, RT_TRUE);

//    /* 删除非自动删除窗口 */
//    rtgui_win_destroy(win);
//}

/* 触发无标题窗口显示    用于显示系统信息*/
static void Calibration_onbutton(struct rtgui_object *object, rtgui_event_t *event)
{
    rtgui_win_t *win;
    rtgui_button_t *button;  
    struct rtgui_notebook *notebook;
    struct rtgui_textview *tv;	
    rtgui_rect_t widget_rect, rect = {0, 0, 220, 160};

    rtgui_rect_moveto(&rect,120, 40);

    /* 创建一个窗口，风格为无标题及无边框 */
    win = rtgui_win_create(main_win,
                           "Warning", &rect, RTGUI_WIN_STYLE_MINIBOX |
                           RTGUI_WIN_STYLE_DESTROY_ON_CLOSE);
    RTGUI_WIDGET_BACKGROUND(win) = white;

		    /* create a no title notebook that we can switch demo on it easily. */
     notebook = rtgui_notebook_create(&rect,2);
		
		
	  tv = rtgui_textview_create("是否进行触摸校验??",&rect);
    rtgui_notebook_add(notebook, "", RTGUI_WIDGET(tv));
    RTGUI_WIDGET_BACKGROUND(tv) = white;
		

    /* 创建一个关闭按钮 */
    widget_rect.x1 = 0;
    widget_rect.y1 = 50;
    widget_rect.x2 = 80;
    widget_rect.y2 = 70;
    rtgui_rect_moveto_align(&rect, &widget_rect, RTGUI_ALIGN_CENTER_HORIZONTAL);
    widget_rect.y1 += 20;
    widget_rect.y2 += 30;
    button = rtgui_button_create("退出");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &widget_rect);
    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
    rtgui_button_set_onbutton(button, close_window);
		
		 widget_rect.x1 = 0;
    widget_rect.y1 = 100;
    widget_rect.x2 = 80;
    widget_rect.y2 = 120;
    rtgui_rect_moveto_align(&rect, &widget_rect, RTGUI_ALIGN_CENTER_HORIZONTAL);
    widget_rect.y1 += 20;
    widget_rect.y2 += 30;
    button = rtgui_button_create("确认");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &widget_rect);
    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
    rtgui_button_set_onbutton(button, Calibration_work);	
		
		
	   rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(notebook));
     rtgui_win_show(win, RT_FALSE);
}



static rt_bool_t _on_show_rt(struct rtgui_object *object, struct rtgui_event *event)
{
	static char image_path[128]="/PICTURE/RTT_LOGO.HDC";
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

		image = rtgui_image_create(image_path, RT_TRUE);
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



static rt_bool_t _on_show_sust(struct rtgui_object *object, struct rtgui_event *event)
{
	static char image_pathsust[128]="/PICTURE/SUST.HDC";
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

		image = rtgui_image_create(image_pathsust, RT_TRUE);
		if (image != RT_NULL)
		{
			rtgui_image_blit(image, dc, RT_NULL);
			rtgui_image_destroy(image);
		}
		else
		{
			rt_kprintf("open image:%s failed!\n", image_pathsust);
		}

		rtgui_dc_draw_border(dc, &rect, panel->border_style);
        /* paint on each child */
        rtgui_container_dispatch_event(RTGUI_CONTAINER(panel), event);

        rtgui_dc_end_drawing(dc);
		return RT_FALSE;
	}

	return rtgui_panel_event_handler(object, event);
}

rtgui_container_t * direction_view(void) 
{  
    rtgui_rect_t rect = {30, 40, 150, 120};
    rtgui_container_t *container;
    rtgui_button_t *button;
	  struct rtgui_label      *label;
    struct rtgui_staticline *line;
	  const char *title="RT-THREAD 1.2.2    RTGUI 0.8.1";

   		
    /* 创建一个演示用的视图 */
    container = view("系统");

			if (container == RT_NULL) return RT_FALSE;
	
	   /* 获得视图的位置信息(在加入到 notebook 中时，notebook 会自动调整 container
     * 的大小) */
    rtgui_widget_get_rect(RTGUI_WIDGET(container), &rect);
    rtgui_widget_rect_to_device(RTGUI_WIDGET(container), &rect);
    rect.x1 += 5;
    rect.y1 += 5;
    rect.x2 = rect.x1 + rt_strlen(title)*8;
    rect.y2 = rect.y1 + 20;

   /* 创建标题用的标签 */
   label = rtgui_label_create(title);
    /* 设置标签位置信息 */
   rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    /* 添加标签到视图中 */
   rtgui_container_add_child(container, RTGUI_WIDGET(label));
	
	 rtgui_widget_get_rect(RTGUI_WIDGET(container), &rect);
	 rtgui_widget_rect_to_device(RTGUI_WIDGET(container), &rect);
   rect.y1 += 20 + 5;
    rect.y2 = rect.y1 + 2;
    /* 创建一个水平的 staticline 线 */
   line = rtgui_staticline_create(RTGUI_HORIZONTAL);
    /* 设置静态线的位置信息 */
   rtgui_widget_set_rect(RTGUI_WIDGET(line), &rect);
   /* 添加静态线到视图中 */
   rtgui_container_add_child(container, RTGUI_WIDGET(line));

  
    view_get_rect(container, &rect);
    rect.x1 += 5;
    rect.x2 = rect.x1 + 100;
    rect.y1 -= 15;
    rect.y2 = rect.y1 + 30;
    /* 创建按钮用于显示正常窗口 */
    button = rtgui_button_create("时间设置");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(container), RTGUI_WIDGET(button));
    /* 设置onbutton为demo_win_onbutton函数 */
    rtgui_button_set_onbutton(button, demo_normal_window_onbutton);

    rect.y1 += 35;
    rect.y2 = rect.y1 + 30;
    /* 创建按钮用于显示一个自动关闭的窗口 */
    button = rtgui_button_create("设备管理");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(container), RTGUI_WIDGET(button));
    /* 设置onbutton为demo_autowin_onbutton函数 */
    rtgui_button_set_onbutton(button, Deviceman_onbutton);


//    rect.y1 += 35;
//    rect.y2 = rect.y1 + 30;
//    /* 创建按钮用于触发一个模式窗口 */
//    button = rtgui_button_create("网络管理");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(container), RTGUI_WIDGET(button));
//    /* 设置onbutton为demo_modalwin_onbutton函数 */
//    //rtgui_button_set_onbutton(button, net_manager_onbutton);


    rect.y1 += 35;
    rect.y2 = rect.y1 + 30;
    /* 创建按钮用于触发一个不包含标题的窗口 */
    button = rtgui_button_create("触摸校验");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(container), RTGUI_WIDGET(button));
    /* 设置onbutton为demo_ntitlewin_onbutton函数 */
    rtgui_button_set_onbutton(button, Calibration_onbutton);
		
		
  
    rect.y1 += 35;
    rect.y2 = rect.y1 + 30;
    /* 创建按钮用于触发一个不包含标题的窗口 */
    button = rtgui_button_create("说明");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(container), RTGUI_WIDGET(button));
    rtgui_button_set_onbutton(button, demo_direction_onbutton);

//    rect.x1=120;
//		rect.x2=rect.x1+100;
//    /* 创建按钮用于触发一个不包含标题的窗口 */
//    button = rtgui_button_create("WIFI");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(container), RTGUI_WIDGET(button));
//    rtgui_button_set_onbutton(button, RTT_THREAD_MANAGE);

		
		/*用显示LOGO的部分代码*/
		{
			struct rtgui_panel  *image_panel;
	
			
			view_get_rect(container, &rect);
			rect.x1 += 300;
			rect.x2 = rect.x1 + 120;
			rect.y1 += 10;
			rect.y2 = rect.y1 + 62;
			
			image_panel = rtgui_panel_create(RTGUI_BORDER_NONE);//RTGUI_BORDER_SIMPLE  RTGUI_BORDER_NONE
			rtgui_widget_set_rect(RTGUI_WIDGET(image_panel), &rect);
			rtgui_object_set_event_handler(RTGUI_OBJECT(image_panel), _on_show_rt);
			RTGUI_WIDGET_ALIGN(image_panel) = RTGUI_ALIGN_EXPAND | RTGUI_ALIGN_STRETCH;
			rtgui_container_add_child(RTGUI_CONTAINER(container), RTGUI_WIDGET(image_panel));
						

			rect.x1 += 20;
			rect.x2 = rect.x1 + 80;
			rect.y1 += 80;
			rect.y2 = rect.y1 + 80;
			
			image_panel = rtgui_panel_create(RTGUI_BORDER_NONE);//RTGUI_BORDER_SIMPLE  RTGUI_BORDER_NONE
			rtgui_widget_set_rect(RTGUI_WIDGET(image_panel), &rect);
			rtgui_object_set_event_handler(RTGUI_OBJECT(image_panel), _on_show_sust);
			RTGUI_WIDGET_ALIGN(image_panel) = RTGUI_ALIGN_EXPAND | RTGUI_ALIGN_STRETCH;
			rtgui_container_add_child(RTGUI_CONTAINER(container), RTGUI_WIDGET(image_panel));
		}


		  rtgui_container_layout(RTGUI_CONTAINER(container));
      return container;
}








void window_thread_entry(void* parameter)
{
    struct rtgui_app* app;
    struct rtgui_win *win;
    struct rtgui_box *box;
    struct rtgui_button *button;
    struct rtgui_panel* panel;
    struct rtgui_textbox* text;
    struct rtgui_label *label;

    struct rtgui_rect rect = {50, 50, 350, 170};

    app = rtgui_app_create("MyApp");
    RT_ASSERT(app != RT_NULL);

    win = rtgui_win_create(RT_NULL, "Login", &rect, RTGUI_WIN_STYLE_DEFAULT);

    box = rtgui_box_create(RTGUI_VERTICAL, 10);
    rtgui_container_set_box(RTGUI_CONTAINER(win), box);

    /* Usename */
    {

        struct rtgui_box *box;

        panel = rtgui_panel_create(RTGUI_BORDER_NONE);
        rtgui_widget_set_minheight(RTGUI_WIDGET(panel), 25);
        RTGUI_WIDGET_ALIGN(panel) = RTGUI_ALIGN_EXPAND;
        rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(panel));

        box = rtgui_box_create(RTGUI_HORIZONTAL, 3);
        rtgui_container_set_box(RTGUI_CONTAINER(panel), box);

        label = rtgui_label_create("Usename:");
        rtgui_widget_set_minwidth(RTGUI_WIDGET(label), 80);
        rtgui_container_add_child(RTGUI_CONTAINER(panel), RTGUI_WIDGET(label));

        text = rtgui_textbox_create("", RTGUI_TEXTBOX_SINGLE);
        RTGUI_WIDGET_ALIGN(text) = RTGUI_ALIGN_STRETCH;
        rtgui_widget_set_minwidth(RTGUI_WIDGET(text), 80);
        /*rtgui_widget_set_minheight(RTGUI_WIDGET(text), 25);*/
        rtgui_container_add_child(RTGUI_CONTAINER(panel), RTGUI_WIDGET(text));
    }

    /* Password */
    {
        struct rtgui_box *box;

        panel = rtgui_panel_create(RTGUI_BORDER_NONE);
        rtgui_widget_set_minheight(RTGUI_WIDGET(panel), 25);
        RTGUI_WIDGET_ALIGN(panel) = RTGUI_ALIGN_EXPAND;
        rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(panel));

        box = rtgui_box_create(RTGUI_HORIZONTAL, 3);
        rtgui_container_set_box(RTGUI_CONTAINER(panel), box);

        label = rtgui_label_create("Password:");
        rtgui_widget_set_minwidth(RTGUI_WIDGET(label), 80);
        rtgui_container_add_child(RTGUI_CONTAINER(panel), RTGUI_WIDGET(label));

        text = rtgui_textbox_create("", RTGUI_TEXTBOX_MASK);
        RTGUI_WIDGET_ALIGN(text) = RTGUI_ALIGN_STRETCH;
        rtgui_widget_set_minwidth(RTGUI_WIDGET(text), 80);
        /*rtgui_widget_set_minheight(RTGUI_WIDGET(text), 25);*/
        rtgui_container_add_child(RTGUI_CONTAINER(panel), RTGUI_WIDGET(text));
    }

    /* Button */
    button = rtgui_button_create("OK");
    rtgui_widget_set_minwidth(RTGUI_WIDGET(button), 80);
    rtgui_widget_set_minheight(RTGUI_WIDGET(button), 25);
    RTGUI_WIDGET_ALIGN(button) = RTGUI_ALIGN_RIGHT;
    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));

    /* re-layout */
    rtgui_container_layout(RTGUI_CONTAINER(win));

    rtgui_win_show(win, RT_FALSE);
    rtgui_app_run(app);

    rtgui_win_destroy(win);
    rtgui_app_destroy(app);
}

int window_application_init()
{
	rt_thread_t tid;

    tid = rt_thread_create("win", window_thread_entry, RT_NULL,
        2048, 20, 5);
    if (tid != RT_NULL)
    {
        rt_thread_startup(tid);
    }

	return 0;
}

