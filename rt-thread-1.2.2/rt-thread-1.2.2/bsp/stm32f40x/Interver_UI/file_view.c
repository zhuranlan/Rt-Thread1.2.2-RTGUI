#include "view.h"
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/button.h>
#include <rtgui/widgets/filelist_view.h>

#if defined(RTGUI_USING_DFS_FILERW) || defined(RTGUI_USING_STDIO_FILERW)
/* 创建用于演示文件列表视图的视图 */
rtgui_container_t *fn_view(struct rtgui_application *app)
{
    rtgui_rect_t rect={0,30,480,320};
    rtgui_container_t *FILE;

    rtgui_filelist_view_t *flist;

    FILE = view("文件");
 
    rect.x1 += 5;
	  rect.y1 += 5;
    rect.x2 -= 5;
    rect.y2 -= 10;

    flist = rtgui_filelist_view_create("/", "*.*", &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(FILE), RTGUI_WIDGET(flist));

    return FILE;
}
#endif
