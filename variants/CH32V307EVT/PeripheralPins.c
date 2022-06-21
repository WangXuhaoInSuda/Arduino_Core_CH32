/*
 *******************************************************************************
 * Copyright (c) 2019, STMicroelectronics
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *******************************************************************************
 * Automatically generated from STM32L432K(B-C)Ux.xml
 */
#include "Arduino.h"
#include "PeripheralPins.h"

/* =====
 * Note: Commented lines are alternative possibilities which are not used per default.
 *       If you change them, you will have to know what you do
 * =====
 */

//*** ADC ***

#ifdef ADC_MODULE_ENABLED
const PinMap PinMap_ADC[] = {
  {PA_0,  ADC1,  CH_PIN_DATA_EXT(CH_MODE_ANALOG, GPIO_Mode_AIN, 0, ADC_Channel_0)}, // ADC1_IN0
  {PA_1,  ADC1,  CH_PIN_DATA_EXT(CH_MODE_ANALOG, GPIO_Mode_AIN, 0, ADC_Channel_1)}, // ADC1_IN1
  {PA_2,  ADC1,  CH_PIN_DATA_EXT(CH_MODE_ANALOG, GPIO_Mode_AIN, 0, ADC_Channel_2)}, // ADC1_IN2
  {PA_3,  ADC1,  CH_PIN_DATA_EXT(CH_MODE_ANALOG, GPIO_Mode_AIN, 0, ADC_Channel_3)}, // ADC1_IN3
  {PA_4,  ADC1,  CH_PIN_DATA_EXT(CH_MODE_ANALOG, GPIO_Mode_AIN, 0, ADC_Channel_4)}, // ADC1_IN4
  {PA_5,  ADC1,  CH_PIN_DATA_EXT(CH_MODE_ANALOG, GPIO_Mode_AIN, 0, ADC_Channel_5)}, // ADC1_IN5
  {PA_6,  ADC1,  CH_PIN_DATA_EXT(CH_MODE_ANALOG, GPIO_Mode_AIN, 0, ADC_Channel_6)}, // ADC1_IN6
  {PA_7,  ADC1,  CH_PIN_DATA_EXT(CH_MODE_ANALOG, GPIO_Mode_AIN, 0, ADC_Channel_7)}, // ADC1_IN7
  {PB_0,  ADC1,  CH_PIN_DATA_EXT(CH_MODE_ANALOG, GPIO_Mode_AIN, 0, ADC_Channel_8)}, // ADC1_IN8
  {PB_1,  ADC1,  CH_PIN_DATA_EXT(CH_MODE_ANALOG, GPIO_Mode_AIN, 0, ADC_Channel_9)}, // ADC1_IN9
  {PC_0,  ADC1,  CH_PIN_DATA_EXT(CH_MODE_ANALOG, GPIO_Mode_AIN, 0, ADC_Channel_10)}, // ADC1_IN10
  {PC_1,  ADC1,  CH_PIN_DATA_EXT(CH_MODE_ANALOG, GPIO_Mode_AIN, 0, ADC_Channel_11)}, // ADC1_IN11
  {PC_2,  ADC1,  CH_PIN_DATA_EXT(CH_MODE_ANALOG, GPIO_Mode_AIN, 0, ADC_Channel_12)}, // ADC1_IN12
  {PC_3,  ADC1,  CH_PIN_DATA_EXT(CH_MODE_ANALOG, GPIO_Mode_AIN, 0, ADC_Channel_13)}, // ADC1_IN13
  {PC_4,  ADC1,  CH_PIN_DATA_EXT(CH_MODE_ANALOG, GPIO_Mode_AIN, 0, ADC_Channel_14)}, // ADC1_IN14
  {PC_5,  ADC1,  CH_PIN_DATA_EXT(CH_MODE_ANALOG, GPIO_Mode_AIN, 0, ADC_Channel_15)}, // ADC1_IN15
  {NC,    NP,    0}
};
#endif

//*** DAC ***

#ifdef DAC_MODULE_ENABLED
const PinMap PinMap_DAC[] = {
  {PA_4,  DAC, CH_PIN_DATA_EXT(CH_MODE_ANALOG, GPIO_Mode_AIN, 0, 0)}, // DAC1
  {PA_5,  DAC, CH_PIN_DATA_EXT(CH_MODE_ANALOG, GPIO_Mode_AIN, 0, 1)}, // DAC2
  {NC,    NP,    0}
};
#endif

//*** I2C ***

#ifdef I2C_MODULE_ENABLED
const PinMap PinMap_I2C_SDA[] = {
  {PB_7,  I2C1, CH_PIN_DATA_EXT(GPIO_Mode_AF_OD, GPIO_Mode_AF_OD, 1, 0)},
  {PB_11,  I2C2, CH_PIN_DATA_EXT(GPIO_Mode_AF_OD, GPIO_Mode_AF_OD, 1, 0)},
  {PB_9,  I2C1, CH_PIN_DATA_EXT(GPIO_Mode_AF_OD, GPIO_Mode_AF_OD, 1, 1)},
  {NC,    NP,    0}
};
#endif

