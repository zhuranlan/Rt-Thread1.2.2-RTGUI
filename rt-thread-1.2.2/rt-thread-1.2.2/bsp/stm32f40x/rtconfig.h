/* RT-Thread config file */
#ifndef __RTTHREAD_CFG_H__
#define __RTTHREAD_CFG_H__

//#define RT_USING_NEWLIB

/* RT_NAME_MAX*/
#define RT_NAME_MAX    8

/* RT_ALIGN_SIZE*/
#define RT_ALIGN_SIZE    4

/* PRIORITY_MAX */
#define RT_THREAD_PRIORITY_MAX  32

/* Tick per Second */
#define RT_TICK_PER_SECOND     900//168//240*2

/* SECTION: RT_DEBUG */
/* Thread Debug */
#define RT_DEBUG

#define RT_USING_OVERFLOW_CHECK

/* Using Hook */
#define RT_USING_HOOK

#define IDLE_THREAD_STACK_SIZE     1024
/* Using Software Timer */
/* #define RT_USING_TIMER_SOFT */
#define RT_TIMER_THREAD_PRIO        4
#define RT_TIMER_THREAD_STACK_SIZE  512
#define RT_TIMER_TICK_PER_SECOND    10

/* SECTION: IPC */
/* Using Semaphore*/
#define RT_USING_SEMAPHORE

/* Using Mutex */
#define RT_USING_MUTEX

/* Using Event */
#define RT_USING_EVENT

/* Using MailBox */
#define RT_USING_MAILBOX

/* Using Message Queue */
#define RT_USING_MESSAGEQUEUE

/* SECTION: Memory Management */
/* Using Memory Pool Management*/
#define RT_USING_MEMPOOL

/* Using Dynamic Heap Management */
#define RT_USING_HEAP

/* Using Small MM */
#define RT_USING_SMALL_MEM

/* SECTION: Device System */
/* Using Device System */
#define RT_USING_DEVICE
// <bool name=RT_USING_DEVICE_IPC description="Using IPC in Device Driver Framework" default="true" />
#define RT_USING_DEVICE_IPC

/* SECTION: Console options */
#define RT_USING_CONSOLE
/* the buffer size of console*/
#define RT_CONSOLEBUF_SIZE	128
/* console name */
#define RT_CONSOLE_DEVICE_NAME	"uart2"

/* SECTION: finsh, a C-Express shell */
#define RT_USING_FINSH
#define FINSH_USING_MSH//RT_USING_FINSH
//#define FINSH_USING_MSH_ONLY

/* Using symbol table */
#define FINSH_USING_SYMTAB
#define FINSH_USING_DESCRIPTION

/* SECTION: device filesystem */
#define RT_USING_DFS
#define RT_USING_DFS_NFS

//#define RT_USING_DFS_ROMFS


#define RT_USING_DFS_ELMFAT
#define RT_DFS_ELM_WORD_ACCESS
//#define DFS_USING_WORKDIR
/* Reentrancy (thread safe) of the FatFs module.  */
#define RT_DFS_ELM_REENTRANT
/* Number of volumes (logical drives) to be used. */
#define RT_DFS_ELM_DRIVES			2
/* #define RT_DFS_ELM_USE_LFN			1 */
#define RT_DFS_ELM_MAX_LFN			255
/* Maximum sector size to be handled. */
#define RT_DFS_ELM_MAX_SECTOR_SIZE  4096

/* the max number of mounted filesystem */
#define DFS_FILESYSTEMS_MAX			4
/* the max number of opened files 		*/
#define DFS_FD_MAX					4



/* SECTION: lwip, a lighwight TCP/IP protocol stack */
#define RT_USING_LWIP
/* LwIP uses RT-Thread Memory Management */
#define RT_LWIP_USING_RT_MEM
/* Enable ICMP protocol*/
#define RT_LWIP_ICMP
/* Enable UDP protocol*/
#define RT_LWIP_UDP
/* Enable TCP protocol*/
#define RT_LWIP_TCP
/* Enable DNS */
#define RT_LWIP_DNS

