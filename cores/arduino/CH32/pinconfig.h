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

static inline void pin_DisconnectDebug(PinName pin)
{
#ifdef CH32V3xx
  pinV3_DisconnectDebug(pin);
#else
  UNUSED(pin);
#endif /* CH32V3xx */
}

static inline void pin_PullConfig(GPIO_TypeDef *gpio, uint32_t pin, uint32_t pull_config)
{
#ifdef CH32V3xx
  uint32_t function = GPIO_GetPinMode(gpio, pin);
#endif

  switch (pull_config) {
    case GPIO_PULLUP:
#ifdef CH32V3xx
      if (function == LL_GPIO_MODE_FLOATING) {
        LL_GPIO_SetPinMode(gpio, ll_pin, LL_GPIO_MODE_INPUT);
      }
#endif
      LL_GPIO_SetPinPull(gpio, ll_pin, LL_GPIO_PULL_UP);
      break;
    case GPIO_PULLDOWN:
#ifdef CH32V3xx
      if (function == LL_GPIO_MODE_FLOATING) {
        LL_GPIO_SetPinMode(gpio, ll_pin, LL_GPIO_MODE_INPUT);
      }
#endif
      LL_GPIO_SetPinPull(gpio, ll_pin, LL_GPIO_PULL_DOWN);
      break;
    default:
#ifdef CH32V3xx
      /*  Input+NoPull = Floating for F1 family */
      if (function == LL_GPIO_MODE_INPUT) {
        LL_GPIO_SetPinMode(gpio, ll_pin, LL_GPIO_MODE_FLOATING);
      }
#else
      LL_GPIO_SetPinPull(gpio, ll_pin, LL_GPIO_PULL_NO);
#endif
      break;
  }
}

static inline void pin_SetAFPin(GPIO_TypeDef *gpio, PinName pin, uint32_t afnum)
{
#ifdef CH32V3xx
  UNUSED(gpio);
  UNUSED(pin);
  pin_SetV3AFPin(afnum);
#else
  uint32_t ll_pin  = CH_GPIO_PIN(pin);

  if (CH_PIN(pin) > 7) {
    GPIO_SetAFPin_8_15(gpio, pin, afnum);
  } else {
    GPIO_SetAFPin_0_7(gpio, pin, afnum);
  }
#endif
}

#endif
