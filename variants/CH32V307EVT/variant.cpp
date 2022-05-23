/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
  ****************************************************
  ****************************************************
  modified by WangXuhao
  20220521
  completed work:
  rewrite digitalPin[]
  To be done:
  Confirm sysclock
*/

#include "variant.h"

#ifdef __cplusplus
extern "C"
{
#endif

  // Pin number
  const PinName digitalPin[] = {
      PA0,  // PA0/WKUP/ADC0
      PA1,  // PA1/ADC1
      PA2,  // PA2/ADC2
      PA3,  // PA3/ADC3
      PA4,  // PA4/ADC4/DAC0
      PA5,  // PA5/ADC5/DAC1
      PA6,  // PA6/ADC6
      PA7,  // PA7/ADC7
      PA8,  // PA8/MCO
      PA9,  // PA9
      PA10, // PA10
      PA11, // PA11/USB1DM
      PA12, // PA12/USB1DP
      PA13, // PA13/SWDIO
      PA14, // PA14/SWCLK
      PA15, // PA15

      PB0,  // PB0/ADC8
      PB1,  // PB1/ADC9
      PB2,  // PB2
      PB3,  // PB3
      PB4,  // PB4
      PB5,  // PB5
      PB6,  // PB6/USB2DM
      PB7,  // PB7/USB2DP
      PB8,  // PB8
      PB9,  // PB9
      PB10, // PB10
      PB11, // PB11
      PB12, // PB12
      PB13, // PB13
      PB14, // PB14
      PB15, // PB15

      PC0,  // PC0/ADC10
      PC1,  // PC1/ADC11
      PC2,  // PC2/ADC12
      PC2,  // PC2/ADC12
      PC3,  // PC3/ADC13
      PC4,  // PC4/ADC14
      PC5,  // PC5/ADC15
      PC6,  // PC6/ERXP
      PC7,  // PC7/ERXN
      PC8,  // PC8/ETXP
      PC9,  // PC9/ETXN
      PC10, // PC10
      PC11, // PC11
      PC12, // PC12
      PC13, // PC13/TAMPER-RTC
      PC14, // PC14/OSC32IN
      PC15, // PC15/OSC32OUT

      PD0,  // PD0
      PD1,  // PD1
      PD2,  // PD2
      PD3,  // PD3
      PD4,  // PD4
      PD5,  // PD5
      PD6,  // PD6
      PD7,  // PD7
      PD8,  // PD8
      PD9,  // PD9
      PD10, // PD10
      PD11, // PD11
      PD12, // PD12
      PD13, // PD13
      PD14, // PD14
      PD15, // PD15

      PE0,     // PE0
      PE1      // PE1
      PE2,     // PE2
      PE3,     // PE3
      PE4,     // PE4
      PE5,     // PE5
      PE6,     // PE6
      PE7,     // PE7
      PE8,     // PE8
      PE9,     // PE9
      PE10,    // PE10
      PE11,    // PE11
      PE12,    // PE12
      PE13,    // PE13
      PE14,    // PE14
      PE15    // PE15

  };

#ifdef __cplusplus
}
#endif

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif

  /**
   * @brief  System Clock Configuration
   *         The system Clock is configured as follow :
   *            System Clock source            = PLL (HSI/2)
   *            SYSCLK(Hz)                     = 48000000
   *            HCLK(Hz)                       = 48000000
   *            AHB Prescaler                  = 1
   *            APB1 Prescaler                 = 1
   *            HSI Frequency(Hz)              = 8000000
   *            PREDIV                         = 1
   *            PLLMUL                         = 12
   *            Flash Latency(WS)              = 1
   * @param  None
   * @retval None
   */
  WEAK void SystemClock_Config(void)
  {
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_OscInitTypeDef RCC_OscInitStruct;

    /* No HSE Oscillator on Nucleo, Activate PLL with HSI/2 as source */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = 15;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
      /* Initialization Error */
      while (1)
        ;
    }

    /* Select PLL as system clock source and configure the HCLK, PCLK1 clocks dividers */
    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1);
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
    {
      /* Initialization Error */
      while (1)
        ;
    }

    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

    /* SysTick_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
  }

#ifdef __cplusplus
}
#endif
