//////////////////////////////////////////////////////////////////////////////////	 
//ALIENTEK STM32 EVB	   
//Website:www.openedv.com
//Date:2012/8/18
//Version：V1.7
//Copyright(C) ALIENTEK 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 

#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 
#include <stdarg.h>

#define USART_REC_LEN  			200  	
#define EN_USART1_RX 			1		
	  	
extern u8  USART_RX_BUF[USART_REC_LEN];
extern u16 USART_RX_STA;
void uart_init(u32 bound);


#endif


