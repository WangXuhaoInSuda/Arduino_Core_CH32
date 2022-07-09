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
*/

#include "pins_arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

  uint8_t A0;
  uint8_t A1;
  uint8_t A2;
  uint8_t A3;
  uint8_t A4;
  uint8_t A5;
  uint8_t A6;
  uint8_t A7;
  uint8_t A8;
  uint8_t A9;
  uint8_t A10;
  uint8_t A11;
  uint8_t A12;
  uint8_t A13;
  uint8_t A14;
  uint8_t A15;
  uint8_t A16;
  uint8_t A17;
  uint8_t A18;
  uint8_t A19;
  uint8_t A20;
  uint8_t A21;
  uint8_t A22;
  uint8_t A23;

  void analogPinInit(void)
  {
#if NUM_ANALOG_INPUTS > 0
    A0 = pinNametoDigitalPin(PA_0);
#endif
#if NUM_ANALOG_INPUTS > 1
    A1 = A0 + 1;
#endif
#if NUM_ANALOG_INPUTS > 2
    A2 = A1 + 1;
#endif
#if NUM_ANALOG_INPUTS > 3
    A3 = A2 + 1;
#endif
#if NUM_ANALOG_INPUTS > 4
    A4 = A3 + 1;
#endif
#if NUM_ANALOG_INPUTS > 5
    A5 = A4 + 1;
#endif
#if NUM_ANALOG_INPUTS > 6
    A6 = A5 + 1;
#endif
#if NUM_ANALOG_INPUTS > 7
    A7 = A6 + 1;
#endif
#if NUM_ANALOG_INPUTS > 8
    A8 = A7 + 1;
#endif
#if NUM_ANALOG_INPUTS > 9
    A9 = A8 + 1;
#endif
#if NUM_ANALOG_INPUTS > 10
    A10 = A9 + 1;
#endif
#if NUM_ANALOG_INPUTS > 11
    A11 = A10 + 1;
#endif
#if NUM_ANALOG_INPUTS > 12
    A12 = A11 + 1;
#endif
#if NUM_ANALOG_INPUTS > 13
    A13 = A12 + 1;
#endif
#if NUM_ANALOG_INPUTS > 14
    A14 = A13 + 1;
#endif
#if NUM_ANALOG_INPUTS > 15
    A15 = A14 + 1;
#endif
#if NUM_ANALOG_INPUTS > 16
    A16 = A15 + 1;
#endif
#if NUM_ANALOG_INPUTS > 17
    A17 = A16 + 1;
#endif
#if NUM_ANALOG_INPUTS > 18
    A18 = A17 + 1;
#endif
#if NUM_ANALOG_INPUTS > 19
    A19 = A18 + 1;
#endif
#if NUM_ANALOG_INPUTS > 20
    A20 = A19 + 1;
#endif
#if NUM_ANALOG_INPUTS > 21
    A21 = A20 + 1;
#endif
#if NUM_ANALOG_INPUTS > 22
    A22 = A21 + 1;
#endif
#if NUM_ANALOG_INPUTS > 23
    A23 = A22 + 1;
#endif
  }


WEAK uint32_t pinNametoDigitalPin(PinName p)
{
  uint32_t i = NUM_DIGITAL_PINS;
  if (CH_VALID_PINNAME(p)) {
    for (i = 0; i < NUM_DIGITAL_PINS; i++) {
      if (digitalPin[i] == p) {
        break;
      }
    }
  }
  return i;
}

PinName analogInputToPinName(uint32_t p)
{
  PinName pn = digitalPinToPinName(analogInputToDigitalPin(p));
  if (pn == NC) {
    switch (p) {
#ifdef ATEMP
      case ATEMP:
        pn = PADC_TEMP;
        break;
#endif
#ifdef AVREF
      case AVREF:
        pn = PADC_VREF;
        break;
#endif
#ifdef AVBAT
      case AVBAT:
        pn = PADC_VBAT;
        break;
#endif
      default:
        break;
    }
  }
  return pn;
}

#ifdef __cplusplus
}
#endif
