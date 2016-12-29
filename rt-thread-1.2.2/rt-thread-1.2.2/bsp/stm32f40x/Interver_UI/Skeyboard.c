#include <rtthread.h>
#include <rtgui/widgets/window.h>
#include <rtgui/widgets/button.h>
#include "view.h"
#include <rtgui/widgets/textbox.h>
#include <rtgui/widgets/panel.h>
#include "Interver_RTU.h"

extern struct power_parameter power_data;
//unsigned char KeyBoard_Data[20]="0000000";
//unsigned char KeyBoard_DataC[20]="0000000";
//static int number=6;
//static int number_key=0;
//struct Key_board_Value
//	{
//  rt_uint32_t Value_data_Decimal;
//  };

//struct Key_board_Value keyboard_data;
//static void Softkeyboard_ok(struct rtgui_object *object, rtgui_event_t *event)
//{
//	int i,j;
//	keyboard_data.Value_data_Decimal=0;
//	
//	keyboard_data.Value_data_Decimal+=(KeyBoard_DataC[number]-48);
//	keyboard_data.Value_data_Decimal+=(KeyBoard_DataC[number-1]-48)*10;
//	keyboard_data.Value_data_Decimal+=(KeyBoard_DataC[number-2]-48)*100;
//	keyboard_data.Value_data_Decimal+=(KeyBoard_DataC[number-3]-48)*1000;
//	keyboard_data.Value_data_Decimal+=(KeyBoard_DataC[number-4]-48)*10000;
//	keyboard_data.Value_data_Decimal+=(KeyBoard_DataC[number-5]-48)*100000;
//	keyboard_data.Value_data_Decimal+=(KeyBoard_DataC[number-6]-48)*1000000;
//	power_data.SET_DATA=keyboard_data.Value_data_Decimal;
//}


//static void Softkeyboard_clear(struct rtgui_object *object, rtgui_event_t *event)
//{
//	  int i;
//	  struct rtgui_textbox* text;
//    number_key=0;
//	  text = RTGUI_TEXTBOX(rtgui_get_self_object(Data_key_board));
//	  for(i=0;i<number+1;i++)
//	{
//    KeyBoard_Data[i]=0+48;
//		KeyBoard_DataC[i]=0+48;
//	}
//    rtgui_textbox_set_value(text, KeyBoard_DataC);
//    rtgui_widget_update(RTGUI_WIDGET(text));
//}

//static void Softkeyboard_num_0(struct rtgui_object *object, rtgui_event_t *event)
//{
//	  struct rtgui_textbox* text;
//	  int i,j;
//	
//	  text = RTGUI_TEXTBOX(rtgui_get_self_object(Data_key_board));
//    KeyBoard_Data[number_key]=0+48;
//	  if(number_key<=number&&number_key!=0)
//	  number_key++;
//		for(i=number_key,j=0;i>0;i--,j++)
//    KeyBoard_DataC[number-i+1]=KeyBoard_Data[j];
//    rtgui_textbox_set_value(text, KeyBoard_DataC);
//    rtgui_widget_update(RTGUI_WIDGET(text));
//		

//}

//static void Softkeyboard_num_1(struct rtgui_object *object, rtgui_event_t *event)
//{
//	  struct rtgui_textbox* text;
//    int i,j;
//	  text = RTGUI_TEXTBOX(rtgui_get_self_object(Data_key_board));
//    KeyBoard_Data[number_key]=1+48;
//	  if(number_key<=number)
//	  number_key++;
//		for(i=number_key,j=0;i>0;i--,j++)
//    KeyBoard_DataC[number-i+1]=KeyBoard_Data[j];
//    rtgui_textbox_set_value(text, KeyBoard_DataC);
//    rtgui_widget_update(RTGUI_WIDGET(text));
//}

//static void Softkeyboard_num_2(struct rtgui_object *object, rtgui_event_t *event)
//{
//	  struct rtgui_textbox* text;
//	  int i,j;
//	  text = RTGUI_TEXTBOX(rtgui_get_self_object(Data_key_board));
//    

//		KeyBoard_Data[number_key]=2+48;
//	  if(number_key<=number)
//	  number_key++;
//		for(i=number_key,j=0;i>0;i--,j++)
//    KeyBoard_DataC[number-i+1]=KeyBoard_Data[j];
//    rtgui_textbox_set_value(text, KeyBoard_DataC);
//    rtgui_widget_update(RTGUI_WIDGET(text));
//}

