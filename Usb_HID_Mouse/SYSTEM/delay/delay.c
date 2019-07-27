/**
  ******************************************************************************
  * @file	 delay.c
  * @author  MCD Application Team
  * @version V3.5.0
  * @date	 11-March-2011
  * @brief	 This file contains all the functions prototypes for the BKP firmware 
  * 		 library.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */
  
#include "delay.h"

#if SYSTEM_SUPPORT_OS
	#include "FreeRTOS.h"					//FreeRTOS 		  
	#include "task.h"

static u8  fac_us=0;		//factor of delay us			   
static u16 fac_ms=0;		//factor of delay ms,in ucos, which represents beats of ms
	
extern void xPortSysTickHandler(void);


void SysTick_Handler(void)
{	
    if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED) //OS is running
    {
        xPortSysTickHandler();	
    }
}
		   
//Normally, SYSTICK = AHB/8.  But for FreeRTOS£¬SYSTICK equal to Frequency of AHB
//SYSCLK: system clock
void delay_init()
{
	u32 reload;
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);//use external clock: HCLK
	fac_us=SystemCoreClock/1000000;				
	reload=SystemCoreClock/1000000;				
	reload*=1000000/configTICK_RATE_HZ;			
												//reload 24-bits Reg, Maximum:16777216, while in 72M system clokc, ~= 0.233s	
	fac_ms=1000/configTICK_RATE_HZ;				// the least unit to delay in OS	   

	SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;   	//enable SYSTICK interrupt
	SysTick->LOAD=reload; 						// every 1/configTICK_RATE_HZ s to trigger interrupt	
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;   	//enable SYSTICK    
}								    
  								   
void delay_us(u32 nus)
{		
	u32 ticks;
	u32 told,tnow,tcnt=0;
	u32 reload=SysTick->LOAD;	  	 
	ticks=nus*fac_us; 					
	told=SysTick->VAL;        			
	while(1)
	{
		tnow=SysTick->VAL;	
		if(tnow!=told)
		{	    
			if(tnow<told)tcnt+=told-tnow;	
			else tcnt+=reload-tnow+told;	    
			told=tnow;
			if(tcnt>=ticks)break;
		}  
	};										    
}  
// delay nms
//nms:number of ms
//nms:0~65535
void delay_ms(u32 nms)
{	
	if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED)//RTOS is running 
	{		
		if(nms>=fac_ms)
		{ 
   			vTaskDelay(nms/fac_ms);	 	
		nms%=fac_ms;						
	}
	delay_us((u32)(nms*1000));				
}

void delay_xms(u32 nms)
{
	u32 i;
	for(i=0;i<nms;i++) 
		delay_us(1000);
}

#else

void delay_init()
{
	;;;  //fuke API to init
}

//delay nus
//nus: number of us to delay.	
//nus:0~204522252(maximum 2^32/fac_us@fac_us=168)	    								   
void delay_us(u32 nus)
{	
	volatile u32 i =0;
	volatile u32 j = 0;
	
	for(i=0;i<nus;i++)
		for(j=0;j<5;j++);
}

void delay_ms(u32 nms)
{	
	delay_us((u32)(nms*1000));// normal delay
}

void delay_xms(u32 nms)
{
	u32 i;
	for(i=0;i<nms;i++) 
		delay_us(1000);
}

#endif 


