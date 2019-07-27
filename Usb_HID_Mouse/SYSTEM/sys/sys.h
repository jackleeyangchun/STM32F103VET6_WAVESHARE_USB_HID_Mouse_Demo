#ifndef __SYS_H
#define __SYS_H	
#include "stm32f10x.h"
//////////////////////////////////////////////////////////////////////////////////	 
//ALIENTEK STM32 EVB	   
//Website:www.openedv.com
//Date:2012/8/18
//Version: V1.7
//Copyright(C) ALIENTEK 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	 

//0,Support OS
//1,Not Support OS
#define SYSTEM_SUPPORT_OS		0		
																	    
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

//IO Address Map
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 

//I/O Operation
//please make sure n < 16  !!!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //Output
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //Input

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //Output
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //Input

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //Output
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //Input

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //Output
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //Input

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //Output
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //Input

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //Output
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //Input

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //Output
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //Input

// ASM API
void WFI_SET(void);		//execute WFI
void INTX_DISABLE(void);// disable all interruption
void INTX_ENABLE(void);	//enable all interruption
void MSR_MSP(u32 addr);	//configure stack address

#endif
