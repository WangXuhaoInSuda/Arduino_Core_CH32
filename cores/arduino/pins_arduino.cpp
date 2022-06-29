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