#ifdef I2C_MODULE_ENABLED
const PinMap PinMap_I2C_SCL[] = {
  {PB_6,  I2C1, CH_PIN_DATA_EXT(GPIO_Mode_AF_OD, GPIO_Mode_AF_OD, 1,0)},
  {PA_7,  I2C2, CH_PIN_DATA_EXT(GPIO_Mode_AF_OD, GPIO_Mode_AF_OD, 1,0)},
  {PB_8,  I2C1, CH_PIN_DATA_EXT(GPIO_Mode_AF_OD, GPIO_Mode_AF_OD, 1, 1)},
  {NC,    NP,    0}
};
#endif

//*** PWM ***
//1 2 3 4 5 8 9 10  
//CHANNEL define:
//[0] complementary config CHx 0 CHxN 1
//[2:1] channel config CH1 00 CH2 01 CH3 10 CH4 11
//[3] remap config
#ifdef TIM_MODULE_ENABLED
const PinMap PinMap_PWM[] = {
  {PB_13,  TIM1,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0001)}, // TIM1_CH1N
  {PB_14,  TIM1,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0011)}, // TIM1_CH2N
  {PB_15,  TIM1,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0101)}, // TIM1_CH3N
  {PA_8,   TIM1,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0000)}, // TIM1_CH1
  {PA_9,   TIM1,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0010)}, // TIM1_CH2
  {PA_10,  TIM1,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0100)}, // TIM1_CH3
  {PA_11,  TIM1,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0110)}, // TIM1_CH4

  {PA_0,   TIM2,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0000)}, // TIM2_CH1
  {PA_1,   TIM2,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0010)}, // TIM2_CH2
  {PA_2,   TIM2,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0100)}, // TIM2_CH3
  {PA_3,   TIM2,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0110)}, // TIM2_CH4

  {PA_6,   TIM3,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0000)}, // TIM3_CH1
  {PA_7,   TIM3,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0010)}, // TIM3_CH2
  {PB_0,   TIM3,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0100)}, // TIM3_CH3
  {PB_1,   TIM3,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0110)}, // TIM3_CH4

  {PB_6,   TIM4,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0000)}, // TIM4_CH1
  {PB_7,   TIM4,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0010)}, // TIM4_CH2
  {PB_8,   TIM4,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0100)}, // TIM4_CH3
  {PB_9,   TIM4,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0110)}, // TIM4_CH4
  
  {PA_0,   TIM5,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0000)}, // TIM5_CH1
  {PA_1,   TIM5,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0010)}, // TIM5_CH2
  {PA_2,   TIM5,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0100)}, // TIM5_CH3
  {PA_3,   TIM5,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0110)}, // TIM5_CH4
  
  {PA_7,   TIM8,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0001)}, // TIM8_CH1N
  {PB_0,   TIM8,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0011)}, // TIM8_CH2N
  {PB_1,   TIM8,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0101)}, // TIM8_CH3N
  {PC_6,   TIM8,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0000)}, // TIM8_CH1
  {PC_7,   TIM8,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0010)}, // TIM8_CH2
  {PC_8,   TIM8,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0100)}, // TIM8_CH3
  {PC_9,   TIM8,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0110)}, // TIM8_CH4

  {PC_0,   TIM9,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0001)}, // TIM8_CH1N
  {PC_1,   TIM9,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0011)}, // TIM8_CH2N
  {PC_2,   TIM9,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0101)}, // TIM8_CH3N
  {PA_2,   TIM9,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0000)}, // TIM8_CH1
  {PA_3,   TIM9,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0010)}, // TIM8_CH2
  {PA_4,   TIM9,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0100)}, // TIM8_CH3
  {PC_4,   TIM9,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0110)}, // TIM8_CH4

  {PA_12,  TIM10,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0001)}, // TIM8_CH1N
  {PA_13,  TIM10,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0011)}, // TIM8_CH2N
  {PA_14,  TIM10,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0101)}, // TIM8_CH3N
  {PB_8,   TIM10,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0000)}, // TIM8_CH1
  {PB_9,   TIM10,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0010)}, // TIM8_CH2
  {PC_3,   TIM10,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0100)}, // TIM8_CH3
  {PC_4,   TIM10,   CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b0110)}, // TIM8_CH4

//remap 
  {PA_7,   TIM1,    CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b1001)}, // TIM1_CH1N_1
  {PE_8,   TIM1,    CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b1001)}, // TIM1_CH1N_3
  {PB_0,   TIM1,    CH_PIN_DATA_EXT(GPIO_Mode_AF_PP, GPIO_Mode_AF_PP, 1, 0b1001)}, // TIM1_CH2N_1
  {NC,    NP,    0}
};
#endif

