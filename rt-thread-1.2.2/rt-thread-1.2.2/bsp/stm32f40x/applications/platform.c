#include <rtthread.h>
#include "board.h"
#include <GPIO.h>

#ifdef RT_USING_DFS
	#include <dfs_init.h>
	#include <dfs_elm.h>
	#include <dfs_fs.h>
	extern void rt_hw_spi1_init(void);
	extern void rt_hw_sdcard_init(void);
#endif


#ifdef RT_USING_USB_DEVICE
	extern void rt_hw_usbd_init(void);
	extern rt_err_t rt_usb_device_init(const char* udc_name);
	extern void rt_hw_ramdisk_init(void);
	extern void rt_usb_vcom_init(void);
#endif

void rt_platform_init(void);

#ifdef RT_USING_RTC
#include "stm32f4_rtc.h"
#endif /* RT_USING_RTC */

#ifdef RT_USING_SPI
#include "stm32f20x_40x_spi.h"
#include "spi_flash_w25qxx.h"

/*
SPI2_MOSI: PB6
SPI2_MISO: PB7
SPI2_SCK : PB5

CS0: PB2  SPI FLASH
CS1: PB12  TOUCH
*/
 void rt_hw_spi1_init(void)  
{  
    /* register spi bus */  
    {  
        static struct stm32_spi_bus stm32_spi;  
        GPIO_InitTypeDef GPIO_InitStructure;  
  
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  

        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;  
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  
        GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;  
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;  
  
        /*!< SPI SCK pin configuration */  
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;  
        GPIO_Init(GPIOA, &GPIO_InitStructure);  
  
        /* Connect alternate function */  
			  GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);
  
        stm32_spi_register(SPI1, &stm32_spi, "spi1");  
    }  
  
    /* attach cs */  
    {  
			static struct rt_spi_device spi_device,spi_device_1;  
      static struct stm32_spi_cs  spi_cs,spi_cs_1;  
  
        GPIO_InitTypeDef GPIO_InitStructure;  
  
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;  
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  
        GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;  
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;  
  
        /* spi0: PD3 */  
        spi_cs.GPIOx = GPIOD;  
        spi_cs.GPIO_Pin = GPIO_Pin_3;  
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);  
  
        GPIO_InitStructure.GPIO_Pin = spi_cs.GPIO_Pin;  
        GPIO_SetBits(spi_cs.GPIOx, spi_cs.GPIO_Pin);  
        GPIO_Init(spi_cs.GPIOx, &GPIO_InitStructure);  

        rt_spi_bus_attach_device(&spi_device, "spi1_flash", "spi1", (void*)&spi_cs);   
				
        /* spi0: PD12 */  
        spi_cs_1.GPIOx = GPIOD;  
        spi_cs_1.GPIO_Pin = GPIO_Pin_12;  
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);  
				
        GPIO_InitStructure.GPIO_Pin = spi_cs_1.GPIO_Pin;  
        GPIO_SetBits(spi_cs_1.GPIOx, spi_cs_1.GPIO_Pin);  
        GPIO_Init(spi_cs_1.GPIOx, &GPIO_InitStructure);  
        rt_spi_bus_attach_device(&spi_device_1, "spi1_net", "spi1", (void*)&spi_cs_1);  
    }  
} 

