/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f0xx_it.c
  * @brief   Interrupt Service Routines.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f0xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */
/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
uint32_t timecount = 0;
uint16_t delay;
uint32_t lastCapture;
uint8_t bitIndex = 0;
uint32_t currentCapture;
uint32_t pulseWidth;
uint8_t show_flag=0;
uint16_t show_cnt=0;

uint8_t cnt=0;
int delay_data=0;
uint32_t scount=0;
uint32_t command_pre;
uint8_t spoint,mpoint,hpoint;
uint8_t date[14];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
void renew(uint8_t idx_datab, uint8_t idx_datac);
uint32_t convert_input(uint32_t input);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */
uint32_t command;
_Bool FinishReading;
uint32_t currentCapture;
uint32_t laaCapture;
uint32_t pulseWidth;
/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M0 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
   while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVC_IRQn 0 */

  /* USER CODE END SVC_IRQn 0 */
  /* USER CODE BEGIN SVC_IRQn 1 */

  /* USER CODE END SVC_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */

  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f0xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line 4 to 15 interrupts.
  */
void EXTI4_15_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI4_15_IRQn 0 */
  /* USER CODE END EXTI4_15_IRQn 0 */
  if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_6) != RESET)
  {
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_6);
    /* USER CODE BEGIN LL_EXTI_LINE_6 */
    if(timecount<120) return;
    uint16_t timeint = (timecount*(LL_TIM_GetAutoReload(TIM3)+1)+LL_TIM_GetCounter(TIM3)+1)/240;
		LL_TIM_SetAutoReload(TIM3,timeint-1);
    timecount = 0;
    if(rotate_v==5) return;
    cnt++;
    if(cnt>=rotate_v)
    {
      cnt=0;
      delay_data++;
      if(delay_data>=240) delay_data=0;
    }
    /* USER CODE END LL_EXTI_LINE_6 */
  }
  if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_7) != RESET)
  {
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_7);
    /* USER CODE BEGIN LL_EXTI_LINE_7 */
    currentCapture = LL_TIM_GetCounter(TIM2);
    pulseWidth = currentCapture - lastCapture;
    lastCapture = currentCapture;
    laaCapture = lastCapture;
    if(pulseWidth > 13000 && pulseWidth < 14000 && dataReady == 0 )  //9000+4500 = 13500
    {
      bitIndex = 0;
      command_pre = 0;
      FinishReading = 0;
    }
    else if( pulseWidth > 10500 && pulseWidth < 12000 && FinishReading != 1)//9000+2250 = 11250
    {
      bitIndex = 0;
      command_pre = 0;
    }
    else if(FinishReading)  return;
    else if(pulseWidth<500)
    {
      lastCapture = laaCapture;
      return;
    }
    else if(pulseWidth > 2000 && pulseWidth < 2500) // 560+1690 = 2250
    {
      command_pre = (command_pre << 1)|1;
      bitIndex++;
    }
    else if(pulseWidth > 800 && pulseWidth < 1500) //560+560 = 1120
    {
      command_pre = command_pre << 1;
      bitIndex++;
    }
    if(bitIndex == 32)
    {
      bitIndex = 0;
      command = command_pre;
      dataReady = 1;
      FinishReading = 1;
    }
    /* USER CODE END LL_EXTI_LINE_7 */
  }
  /* USER CODE BEGIN EXTI4_15_IRQn 1 */

  /* USER CODE END EXTI4_15_IRQn 1 */
}

/**
  * @brief This function handles TIM1 break, update, trigger and commutation interrupts.
  */
void TIM1_BRK_UP_TRG_COM_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_BRK_UP_TRG_COM_IRQn 0 */
  if(LL_TIM_IsActiveFlag_UPDATE(TIM1)!= RESET)
  {
    LL_TIM_ClearFlag_UPDATE(TIM1);
    getdate();
    spoint=date[12]*10+date[13];
    mpoint=date[10]*10+date[11];
    hpoint=(date[8]&1)*10+date[9];  
  }
  /* USER CODE END TIM1_BRK_UP_TRG_COM_IRQn 0 */
  /* USER CODE BEGIN TIM1_BRK_UP_TRG_COM_IRQn 1 */

  /* USER CODE END TIM1_BRK_UP_TRG_COM_IRQn 1 */
}

/**
  * @brief This function handles TIM3 global interrupt.
  */
