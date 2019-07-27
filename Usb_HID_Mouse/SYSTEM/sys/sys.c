//////////////////////////////////////////////////////////////////////////////////	 
//ALIENTEK STM32 EVB	   
//Website:www.openedv.com
//Date:2012/8/18
//Version：V1.7
//Copyright(C) ALIENTEK 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	 
#include "sys.h"

void WFI_SET(void)
{
	__ASM volatile("wfi");		  
}

void INTX_DISABLE(void)
{		  
	__ASM volatile("cpsid i");
}

void INTX_ENABLE(void)
{
	__ASM volatile("cpsie i");		  
}

__asm void MSR_MSP(u32 addr) 
{
    MSR MSP, r0 			//set Main Stack value
    BX r14
}
