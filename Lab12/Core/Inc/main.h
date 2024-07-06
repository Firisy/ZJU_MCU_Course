/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_ll_crs.h"
#include "stm32f0xx_ll_rcc.h"
#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_system.h"
#include "stm32f0xx_ll_exti.h"
#include "stm32f0xx_ll_cortex.h"
#include "stm32f0xx_ll_utils.h"
#include "stm32f0xx_ll_pwr.h"
#include "stm32f0xx_ll_dma.h"
#include "stm32f0xx_ll_tim.h"
#include "stm32f0xx_ll_gpio.h"

#if defined(USE_FULL_ASSERT)
#include "stm32_assert.h"
#endif /* USE_FULL_ASSERT */

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
extern uint16_t datac_pre[240];
extern uint16_t datab_pre[240];
extern uint8_t spoint,mpoint,hpoint;
extern uint32_t command;
extern _Bool dataReady;
extern uint8_t date[14];
extern _Bool FinishReading;
extern uint32_t WorkState;
extern uint8_t rotate_v;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
extern uint8_t DS1302Read(uint8_t cmd);
extern void DS1302Write(uint8_t cmd, uint8_t dat);
extern void getdate(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED17_Pin LL_GPIO_PIN_0
#define LED17_GPIO_Port GPIOA
#define LED18_Pin LL_GPIO_PIN_1
#define LED18_GPIO_Port GPIOA
#define LED19_Pin LL_GPIO_PIN_2
#define LED19_GPIO_Port GPIOA
#define LED20_Pin LL_GPIO_PIN_3
#define LED20_GPIO_Port GPIOA
#define LED21_Pin LL_GPIO_PIN_4
#define LED21_GPIO_Port GPIOA
#define LED22_Pin LL_GPIO_PIN_5
#define LED22_GPIO_Port GPIOA
#define LED23_Pin LL_GPIO_PIN_6
#define LED23_GPIO_Port GPIOA
#define LED24_Pin LL_GPIO_PIN_7
#define LED24_GPIO_Port GPIOA
#define LED25_Pin LL_GPIO_PIN_0
#define LED25_GPIO_Port GPIOB
#define LED26_Pin LL_GPIO_PIN_1
#define LED26_GPIO_Port GPIOB
#define LED27_Pin LL_GPIO_PIN_2
#define LED27_GPIO_Port GPIOB
#define LED28_Pin LL_GPIO_PIN_10
#define LED28_GPIO_Port GPIOB
#define LED29_Pin LL_GPIO_PIN_11
#define LED29_GPIO_Port GPIOB
#define LED30_Pin LL_GPIO_PIN_12
#define LED30_GPIO_Port GPIOB
#define LED31_Pin LL_GPIO_PIN_13
#define LED31_GPIO_Port GPIOB
#define LED32_Pin LL_GPIO_PIN_14
#define LED32_GPIO_Port GPIOB
#define LED0_Pin LL_GPIO_PIN_15
#define LED0_GPIO_Port GPIOB
#define RST_Pin LL_GPIO_PIN_10
#define RST_GPIO_Port GPIOA
#define T_SDA_Pin LL_GPIO_PIN_11
#define T_SDA_GPIO_Port GPIOA
#define T_SCL_Pin LL_GPIO_PIN_12
#define T_SCL_GPIO_Port GPIOA
#define DATA_Pin LL_GPIO_PIN_15
#define DATA_GPIO_Port GPIOA
#define CE_Pin LL_GPIO_PIN_3
#define CE_GPIO_Port GPIOB
#define RCK_Pin LL_GPIO_PIN_4
#define RCK_GPIO_Port GPIOB
#define SCK_Pin LL_GPIO_PIN_5
#define SCK_GPIO_Port GPIOB
#define INT0_IR_Pin LL_GPIO_PIN_6
#define INT0_IR_GPIO_Port GPIOB
#define INT0_IR_EXTI_IRQn EXTI4_15_IRQn
#define INT0_YK_Pin LL_GPIO_PIN_7
#define INT0_YK_GPIO_Port GPIOB
#define INT0_YK_EXTI_IRQn EXTI4_15_IRQn
#define LED00_Pin LL_GPIO_PIN_8
#define LED00_GPIO_Port GPIOB
#ifndef NVIC_PRIORITYGROUP_0
#define NVIC_PRIORITYGROUP_0         ((uint32_t)0x00000007) /*!< 0 bit  for pre-emption priority,
                                                                 4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1         ((uint32_t)0x00000006) /*!< 1 bit  for pre-emption priority,
                                                                 3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2         ((uint32_t)0x00000005) /*!< 2 bits for pre-emption priority,
                                                                 2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3         ((uint32_t)0x00000004) /*!< 3 bits for pre-emption priority,
                                                                 1 bit  for subpriority */
#define NVIC_PRIORITYGROUP_4         ((uint32_t)0x00000003) /*!< 4 bits for pre-emption priority,
                                                                 0 bit  for subpriority */
#endif

/* USER CODE BEGIN Private defines */
#define IRR_CH_Neg (0x00FFA25D)
#define IRR_CH (0x00FF629D)
#define IRR_Start (0x00FFC23D)
#define IRR_Right (0x00FF02FD)
#define IRR_Left (0x00FF22DD)
#define IRR_Up (0x00FFA857)
#define IRR_Down (0x00FFA857)
#define IRR_CH_Plus (0x00FFE21D)
#define IRR_1 (0x00FF30CF)
#define IRR_2 (0x00FF18E7)
#define IRR_3 (0x00FF7A85)
#define IRR_4 (0x00FF10EF)
#define IRR_5 (0x00FF38C7)
#define IRR_6 (0x00FF5AA5)
#define IRR_7 (0x00FF42BD)
#define IRR_8 (0x00FF4AB5)
#define IRR_9 (0x00FF52AD)

#define NEC_Rotate_Right (1<<0)
#define NEC_Rotate_Left (1<<1)
#define NEC_Time_Adjust (1<<2)
#define NEC_Show (1<<3)

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
