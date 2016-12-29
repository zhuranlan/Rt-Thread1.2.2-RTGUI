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
#include "messagedialog.h"
#define SCREENSHOT_PATH "/SD/DATA"
unsigned int Find_file(char* filename);
extern char label_text[100];
extern q15_t store_data[8192];
extern q15_t turn_data_temp[8192];
extern rtgui_combobox_t *box_ch1,*box_ch2,*box_ch3;
unsigned char save_data(char* filename, unsigned int total_length,q15_t *data);
unsigned char save_flag=1;
void SAVE_DATA_onbutton(struct rtgui_object *object, rtgui_event_t *event)
{	
	rtgui_rect_t rect;
	struct rtgui_label *label;
	struct rtgui_listbox_item *get_select;
	q15_t i;
	save_flag=0;
	if(scope_setting.ch1_choice==1&&power_data.ch1_data_length>0)
	{
		
	get_select=(rtgui_combox_get_select(box_ch1));
	rt_sprintf(label_text, "/SD/DATA/%s_%d.dat",get_select->name,Find_file(get_select->name)); 
		
  for(i=0;i<power_data.ch1_data_length;i++)
	turn_data_temp[i]=store_data[i];
	save_data(label_text,power_data.ch1_data_length,turn_data_temp);
	}
	
	
	if(scope_setting.ch2_choice==1&&power_data.ch2_data_length>0)
	{
	get_select=(rtgui_combox_get_select(box_ch2));
	rt_sprintf(label_text, "/SD/DATA/%s_%d.dat",get_select->name,Find_file(get_select->name)); 
		
	for(i=power_data.ch1_data_length;i<(power_data.ch2_data_length+power_data.ch1_data_length);i++)
  turn_data_temp[i-power_data.ch1_data_length]=store_data[i];
	save_data(label_text,power_data.ch2_data_length,turn_data_temp);
	}
	
	if(scope_setting.ch3_choice==1&&power_data.ch3_data_length>0)
	{
	get_select=(rtgui_combox_get_select(box_ch3));
	rt_sprintf(label_text, "/SD/DATA/%s_%d.dat",get_select->name,Find_file(get_select->name)); 
		
  for(i=(power_data.ch1_data_length+power_data.ch2_data_length);i<(power_data.ch1_data_length+power_data.ch2_data_length+power_data.ch3_data_length);i++)
  turn_data_temp[i-(power_data.ch1_data_length+power_data.ch2_data_length)]=store_data[i];
	save_data(label_text,power_data.ch3_data_length,turn_data_temp);
	}
	
	/*显示存储情况*/
	if(save_flag==1)
	{	
	label = RTGUI_LABEL(rtgui_get_self_object(LOADDATA_PRO_ID));
	rt_sprintf(label_text, "Save OK!!");
  rtgui_label_set_text(label, label_text);
	rtgui_widget_update(RTGUI_WIDGET(label));
	}
	else if(save_flag==0)
	{	
	label = RTGUI_LABEL(rtgui_get_self_object(LOADDATA_PRO_ID));
	rt_sprintf(label_text, "Save Failed!!");
  rtgui_label_set_text(label, label_text);
	rtgui_widget_update(RTGUI_WIDGET(label));
	}
	
}



unsigned char save_data(char* filename, unsigned int total_length,q15_t *data)
{
   int fd, size,i,j,k;
	 q15_t temp;
    char* p_str;
	unsigned char count;
    char* buf = rt_malloc(1024*4+1024+200);
	  count=total_length/1024;

    if (buf == RT_NULL)
    {
			  save_flag=0;
        rt_kprintf("no memory\r\n");
			  return 0;
    }

    p_str = buf;

    fd = open(filename, O_WRONLY | O_TRUNC, 0);
    if (fd >= 0)
    {
      size = sprintf(p_str, "%s--采样频率:%dHZ--采样点数:%d\r\n",filename,power_data.DSP_Sampling_f,total_length);
      p_str += size;
			i=0;
			j=0;
			k=0;
        for(i=0;i<total_length;i++)
			{

				temp=data[i];
        size = sprintf(p_str, "%d,",temp); 
				//rt_kprintf("[%d]=%d \n",i,temp);
        p_str += size;
				j++;
					if(j==1024)
					{
						write(fd, buf, p_str - buf);
						p_str = buf;
						j=0;
						k++;
					}
				
			}
    }

    size = write(fd, buf, p_str - buf);
		//size = write(fd, buf, p_str - buf);
    if (k == count)
    {
			rt_kprintf("file write succeed:%s   采样频率:%d\r\n",filename,power_data.DSP_Sampling_f);
			save_flag=1;
    }
		else 
			save_flag=0;

    close(fd);
    rt_free(buf);

}


unsigned int Find_file(char* filename)
{
  static DIR *dir;
	static char fullpath[256];
	static char path_screen[100];
	static int count_file;
	static char all_fille[100]={0};
	static int i,j;
	count_file=0;

	dir = opendir(SCREENSHOT_PATH);
	if(dir!=RT_NULL)
		{
		struct dirent* dirent;
		struct stat s;
		
			for(i=0;i<100;i++)
			all_fille[i]=0;
		do
		{
			dirent = readdir(dir);
			/*如果文件夹为空直接截屏存储*/
			if (dirent == RT_NULL) 
				break;
			
			rt_memset(&s, 0, sizeof(struct stat));

			/* build full path for each file */
			rt_sprintf(fullpath, "%s/%s", SCREENSHOT_PATH, dirent->d_name);

			stat(fullpath, &s);
			if ( s.st_mode & DFS_S_IFDIR )
			{
				
			}
			else
			{
				for(i=0;i<100;i++)
				{
				 rt_sprintf(path_screen, "%s_%d.DAT",filename,i);
				  if(strcmp(dirent->d_name,path_screen)==0)
					{
						all_fille[count_file]=i;
						count_file++;
					}	
				}
			}
		} while (dirent != RT_NULL);
		closedir(dir);
		
		
{
		int find_flag=1;
			find_flag=1;
		if(count_file<99)
		{
		for(i=1;i<100;i++)
			{
				if(find_flag==1)
				{
				find_flag=0;
		for(j=0;j<count_file;j++)
				{
		if(all_fille[j]==i)
			find_flag=1;
	      }
				if(find_flag==0)
				{
					return i;
				}
			 }	
	    }
		}
		else
		{
			return 0;
		}

 }
		
	}

}
