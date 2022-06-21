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
//Based on mbed-os/hal/mbed_pinmap_common.c
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
  GPIO_Pin_15
};

bool pin_in_pinmap(PinName pin, const PinMap *map)
{
  if (pin != (PinName)NC) {
    while (map->pin != NC) {
      if (map->pin == pin) {
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
  uint32_t mode  = CH_PIN_MODE(function);
  uint32_t afnum = CH_PIN_AFNUM(function);
  uint32_t port = CH_PORT(pin);
  uint32_t pin  = CH_GPIO_PIN(pin);
  uint32_t mode = 0;

  if (pin == (PinName)NC) {
    Error_Handler();
  }

  /* Enable GPIO clock */
  GPIO_TypeDef *gpio = set_GPIO_Port_Clock(port);

  /*  Set default speed to high.
   *  For most families there are dedicated registers so it is
   *  not so important, register can be set at any time.
   *  But for families like F1, speed only applies to output.
   */
#if defined (STM32F1xx)
  if (mode == CH_PIN_OUTPUT) {
#endif
#ifdef GPIO_SPEED_FREQ_VERY_HIGH
    GPIO_SetPinSpeed(gpio, pin, GPIO_SPEED_FREQ_VERY_HIGH);
#else
    GPIO_SetPinSpeed(gpio, pin, GPIO_SPEED_FREQ_VERY_HIGH);
#endif
#if defined (STM32F1xx)
  }
#endif

  switch (mode) {
    case CH_PIN_INPUT:
      mode = GPIO_MODE_INPUT;
      break;
    case CH_PIN_OUTPUT:
      mode = GPIO_MODE_OUTPUT;
      break;
    case CH_PIN_ALTERNATE:
      mode = GPIO_MODE_ALTERNATE;
      /* In case of ALT function, also set the afnum */
      pin_SetAFPin(gpio, pin, afnum);
      break;
    case CH_PIN_ANALOG:
      mode = GPIO_MODE_ANALOG;
      break;
    default:
      Error_Handler();
      break;
  }
  GPIO_SetPinMode(gpio, pin, mode);

#if defined(GPIO_ASCR_ASC0)
  /* For families where Analog Control ASC0 register is present */
  if (CH_PIN_ANALOG_CONTROL(function)) {
    GPIO_EnablePinAnalogControl(gpio, pin);
  } else {
    GPIO_DisablePinAnalogControl(gpio, pin);
  }
#endif

  if ((mode == CH_PIN_OUTPUT) || (mode == CH_PIN_ALTERNATE)) {
    if (CH_PIN_OD(function)) {
      GPIO_SetPinOutputType(gpio, pin, GPIO_OUTPUT_OPENDRAIN);
    } else {
      GPIO_SetPinOutputType(gpio, pin, GPIO_OUTPUT_PUSHPULL);
    }
  }

  pin_PullConfig(gpio, pin, CH_PIN_PUPD(function));

  pin_DisconnectDebug(pin);
}

void pinmap_pinout(PinName pin, const PinMap *map)
{
  if (pin == NC) {
    return;
  }

  while (map->pin != NC) {
    if (map->pin == pin) {
      pin_function(pin, map->function);
      return;
    }
    map++;
  }
  Error_Handler();
}

void *pinmap_find_peripheral(PinName pin, const PinMap *map)
{
  while (map->pin != NC) {
    if (map->pin == pin) {
      return map->peripheral;
    }
    map++;
  }
  return NP;
}

void *pinmap_peripheral(PinName pin, const PinMap *map)
{
  void *peripheral = NP;

  if (pin != (PinName)NC) {
    peripheral = pinmap_find_peripheral(pin, map);
  }
  return peripheral;
}

PinName pinmap_find_pin(void *peripheral, const PinMap *map)
{
  while (map->peripheral != NP) {
    if (map->peripheral == peripheral) {
      return map->pin;
    }
    map++;
  }
  return NC;
}

PinName pinmap_pin(void *peripheral, const PinMap *map)
{
  PinName pin = NC;

  if (peripheral != NP) {
    pin = pinmap_find_pin(peripheral, map);
  }
  return pin;
}

uint32_t pinmap_find_function(PinName pin, const PinMap *map)
{
  while (map->pin != NC) {
    if (map->pin == pin) {
      return map->function;
    }
    map++;
  }
  return (uint32_t)NC;
}

uint32_t pinmap_function(PinName pin, const PinMap *map)
{
  uint32_t function = (uint32_t)NC;

  if (pin != (PinName)NC) {
    function = pinmap_find_function(pin, map);
  }
  return function;
}

// Merge peripherals
void *pinmap_merge_peripheral(void *a, void *b)
{
  // both are the same (inc both NP)
  if (a == b) {
    return a;
  }

  // one (or both) is not set
  if (a == NP) {
    return b;
  }
  if (b == NP) {
    return a;
  }

  // mis-match error case
  return NP;
}
