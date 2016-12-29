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
struct rtgui_digtube * digtube;
rtgui_container_t *container_Grid;
extern struct rtgui_notebook *the_notebook;
static struct rtgui_timer *timer_grid;

static void Grid_update(struct rtgui_timer *timer, void *parameter)
{
	struct rtgui_rect rect;
	if(rtgui_notebook_get_current_index(the_notebook)==5)
	{
//	 digtube=RTGUI_DIGTUBE(rtgui_get_self_object(Digtube_ID));
//	 /* add digtube 1: use the default digit font */
//	 digtube = rtgui_digtube_create(RT_NULL, 5, (void *)1234, 0);	
//   //rtgui_widget_set_rect(RTGUI_WIDGET(digtube), &rect);
//	 rtgui_widget_update(RTGUI_WIDGET(digtube));
	}
	
}



rtgui_container_t * Grid_connected_panel(void)
{	
	  struct rtgui_digitfont digitfont;
	  struct rtgui_textbox* text;
		struct rtgui_label      *label;
	  
	  struct rtgui_rect rect;
	  container_Grid = view("²¢Íø");
		if (container_Grid == RT_NULL)
    return RT_NULL;
		
		view_get_rect(container_Grid, &rect);
	  rect.y2 = rect.y1 + 80;

		/* add digtube 1: use the default digit font */
	  digtube = rtgui_digtube_create(RT_NULL, 5, (void *)4213, 0);	
		rtgui_widget_set_rect(RTGUI_WIDGET(digtube), &rect);
	  rtgui_container_add_child(container_Grid, RTGUI_WIDGET(digtube));
		rtgui_object_set_id(RTGUI_OBJECT(digtube), Digtube_ID);
		
		timer_grid = rtgui_timer_create(50, RT_TIMER_FLAG_PERIODIC, Grid_update, RT_NULL);
	  rtgui_timer_start(timer_grid);		
		
		return container_Grid;
		
	}