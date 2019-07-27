/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
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

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h" 
#include "stm32f10x.h" 
#include "stm32f10x_exti.h" 
#include "usb_int.h"
#include "usb_istr.h"

#include "delay.h"
#include "usart.h"
#include "sys.h"

#include "misc.h"
#include "hw_config.h"
#include "usb_init.h"
#include "usb_pwr.h"
#include "stdio.h"

extern __IO uint8_t PrevXferComplete;

extern uint8_t button_type;

//add by simon to debug USB interface (Device Mass Storage)
#if 1

void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line13) != RESET) //确保是否产生了 EXTI Line中断
	{
		// LED1 = 0;
		GPIO_WriteBit(GPIOE, GPIO_Pin_7, (BitAction)0);
		EXTI_ClearITPendingBit(EXTI_Line13); //清除中断标志位

		// Joystick_Send(DOWN);
		PrevXferComplete = 1;

		button_type = 1;
		printf("EXTI_Line13 \r\n");
	}

	if(EXTI_GetITStatus(EXTI_Line14) != RESET) //确保是否产生了 EXTI Line中断
	{
		// LED1 = 0;
		GPIO_WriteBit(GPIOE, GPIO_Pin_7, (BitAction)1);
		EXTI_ClearITPendingBit(EXTI_Line14); //清除中断标志位

	//	Joystick_Send(LEFT);
		PrevXferComplete = 1;
		button_type = 2;
		printf("EXTI_Line14 \r\n");
	}

	if(EXTI_GetITStatus(EXTI_Line15) != RESET) //确保是否产生了 EXTI Line中断
	{
		// LED1 = ~LED1;
		GPIO_WriteBit(GPIOE, GPIO_Pin_7, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_7)));
		EXTI_ClearITPendingBit(EXTI_Line15); //清除中断标志位

	//	Joystick_Send(UP);
		PrevXferComplete = 1;
		button_type = 3;
		printf("EXTI_Line15 \r\n");
	}		
}


void USB_LP_CAN1_RX0_IRQHandler(void)
{
    USB_Istr();
}

void USB_HP_CAN1_TX_IRQHandler(void)
{
	CTR_HP();
}

/*******************************************************************************
* Function Name  : USBWakeUp_IRQHandler
* Description    : This function handles USB WakeUp interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USBWakeUp_IRQHandler(void)
{
  EXTI_ClearITPendingBit(EXTI_Line18);
}


#endif  // end of debug bt simon 7/21


void NMI_Handler(void)
{
}
 
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}
 
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

 
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}
 
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}
 
//void SVC_Handler(void)
//{
//}
 
void DebugMon_Handler(void)
{
}
 
//void PendSV_Handler(void)
//{
//}
// 
//void SysTick_Handler(void)
//{
//}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
