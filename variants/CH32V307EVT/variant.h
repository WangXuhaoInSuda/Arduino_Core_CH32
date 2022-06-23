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

    ----------------------------
  modified by WangXuhao
  20220221
  completed work:
  rewrite enum, On-board pads,USB,usart
  works need to do :
  add pins according to to board manual
*/

#ifndef _VARIANT_ARDUINO_CH32_
#define _VARIANT_ARDUINO_CH32_

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "pins_arduino.h"
#include "ch32v30x_conf.h"
#include "PinNames.h"
#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

  /*----------------------------------------------------------------------------
   *        Pins
   *----------------------------------------------------------------------------*/
  extern const PinName digitalPin[];


#define NUM_DIGITAL_PINS 80
#define NUM_ANALOG_INPUTS 2
#define NUM_ANALOG_FIRST 10 //temp val
// On-board pads
#define PAD_MCO PA8
#define PAD_PA1 PA1
#define PAD_PC13 PC13

// USB
#define USB1DP PA12
#define USB1DM PA11
#define USB2DP PB7
#define USB2DM PB6

// usart
#define ETXN PC9
#define ERXN PC7
#define ETXP PC8
#define ERXP PC6

#ifdef __cplusplus
} // extern "C"
#endif
/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus
// These serial port names are intended to allow libraries and architecture-neutral
// sketches to automatically default to the correct port name for a particular type
// of use.  For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
// the first hardware serial port whose RX/TX pins are not dedicated to another use.
//
// SERIAL_PORT_MONITOR        Port which normally prints to the Arduino Serial Monitor
//
// SERIAL_PORT_USBVIRTUAL     Port which is USB virtual serial
//
// SERIAL_PORT_LINUXBRIDGE    Port which connects to a Linux system via Bridge library
//
// SERIAL_PORT_HARDWARE       Hardware serial port, physical RX & TX pins.
//
// SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
//                            pins are NOT connected to anything by default.
#define SERIAL_PORT_MONITOR Serial
#define SERIAL_PORT_HARDWARE Serial
#endif

#endif /* _VARIANT_ARDUINO_CH32_ */