//static void Softkeyboard_num_3(struct rtgui_object *object, rtgui_event_t *event)
//{
//	  struct rtgui_textbox* text;
//	  int i,j;
//	
//	  text = RTGUI_TEXTBOX(rtgui_get_self_object(Data_key_board));
//    KeyBoard_Data[number_key]=3+48;
//	  if(number_key<=number)
//	  number_key++;
//		for(i=number_key,j=0;i>0;i--,j++)
//    KeyBoard_DataC[number-i+1]=KeyBoard_Data[j];
//    rtgui_textbox_set_value(text, KeyBoard_DataC);
//    rtgui_widget_update(RTGUI_WIDGET(text));
//}

//static void Softkeyboard_num_4(struct rtgui_object *object, rtgui_event_t *event)
//{
//	  struct rtgui_textbox* text;
//	  int i,j;
//	  text = RTGUI_TEXTBOX(rtgui_get_self_object(Data_key_board));
//    KeyBoard_Data[number_key]=4+48;
//	  if(number_key<=number)
//	  number_key++;
//		for(i=number_key,j=0;i>0;i--,j++)
//    KeyBoard_DataC[number-i+1]=KeyBoard_Data[j];
//    rtgui_textbox_set_value(text, KeyBoard_DataC);
//    rtgui_widget_update(RTGUI_WIDGET(text));
//}

//static void Softkeyboard_num_5(struct rtgui_object *object, rtgui_event_t *event)
//{
//	  struct rtgui_textbox* text;
//	  int i,j;
//	
//	  text = RTGUI_TEXTBOX(rtgui_get_self_object(Data_key_board));
//    KeyBoard_Data[number_key]=5+48;
//	  if(number_key<=number)
//	  number_key++;
//		for(i=number_key,j=0;i>0;i--,j++)
//    KeyBoard_DataC[number-i+1]=KeyBoard_Data[j];
//    rtgui_textbox_set_value(text, KeyBoard_DataC);
//    rtgui_widget_update(RTGUI_WIDGET(text));
//}

//static void Softkeyboard_num_6(struct rtgui_object *object, rtgui_event_t *event)
//{
//	  struct rtgui_textbox* text;
//	  int i,j;
//	
//	  text = RTGUI_TEXTBOX(rtgui_get_self_object(Data_key_board));
//    KeyBoard_Data[number_key]=6+48;
//	  if(number_key<=number)
//	  number_key++;
//		for(i=number_key,j=0;i>0;i--,j++)
//    KeyBoard_DataC[number-i+1]=KeyBoard_Data[j];
//    rtgui_textbox_set_value(text, KeyBoard_DataC);
//    rtgui_widget_update(RTGUI_WIDGET(text));
//}

//static void Softkeyboard_num_7(struct rtgui_object *object, rtgui_event_t *event)
//{
//	  struct rtgui_textbox* text;
//	  int i,j;
//	
//	  text = RTGUI_TEXTBOX(rtgui_get_self_object(Data_key_board));
//    KeyBoard_Data[number_key]=7+48;
//	  if(number_key<=number)
//	  number_key++;
//		for(i=number_key,j=0;i>0;i--,j++)
//    KeyBoard_DataC[number-i+1]=KeyBoard_Data[j];
//    rtgui_textbox_set_value(text, KeyBoard_DataC);
//    rtgui_widget_update(RTGUI_WIDGET(text));
//}
//static void Softkeyboard_num_8(struct rtgui_object *object, rtgui_event_t *event)
//{
//	  struct rtgui_textbox* text;
//	  int i,j;
//	
//	  text = RTGUI_TEXTBOX(rtgui_get_self_object(Data_key_board));
//    KeyBoard_Data[number_key]=8+48;
//	  if(number_key<=number)
//	  number_key++;
//		for(i=number_key,j=0;i>0;i--,j++)
//    KeyBoard_DataC[number-i+1]=KeyBoard_Data[j];
//    rtgui_textbox_set_value(text, KeyBoard_DataC);
//    rtgui_widget_update(RTGUI_WIDGET(text));
//}

