/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM1_Init(void);
/* USER CODE BEGIN PFP */
void DS1302WriteByte(uint8_t dat);
uint8_t DS1302ReadByte(void);
void Init_DS1302(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t date[14];
char str[15]="fjy 3220104119";
uint8_t datamode[15][32]=
{
  {0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xF8,0x20,0x04,0x40,0x02,0x40,0x02,0x40,0x02,
  0x40,0x02,0x40,0x02,0x20,0x04,0x1F,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, //0
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x02,0x20,0x02,0x7F,0xFE,
  0x00,0x02,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, //1
  {0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x06,0x20,0x0A,0x40,0x12,0x40,0x22,0x40,0x42,
  0x40,0x82,0x21,0x02,0x1E,0x02,0x00,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, //2
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x02,0x40,0x02,0x40,0x02,0x42,0x02,
  0x42,0x04,0x46,0x04,0x49,0x08,0x30,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, //3
  {0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x70,0x01,0x90,0x06,0x10,0x18,0x12,0x60,0x12,
  0x7F,0xFE,0x00,0x12,0x00,0x12,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, //4
  {0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x82,0x41,0x02,0x42,0x02,0x42,0x04,0x42,0x04,
  0x42,0x04,0x41,0x18,0x40,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, //5
  {0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xF8,0x0C,0x84,0x11,0x02,0x21,0x02,0x41,0x02,
  0x41,0x02,0x00,0x84,0x00,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, //6
  {0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x00,0x40,0x00,0x40,0x00,0x40,0x0E,0x40,0x70,
  0x41,0x80,0x42,0x00,0x4C,0x00,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, //7
  {0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x78,0x22,0x84,0x41,0x02,0x41,0x02,0x41,0x02,
  0x41,0x02,0x41,0x02,0x22,0x84,0x1C,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, //8
  {0x00,0x00,0x00,0x00,0x00,0x00,0x1E,0x00,0x21,0x00,0x40,0x82,0x40,0x82,0x40,0x84,
  0x40,0x88,0x21,0x30,0x1F,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, //9
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, //" "
  {0x00,0x00,0x40,0x10,0x30,0x1C,0x38,0x3E,0x10,0xE4,0x01,0x10,0x40,0x10,0x7F,0x90,
  0x7F,0x10,0x41,0x10,0x41,0x14,0x7F,0x32,0xFF,0x13,0x41,0xFE,0x03,0xFC,0x01,0x00}, //"冯"
  {0x00,0x00,0x02,0x00,0x2B,0xFF,0x2A,0xFE,0xFE,0xA8,0x7E,0xAA,0x2A,0xFF,0x2F,0xFE,
  0x1D,0x44,0xF5,0x42,0x67,0xFF,0x2F,0xFE,0x3D,0x40,0x77,0xE0,0x2F,0xC0,0x05,0x00}, //"静"
  {0x00,0x00,0x07,0x00,0x18,0x00,0xFF,0xFF,0xFF,0xFE,0x0C,0x00,0x06,0x00,0x04,0x00,
  0x0E,0xFF,0x1C,0xFF,0x74,0x42,0xE4,0x42,0x44,0x42,0x1C,0x7F,0x0E,0xFE,0x04,0x40}, //"怡"
  { 0x00,0x00,0x10,0x02,
    0x20,0x02,0x7F,0xFE,
    0x00,0x02,0x00,0x02,
    0x00,0x00,0x18,0x06,
    0x20,0x0A,0x40,0x12,
    0x40,0x22,0x40,0x42,
    0x40,0x82,0x21,0x02,
    0x1E,0x02,0x00,0x0E}  //"12"
};
uint8_t datamod_8[18][8]={
  {0x3c, 0x46, 0x46, 0x3c, 0x00, 0x00, 0x00, 0x00},//0
  {0x00, 0x44, 0x7e, 0x40, 0x00, 0x00, 0x00, 0x00},//1
  {0x66, 0x77, 0x7b, 0x5f, 0x46, 0x00, 0x00, 0x00},//2
  {0x22, 0x6b, 0x6f, 0x7f, 0x30, 0x00, 0x00, 0x00},//3
  {0x18, 0x1c, 0x76, 0x7f, 0x10, 0x00, 0x00, 0x00},//4
  {0x6c, 0x6e, 0x6a, 0x7a, 0x32, 0x00, 0x00, 0x00},//5
  {0x38, 0x7e, 0x6f, 0x7b, 0x30, 0x00, 0x00, 0x00},//6
  {0x06, 0x72, 0x1e, 0x06, 0x00, 0x00, 0x00, 0x00},//7
  {0x6c, 0x5a, 0x5a, 0x6c, 0x00, 0x00, 0x00, 0x00},//8
  {0x1c, 0x52, 0x56, 0x3c, 0x00, 0x00, 0x00, 0x00},//9
  {0x00,0x44,0x7e,0x40,0x3c,0x46,0x46,0x3c},//10
  {0x00,0x44,0x7e,0x40,0x00,0x44,0x7e,0x40},//11
  {0x00,0x44,0x7e,0x40,0x4c,0x62,0x52,0x4c},//12
  {0x24, 0x3f, 0x2a, 0x2a, 0xfe, 0x2a, 0x2a, 0x20},//年
  {0x80, 0x7f, 0x15, 0x15, 0x15, 0x95, 0xff, 0x00},//月
  {0x00, 0xff, 0x89, 0x89, 0x89, 0xff, 0x00, 0x00},//日
  {0xa0, 0xbf, 0xb7, 0xff, 0xb7, 0xb7, 0x90, 0x00},//星
  {0xa2, 0x7f, 0x76, 0xff, 0x7f, 0x95, 0xff, 0x00}//期
};
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
void Initial_c(void)
{
  uint8_t i=0;
  uint8_t j=0;
  int k=10;
	while(str[i]!='\0')
  {
    if(str[i]<='9'&&str[i]>='0')  
      k=str[i]-'0';
    else if(str[i]=='f') k=11;
    else if(str[i]=='j') k=12;
    else if(str[i]=='y') k=13;
    else if(str[i]==' ') k=10;
    else k=10;
    for(int w=0;w<32;w+=2)
    {
      datac_pre[j]=0;
      datab_pre[j]=0;
      datac_pre[j]=((datamode[k][w]))|((datamode[k][w+1])<<8);
      if(j%4==0)
      {
        datab_pre[j]=1<<8;
      }
      j++;
    }
		i++;
  }
  for(k=j;k<=239;k++)
  {
    datab_pre[k]=0;
    if(k%4==0)
    {
      datab_pre[k]|=1<<8;
    }
	}
  for(k=236;k<=243;k++)
  {
    datab_pre[239-k%240]|=datamod_8[12][k-236]<<8;
  }
  i=1;
  for(i=1;i<=9;i++)
  {
    for(k=i*20-2;k<=i*20+5;k++)
    {
      datab_pre[239-k]|=datamod_8[i][k-i*20+2]<<8;
    }
  }
  for(i=10;i<=11;i++)
  {
    for(k=i*20-5;k<=i*20+2;k++)
    {
      datab_pre[239-k]|=datamod_8[i][k-i*20+5]<<8;
    }
  }
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  /* SysTick_IRQn interrupt configuration */
  NVIC_SetPriority(SysTick_IRQn, 3);

  /* USER CODE BEGIN Init */
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM3_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
  //Init_DS1302();
  Initial_c();
	uint16_t delay;
	LL_GPIO_ResetOutputPin(CE_GPIO_Port, CE_Pin);
  LL_GPIO_ResetOutputPin(SCK_GPIO_Port, SCK_Pin);
	LL_GPIO_ResetOutputPin(RCK_GPIO_Port, RCK_Pin);
  for(int i=0;i<32;i++)
  {
    LL_GPIO_SetOutputPin(DATA_GPIO_Port, DATA_Pin);
		for(delay = 0; delay < 1; delay++) {
      // Do nothing
    }
    LL_GPIO_SetOutputPin(SCK_GPIO_Port, SCK_Pin);
    // Add a short delay
    for(delay = 0; delay < 1; delay++) {
      // Do nothing
    }
    LL_GPIO_ResetOutputPin(SCK_GPIO_Port, SCK_Pin);
		
  }
	LL_GPIO_SetOutputPin(RCK_GPIO_Port, RCK_Pin);
	for(delay = 0; delay < 1; delay++) {
		// Do nothing
	}
	LL_GPIO_ResetOutputPin(RCK_GPIO_Port, RCK_Pin);
	LL_TIM_SetAutoReload(TIM3,1000-1);
  LL_TIM_EnableIT_UPDATE(TIM3);
  LL_TIM_EnableCounter(TIM3);
  //LL_TIM_EnableIT_UPDATE(TIM1);
  //LL_TIM_EnableCounter(TIM1);
 
  /* Enable GPIO interrupt for INT0_IR */
  LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_6);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    getdate();
    spoint=date[12]*10+date[13];
    mpoint=date[10]*10+date[11];
    hpoint=(date[8]&1)*10+date[9];
    /*for( i=0;i<14;i++)// s0,s1,m0,m1,h0,h1,w0,00,d0,d1,m0,m1,y0,y1
    {
      for(uint8_t w=0;w<32;w+=2)
      {
        datab_pre[j]=((uint32_t)(datamode[date[i]][w]))|((uint32_t)(datamode[date[i]][w+1])<<8);
        j++;
      }
    }
    for(uint8_t w=j;w<239;w++)
    {
      datab_pre[j]=0;
      j++;
    }*/
    LL_mDelay(990);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);
  while(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_1)
  {
  }
  LL_RCC_HSI_Enable();

   /* Wait till HSI is ready */
  while(LL_RCC_HSI_IsReady() != 1)
  {

  }
  LL_RCC_HSI_SetCalibTrimming(16);
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI_DIV_2, LL_RCC_PLL_MUL_12);
  LL_RCC_PLL_Enable();

   /* Wait till PLL is ready */
  while(LL_RCC_PLL_IsReady() != 1)
  {

  }
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {

  }
  LL_Init1msTick(48000000);
  LL_SetSystemCoreClock(48000000);
}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  LL_TIM_InitTypeDef TIM_InitStruct = {0};

  /* Peripheral clock enable */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_TIM1);

  /* TIM1 interrupt Init */
  NVIC_SetPriority(TIM1_BRK_UP_TRG_COM_IRQn, 0);
  NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  TIM_InitStruct.Prescaler = 479;
  TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
  TIM_InitStruct.Autoreload = 99;
  TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
  TIM_InitStruct.RepetitionCounter = 0;
  LL_TIM_Init(TIM1, &TIM_InitStruct);
  LL_TIM_DisableARRPreload(TIM1);
  LL_TIM_SetClockSource(TIM1, LL_TIM_CLOCKSOURCE_INTERNAL);
  LL_TIM_SetTriggerOutput(TIM1, LL_TIM_TRGO_RESET);
  LL_TIM_DisableMasterSlaveMode(TIM1);
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  LL_TIM_InitTypeDef TIM_InitStruct = {0};

  /* Peripheral clock enable */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);

  /* TIM3 interrupt Init */
  NVIC_SetPriority(TIM3_IRQn, 1);
  NVIC_EnableIRQ(TIM3_IRQn);

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  TIM_InitStruct.Prescaler = 15;
  TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
  TIM_InitStruct.Autoreload = 1999;
  TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
  LL_TIM_Init(TIM3, &TIM_InitStruct);
  LL_TIM_DisableARRPreload(TIM3);
  LL_TIM_SetClockSource(TIM3, LL_TIM_CLOCKSOURCE_INTERNAL);
  LL_TIM_SetTriggerOutput(TIM3, LL_TIM_TRGO_RESET);
  LL_TIM_DisableMasterSlaveMode(TIM3);
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  LL_EXTI_InitTypeDef EXTI_InitStruct = {0};
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);

  /**/
  LL_GPIO_SetOutputPin(LED17_GPIO_Port, LED17_Pin);

  /**/
  LL_GPIO_SetOutputPin(LED18_GPIO_Port, LED18_Pin);

  /**/
  LL_GPIO_SetOutputPin(LED19_GPIO_Port, LED19_Pin);

  /**/
  LL_GPIO_SetOutputPin(LED20_GPIO_Port, LED20_Pin);

  /**/
  LL_GPIO_SetOutputPin(LED21_GPIO_Port, LED21_Pin);

  /**/
  LL_GPIO_SetOutputPin(LED22_GPIO_Port, LED22_Pin);

  /**/
  LL_GPIO_SetOutputPin(LED23_GPIO_Port, LED23_Pin);

  /**/
  LL_GPIO_SetOutputPin(LED24_GPIO_Port, LED24_Pin);

  /**/
  LL_GPIO_SetOutputPin(LED25_GPIO_Port, LED25_Pin);

  /**/
  LL_GPIO_SetOutputPin(LED26_GPIO_Port, LED26_Pin);

  /**/
  LL_GPIO_SetOutputPin(LED27_GPIO_Port, LED27_Pin);

  /**/
  LL_GPIO_SetOutputPin(LED28_GPIO_Port, LED28_Pin);

  /**/
  LL_GPIO_SetOutputPin(LED29_GPIO_Port, LED29_Pin);

  /**/
  LL_GPIO_SetOutputPin(LED30_GPIO_Port, LED30_Pin);

  /**/
  LL_GPIO_SetOutputPin(LED31_GPIO_Port, LED31_Pin);

  /**/
  LL_GPIO_SetOutputPin(LED32_GPIO_Port, LED32_Pin);

  /**/
  LL_GPIO_SetOutputPin(LED0_GPIO_Port, LED0_Pin);

  /**/
  LL_GPIO_SetOutputPin(CE_GPIO_Port, CE_Pin);

  /**/
  LL_GPIO_ResetOutputPin(RST_GPIO_Port, RST_Pin);

  /**/
  LL_GPIO_ResetOutputPin(T_SDA_GPIO_Port, T_SDA_Pin);

  /**/
  LL_GPIO_ResetOutputPin(T_SCL_GPIO_Port, T_SCL_Pin);

  /**/
  LL_GPIO_ResetOutputPin(DATA_GPIO_Port, DATA_Pin);

  /**/
  LL_GPIO_ResetOutputPin(RCK_GPIO_Port, RCK_Pin);

  /**/
  LL_GPIO_ResetOutputPin(SCK_GPIO_Port, SCK_Pin);

  /**/
  LL_GPIO_ResetOutputPin(LED00_GPIO_Port, LED00_Pin);

  /**/
  GPIO_InitStruct.Pin = LED17_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LED17_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LED18_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LED18_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LED19_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LED19_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LED20_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LED20_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LED21_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LED21_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LED22_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LED22_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LED23_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LED23_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LED24_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LED24_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LED25_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LED25_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LED26_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LED26_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LED27_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LED27_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LED28_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LED28_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LED29_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LED29_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LED30_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LED30_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LED31_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LED31_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LED32_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LED32_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LED0_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LED0_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = RST_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(RST_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = T_SDA_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(T_SDA_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = T_SCL_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(T_SCL_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = DATA_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(DATA_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = CE_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(CE_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = RCK_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(RCK_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = SCK_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(SCK_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LED00_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LED00_GPIO_Port, &GPIO_InitStruct);

  /**/
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB, LL_SYSCFG_EXTI_LINE6);

  /**/
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB, LL_SYSCFG_EXTI_LINE7);

  /**/
  LL_GPIO_SetPinPull(INT0_IR_GPIO_Port, INT0_IR_Pin, LL_GPIO_PULL_NO);

  /**/
  LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_7, LL_GPIO_PULL_NO);

  /**/
  LL_GPIO_SetPinMode(INT0_IR_GPIO_Port, INT0_IR_Pin, LL_GPIO_MODE_INPUT);

  /**/
  LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_7, LL_GPIO_MODE_INPUT);

  /**/
  EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_6;
  EXTI_InitStruct.LineCommand = ENABLE;
  EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
  EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
  LL_EXTI_Init(&EXTI_InitStruct);

  /**/
  EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_7;
  EXTI_InitStruct.LineCommand = ENABLE;
  EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
  EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_FALLING;
  LL_EXTI_Init(&EXTI_InitStruct);

  /* EXTI interrupt init*/
  NVIC_SetPriority(EXTI4_15_IRQn, 0);
  NVIC_EnableIRQ(EXTI4_15_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
uint8_t DS1302Read(uint8_t cmd)
{
  uint8_t dat=0;
  LL_GPIO_ResetOutputPin(RST_GPIO_Port, RST_Pin);
  LL_GPIO_ResetOutputPin(T_SCL_GPIO_Port, T_SCL_Pin);
  LL_GPIO_SetOutputPin(RST_GPIO_Port, RST_Pin);
  DS1302WriteByte(cmd);
  LL_GPIO_SetPinMode(T_SDA_GPIO_Port, T_SDA_Pin, LL_GPIO_MODE_INPUT);
  dat=DS1302ReadByte();
  LL_GPIO_SetPinMode(T_SDA_GPIO_Port,T_SDA_Pin,LL_GPIO_MODE_OUTPUT);
  LL_GPIO_SetOutputPin(T_SCL_GPIO_Port, T_SCL_Pin);
  LL_GPIO_ResetOutputPin(RST_GPIO_Port, RST_Pin);
  return dat;
}
void DS1302Write(uint8_t cmd, uint8_t dat)
{
  LL_GPIO_ResetOutputPin(RST_GPIO_Port, RST_Pin);
  LL_GPIO_ResetOutputPin(T_SCL_GPIO_Port, T_SCL_Pin);
  LL_GPIO_SetOutputPin(RST_GPIO_Port, RST_Pin);
  DS1302WriteByte(cmd);
  DS1302WriteByte(dat);
  LL_GPIO_SetOutputPin(T_SCL_GPIO_Port, T_SCL_Pin);
  LL_GPIO_ResetOutputPin(RST_GPIO_Port, RST_Pin);
}
void DS1302WriteByte(uint8_t dat)
{
  uint8_t i;
  LL_GPIO_ResetOutputPin(T_SCL_GPIO_Port, T_SCL_Pin);
  for(int delay=0;delay<2;delay++){}
  for(i=0;i<8;i++)
  {
    if(dat&0x01)
    {
      LL_GPIO_SetOutputPin(T_SDA_GPIO_Port, T_SDA_Pin);
    }
    else
    {
      LL_GPIO_ResetOutputPin(T_SDA_GPIO_Port, T_SDA_Pin);
    }
    for(int delay=0;delay<2;delay++){}
    LL_GPIO_SetOutputPin(T_SCL_GPIO_Port, T_SCL_Pin);
    for(int delay=0;delay<2;delay++){}
    LL_GPIO_ResetOutputPin(T_SCL_GPIO_Port, T_SCL_Pin);
    dat>>=1;
  }
}
uint8_t DS1302ReadByte(void)
{
  uint8_t i,dat=0;
  for(int delay=0;delay<1;delay++){}
  for(i=0;i<8;i++)
  {
    dat>>=1;
    if(LL_GPIO_IsInputPinSet(T_SDA_GPIO_Port, T_SDA_Pin))
    {
      dat|=0x80;
    }
    LL_GPIO_SetOutputPin(T_SCL_GPIO_Port, T_SCL_Pin);
    for(int delay=0;delay<2;delay++){}
    LL_GPIO_ResetOutputPin(T_SCL_GPIO_Port, T_SCL_Pin);
    for(int delay=0;delay<2;delay++){}
  }
  return dat;
}
void Init_DS1302(void)
{
  DS1302Write(0x8e,0x00);//写入保护开关
  DS1302Write(0x80,0x20);//写入秒
  DS1302Write(0x82,0x27);//写入分钟
  DS1302Write(0x84,0x89);//写入小时
  DS1302Write(0x86,0x05);//写入日
  DS1302Write(0x88,0x06);//写入月
  DS1302Write(0x8a,0x03);//写入星期
  DS1302Write(0x8c,0x24);//写入年
  DS1302Write(0x90,0x01);//充电
  DS1302Write(0xc0,0xf0);//初始化一次标识
  DS1302Write(0x8e,0x80);//写保护
}
void getdate()
{
  uint32_t date1;
  date1=DS1302Read(0x8d);
	date[0]=(date1&0xf0)>>4;
	date[1]=date1&0x0f;
  date1=DS1302Read(0x89);
	date[2]=(date1&0xf0)>>4;
	date[3]=date1&0x0f;
  date1=DS1302Read(0x87);
	date[4]=(date1&0xf0)>>4;
	date[5]=date1&0x0f;
  date1=DS1302Read(0x8b);
	date[6]=0;
	date[7]=date1&0x0f;
  date1=DS1302Read(0x85);
	date[8]=(date1&0x30)>>4;
	date[9]=date1&0x0f;
  date1=DS1302Read(0x83);
	date[10]=(date1&0xf0)>>4;
	date[11]=date1&0x0f;
  date1=DS1302Read(0x81);
	date[12]=(date1&0xf0)>>4;
	date[13]=date1&0x0f;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
