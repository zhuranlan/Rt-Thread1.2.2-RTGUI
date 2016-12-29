/*
 * 程序清单：view演示
 *
 * 这是一个视图的演示，也是为了配合整个GUI演示而制作的视图，或者说，其他大多数控件的演示
 * 都是采用，先创建一个demo_view（演示视图），然后再在这个演示视图上添加相应的控件。
 *
 * 这个演示视图默认上方带一个演示标题，下方带两个按钮，点击它切换到前一个视图或后一个视图。
 * 针对控件演示而言，这个演示视图最重要的是提供了一个可显示的区域，只需要在这块区域上添加
 * 控件即可达到演示的目的。
 *
 * 获得这个显示区域的函数是：
 * demo_view_get_rect函数。
 */
#ifndef __VIEW_H__
#define __VIEW_H__

#include <rtgui/rtgui.h>
#include <rtgui/rtgui_app.h>
#include <rtgui/widgets/container.h>

/* 如果是标准版本，可以启用box自动布局引擎 */
#ifndef RTGUI_USING_SMALL_SIZE
#include <rtgui/widgets/box.h>
#endif

/*用来枚举控件ID号*/
enum {
    NORMAL_WIN_ID,
    NORMAL_WIN_LABEL_ID,
		USER_DATA_1,
		USER_DATA_2,
		USER_DATA_3,
		USER_DATA_4,
		USER_DATA_5,
		USER_DATA_6,
    AUTO_CLOSE_LABEL_ID,
	  VOLTAGE_Z_ID,
	  VOLTAGE_A_ID,
	  VOLTAGE_B_ID,
	  VOLTAGE_C_ID,
    CURRENT_A_ID,
	  CURRENT_B_ID,
	  CURRENT_C_ID,
	  SET_DATA_ID,
	  DUTY_ID,
	  Temperature_ID,
	MCU_INFORMATION_ID,
	MCU_INFORMATION_ID2,
	MCU_INFORMATION_ID3,
	MCU_INFORMATION_ID4,
  MCU_INFORMATION_ID5,
	MCU_INFORMATION_ID6,
	MCU_INFORMATION_ID7,
	MCU_INFORMATION_ID8,
	MCU_INFORMATION_ID9,
	LOADDATA_PRO_ID,
	AUTO_LABEL_ID,
	AUTO_TIME_ID,
	AUTO_TIME_ID2,
	AUTO_TIME_ID3,
	AUTO_TIME_ID4,
	AUTO_TIME_ID5,
	AUTO_TIME_ID6,
  AUTO_TIME_ID7,
	AUTO_TIME_ID8,
	AUTO_TIME_ID9,
	  TIMEDATE1_ID,
	  TIMEDATE2_ID,
	  USB_HOST_msgx_ID,
	  RAM_Information_1,
	  RAM_Information_2,
	  CPU_Information,
		Text_ip_1,
		Data_key_board,
		Data_key_board_user,
		SIMPLE_TIME_CH1,
		SIMPLE_TIME_CH2,
		SIMPLE_TIME_CH3,
		USER_DATA_NAME_1,
		USER_DATA_NAME_2,
		USER_DATA_NAME_3,
		USER_DATA_NAME_4,
		USER_DATA_NAME_5,
		USER_DATA_NAME_6,	
		USER_DATA_SETTING_1,
		USER_DATA_SETTING_2,
		USER_DATA_SETTING_3,
		USER_DATA_SETTING_4,
		USER_DATA_SETTING_5,
		SCOPE_PANEL_ID,
		Digtube_ID
};
/* 创建一个演示视图，需要给出这个视图的演示标题 */
rtgui_container_t *view(const char *title);
/* 获得演示视图提供给演示控件用的区域信息 */
void view_get_rect(rtgui_container_t *view, rtgui_rect_t *rect);
void view_get_logic_rect(rtgui_container_t *view, rtgui_rect_t *rect);
void view_show(void);

#endif
