//////////////////////////////////////////////////////////////////////////////////	 
//ALIENTEK STM32 EVB	   
//Website:www.openedv.com
//Date:2012/8/18
//Version£ºV1.7
//Copyright(C) ALIENTEK 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 

#include "sys.h"
#include "usart.h"	

#define USE_STD_PRINTF_NOT_KEIL_MICROLIB (1)

#if USE_STD_PRINTF_NOT_KEIL_MICROLIB

#pragma import(__use_no_semihosting)     

/* structure needed by Standard C Lib */                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;

//Use _sys_exit() to avoid use half-host mode    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//redefine fputc() API 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//repeat sending, until finish  
    USART1->DR = (u8) ch;      
	return ch;
}

int printf(const char *fmt, ...)
{
    int ret;
    va_list vl;
    va_start(vl, fmt);
    ret = vprintf(fmt, vl);
    va_end(vl);
    return ret;
}

#endif 

#if EN_USART1_RX
//Note: read USARTx->SR to avoid unknown error  	
u8 USART_RX_BUF[USART_REC_LEN];

//RX status
//bit[15]£¬	RX finished flag
//bit[14]£¬	Received 0x0d
//bit[13~0]£¬number of received data
u16 USART_RX_STA=0;       //receive status flag	  
  
void uart_init(u32 bound)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	
	//USART1_TX   GPIOA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
   
	//USART1_RX	  GPIOA.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//Usart1 NVIC
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	
  
	//USART

	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	

	USART_Init(USART1, &USART_InitStructure); 
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART1, ENABLE);                   
}

//uart-1 ISR handle
void USART1_IRQHandler(void)                	
{
	u8 Res;

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //UART RX interrupt(uart data must be finished by 0x0d 0x0a["\r\n"])
		{
		Res =USART_ReceiveData(USART1);	//Read received data from buffer
		
		if((USART_RX_STA&0x8000)==0)//Receive not finish
			{
			if(USART_RX_STA&0x4000) //Receive 0x0d
				{
				if(Res!=0x0a)USART_RX_STA=0; // Receive data error, restart	
				else USART_RX_STA|=0x8000;	// Receive finish
				}
			else //not receive 0x0d
				{	
				if(Res==0x0d)USART_RX_STA|=0x4000;
				else
					{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;  //Receive data error, restart	  
					}		 
				}
			}   		 
     } 
} 
#endif	

