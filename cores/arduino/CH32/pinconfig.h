/*
 *******************************************************************************
 * Copyright (c) 2018, STMicroelectronics
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
 * Based on mbed-os/target/TARGET_STM/TARGET_STMYY/pin_device.h
 */
#ifndef _PINCONFIG_H
#define _PINCONFIG_H

#include "PinAF_CH32V3xx.h"
#include "ch32v30x_gpio.h"

#ifdef __cplusplus
extern "C" {

#endif
static inline void pin_DisconnectDebug(PinName pin)
{
#ifdef CH32V3xx
  pinV3_DisconnectDebug(pin);
#else
  UNUSED(pin);
#endif /* CH32V3xx */
}
/*
@param  pull_config This parameter can be one of the following values:
  *         @arg @ref GPIO_PULL_NO
  *         @arg @ref GPIO_PULL_UP
  *         @arg @ref GPIO_PULL_DOWN
*/
static inline void pin_PullConfig(GPIO_TypeDef *gpio, uint32_t pin, uint32_t pull_config)
{
  switch (pull_config) {
    case GPIO_PULLUP:
      GPIO_SetPinMode(gpio, pin, GPIO_Mode_IPU,GPIO_Speed_Current);
      break;
    case GPIO_PULLDOWN:
      GPIO_SetPinMode(gpio, pin, GPIO_Mode_IPD,GPIO_Speed_Current);
      break;
    default:
      /*  Input+NoPull = Floating for V3 family */
      GPIO_SetPinMode(gpio, pin, GPIO_Mode_IN_FLOATING,GPIO_Speed_Current);
      break;
  }
}

static inline void pin_SetAFPin(GPIO_TypeDef *gpio, PinName pin, uint32_t afnum)
{
  UNUSED(gpio);
  UNUSED(pin);
  pin_SetV3AFPin(afnum);
}
#ifdef __cplusplus
}

#endif
#endif