///* depended for ftp server */
#define SO_REUSE  1


//#define RT_LWIP_DHCP   /*动态分配ip地址*/
#define RT_USING_NETUTILS

/* the number of simulatenously active TCP connections*/
#define RT_LWIP_TCP_PCB_NUM	10

/* ip address of target*/
#define RT_LWIP_IPADDR0	192
#define RT_LWIP_IPADDR1	168
#define RT_LWIP_IPADDR2	1
#define RT_LWIP_IPADDR3	115

/* gateway address of target*/
#define RT_LWIP_GWADDR0	192
#define RT_LWIP_GWADDR1	168
#define RT_LWIP_GWADDR2	1
#define RT_LWIP_GWADDR3	1

/* mask address of target*/
#define RT_LWIP_MSKADDR0	255
#define RT_LWIP_MSKADDR1	255
#define RT_LWIP_MSKADDR2	255
#define RT_LWIP_MSKADDR3	0

/* tcp thread options */
#define RT_LWIP_TCPTHREAD_PRIORITY		4
#define RT_LWIP_TCPTHREAD_MBOX_SIZE		8
#define RT_LWIP_TCPTHREAD_STACKSIZE		2048

/* ethernet if thread options */
#define RT_LWIP_ETHTHREAD_PRIORITY		5
#define RT_LWIP_ETHTHREAD_MBOX_SIZE		8
#define RT_LWIP_ETHTHREAD_STACKSIZE		2048

/* TCP sender buffer space */
#define RT_LWIP_TCP_SND_BUF	2048*4
/* TCP receive window. */
#define RT_LWIP_TCP_WND		2048*4



#define CHECKSUM_CHECK_TCP              1
#define CHECKSUM_CHECK_IP               1
#define CHECKSUM_CHECK_UDP              1

#define CHECKSUM_GEN_TCP                1
#define CHECKSUM_GEN_IP                 1
#define CHECKSUM_GEN_UDP                1

#define CHECKSUM_GEN_ICMP               1


#define RT_USING_SPI
#define RT_USING_RTC


/* SECTION: RT-Thread/GUI */
#define RT_USING_RTGUI

/* name length of RTGUI object */
#define RTGUI_NAME_MAX		12
/* support 16 weight font */
#define RTGUI_USING_FONT12
#define RTGUI_USING_FONT16
#define RTGUI_USING_FONT24
/* support Chinese font */
#define RTGUI_USING_FONTHZ
/* use DFS as file interface */
#define RTGUI_USING_DFS_FILERW
/* use font file as Chinese font */
#define RTGUI_USING_HZ_FILE 
/* use Chinese bitmap font */
#define RTGUI_USING_HZ_BMP
/* use small size in RTGUI */
//#define RTGUI_USING_SMALL_SIZE
/* use mouse cursor */
//#define RTGUI_USING_MOUSE_CURSOR 
/* default font size in RTGUI */
#define RTGUI_DEFAULT_FONT_SIZE	16

///* image support */
//#define RTGUI_IMAGE_XPM
#define RTGUI_IMAGE_BMP
//#define RTGUI_IMAGE_JPEG 
//#define RTGUI_IMAGE_PNG 
//#define RTGUI_IMAGE_TJPGD
//#define RTGUI_IMAGE_LODEPNG
//#define RTGUI_IMAGE_CONTAINER
//#define RTGUI_USING_WINMOVE
//#define RTGUI_USING_NOTEBOOK_IMAGE
#define RTGUI_USING_DIALOG
//#define  RT_USING_MODULE
#define  RTGUI_USING_CALI    /*开启校验功能*/


//#define NES_Simulator
//#define RT_USING_USB_HOST
//#define  RT_USING_CMSIS_OS
//#define RT_USING_MODBUS
//#define RT_MODBUS_MASTER_SLAVE_RTU


#endif
