/*
 * �����嵥��view��ʾ
 *
 * ����һ����ͼ����ʾ��Ҳ��Ϊ���������GUI��ʾ����������ͼ������˵������������ؼ�����ʾ
 * ���ǲ��ã��ȴ���һ��demo_view����ʾ��ͼ����Ȼ�����������ʾ��ͼ�������Ӧ�Ŀؼ���
 *
 * �����ʾ��ͼĬ���Ϸ���һ����ʾ���⣬�·���������ť��������л���ǰһ����ͼ���һ����ͼ��
 * ��Կؼ���ʾ���ԣ������ʾ��ͼ����Ҫ�����ṩ��һ������ʾ������ֻ��Ҫ��������������
 * �ؼ����ɴﵽ��ʾ��Ŀ�ġ�
 *
 * ��������ʾ����ĺ����ǣ�
 * demo_view_get_rect������
 */
#ifndef __VIEW_H__
#define __VIEW_H__

#include <rtgui/rtgui.h>
#include <rtgui/rtgui_app.h>
#include <rtgui/widgets/container.h>

/* ����Ǳ�׼�汾����������box�Զ��������� */
#ifndef RTGUI_USING_SMALL_SIZE
#include <rtgui/widgets/box.h>
#endif

/*����ö�ٿؼ�ID��*/
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
/* ����һ����ʾ��ͼ����Ҫ���������ͼ����ʾ���� */
rtgui_container_t *view(const char *title);
/* �����ʾ��ͼ�ṩ����ʾ�ؼ��õ�������Ϣ */
void view_get_rect(rtgui_container_t *view, rtgui_rect_t *rect);
void view_get_logic_rect(rtgui_container_t *view, rtgui_rect_t *rect);
void view_show(void);

#endif
