#include "view.h"
#include <rtgui/dc.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/slider.h>
#include <rtgui/image_hdc.h>
#include <rtgui/widgets/combobox.h>
#include <rtgui/dc.h>
#include <rtgui/dc_hw.h>
#include <rtgui/widgets/container.h>

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
#include "Interver_RTU.h"
#include <rtgui/widgets/progressbar.h>
#include <rtgui/widgets/checkbox.h>
#include <rtgui/widgets/scrollbar.h>
#include "arm_math.h"
extern  void GO_TO_Scope(void);
#define Sample_Frequency power_data.DSP_Sampling_f//DSP采样频率 单位HZ
extern unsigned char complete_flag_ch1,complete_flag_ch2,complete_flag_ch3;
//extern q15_t store_data_ch1[1600],store_data_ch2[1600],store_data_ch3[1600];
extern q15_t store_data[8192];
extern char label_text[100];
struct rtgui_win *scope_analyse_win;
extern char * rt_kprintf_float(double data);
extern void screenshot(const char *filename);
extern struct rtgui_notebook *the_notebook;
unsigned char FFT_Open_flag=0;
rtgui_win_t *win_analyze;
extern rtgui_checkbox_t *ch1_checkbox,*ch2_checkbox,*ch3_checkbox,*ch1_checkbox_1,*ch2_checkbox_1,*ch3_checkbox_1;
unsigned int current_scrollbar_valve_fft=0;
#define TEST_LENGTH_SAMPLES 2048 //采样点数
#define fftSize  1024//定义变换点数
/* ------------------------------------------------------------------- 
* External Input and Output buffer Declarations for FFT Bin Example 
* ------------------------------------------------------------------- */ 
extern const float32_t testInput_f32_10khz[2048]; 
float32_t fftOutput_f32[2048]__attribute__((at(0X10000000+1024*4)));
float32_t fftInput_f32[2048]__attribute__((at(0X10000000+1024*32+1024*16)));
/* ------------------------------------------------------------------ 
* Global variables for FFT Bin Example 
* ------------------------------------------------------------------- */ 
/*设定上位机的采样频率为1KHZ*/
uint32_t ifftFlag = 0; 
uint32_t doBitReverse = 1;
uint16_t graphic_count=0;
float32_t maxValue,maxValue_1,maxValue_2,maxValue_3,maxValue_4,maxValue_5,maxValue_all[6],dc_0hz; 
/* Reference index at which max energy of bin ocuurs */ 
uint32_t testIndex = 0;
uint32_t main_hz,main_hz_1,main_hz_2,main_hz_3,main_hz_4,main_hz_5,main_hz_all[6];
int32_t fft_convert(void) 
{ 
 uint16_t i;
 arm_rfft_fast_instance_f32 S;
 //float32_t * fftOutput_f32=(float32_t *) rt_malloc(2048);//申请RAM
	
 for(i=0;i<2048;i++)
 fftOutput_f32[i]=0;
	 
 ifftFlag = 0;
 arm_rfft_fast_init_f32(&S, fftSize);

 arm_rfft_fast_f32(&S, fftInput_f32, fftOutput_f32, ifftFlag);
 arm_cmplx_mag_f32(fftOutput_f32, fftInput_f32, fftSize);//为了节约RAM  将输入作为输出使用
// rt_free(fftOutput_f32);//释放RAM
	/*进行真实幅值计算  mv*/
		for(i=1;i<1024;i++)
		fftInput_f32[i]=1000*(fftInput_f32[i]/(1024/2))/512;
	
	dc_0hz=fftInput_f32[0];
	fftInput_f32[0]=0;
/* Calculates maxValue and returns corresponding BIN value */ 
	 arm_max_f32(fftInput_f32, fftSize, &maxValue, &main_hz); 
   
	fftInput_f32[main_hz]=0;
	arm_max_f32(fftInput_f32, fftSize, &maxValue_1, &main_hz_1); 
	
	fftInput_f32[main_hz_1]=0;
	arm_max_f32(fftInput_f32, fftSize, &maxValue_2, &main_hz_2); 
	
	fftInput_f32[main_hz_2]=0;
	arm_max_f32(fftInput_f32, fftSize, &maxValue_3, &main_hz_3); 
	
	fftInput_f32[main_hz_3]=0;
	arm_max_f32(fftInput_f32, fftSize, &maxValue_4, &main_hz_4); 
	
	fftInput_f32[main_hz_4]=0;
	arm_max_f32(fftInput_f32, fftSize, &maxValue_5, &main_hz_5); 
	
	
	fftInput_f32[0]=dc_0hz;
	fftInput_f32[main_hz]=maxValue;
	fftInput_f32[main_hz_1]=maxValue_1;
	fftInput_f32[main_hz_2]=maxValue_2;
	fftInput_f32[main_hz_3]=maxValue_3;
	fftInput_f32[main_hz_4]=maxValue_4;
	fftInput_f32[main_hz_5]=maxValue_5;

  return 0;
} 