/*
SPI2_MOSI: PC3
SPI2_MISO: PC2
SPI2_SCK : PB10

CS1: PB12  TOUCH
*/
static int rt_hw_spi2_init(void)
{
    /* register spi bus */
    {
        static struct stm32_spi_bus stm32_spi;
        GPIO_InitTypeDef GPIO_InitStructure;

        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

        /*!< SPI SCK pin configuration */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2| GPIO_Pin_3;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
			
			  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
        GPIO_Init(GPIOB, &GPIO_InitStructure);

        /* Connect alternate function */
        GPIO_PinAFConfig(GPIOC, GPIO_PinSource2, GPIO_AF_SPI2);
        GPIO_PinAFConfig(GPIOC, GPIO_PinSource3, GPIO_AF_SPI2);
        GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_SPI2);

        stm32_spi_register(SPI2, &stm32_spi, "spi2");
    }

    /* attach cs */
    {
        static struct rt_spi_device spi_device;
        static struct stm32_spi_cs  spi_cs;

        GPIO_InitTypeDef GPIO_InitStructure;

        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

        /* spi_touch: PC13 */
        spi_cs.GPIOx = GPIOC;
        spi_cs.GPIO_Pin = GPIO_Pin_13;
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

        GPIO_InitStructure.GPIO_Pin = spi_cs.GPIO_Pin;
        GPIO_SetBits(spi_cs.GPIOx, spi_cs.GPIO_Pin);
        GPIO_Init(spi_cs.GPIOx, &GPIO_InitStructure);

        rt_spi_bus_attach_device(&spi_device, "spi2_touch", "spi2", (void*)&spi_cs);
    }


    return 0;
}
INIT_BOARD_EXPORT(rt_hw_spi2_init);
#endif /* RT_USING_SPI */
#include <rtgui/calibration.h>
#include <rtgui/driver.h>
#include "setup.h"
rt_bool_t cali_setup(void)
{
    struct setup_items setup;

    if(setup_load(&setup) == RT_EOK)
    {
        struct calibration_data data;
        rt_device_t device;

        data.min_x = setup.touch_min_x;
        data.max_x = setup.touch_max_x;
        data.min_y = setup.touch_min_y;
        data.max_y = setup.touch_max_y;


        device = rt_device_find("touch");
        if(device != RT_NULL)
            rt_device_control(device, RT_TOUCH_CALIBRATION_DATA, &data);
        return RT_TRUE;
    }
    return RT_FALSE;
}

