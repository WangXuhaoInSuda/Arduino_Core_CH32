/*
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
// Based on mbed-os/hal/mbed_pinmap_common.c
#include "pinmap.h"
#include "pinconfig.h"
#include "ch32v30x_gpio.h"

/* Map CH_PIN to LL */
const uint32_t pin_map[16] = {
    GPIO_Pin_0,
    GPIO_Pin_1,
    GPIO_Pin_2,
    GPIO_Pin_3,
    GPIO_Pin_4,
    GPIO_Pin_5,
    GPIO_Pin_6,
    GPIO_Pin_7,
    GPIO_Pin_8,
    GPIO_Pin_9,
    GPIO_Pin_10,
    GPIO_Pin_11,
    GPIO_Pin_12,
    GPIO_Pin_13,
    GPIO_Pin_14,
    GPIO_Pin_15};

bool pin_in_pinmap(PinName pin, const PinMap *map)
{
  if (pin != (PinName)NC)
  {
    while (map->pin != NC)
    {
      if (map->pin == pin)
      {
        return true;
      }
      map++;
    }
  }
  return false;
}

/**
 * Configure pin (mode, speed, output type and pull-up/pull-down)
 */
void pin_function(PinName pin, int function)
{
  /* Get the pin informations */
  GPIO_InitTypeDef *GPIO_InitStructure;
  uint8_t mode = CH_PIN_MODE(function);
  uint8_t cnf = CH_PIN_CNF(function);
  uint8_t port = CH_PORT(pin);
  uint8_t pupd = CH_PIN_PUPD(function);
  uint32_t ch_pin = CH_MGPIO_PIN(pin);
  uint8_t ch_mode = 0;

  if (pin == (PinName)NC)
  {
    Error_Handler();
  }

  /* Enable GPIO clock */
  GPIO_TypeDef *gpio = set_GPIO_Port_Clock(port);

  /*  Set default speed to high.
   *  For most families there are dedicated registers so it is
   *  not so important, register can be set at any time.
   *  speed only applies to output.
   */

  if (mode > 0)
  {
    GPIO_InitStructure->GPIO_Speed = GPIO_Speed_50MHz;
    switch (cnf)
    {
    case GPIO_CNF_OUTPUT_PP:
      GPIO_InitStructure->GPIO_Mode = GPIO_Mode_Out_PP;
      break;
    case GPIO_CNF_OUTPUT_OD:
      GPIO_InitStructure->GPIO_Mode = GPIO_Mode_Out_OD;
      break;
    case GPIO_CNF_OUTPUT_AF_PP:
      GPIO_InitStructure->GPIO_Mode = GPIO_Mode_AF_PP;
      break;
    case GPIO_CNF_OUTPUT_AF_OD:
      GPIO_InitStructure->GPIO_Mode = GPIO_Mode_AF_OD;
      break;
    default:
      GPIO_InitStructure->GPIO_Mode = GPIO_Mode_Out_OD;
      break;
    }
  }
  else
  {
    switch (cnf)
    {
    case GPIO_CNF_INPUT_ANALOG:
      GPIO_InitStructure->GPIO_Mode = GPIO_Mode_AIN;
      break;
    case GPIO_CNF_INPUT_FLOAT:
      GPIO_InitStructure->GPIO_Mode = GPIO_Mode_IN_FLOATING;
      break;
    case GPIO_CNF_INPUT_PUPD:
    {
      if (pupd == 0b01)
        GPIO_InitStructure->GPIO_Mode = GPIO_Mode_IPD;
      else
        GPIO_InitStructure->GPIO_Mode = GPIO_Mode_IPU;
    }
    break;
    default:
      GPIO_InitStructure->GPIO_Mode = GPIO_Mode_IN_FLOATING;
      break;
    }
  }

  GPIO_SetPinMode(gpio, ch_pin, GPIO_InitStructure->GPIO_Mode, GPIO_InitStructure->GPIO_Speed);

  pin_DisconnectDebug(pin);
}

void pinmap_pinout(PinName pin, const PinMap *map)
{
  if (pin == NC)
  {
    return;
  }

  while (map->pin != NC)
  {
    if (map->pin == pin)
    {
      pin_function(pin, map->function);
      return;
    }
    map++;
  }
  Error_Handler();
}

void *pinmap_find_peripheral(PinName pin, const PinMap *map)
{
  while (map->pin != NC)
  {
    if (map->pin == pin)
    {
      return map->peripheral;
    }
    map++;
  }
  return NP;
}

void *pinmap_peripheral(PinName pin, const PinMap *map)
{
  void *peripheral = NP;

  if (pin != (PinName)NC)
  {
    peripheral = pinmap_find_peripheral(pin, map);
  }
  return peripheral;
}

PinName pinmap_find_pin(void *peripheral, const PinMap *map)
{
  while (map->peripheral != NP)
  {
    if (map->peripheral == peripheral)
    {
      return map->pin;
    }
    map++;
  }
  return NC;
}

PinName pinmap_pin(void *peripheral, const PinMap *map)
{
  PinName pin = NC;

  if (peripheral != NP)
  {
    pin = pinmap_find_pin(peripheral, map);
  }
  return pin;
}

uint32_t pinmap_find_function(PinName pin, const PinMap *map)
{
  while (map->pin != NC)
  {
    if (map->pin == pin)
    {
      return map->function;
    }
    map++;
  }
  return (uint32_t)NC;
}

uint32_t pinmap_function(PinName pin, const PinMap *map)
{
  uint32_t function = (uint32_t)NC;

  if (pin != (PinName)NC)
  {
    function = pinmap_find_function(pin, map);
  }
  return function;
}

// Merge peripherals
void *pinmap_merge_peripheral(void *a, void *b)
{
  // both are the same (inc both NP)
  if (a == b)
  {
    return a;
  }

  // one (or both) is not set
  if (a == NP)
  {
    return b;
  }
  if (b == NP)
  {
    return a;
  }

  // mis-match error case
  return NP;
}
