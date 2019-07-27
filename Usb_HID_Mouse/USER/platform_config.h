/**
  ******************************************************************************
  * @file    platform_config.h
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   Evaluation board specific configuration file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PLATFORM_CONFIG_H
#define __PLATFORM_CONFIG_H

/* Includes ------------------------------------------------------------------*/

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_pwr.h"

/*Unique Devices IDs register set*/
#define         ID1          (0x1FFFF7E8)
#define         ID2          (0x1FFFF7EC)
#define         ID3          (0x1FFFF7F0)

/*
	WaveShare EVK Board, STM32F103_VET6
	Software Debug: by Simon Lee, 2019/07/27
*/

#define LED1 PEout(7)		// PE7
#define LED2 PEout(8)		// PE8	
#define LED3 PEout(9)		// PE9
#define LED4 PEout(10)		// PE10

#define BUTTON1 PBout(13)		// PB13
#define BUTTON2 PBout(14)		// PB14
#define BUTTON3 PBout(15)		// PB15

typedef  void (*user_app)(void);  

//u8  FLASH_TMP_BUF[1024];
// extern u8  FLASH_TMP_BUF[];
//extern u8  KEY[];	


/* Define the STM32F10x hardware depending on the used evaluation board */

#define USB_DISCONNECT                      GPIOE
#define USB_DISCONNECT_PIN                  GPIO_Pin_8
#define RCC_APB2Periph_GPIO_DISCONNECT      RCC_APB2Periph_GPIOE

#define GPIO_Pin_DOWN						GPIO_Pin_8	/* PD.8 */
#define GPIO_Pin_LEFT						GPIO_Pin_9	/* PD.9 */
#define GPIO_Pin_RIGHT						GPIO_Pin_10	/* PD.10 */
#define GPIO_Pin_UP 						GPIO_Pin_11 /* PD.11 */
#define GPIO_Pin_KEY						GPIO_Pin_12	/* PD.12 */
#define RCC_AHBPeriph_GPIO_JOY_SET1 RCC_APB2Periph_GPIOD

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

typedef enum 
{  
  BUTTON_WAKEUP = 0,
  BUTTON_TAMPER = 1,
  BUTTON_KEY = 2,
  BUTTON_RIGHT = 3,
  BUTTON_LEFT = 4,
  BUTTON_UP = 5,
  BUTTON_DOWN = 6,
  BUTTON_SEL = 7
} Button_TypeDef;

typedef enum 
{  
  BUTTON_MODE_GPIO = 0,
  BUTTON_MODE_EXTI = 1
} ButtonMode_TypeDef;

typedef enum 
{ 
  JOY_NONE = 0,
  JOY_SEL = 1,
  JOY_DOWN = 2,
  JOY_LEFT = 3,
  JOY_RIGHT = 4,
  JOY_UP = 5
} JOYState_TypeDef;

typedef enum 
{
  COM1 = 0,
  COM2 = 1
} COM_TypeDef;

#endif /* __PLATFORM_CONFIG_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
