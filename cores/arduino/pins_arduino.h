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
*/
#ifndef _PINS_ARDUINO_H_
#define _PINS_ARDUINO_H_
// Include board variant
#include <stdint.h>
#include <stdlib.h> /* Required for static_assert */
#include "PinNames.h"
#include "variant.h"

#ifdef __cplusplus
extern "C"
{
#endif
/*
 * Pin number mask
 * allows to retrieve the pin number without ALTx
 */
#define PNUM_MASK 0xFF

/* Pin not defined */
#define PNUM_NOT_DEFINED NUM_DIGITAL_PINS

// Default for Arduino connector compatibility
// SPI Definitions SPI1
#ifndef PIN_SPI_SS
#define PIN_SPI_SS 4
#endif
#ifndef PIN_SPI_MOSI
#define PIN_SPI_MOSI 7
#endif
#ifndef PIN_SPI_MISO
#define PIN_SPI_MISO 6
#endif
#ifndef PIN_SPI_SCK
#define PIN_SPI_SCK 5
#endif

  static uint32_t SS = PIN_SPI_SS;
  static uint32_t MOSI = PIN_SPI_MOSI;
  static uint32_t MISO = PIN_SPI_MISO;
  static uint32_t SCK = PIN_SPI_SCK;

// I2C Definitions I2C1
#ifndef PIN_WIRE_SDA
#define PIN_WIRE_SDA 24
#endif
#ifndef PIN_WIRE_SCL
#define PIN_WIRE_SCL 23
#endif

  static uint32_t SDA = PIN_WIRE_SDA;
  static uint32_t SCL = PIN_WIRE_SCL;

  extern PinName digitalPin[];
#define NOT_AN_INTERRUPT NC // -1

// Convert a digital pin number Dxx to a PinName PX_n
// Note: Analog pin is also a digital pin.
#define digitalPinToPinName(p) (((uint32_t)p < NUM_DIGITAL_PINS) ? digitalPin[p] : NC)

  // Convert a PinName PX_n to a digital pin number
  uint32_t pinNametoDigitalPin(PinName p);

// Convert an analog pin number to a digital pin number
// Used by analogRead api to have A0 == 0
#define analogInputToDigitalPin(p) (((uint32_t)p < NUM_ANALOG_INPUTS) ? (p + A0) : p)
  // Convert an analog pin number Axx to a PinName PX_n
  PinName analogInputToPinName(uint32_t pin);

// All pins could manage EXTI
#define digitalPinToInterrupt(p) (digitalPinIsValid(p) ? p : NOT_AN_INTERRUPT)

#define digitalPinHasI2C(p) (pin_in_pinmap(digitalPinToPinName(p), PinMap_I2C_SDA) || \
                             pin_in_pinmap(digitalPinToPinName(p), PinMap_I2C_SCL))
#define digitalPinHasPWM(p) (pin_in_pinmap(digitalPinToPinName(p), PinMap_PWM))
#define digitalPinHasSerial(p) (pin_in_pinmap(digitalPinToPinName(p), PinMap_UART_RX) || \
                                pin_in_pinmap(digitalPinToPinName(p), PinMap_UART_TX))
#define digitalPinHasSPI(p) (pin_in_pinmap(digitalPinToPinName(p), PinMap_SPI_MOSI) || \
                             pin_in_pinmap(digitalPinToPinName(p), PinMap_SPI_MISO) || \
                             pin_in_pinmap(digitalPinToPinName(p), PinMap_SPI_SCLK) || \
                             pin_in_pinmap(digitalPinToPinName(p), PinMap_SPI_SSEL))

#define digitalPinToPort(p) (get_GPIO_Port(CH_PORT(digitalPinToPinName(p))))
#define digitalPinToBitMask(p) (CH_GPIO_PIN(digitalPinToPinName(p)))

#define analogInPinToBit(p) (CH_GPIO_PIN(digitalPinToPinName(p)))
#define portOutputRegister(P) (&(P->OUTDR))
#define portInputRegister(P) (&(P->INDR))

#define portSetRegister(P) (&(P->BSHR))
#define portClearRegister(P) (&(P->BCR))

// #if defined(STM32F1xx)
// // Config registers split in 2 registers:
// // CRL: pin 0..7
// // CRH: pin 8..15
// // Return only CRL
// #define portModeRegister(P)         (&(P->CRL))
// #else
#define portModeRegister(P) (&(P->MODER))
// #endif
#define portConfigRegister(P) (portModeRegister(P))

#define digitalPinIsValid(p) (digitalPinToPinName(p) != NC)

// As some pin could be duplicated in digitalPin[]
// return first occurence of linked PinName (PYx)
#define digitalPinFirstOccurence(p) (pinNametoDigitalPin(digitalPinToPinName(p)))

// Specific for Firmata. As some pins could be duplicated,
// ensure 'p' is not one of the serial pins
#if defined(PIN_SERIAL_RX) && defined(PIN_SERIAL_TX)
#define pinIsSerial(p) ((digitalPinFirstOccurence(p) == PIN_SERIAL_RX) || \
                        (digitalPinFirstOccurence(p) == PIN_SERIAL_TX))
#endif

// Default Definitions, could be redefined in variant.h
#ifndef ADC_RESOLUTION
#define ADC_RESOLUTION 12
#endif
#ifndef DACC_RESOLUTION
#define DACC_RESOLUTION 12
#endif
#ifndef PWM_RESOLUTION
#define PWM_RESOLUTION 8
#endif
#ifndef PWM_FREQUENCY
#define PWM_FREQUENCY 1000
#endif
#ifndef PWM_MAX_DUTY_CYCLE
#define PWM_MAX_DUTY_CYCLE 255
#endif

  /* Default for Arduino connector compatibility */
  extern uint8_t A0;
  extern uint8_t A1;
  extern uint8_t A2;
  extern uint8_t A3;
  extern uint8_t A4;
  extern uint8_t A5;
  extern uint8_t A6;
  extern uint8_t A7;
  extern uint8_t A8;
  extern uint8_t A9;
  extern uint8_t A10;
  extern uint8_t A11;
  extern uint8_t A12;
  extern uint8_t A13;
  extern uint8_t A14;
  extern uint8_t A15;
  extern uint8_t A16;
  extern uint8_t A17;
  extern uint8_t A18;
  extern uint8_t A19;
  extern uint8_t A20;
  extern uint8_t A21;
  extern uint8_t A22;
  extern uint8_t A23;

  void analogPinInit(void);

#ifdef __cplusplus
}
#endif

#endif /*_PINS_ARDUINO_H_*/
