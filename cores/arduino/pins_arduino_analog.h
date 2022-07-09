/*
 *******************************************************************************
 * Copyright (c) 2020, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef _PINS_ARDUINO_ANALOG_H_
#define _PINS_ARDUINO_ANALOG_H_
#include "variant.h"
#include "PinNames.h"

/*
 * Pin number Analog base
 * To check if a pin number is an analog pin:
 * ((p & PNUM_ANALOG_BASE) == PNUM_ANALOG_BASE)
 * if true then p is an analog pin number
 * else not
 */
#define PNUM_ANALOG_BASE    0xC0
/*
 * Pin number Analog index
 * allows to retrieve the pin number index of an analog pin
 * in the analogInputPin[] array:
 * analogInputPin[p & PNUM_ANALOG_INDEX]
 */
#define PNUM_ANALOG_INDEX   0x3F

/* Arduino analog pins */


/* Analog internal pin numbers follow the analog pin number */
#define NUM_ANALOG_INTERNAL_FIRST (PNUM_ANALOG_BASE + NUM_ANALOG_INPUTS)

/* ADC internal channels (not a pins) */
/* Only used for analogRead() */
#if defined(ADC_CHANNEL_TEMPSENSOR) || defined(ADC_CHANNEL_TEMPSENSOR_ADC1)
  #define ATEMP        (NUM_ANALOG_INTERNAL_FIRST)
#endif
#ifdef ADC_CHANNEL_VREFINT
  #define AVREF        (NUM_ANALOG_INTERNAL_FIRST + 1)
#endif
#ifdef ADC_CHANNEL_VBAT
  #define AVBAT        (NUM_ANALOG_INTERNAL_FIRST + 2)
#endif
#if defined(ADC5) && defined(ADC_CHANNEL_TEMPSENSOR_ADC5)
  #define ATEMP_ADC5   (NUM_ANALOG_INTERNAL_FIRST + 3)
#endif


#endif /*_PINS_ARDUINO_ANALOG_H_*/
