#ifndef __CRC_CHECK_H__
#define __CRC_CHECK_H__
#include "rtthread.h"
typedef enum {FALSE = 0, TRUE = !FALSE} bool;
extern bool ACK;
extern bool ACK_PROTECT;
extern bool ACK_GET;
extern bool ACK_SEND;
extern unsigned char ACK_BUFFER[16];
extern char ACK_TARGET;
extern char ACK_TARGET_CMD;
extern bool ACK_getdata;

unsigned int CRC_Check_Bit(  unsigned char data[32],unsigned char len );
rt_uint32_t CRC_Check_Byte(char data[32],unsigned char len );
#endif
