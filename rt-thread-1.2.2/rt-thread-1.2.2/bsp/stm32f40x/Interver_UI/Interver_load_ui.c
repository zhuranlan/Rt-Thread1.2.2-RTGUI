#include "rtthread.h"
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
#include <rtgui/rtgui.h>
#include <rtgui/event.h>
#include <rtgui/rtgui_server.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/rtgui_app.h>
#include <rtgui/widgets/window.h>
#include <rtgui/widgets/widget.h>
#include "messagedialog.h"
#include <rtgui/widgets/progressbar.h>
rtgui_progressbar_t *load_hbar;
static struct rtgui_timer *timer;
int load_progress=0;
struct rtgui_win *win;
struct rtgui_app* app;
    rt_thread_t load_ui;
static rt_bool_t _on_show_rt(struct rtgui_object *object, struct rtgui_event *event)
{
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

		image = rtgui_image_create("/PICTURE/SUST.BMP", RT_TRUE);
		if (image != RT_NULL)
		{
			rtgui_image_blit(image, dc, RT_NULL);
			rtgui_image_destroy(image);
		}
		else
		{
			rt_kprintf("open image:/PICTURE/SUST.BMP failed!\n");
		}

		rtgui_dc_draw_border(dc, &rect, panel->border_style);
        /* paint on each child */
        rtgui_container_dispatch_event(RTGUI_CONTAINER(panel), event);

        rtgui_dc_end_drawing(dc);
		return RT_FALSE;
	}

	return rtgui_panel_event_handler(object, event);
}
static void Load_bar(struct rtgui_timer *timer, void *parameter)
{


	rtgui_progressbar_set_value(load_hbar, load_progress);
	load_progress+=20;

	if(load_progress>=120)
	{
	rtgui_win_destroy(win);
	rtgui_app_destroy(app);
	}
		
}
extern void gui_application_init(void);
rt_bool_t auto_window_close(struct rtgui_object *object, struct rtgui_event *event)
{
    if (timer != RT_NULL)
    {
        rtgui_timer_stop(timer);
        rtgui_timer_destory(timer);

        timer = RT_NULL;
    }
    win = RT_NULL;
	  gui_application_init();
		
	  /*删除线程*/
    rt_thread_delete(load_ui);
    load_ui = RT_NULL;
		rt_kprintf("Load RT-THREAD OK!!\n");
    return RT_TRUE;
}
void loadui_thread_entry(void* parameter) 
{ 
    
    struct rtgui_label *label;
    struct rtgui_rect rect = {0, 0, 480, 320};

    app = rtgui_app_create("MyApp");
    RT_ASSERT(app != RT_NULL);

    win = rtgui_win_create(RT_NULL, "  ", &rect, RTGUI_WIN_STYLE_NO_TITLE |
                           RTGUI_WIN_STYLE_DESTROY_ON_CLOSE);
		 RTGUI_WIDGET_BACKGROUND(win) = black;
		
				
		/*用显示LOGO的部分代码*/
		{
			struct rtgui_panel  *image_panel;
	
			rect.x1 += 140;
			rect.x2 = rect.x1 + 200;
			rect.y1 += 10;
			rect.y2 = rect.y1 + 200;
			
			image_panel = rtgui_panel_create(RTGUI_BORDER_NONE);//RTGUI_BORDER_SIMPLE  RTGUI_BORDER_NONE
			rtgui_widget_set_rect(RTGUI_WIDGET(image_panel), &rect);
			rtgui_object_set_event_handler(RTGUI_OBJECT(image_panel), _on_show_rt);
			RTGUI_WIDGET_ALIGN(image_panel) = RTGUI_ALIGN_EXPAND | RTGUI_ALIGN_STRETCH;
			rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(image_panel));

			rect.x1 = 200;
			rect.x2 = rect.x1 + 200;
			rect.y1 = 250-16;
			rect.y2 = rect.y1 + 16;
			
		  //rt_sprintf(label_text, "Load.......");	
		  label = rtgui_label_create("Load.......");	
			RTGUI_WIDGET_BACKGROUND(label) = black;
			RTGUI_WIDGET_FOREGROUND(label)=white;
		  //rtgui_label_set_text(label, label_text);	
      rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
      rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(label));
			
			rect.x1 = 140;
			rect.x2 = rect.x1 + 200;
			rect.y1 = 250;
			rect.y2 = rect.y1 + 30;
			
		  load_hbar = rtgui_progressbar_create(RTGUI_HORIZONTAL, 100, &rect);
      RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(load_hbar)) = red;
      rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(load_hbar));
	    rtgui_progressbar_set_value(load_hbar, 0);
			
		  timer = rtgui_timer_create(50, RT_TIMER_FLAG_PERIODIC, Load_bar, RT_NULL);
      rtgui_timer_start(timer);
		}

		rtgui_win_set_onclose(win, auto_window_close);

    /* re-layout */
    rtgui_container_layout(RTGUI_CONTAINER(win));

    rtgui_win_show(win, RT_FALSE);
    rtgui_app_run(app);

    rtgui_win_destroy(win);
    rtgui_app_destroy(app);
}
/*开机初始化*/
int load_ui_init(void)
{


    load_ui = rt_thread_create("win", loadui_thread_entry, RT_NULL,
                           2048, 20, 20);
    if (load_ui != RT_NULL)
        rt_thread_startup(load_ui);

	
  return 0;
}