void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */
   if(LL_TIM_IsActiveFlag_UPDATE(TIM3)!= RESET)
    {
        LL_TIM_ClearFlag_UPDATE(TIM3);
        uint8_t idx_c;
        if(WorkState&NEC_Rotate_Left)
          idx_c=(timecount+(uint32_t)delay_data)%240;
        else if(WorkState&NEC_Rotate_Right)
          idx_c=(240+timecount-(uint32_t)delay_data)%240;
        else
          idx_c=timecount%240;
        renew(timecount%240,idx_c);
        timecount++;
    }
  /* USER CODE END TIM3_IRQn 0 */
  /* USER CODE BEGIN TIM3_IRQn 1 */
  
  /* USER CODE END TIM3_IRQn 1 */
}

/* USER CODE BEGIN 1 */
uint32_t display_date(uint8_t idx)
{
  uint8_t datamod2_8[18][8]={
  {0x3c, 0x62, 0x62, 0x3c, 0x00, 0x00, 0x00, 0x00},
  {0x00, 0x22, 0x7e, 0x02, 0x00, 0x00, 0x00, 0x00},
  {0x66, 0xee, 0xde, 0xfa, 0x62, 0x00, 0x00, 0x00},
  {0x44, 0xd6, 0xf6, 0xfe, 0x0c, 0x00, 0x00, 0x00},
  {0x18, 0x38, 0x6e, 0xfe, 0x08, 0x00, 0x00, 0x00},
  {0x36, 0x76, 0x56, 0x5e, 0x4c, 0x00, 0x00, 0x00},
  {0x1c, 0x7e, 0xf6, 0xde, 0x0c, 0x00, 0x00, 0x00},
  {0x60, 0x4e, 0x78, 0x60, 0x00, 0x00, 0x00, 0x00},
  {0x36, 0x5a, 0x5a, 0x36, 0x00, 0x00, 0x00, 0x00},
  {0x38, 0x4a, 0x6a, 0x3c, 0x00, 0x00, 0x00, 0x00},
  {0x00, 0x22, 0x7e, 0x02, 0x3c, 0x62, 0x62, 0x3c},
  {0x00, 0x22, 0x7e, 0x02, 0x00, 0x22, 0x7e, 0x02},
  {0x00, 0x22, 0x7e, 0x02, 0x32, 0x46, 0x4a, 0x32},
  {0x24, 0xfc, 0x54, 0x54, 0x7f, 0x54, 0x54, 0x04},
  {0x01, 0xfe, 0xa8, 0xa8, 0xa8, 0xa9, 0xff, 0x00},
  {0x00, 0xff, 0x91, 0x91, 0x91, 0xff, 0x00, 0x00},
  {0x05, 0xfd, 0xed, 0xff, 0xed, 0xed, 0x09, 0x00},
  {0x45, 0xfe, 0x6e, 0xff, 0xfe, 0xa9, 0xff, 0x00},
  };
  if(idx<64) return 0;
  else if(idx>=176)  return 0;
  uint8_t idxx=idx-64;
  uint8_t k=idxx%8;
  if(idxx<8)  return datamod2_8[2][k];
  if(idxx<16)  return datamod2_8[0][k];
  if(idxx<24)  return datamod2_8[date[0]][k];
  if(idxx<32)  return datamod2_8[date[1]][k];
  if(idxx<40)  return datamod2_8[13][k];
  if(idxx<48)  return datamod2_8[date[2]][k];
  if(idxx<56)  return datamod2_8[date[3]][k];
  if(idxx<64)  return datamod2_8[14][k];
  if(idxx<72)  return datamod2_8[date[4]][k];
  if(idxx<80)  return datamod2_8[date[5]][k];
  if(idxx<88)  return datamod2_8[15][k];
  if(idxx<96)  return datamod2_8[16][k];
  if(idxx<104)  return datamod2_8[17][k];
  if(idxx<112)  return datamod2_8[date[7]][k];
  return 0;
}
void renew(uint8_t idx_datab,uint8_t idx_datac)
{
  uint32_t tmp=0x80000000;
  uint32_t shine=datac_pre[idx_datac]<<16;
  uint8_t spointer,mpointer,hpointer;
  if((WorkState&NEC_Show)==0)
  {
    shine|=datab_pre[idx_datab];
    spointer=spoint*4;
    mpointer=spointer/60+mpoint*4;
    hpointer=mpointer/12+hpoint*20;
    shine|=display_date(idx_datab);
    if(idx_datab==(239-spointer)) shine|=0xF0FF;
    else if(idx_datab==(239-mpointer))  shine|=0xFC; 
  }
  else
  {
    show_cnt++;
    if(show_cnt>=480)
    {
      show_cnt=0;
      show_flag=(show_flag+1)%4;
    }
    shine |= x[show_flag][idx_datab];
  }
  LL_GPIO_ResetOutputPin(SCK_GPIO_Port, SCK_Pin);
	LL_GPIO_ResetOutputPin(RCK_GPIO_Port, RCK_Pin);
  for(int i=0;i<32;i++)
  {
    if(shine & tmp)
    {
      LL_GPIO_ResetOutputPin(DATA_GPIO_Port, DATA_Pin);
    }
    else
    {
      LL_GPIO_SetOutputPin(DATA_GPIO_Port, DATA_Pin);
    }
		for(delay = 0; delay < 1; delay++) {
      // Do nothing
    }
    LL_GPIO_SetOutputPin(SCK_GPIO_Port, SCK_Pin);
    // Add a short delay
    for(delay = 0; delay < 1; delay++) {
      // Do nothing
    }
    LL_GPIO_ResetOutputPin(SCK_GPIO_Port, SCK_Pin);
    tmp = tmp >> 1;
  }
	LL_GPIO_SetOutputPin(RCK_GPIO_Port, RCK_Pin);
	for(int delay = 0; delay < 1; delay++) {
				// Do nothing
	}
  LL_GPIO_ResetOutputPin(RCK_GPIO_Port, RCK_Pin);
  if((WorkState&NEC_Show)==0)
  {
    if(idx_datab==(239-spointer))
    {
      LL_GPIO_ResetOutputPin(GPIOA, LED17_Pin|LED18_Pin|LED19_Pin|LED20_Pin|LED21_Pin|LED22_Pin|LED23_Pin|LED24_Pin);
      LL_GPIO_ResetOutputPin(GPIOB, LED25_Pin|LED26_Pin|LED27_Pin|LED28_Pin|LED29_Pin|LED30_Pin|LED31_Pin|LED32_Pin);
    }
    else if(idx_datab==(239-mpointer))
    {
      LL_GPIO_ResetOutputPin(GPIOA, LED17_Pin|LED18_Pin|LED19_Pin|LED20_Pin|LED21_Pin|LED22_Pin|LED23_Pin|LED24_Pin);
      LL_GPIO_ResetOutputPin(GPIOB, LED25_Pin|LED26_Pin|LED27_Pin|LED28_Pin|LED29_Pin|LED30_Pin|LED31_Pin|LED32_Pin);
    }
    else if(idx_datab==(239-hpointer)||idx_datab==(239-hpointer+1)%240||idx_datab==(240+239-hpointer-1)%240)
    {
      LL_GPIO_ResetOutputPin(GPIOA, LED21_Pin|LED22_Pin|LED23_Pin|LED24_Pin);
      LL_GPIO_ResetOutputPin(GPIOB, LED25_Pin|LED26_Pin|LED27_Pin|LED28_Pin|LED29_Pin|LED30_Pin|LED31_Pin|LED32_Pin);
    }
    else
    {
      LL_GPIO_SetOutputPin(GPIOA, LED17_Pin|LED18_Pin|LED19_Pin|LED20_Pin|LED21_Pin|LED22_Pin|LED23_Pin|LED24_Pin);
      LL_GPIO_SetOutputPin(GPIOB, LED25_Pin|LED26_Pin|LED27_Pin|LED28_Pin|LED29_Pin|LED30_Pin|LED31_Pin|LED32_Pin);
    }
    if(idx_datab%20==0)
    {
      LL_GPIO_ResetOutputPin(LED0_GPIO_Port, LED0_Pin);
    }
    else
    {
      LL_GPIO_SetOutputPin(LED0_GPIO_Port, LED0_Pin);
    }
  }
  else
  {
    tmp=y[show_flag][idx_datab]&0xFF;
    LL_GPIO_ResetOutputPin(GPIOA,tmp);
    tmp^=0xFF;
    LL_GPIO_SetOutputPin(GPIOA,tmp);
    tmp=((y[show_flag][idx_datab]>>8)&0x7)|((y[show_flag][idx_datab]>>1)&0x7C00);
    LL_GPIO_ResetOutputPin(GPIOB,tmp);
    tmp^=0x7C07;
    LL_GPIO_SetOutputPin(GPIOB,tmp);
  }
}
uint32_t convert_input(uint32_t input)
{
  uint32_t tmp=0x00000001;
  uint32_t output=0;
	int i;
  for(int i=0;i<8;i++)
  {
    if(tmp&input) output|=(1<<(7-i));
    tmp=tmp<<1;
  }
  for(i=8;i<16;i++)
  {
    if(tmp&input) output|=(1<<(15-i))<<8;
    tmp=tmp<<1;
  }
  for(i=16;i<24;i++)
  {
    if(tmp&input) output|=(1<<(23-i))<<16;
    tmp=tmp<<1;
  }
  for(i=24;i<32;i++)
  {
    if(tmp&input) output|=(1<<(31-i))<<24;
    tmp=tmp<<1;
  }
  return output;
}
/* USER CODE END 1 */