void dc_fft_event_handler(struct rtgui_dc *analyze_dc)
{        
    rtgui_rect_t rect;
    int i,j;
	  float32_t max_vlve,rate;
	  uint32_t place_max;
	
    /*绘制底板颜色以及尺寸*/
    rect.x1 = 0;
		rect.x2 = rect.x1+360;
    rect.y1 = 0;
    rect.y2 = rect.y1+240;
	  RTGUI_DC_FC(analyze_dc) = black;
    rtgui_dc_fill_round_rect(analyze_dc, &rect, 0);
	
		main_hz=main_hz*Sample_Frequency/1024;		
		main_hz_1=main_hz_1*Sample_Frequency/1024;		
		main_hz_2=main_hz_2*Sample_Frequency/1024;		
		main_hz_3=main_hz_3*Sample_Frequency/1024;		
		main_hz_4=main_hz_4*Sample_Frequency/1024;
    main_hz_5=main_hz_5*Sample_Frequency/1024;
	
	 /*在这里添加数值的显示*/
		rect.x1=0;
		rect.y1=0;
		rect.y2=rect.y1+16;
		
		RTGUI_DC_FC(analyze_dc) = Red;
		rect.x2=rect.x1+sizeof(label_text)*8;
	  rt_sprintf(label_text, "           采样频率:%dHZ",Sample_Frequency); 
		rtgui_dc_draw_text(analyze_dc, label_text, &rect);
		
	  rect.y1+=16;
		rect.y2=rect.y1+16;
		RTGUI_DC_FC(analyze_dc) = white;		
	  rt_sprintf(label_text, "1:%dHZ %d  2:%dHZ %d",(main_hz),(unsigned int)(maxValue),
		                                              (main_hz_1),(unsigned int)(maxValue_1)); 
		rect.x2=rect.x1+sizeof(label_text)*8;
		rtgui_dc_draw_text(analyze_dc, label_text, &rect);
					
		rect.y1+=16;
		rect.y2=rect.y1+16;
		RTGUI_DC_FC(analyze_dc) = white;		
	  rt_sprintf(label_text, "3:%dHZ %d  4:%dHZ %d",(main_hz_2),(unsigned int)(maxValue_2),
		                                              (main_hz_3),(unsigned int)(maxValue_3)); 
		rect.x2=rect.x1+sizeof(label_text)*8;
		rtgui_dc_draw_text(analyze_dc, label_text, &rect);
		
		
		rect.y1+=16;
		rect.y2=rect.y1+16;
		RTGUI_DC_FC(analyze_dc) = white;		
	  rt_sprintf(label_text, "5:%dHZ %d  6:%dHZ %d",(main_hz_4),(unsigned int)(maxValue_4),
		                                              (main_hz_5),(unsigned int)(maxValue_5)); 
		rect.x2=rect.x1+sizeof(label_text)*8;
		rtgui_dc_draw_text(analyze_dc, label_text, &rect);
				
//		RTGUI_DC_FC(analyze_dc) = white;
//		rect.x2=rect.x1+sizeof(label_text)*8;
//	  rt_sprintf(label_text, "testIndex:%sHZ 采样频率:%dHZ",rt_kprintf_float(main_hz),Sample_Frequency); 
//		rtgui_dc_draw_text(analyze_dc, label_text, &rect);
//			
//		rect.y1+=16;
//		rect.y2=rect.y1+16;
//		RTGUI_DC_FC(analyze_dc) = white;
//	  rt_sprintf(label_text, "maxValue:%s",rt_kprintf_float(maxValue)); 
//	  rect.x2=rect.x1+sizeof(label_text)*8;
//	  rtgui_dc_draw_text(analyze_dc, label_text, &rect);
//		
//		rect.y1+=16;
//		rect.y2=rect.y1+16;
//		RTGUI_DC_FC(analyze_dc) = white;
//	  rt_sprintf(label_text, "直流分量:%s",rt_kprintf_float(fftInput_f32[0])); 
//	  rect.x2=rect.x1+sizeof(label_text)*8;
//	  rtgui_dc_draw_text(analyze_dc, label_text, &rect);
		
	   /*去除直流分量*/
		// graphic[0]=0;
		fftInput_f32[0]=0;
		/*智能调整数值的幅度*/
		arm_max_f32(fftInput_f32, 360, &max_vlve, &place_max); 
		rate=160/max_vlve;
		/*面板上绘制条形图  频谱图*/
		//RTGUI_DC_FC(analyze_dc) = white;
		RTGUI_DC_FC(analyze_dc) = RTGUI_RGB(00, 0x99, 0xff);
		for(i=0;i<360;i++)
		rtgui_dc_draw_line(analyze_dc,i,220,i,220-rate*fftInput_f32[i]);
		

/*频谱图刻度*/
  rect.y1=220;
	rect.y2=rect.y1+16;
	RTGUI_DC_FC(analyze_dc) = red;



if(power_data.DSP_Sampling_f==1000)
{
	for(i=50;i<350;i+=50)
	{
	rt_sprintf(label_text, "%d",i); 
  if(i<100)		
	  rect.x1=i*1024/Sample_Frequency-8;
	else if(i<1000&i>=100)
		rect.x1=i*1024/Sample_Frequency-12;
	else if(i>=1000)
		rect.x1=i*1024/Sample_Frequency-16;

	for(j=0;j<5;j++)
	rtgui_dc_draw_horizontal_line(analyze_dc,i*1024/Sample_Frequency-1,i*1024/Sample_Frequency+1,220-j);
	
	rect.x2=rect.x1+sizeof(label_text)*8;
	rtgui_dc_draw_text(analyze_dc, label_text, &rect);
	}
}
else if(power_data.DSP_Sampling_f==2000)
{
	for(i=50;i<700;i+=100)
	{
	rt_sprintf(label_text, "%d",i); 
  if(i<100)		
	  rect.x1=i*1024/Sample_Frequency-8;
	else if(i<1000&i>=100)
		rect.x1=i*1024/Sample_Frequency-12;
	else if(i>=1000)
		rect.x1=i*1024/Sample_Frequency-16;

	for(j=0;j<5;j++)
	rtgui_dc_draw_horizontal_line(analyze_dc,i*1024/Sample_Frequency-1,i*1024/Sample_Frequency+1,220-j);
	
	rect.x2=rect.x1+sizeof(label_text)*8;
	rtgui_dc_draw_text(analyze_dc, label_text, &rect);
	}
}
else if (power_data.DSP_Sampling_f==4000)
{
		for(i=50;i<1400;i+=200)
	{
	rt_sprintf(label_text, "%d",i); 
  if(i<100)		
	  rect.x1=i*1024/Sample_Frequency-8;
	else if(i<1000&i>=100)
		rect.x1=i*1024/Sample_Frequency-12;
	else if(i>=1000)
		rect.x1=i*1024/Sample_Frequency-16;

	for(j=0;j<5;j++)
	rtgui_dc_draw_horizontal_line(analyze_dc,i*1024/Sample_Frequency-1,i*1024/Sample_Frequency+1,220-j);
	
	rect.x2=rect.x1+sizeof(label_text)*8;
	rtgui_dc_draw_text(analyze_dc, label_text, &rect);
	}
}
else if (power_data.DSP_Sampling_f==5000)
{
		for(i=50;i<1750;i+=200)
	{
	rt_sprintf(label_text, "%d",i); 
  if(i<100)		
	  rect.x1=i*1024/Sample_Frequency-8;
	else if(i<1000&i>=100)
		rect.x1=i*1024/Sample_Frequency-12;
	else if(i>=1000)
		rect.x1=i*1024/Sample_Frequency-16;

	for(j=0;j<5;j++)
	rtgui_dc_draw_horizontal_line(analyze_dc,i*1024/Sample_Frequency-1,i*1024/Sample_Frequency+1,220-j);
	
	rect.x2=rect.x1+sizeof(label_text)*8;
	rtgui_dc_draw_text(analyze_dc, label_text, &rect);
	}
}

else if (power_data.DSP_Sampling_f==10000)
{
		for(i=100;i<3515;i+=400)
	{
	rt_sprintf(label_text, "%d",i); 
  if(i<100)		
	  rect.x1=i*1024/Sample_Frequency-8;
	else if(i<1000&i>=100)
		rect.x1=i*1024/Sample_Frequency-12;
	else if(i>=1000)
		rect.x1=i*1024/Sample_Frequency-16;

	for(j=0;j<5;j++)
	rtgui_dc_draw_horizontal_line(analyze_dc,i*1024/Sample_Frequency-1,i*1024/Sample_Frequency+1,220-j);
	
	rect.x2=rect.x1+sizeof(label_text)*8;
	rtgui_dc_draw_text(analyze_dc, label_text, &rect);
	}
}

else if (power_data.DSP_Sampling_f==20000)
{
		for(i=200;i<7030;i+=800)
	{
	rt_sprintf(label_text, "%d",i); 
  if(i<100)		
	  rect.x1=i*1024/Sample_Frequency-8;
	else if(i<1000&i>=100)
		rect.x1=i*1024/Sample_Frequency-12;
	else if(i>=1000)
		rect.x1=i*1024/Sample_Frequency-16;

	for(j=0;j<5;j++)
	rtgui_dc_draw_horizontal_line(analyze_dc,i*1024/Sample_Frequency-1,i*1024/Sample_Frequency+1,220-j);
	
	rect.x2=rect.x1+sizeof(label_text)*8;
	rtgui_dc_draw_text(analyze_dc, label_text, &rect);
	}
}
	
	
//	RTGUI_DC_FC(analyze_dc) = red;
//	rt_sprintf(label_text, "%d",150);  
//	rect.x1=150*1024/4000;
//	rect.x2=rect.x1+sizeof(label_text)*8;
//	rtgui_dc_draw_text(analyze_dc, label_text, &rect);
		
		
//	RTGUI_DC_FC(analyze_dc) = red;
//	rtgui_dc_draw_line(analyze_dc,place_max,220,place_max,220-rate*graphic[place_max]);
		
		
//  rtgui_dc_draw_line(analyze_dc,graphic_count+place_max,220,graphic_count+place_max,220-rate*graphic[place_max]);
//  rtgui_dc_draw_vertical_line(analyze_dc,place_max,220-rate*graphic[place_max],220);
		
//	rect.y1+=16;
//	rect.y2=rect.y1+16;
//	RTGUI_DC_FC(analyze_dc) = red;
//	  rt_sprintf(label_text, "%s",rt_kprintf_float(graphic[place_max])); 
//	  rect.x2=rect.x1+sizeof(label_text)*8;
//	  rtgui_dc_draw_text(analyze_dc, label_text, &rect);
		
//		rt_sprintf(label_text, "%s",rt_kprintf_float(graphic[place_max])); 
//		rect.x1=place_max-sizeof(label_text)*8;
//		rect.x2=rect.x1+sizeof(label_text)*8;
//		//rect.y1=(1/3)*((220-rate*graphic[place_max])+220);
//		rect.y1=100;
//		rect.y2=rect.y1+16;

//		rtgui_dc_draw_text(analyze_dc, label_text, &rect);
		
}