//static void Softkeyboard_num_9(struct rtgui_object *object, rtgui_event_t *event)
//{
//	  struct rtgui_textbox* text;
//	  int i,j;
//	
//	  text = RTGUI_TEXTBOX(rtgui_get_self_object(Data_key_board));
//    KeyBoard_Data[number_key]=9+48;
//	  if(number_key<=number)
//	  number_key++;
//		for(i=number_key,j=0;i>0;i--,j++)
//    KeyBoard_DataC[number-i+1]=KeyBoard_Data[j];
//    rtgui_textbox_set_value(text, KeyBoard_DataC);
//    rtgui_widget_update(RTGUI_WIDGET(text));
//}


//void Load_Keyboard(rtgui_win_t *win,rt_uint32_t rect_X,rt_uint32_t rect_Y)
//{
//		rtgui_button_t *button;
//    rtgui_rect_t rect;  
////	  rtgui_label_t *label;
//	  struct rtgui_textbox* text;

//		rect.x1=rect_X+45;
//		rect.y1=rect_Y+10;
//		rect.x2 = rect.x1+60;
//    rect.y2 = rect.y1 + 25;
//    text = rtgui_textbox_create("0000000", RTGUI_TEXTBOX_SINGLE);
//    rtgui_widget_set_rect(RTGUI_WIDGET(text), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(text));
//	  rtgui_object_set_id(RTGUI_OBJECT(text), Data_key_board);
//	 
//    rect.x1 = rect_X;
//		rect.y1 = rect_Y;
//		rect.x2 = rect.x1 + 35;
//    rect.y2 = rect.y1 + 35;
//	
//    rect.x2 = rect.x1 + 35;
//		rect.y1 += 40;
//    rect.y2 = rect.y1 + 35;
//		button = rtgui_button_create("1");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
//		rtgui_button_set_onbutton(button, Softkeyboard_num_1);

//    rect.x1 += 40;
//    rect.x2 = rect.x1+35;
//		button = rtgui_button_create("2");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
//		rtgui_button_set_onbutton(button, Softkeyboard_num_2);
//		
//		rect.x1 += 40;
//    rect.x2 = rect.x1+35;
//		button = rtgui_button_create("3");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
//		rtgui_button_set_onbutton(button, Softkeyboard_num_3);
//		
//		rect.x1 += 40;
//    rect.x2 = rect.x1+35;
//		button = rtgui_button_create("A");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
//		
//		rect.x1 = rect_X;
//    rect.x2 = rect.x1+35;
//		rect.y1 += 40;
//    rect.y2 = rect.y1 + 35;
//		button = rtgui_button_create("4");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
//		rtgui_button_set_onbutton(button, Softkeyboard_num_4);
//		
//		rect.x1 += 40;
//    rect.x2 = rect.x1+35;
//		button = rtgui_button_create("5");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
//		rtgui_button_set_onbutton(button, Softkeyboard_num_5);
//		
//		rect.x1 += 40;
//    rect.x2 = rect.x1+35;
//		button = rtgui_button_create("6");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
//		rtgui_button_set_onbutton(button, Softkeyboard_num_6);
//		
//				rect.x1 += 40;
//    rect.x2 = rect.x1+35;
//		button = rtgui_button_create("B");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
//		
//		
//		rect.x1 = rect_X;
//    rect.x2 = rect.x1+35;
//		rect.y1 += 40;
//    rect.y2 = rect.y1 + 35;
//		button = rtgui_button_create("7");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
//		rtgui_button_set_onbutton(button, Softkeyboard_num_7);
//		
//		rect.x1 += 40;
//    rect.x2 = rect.x1+35;
//		button = rtgui_button_create("8");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
//		rtgui_button_set_onbutton(button, Softkeyboard_num_8);
//		
//		rect.x1 += 40;
//    rect.x2 = rect.x1+35;
//		button = rtgui_button_create("9");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
//		rtgui_button_set_onbutton(button, Softkeyboard_num_9);
//		
//		rect.x1 += 40;
//    rect.x2 = rect.x1+35;
//		button = rtgui_button_create("C");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
//		
//		
//		rect.x1 = rect_X;
//    rect.x2 = rect.x1+35;
//		rect.y1 += 40;
//    rect.y2 = rect.y1 + 35;
//		button = rtgui_button_create("F");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
//		
//	  rect.x1 += 40;
//    rect.x2 = rect.x1+35;
//		button = rtgui_button_create("0");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
//		rtgui_button_set_onbutton(button, Softkeyboard_num_0);
//		
//		rect.x1 += 40;
//    rect.x2 = rect.x1+35;
//		button = rtgui_button_create("E");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
//		
//	  rect.x1 += 40;
//    rect.x2 = rect.x1+35;
//		button = rtgui_button_create("D");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
//		
//		
//		rect.x1 = rect_X;
//    rect.x2 = rect.x1+75;
//		rect.y1 += 40;
//    rect.y2 = rect.y1 + 35;
//		button = rtgui_button_create("Clear");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
//		rtgui_button_set_onbutton(button, Softkeyboard_clear);
//		
//		rect.x1 += 80;
//    rect.x2 = rect.x1+75;
//		button = rtgui_button_create("Ok");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
//	  rtgui_button_set_onbutton(button, Softkeyboard_ok);
//}