//*** SERIAL ***

#ifdef HAL_UART_MODULE_ENABLED
const PinMap PinMap_UART_TX[] = {
  {PC_1,  LPUART1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF8_LPUART1)},
  {PA_2,  USART2,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART2)}, 
  {PA_9,  USART1,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART1)},// STLink TX
  {PC_4,  USART3,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART3)},
  {NC,    NP,    0}
};
#endif

#ifdef HAL_UART_MODULE_ENABLED
const PinMap PinMap_UART_RX[] = {
  {PC_0,  LPUART1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF8_LPUART1)},
  {PA_3,  USART2,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART2)},
  {PA_10, USART1,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART1)},// STLink RX
  {PC_5,  USART3,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART3)},
  {NC,    NP,    0}
};
#endif

#ifdef HAL_UART_MODULE_ENABLED
const PinMap PinMap_UART_RTS[] = {
  // {PA_1,  USART2,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART2)},
  // {PA_12, USART1,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART1)},
  //  {PB_1,  LPUART1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF8_LPUART1)},

  {NC,    NP,    0}
};
#endif

#ifdef HAL_UART_MODULE_ENABLED
const PinMap PinMap_UART_CTS[] = {
  // {PA_0,  USART2,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART2)},
  // {PA_6,  LPUART1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF8_LPUART1)},
  // {PA_11, USART1,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART1)},
  // {PB_4,  USART1,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART1)},
  {NC,    NP,    0}
};
#endif


#ifdef HAL_SPI_MODULE_ENABLED
const PinMap PinMap_SPI_MOSI[] = {
  {PA_7,  SPI1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF5_SPI1)},
  {PA_12, SPI1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF5_SPI1)},
  {PC_3,  SPI2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF5_SPI2)},
  {NC,    NP,    0}
};
#endif

#ifdef HAL_SPI_MODULE_ENABLED
const PinMap PinMap_SPI_MISO[] = {
  {PA_6,  SPI1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF5_SPI1)},
  {PA_11, SPI1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF5_SPI1)},
  {PB_14,  SPI2, STM_PIN_DATA(STM_MODE_AF_PP,GPIO_PULLUP, GPIO_AF5_SPI2)},
  {NC,    NP,    0}
};
#endif

#ifdef HAL_SPI_MODULE_ENABLED
const PinMap PinMap_SPI_SCLK[] = {
  {PA_1,  SPI1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF5_SPI1)},
  {PA_5,  SPI1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF5_SPI1)},
  {PB_13,  SPI2, STM_PIN_DATA(STM_MODE_AF_PP,GPIO_PULLUP, GPIO_AF5_SPI2)},
  {NC,    NP,    0}
};
#endif

#ifdef HAL_SPI_MODULE_ENABLED
const PinMap PinMap_SPI_SSEL[] = {
  {PA_4,  SPI1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF5_SPI1)},
  {PB_12,  SPI2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI2)},
  {NC,    NP,    0}
};
#endif

//*** CAN ***

#ifdef HAL_CAN_MODULE_ENABLED
const PinMap PinMap_CAN_RD[] = {
 // {PA_11, CAN1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF9_CAN1)},
  {NC,    NP,    0}
};
#endif

#ifdef HAL_CAN_MODULE_ENABLED
const PinMap PinMap_CAN_TD[] = {
 // {PA_12, CAN1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF9_CAN1)},
  {NC,    NP,    0}
};
#endif

//*** No ETHERNET ***

//*** QUADSPI ***

#ifdef HAL_QSPI_MODULE_ENABLED
const PinMap PinMap_QUADSPI[] = {
  {PA_2,  QUADSPI, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF10_QUADSPI)}, // QUADSPI_BK1_NCS
  {PB_10, QUADSPI, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF10_QUADSPI)}, // QUADSPI_CLK
  {PB_0,  QUADSPI, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF10_QUADSPI)}, // QUADSPI_BK1_IO1
  {PB_1,  QUADSPI, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF10_QUADSPI)}, // QUADSPI_BK1_IO0
  {NC,    NP,    0}
};
#endif

//*** USB ***

#ifdef HAL_PCD_MODULE_ENABLED
const PinMap PinMap_USB[] = {
  // {PA_11, USB, STM_PIN_DATA(STM_MODE_INPUT, GPIO_NOPULL, GPIO_AF10_USB_FS)}, // USB_DM
  // {PA_12, USB, STM_PIN_DATA(STM_MODE_INPUT, GPIO_NOPULL, GPIO_AF10_USB_FS)}, // USB_DP
  //  {PA_13, USB, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF10_USB_FS)}, // USB_NOE
  {NC,    NP,    0}
};
#endif