extern rt_bool_t dc_event_handler(struct rtgui_object *object, rtgui_event_t *event);
void FFT_onbutton(struct rtgui_object *object, rtgui_event_t *event)
{
	unsigned int i;
	//unsigned char temp;
	/*开启 FFT分析*/
	if(FFT_Open_flag==0)
	FFT_Open_flag=1;
	else if(FFT_Open_flag==1)
	FFT_Open_flag=0;
if(FFT_Open_flag==1)
{
	for(i=0;i<2048;i++)
	fftInput_f32[i]=0;
	
	/*载入通道中的数据  然后进行分析*/
	if(rtgui_checkbox_get_checked(ch1_checkbox_1)==1)
	{
	for(i=0;i<TEST_LENGTH_SAMPLES;i++)
	   fftInput_f32[i]=store_data[i];
	}
	else if (rtgui_checkbox_get_checked(ch2_checkbox_1)==1)
	{
	for(i=power_data.ch1_data_length;i<power_data.ch1_data_length+TEST_LENGTH_SAMPLES;i++)
	   fftInput_f32[i-power_data.ch1_data_length]=store_data[i];
	}
	else if (rtgui_checkbox_get_checked(ch3_checkbox_1)==1)
	{
	for(i=(power_data.ch1_data_length+power_data.ch2_data_length);i<(power_data.ch1_data_length+power_data.ch2_data_length+TEST_LENGTH_SAMPLES);i++)
  fftInput_f32[i-(power_data.ch1_data_length+power_data.ch2_data_length)]=store_data[i];
	}
	fft_convert();
	
 //  for(i=0;i<360;i++)
 //  graphic[i]=0;
 //  temp=(unsigned char)(fftSize/360)+1;

 //  for(i=0;i<fftSize;i++)
 //  graphic[(unsigned int)(i/temp)] += testOutput[i];

}


	//  rtgui_notebook_set_current_by_index(the_notebook,2);

  GO_TO_Scope();
//  if(rtgui_object_get_id(object)==SCOPE_PANEL_ID)
//	{
//		rtgui_object_set_event_handler(RTGUI_OBJECT(object), dc_event_handler);
//	}
}
	