//void Load_Keyboard_C(rtgui_container_t *container,rt_uint32_t rect_X,rt_uint32_t rect_Y)
//{
//		rtgui_button_t *button;
//    rtgui_rect_t rect;  
//	
//		rect.x1=rect_X;
//		rect.y1=rect_Y;
//		rect.x2 = rect.x1+35;
//    rect.y2 = rect.y1 + 35;
//		button = rtgui_button_create("1");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(container, RTGUI_WIDGET(button));
//		rtgui_button_set_onbutton(button, Softkeyboard_num_1);

//    rect.x1 += 40;
//    rect.x2 = rect.x1+35;
//		button = rtgui_button_create("2");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(container, RTGUI_WIDGET(button));
//		
//		rect.x1 += 40;
//    rect.x2 = rect.x1+35;
//		button = rtgui_button_create("3");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(container, RTGUI_WIDGET(button));
//		
//		rect.x1 += 40;
//    rect.x2 = rect.x1+35;
//		button = rtgui_button_create("A");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(container, RTGUI_WIDGET(button));
//		
//		rect.x1 = 300;
//    rect.x2 = rect.x1+35;
//		rect.y1 += 40;
//    rect.y2 = rect.y1 + 35;
//		button = rtgui_button_create("4");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(container, RTGUI_WIDGET(button));
//		
//		rect.x1 += 40;
//    rect.x2 = rect.x1+35;
//		button = rtgui_button_create("5");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(container, RTGUI_WIDGET(button));
//		
//		rect.x1 += 40;
//    rect.x2 = rect.x1+35;
//		button = rtgui_button_create("6");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(container, RTGUI_WIDGET(button));
//		
//				rect.x1 += 40;
//    rect.x2 = rect.x1+35;
//		button = rtgui_button_create("B");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(container, RTGUI_WIDGET(button));
//		
//		
//		rect.x1 = 300;
//    rect.x2 = rect.x1+35;
//		rect.y1 += 40;
//    rect.y2 = rect.y1 + 35;
//		button = rtgui_button_create("7");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(container, RTGUI_WIDGET(button));
//		
//		rect.x1 += 40;
//    rect.x2 = rect.x1+35;
//		button = rtgui_button_create("8");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(container, RTGUI_WIDGET(button));
//		
//		rect.x1 += 40;
//    rect.x2 = rect.x1+35;
//		button = rtgui_button_create("9");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(container, RTGUI_WIDGET(button));
//		
//		rect.x1 += 40;
//    rect.x2 = rect.x1+35;
//		button = rtgui_button_create("C");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(container, RTGUI_WIDGET(button));


//		rect.x1 = 300;
//    rect.x2 = rect.x1+35;
//		rect.y1 += 40;
//    rect.y2 = rect.y1 + 35;
//		button = rtgui_button_create("F");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(container, RTGUI_WIDGET(button));
//		
//	  rect.x1 += 40;
//    rect.x2 = rect.x1+35;
//		button = rtgui_button_create("0");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(container, RTGUI_WIDGET(button));
//		
//		rect.x1 += 40;
//    rect.x2 = rect.x1+35;
//		button = rtgui_button_create("E");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(container, RTGUI_WIDGET(button));
//		
//	  rect.x1 += 40;
//    rect.x2 = rect.x1+35;
//		button = rtgui_button_create("D");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(container, RTGUI_WIDGET(button));
//		
//		
//		rect.x1 = 300;
//    rect.x2 = rect.x1+75;
//		rect.y1 += 40;
//    rect.y2 = rect.y1 + 35;
//		button = rtgui_button_create("Clear");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(container, RTGUI_WIDGET(button));
//		
//		rect.x1 += 80;
//    rect.x2 = rect.x1+75;
//		button = rtgui_button_create("Ok");
//    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
//    rtgui_container_add_child(container, RTGUI_WIDGET(button));
//	
//}
