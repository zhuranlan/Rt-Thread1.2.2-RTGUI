#include <rtgui/rtgui.h>
#include <rtgui/rtgui_app.h>
#include <rtgui/widgets/window.h>
#include <rtgui/widgets/textbox.h>
#include <rtgui/widgets/panel.h>
#include <rtgui/widgets/box.h>
#include <rtgui/widgets/label.h>
#include <rtgui/driver.h>
#include <rtgui/region.h>
#include <rtgui/widgets/button.h>
#include <rtgui/widgets/notebook.h>
#include <rtgui/widgets/container.h>
#include <rtgui/widgets/notebook.h>
#include <rtgui/widgets/button.h>
#include <rtgui/widgets/staticline.h>
#include <rtgui/widgets/box.h>
#include <rtgui/widgets/textview.h>
#include <rtgui/widgets/container.h>
#include <rtgui/widgets/notebook.h>
#include <rtgui/widgets/button.h>
#include <rtgui/widgets/staticline.h>
#include <rtgui/widgets/box.h>
#include <rtgui/widgets/progressbar.h>
#include "view.h"
#include "time.h"


//static rt_bool_t  handle_key(struct rtgui_object *object, struct rtgui_event *event)
//{
//    struct rtgui_event_kbd *ekbd = (struct rtgui_event_kbd *)event;

//    if (ekbd->type == RTGUI_KEYUP)
//    {
//        if (ekbd->key == RTGUIK_RIGHT)
//        {
//            view_next(RT_NULL, RT_NULL);
//            return RT_TRUE;
//        }
//        else if (ekbd->key == RTGUIK_LEFT)
//        {
//            view_prev(RT_NULL, RT_NULL);
//            return RT_TRUE;
//        }
//    }
//    return RT_TRUE;
//}


struct rtgui_notebook *the_notebook;
struct rtgui_win *main_win;
extern rtgui_container_t *scope_setting_panel(void);
extern rtgui_container_t *scope_windows(void);
extern rtgui_container_t * Interver_window(void);
extern rtgui_container_t * direction_view(void) ;
extern rtgui_container_t * User_panel(void);
extern rtgui_container_t * Grid_connected_panel(void);
static void gui_application_entry(void *parameter)
{
  struct rtgui_app *app;
	struct rtgui_rect rect={0,0,480,320};
	struct rtgui_button* btn;

    app = rtgui_app_create("gui");
    if (app == RT_NULL)
        return;

   rtgui_graphic_driver_get_rect(rtgui_graphic_driver_get_default(), &rect);

    main_win = rtgui_win_create(RT_NULL, "demo", &rect,
                                RTGUI_WIN_STYLE_NO_BORDER | RTGUI_WIN_STYLE_NO_TITLE);
    if (main_win == RT_NULL)
    {
        rtgui_app_destroy(app);
        return;
    }

       // rtgui_win_set_onkey(main_win, handle_key);
	     /* create lable in main container */


       /* create a no title notebook that we can switch demo on it easily. */
       the_notebook = rtgui_notebook_create(&rect,RTGUI_NOTEBOOK_TOP);
        if (the_notebook == RT_NULL)
       {
        rtgui_win_destroy(main_win);
        rtgui_app_destroy(app);
        return;
        }
			 
			direction_view();
			Interver_window();
			//view_progressbar();
			//win_picture_entry();
			//demo_view_buffer_animation();
			#if defined(RTGUI_USING_DFS_FILERW)
			  //fn_view();
			#endif
				//view_digtube();
				//plot();
					
			scope_windows();
			scope_setting_panel();
			User_panel();
			Grid_connected_panel();
			//demo_view_buffer_animation();
			//demo_view_dc_buffer();

			


	  rtgui_container_add_child(RTGUI_CONTAINER(main_win), RTGUI_WIDGET(the_notebook));

    rtgui_win_show(main_win, RT_FALSE);

    /* 执行工作台事件循环 */
    rtgui_app_run(app);

    rtgui_app_destroy(app);
}




void gui_application_init(void);
static rt_uint8_t gui_application_stack[ 1024*3 ] __attribute__((at(0X10000000+1024*28)));
static struct rt_thread gui;

void gui_application_init(void)
{
	
	rt_err_t result;

	result = rt_thread_init(&gui,
		                    "powergui",
		                    gui_application_entry, 
							RT_NULL,
		                    &gui_application_stack[0],
							sizeof(gui_application_stack),
							28,
							5
							);

	if (result == RT_EOK)
    rt_thread_startup(&gui);
	
	

    
}