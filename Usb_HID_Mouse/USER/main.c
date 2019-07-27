#include "delay.h"
#include "usart.h"
#include "sys.h"

#include "misc.h"
#include "hw_config.h"
#include "usb_init.h"
#include "usb_pwr.h"
#include "usb_prop.h"

#include "stm32f10x_exti.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x.h"

__IO uint8_t PrevXferComplete = 1;
bool isrt_dbg_printf_flag[10];

uint8_t button_type = 0;

void led_on()
{
	GPIO_SetBits(GPIOE,GPIO_Pin_7); 							   //PE.7 = 1   
//	GPIO_SetBits(GPIOE,GPIO_Pin_8); 			//PE.8, use to USB pull-up control
	GPIO_SetBits(GPIOE,GPIO_Pin_9); 							   //PE.9 = 1
	GPIO_SetBits(GPIOE,GPIO_Pin_10);							   //PE.9 = 1

	printf("led on \r\n");	
}

void led_off()
{
	GPIO_ResetBits(GPIOE,GPIO_Pin_7); 							   //PE.7 = 0    
//	GPIO_ResetBits(GPIOE,GPIO_Pin_8); 			//PE.8, use to USB pull-up control
	GPIO_ResetBits(GPIOE,GPIO_Pin_9); 							   //PE.9 = 0 
	GPIO_ResetBits(GPIOE,GPIO_Pin_10);							   //PE.9 = 0 

	printf("led off \r\n");	
}

void LED_Init()
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	 //enable PE GPIO clock
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 /*| GPIO_Pin_8 */ | GPIO_Pin_9 | GPIO_Pin_10;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_Init(GPIOE, &GPIO_InitStructure);	

 led_on();
	
}

void BUTTON_NVIC_Configuration(void)
{    
	NVIC_InitTypeDef NVIC_InitStructure; 
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);  
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}

void EXTI_BUTTON_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	
	/* config the extiline(PB 13~15) clock and AFIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

 	/* config the NVIC(PB 13~15) */
	BUTTON_NVIC_Configuration();

	 /* EXTI line gpio config(PB 13~15) */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // Input Pull-Up 
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/* EXTI line(PB 13~15) mode config */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource13);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource15);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line13 | EXTI_Line14 | EXTI_Line15;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
}


extern uint16_t gReg_wIstr;
int main(void)
{
	uint8_t i;
	
	uart_init(115200);					
	LED_Init();

	for(i=0;i<10;i++)
		isrt_dbg_printf_flag[i] = FALSE;
	
	EXTI_BUTTON_Config();

	Set_System();  //GPIO control USB to Connect

	delay_ms(500); //wait to USB reset from PC USB Host
	
	Set_USBClock();
	USB_Interrupts_Config();	
	USB_Init();

	while(bDeviceState != CONFIGURED);

	delay_ms(500);
	printf("Init finished... \r\n");

	while(1){	

		for(i=0;i<10;i++){
			if(isrt_dbg_printf_flag[i]){
				isrt_dbg_printf_flag[i] = FALSE;
				printf("%d \r\n", i);
			}
		}
		
		if (bDeviceState == CONFIGURED){
	      if (PrevXferComplete){
		   	if(button_type == 1){
	      		Joystick_Send(UP);
		   	}else if(button_type == 2){
				Joystick_Send(LEFT);
			}else if(button_type == 3){
				Joystick_Send(DOWN);
			}else{
				button_type = 0;
			}

			if(button_type){
				printf("Joystick_Send, button_type = %d \r\n", button_type);
				button_type = 0;
			}
	      }
	    }  
		delay_ms(200);
		led_off();
		delay_ms(200);
		led_on();
	}
}


