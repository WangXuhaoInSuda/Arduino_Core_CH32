/*
 *******************************************************************************
 * Copyright (c) 2017, STMicroelectronics
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
 */
#include "PortNames.h"
#include "ch32v30x_rcc.h"
#include "printf.h"
#ifdef __cplusplus
extern "C" {

#endif
GPIO_TypeDef *GPIOPort[MAX_NB_PORT] = {
  (GPIO_TypeDef *)GPIOA_BASE,
  (GPIO_TypeDef *)GPIOB_BASE
#if defined GPIOC_BASE
  , (GPIO_TypeDef *)GPIOC_BASE
#endif
#if defined GPIOD_BASE
  , (GPIO_TypeDef *)GPIOD_BASE
#endif
#if defined GPIOE_BASE
  , (GPIO_TypeDef *)GPIOE_BASE
#endif
#if defined GPIOF_BASE
  , (GPIO_TypeDef *)GPIOF_BASE
#endif
#if defined GPIOG_BASE
  , (GPIO_TypeDef *)GPIOG_BASE
#endif
#if defined GPIOH_BASE
  , (GPIO_TypeDef *)GPIOH_BASE
#endif
#if defined GPIOI_BASE
  , (GPIO_TypeDef *)GPIOI_BASE
#endif
#if defined GPIOJ_BASE
  , (GPIO_TypeDef *)GPIOJ_BASE
#endif
#if defined GPIOK_BASE
  , (GPIO_TypeDef *)GPIOK_BASE
#endif
};

/* Enable GPIO clock and return GPIO base address */
GPIO_TypeDef *set_GPIO_Port_Clock(uint32_t port_idx)
{
  GPIO_TypeDef *gpioPort = 0;
  switch (port_idx) {
    case PortA:
      gpioPort = (GPIO_TypeDef *)GPIOA_BASE;
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
      break;
    case PortB:
      gpioPort = (GPIO_TypeDef *)GPIOB_BASE;
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
      break;
#if defined GPIOC_BASE
    case PortC:
      gpioPort = (GPIO_TypeDef *)GPIOC_BASE;
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
      break;
#endif
#if defined GPIOD_BASE
    case PortD:
      gpioPort = (GPIO_TypeDef *)GPIOD_BASE;
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
      break;
#endif
#if defined GPIOE_BASE
    case PortE:
      gpioPort = (GPIO_TypeDef *)GPIOE_BASE;
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
      break;
#endif
#if defined GPIOF_BASE
    case PortF:
      gpioPort = (GPIO_TypeDef *)GPIOF_BASE;
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);
      break;
#endif
    default:
      // wrong port number
      //TBD: error management
      gpioPort = 0;
      break;
  }
  return gpioPort;
}
#ifdef __cplusplus
}

#endif