void cali_store(struct calibration_data *data)
{
    struct setup_items setup;
    setup.touch_min_x = data->min_x;
    setup.touch_max_x = data->max_x;
    setup.touch_min_y = data->min_y;
    setup.touch_max_y = data->max_y;
    setup_save(&setup);
}
#define RT_NFS_HOST_EXPORT	"192.168.1.101:/" 
extern void rt_hw_GPIO_init(void);
extern void cpu_usage_init(void);
void rt_platform_init(void)
{
	  rt_hw_GPIO_init();
	  cpu_usage_init();
	
#ifdef RT_USING_RTC
	  {
		 extern void rt_hw_rtc_init(void);
	   rt_hw_rtc_init();
	  }
#endif
		
#ifdef RT_USING_SPI
		{
		rt_hw_spi1_init();
		rt_hw_spi2_init();
		}
#endif
		
#ifdef RT_USING_DFS
    {  
			extern rt_err_t w25qxx_init(const char * flash_device_name,
                            const char * spi_device_name);
			rt_bool_t mount_flag = RT_FALSE;
        dfs_init();  
		#ifdef RT_USING_DFS_ELMFAT              
        elm_init();
		#endif 
			
#if defined(RT_USING_DFS) && defined(RT_USING_LWIP) && defined(RT_USING_DFS_NFS)
	{

	}
#endif

			w25qxx_init("flash0", "spi1_flash"); 
			rt_hw_sdcard_init();
			 
//		  mkfs("elm", "flash0");
//			mkdir("/SD");
//			mkdir("/RESOURCE");
			
			
//			/*加载字库到flah中*/
//			copy("/SD/resource/HZK16.FNT","/RESOURCE");
//			copy("/SD/resource/HZK12.FNT","/RESOURCE");
//			copy("/SD/resource/HZK24.FNT","/RESOURCE");
//			copy("/SD/resource/HZK48.FNT","/RESOURCE");
//			copy("/SD/resource/UNI2GBK.TBL","/RESOURCE");
//			copy("/SD/resource/GBK2UNI.TBL","/RESOURCE");
    

        if (dfs_mount("flash0", "/", "elm", 0, 0) == 0)
        {
            mount_flag = RT_TRUE;
        }
        else
        {
          rt_kprintf("flash0 mount to / failed!, fatmat and try again!\n");

            if (dfs_mount("flash0", "/", "elm", 0, 0) == 0)
            {
                mount_flag = RT_TRUE;
            }
        }

      
        if(mount_flag == RT_TRUE)
        {
            rt_kprintf("flash0 mount to / \n");

		#if (RT_DFS_ELM_USE_LFN != 0) && (defined RT_DFS_ELM_CODE_PAGE_FILE)
            {
               extern void ff_convert_init(void);
                ff_convert_init();
            }
		#endif

            if (dfs_mount("sd0", "/SD", "elm", 0, 0) == 0)
            {
                rt_kprintf("sd0 mount to /SD \n");
							
            }
            else
            {
                rt_kprintf("sd0 mount to /SD failed!\n");
            }
       }
        else
        {
            rt_kprintf("flash0 mount to / failed!\n");
        }
   }
#endif
	
	
	
#ifdef RT_USING_RTGUI
			{
			rt_device_t lcd;
	    extern void rt_hw_lcd_init();
	    extern rt_err_t rtgui_touch_hw_init(const char * spi_device_name);
      extern rt_err_t rtgui_graphic_set_device(rt_device_t device);	
      extern void gui_application_init(void);	
      extern int rtgui_system_server_init(void);		
      extern void load_ui_init(void);				
		  rt_hw_lcd_init();
		  /* find lcd device */
		  lcd = rt_device_find("lcd");
		  /* set lcd device as rtgui graphic driver */	
		  rtgui_graphic_set_device(lcd);
		  rtgui_system_server_init();
			rtgui_touch_hw_init("spi2_touch");
				
			/* add calibrate*/
      calibration_set_restore(cali_setup);
      calibration_set_after(cali_store);
      {
        extern void calibration_init(void);
        calibration_init();
     }
			load_ui_init();
 
      }
      #endif
		
		
      rt_thread_delay(100);
			/* LwIP Initialization */
			#ifdef RT_USING_LWIP
			{
			extern rt_err_t enc28j60_attach(const char * spi_device_name);
			extern void lwip_sys_init(void);
			extern int eth_system_device_init(void);
			extern void TCP_Server_init(void);
      /* register ethernetif device */
      eth_system_device_init();
      enc28j60_attach("spi1_net");
      /* init lwip system */
      lwip_sys_init();
      rt_kprintf("TCP/IP initialized!\n");
//   	  TCP_Server_init();//开启TCP服务器
		#if defined(RT_USING_DFS) && defined(RT_USING_LWIP)
			{
		extern void ftpd_start(void);
		/* start ftp server */
		rt_kprintf("ftp server begin...\n");
		ftpd_start();
		rt_kprintf("ftp server started!!\n");
			}
		#endif
			
     rt_thread_delay(100);
// /* do some thing here. */
//#if defined(RT_USING_DFS) && defined(RT_USING_LWIP) && defined(RT_USING_DFS_NFS)
//	{

//		/* NFSv3 Initialization */
//		rt_kprintf("begin init NFSv3 File System ...\n");
//		nfs_init();
//			
//		/* NFSv3 Initialization */
//		if (dfs_mount(RT_NULL, "/NFS", "nfs", 0, RT_NFS_HOST_EXPORT) == 0)
//			rt_kprintf("NFSv3 File System initialized!\n");
//		else
//			rt_kprintf("NFSv3 File System initialzation failed!\n");
//				
//	}
//#endif

			}
     #endif

			rt_device_init_all();
			
			/*开启串口接收线程*/
			{
		  extern void uart_application_init(void);
		  uart_application_init();
			}
			
			/*初始化CAN*/
			{
				extern void can_INIT(void);
				can_INIT();
			}

}

