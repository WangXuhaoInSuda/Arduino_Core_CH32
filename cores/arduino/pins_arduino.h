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
#include "variant.h"
#include "PinNames.h"
#include "PortNames.h"
#include "pins_arduino_analog.h"
#include "pins_arduino_digital.h"


/*
 * Pin number mask
 * allows to retrieve the pin number without ALTx
 */
#define PNUM_MASK                   0xFF

/* Pin not defined */
#define PNUM_NOT_DEFINED            NUM_DIGITAL_PINS


/* Default for Arduino connector compatibility */

#if NUM_ANALOG_INPUTS > 0
#define PIN_A0       NUM_ANALOG_FIRST
static const uint8_t A0 = PIN_A0;
#endif
#if NUM_ANALOG_INPUTS > 1
#define PIN_A1       (PIN_A0 + 1)
static const uint8_t A1 = PIN_A1;
#endif
#if NUM_ANALOG_INPUTS > 2
#define PIN_A2       (PIN_A1 + 1)
static const uint8_t A2 = PIN_A2;
#endif
#if NUM_ANALOG_INPUTS > 3
#define PIN_A3       (PIN_A2 + 1)
static const uint8_t A3 = PIN_A3;
#endif
#if NUM_ANALOG_INPUTS > 4
#define PIN_A4       (PIN_A3 + 1)
static const uint8_t A4 = PIN_A4;
#endif
#if NUM_ANALOG_INPUTS > 5
#define PIN_A5       (PIN_A4 + 1)
static const uint8_t A5 = PIN_A5;
#endif
#if NUM_ANALOG_INPUTS > 6
#define PIN_A6       (PIN_A5 + 1)
static const uint8_t A6 = PIN_A6;
#endif
#if NUM_ANALOG_INPUTS > 7
#define PIN_A7       (PIN_A6 + 1)
static const uint8_t A7 = PIN_A7;
#endif
#if NUM_ANALOG_INPUTS > 8
#define PIN_A8       (PIN_A7 + 1)
static const uint8_t A8 = PIN_A8;
#endif
#if NUM_ANALOG_INPUTS > 9
#define PIN_A9       (PIN_A8 + 1)
static const uint8_t A9 = PIN_A9;
#endif
#if NUM_ANALOG_INPUTS > 10
#define PIN_A10      (PIN_A9 + 1)
static const uint8_t A10 = PIN_A10;
#endif
#if NUM_ANALOG_INPUTS > 11
#define PIN_A11      (PIN_A10 + 1)
static const uint8_t A11 = PIN_A11;
#endif
#if NUM_ANALOG_INPUTS > 12
#define PIN_A12      (PIN_A11 + 1)
static const uint8_t A12 = PIN_A12;
#endif
#if NUM_ANALOG_INPUTS > 13
#define PIN_A13      (PIN_A12 + 1)
static const uint8_t A13 = PIN_A13;
#endif
#if NUM_ANALOG_INPUTS > 14
#define PIN_A14      (PIN_A13 + 1)
static const uint8_t A14 = PIN_A14;
#endif
#if NUM_ANALOG_INPUTS > 15
#define PIN_A15      (PIN_A14 + 1)
static const uint8_t A15 = PIN_A15;
#endif
#if NUM_ANALOG_INPUTS > 16
#define PIN_A16      (PIN_A15 + 1)
static const uint8_t A16 = PIN_A16;
#endif
#if NUM_ANALOG_INPUTS > 17
#define PIN_A17      (PIN_A16 + 1)
static const uint8_t A17 = PIN_A17;
#endif
#if NUM_ANALOG_INPUTS > 18
#define PIN_A18      (PIN_A17 + 1)
static const uint8_t A18 = PIN_A18;
#endif
#if NUM_ANALOG_INPUTS > 19
#define PIN_A19      (PIN_A18 + 1)
static const uint8_t A19 = PIN_A19;
#endif
#if NUM_ANALOG_INPUTS > 20
#define PIN_A20      (PIN_A19 + 1)
static const uint8_t A20 = PIN_A20;
#endif
#if NUM_ANALOG_INPUTS > 21
#define PIN_A21      (PIN_A20 + 1)
static const uint8_t A21 = PIN_A21;
#endif
#if NUM_ANALOG_INPUTS > 22
#define PIN_A22      (PIN_A21 + 1)
static const uint8_t A22 = PIN_A22;
#endif
#if NUM_ANALOG_INPUTS > 23
#define PIN_A23      (PIN_A22 + 1)
static const uint8_t A23 = PIN_A23;
#endif

// Default for Arduino connector compatibility
// SPI Definitions SPI1
#ifndef PIN_SPI_SS
#define PIN_SPI_SS                  4
#endif
#ifndef PIN_SPI_MOSI
#define PIN_SPI_MOSI                7
#endif
#ifndef PIN_SPI_MISO
#define PIN_SPI_MISO                6
#endif
#ifndef PIN_SPI_SCK
#define PIN_SPI_SCK                 5
#endif

static const uint32_t SS   = PIN_SPI_SS;
static const uint32_t MOSI = PIN_SPI_MOSI;
static const uint32_t MISO = PIN_SPI_MISO;
static const uint32_t SCK  = PIN_SPI_SCK;

// I2C Definitions I2C1
#ifndef PIN_WIRE_SDA
#define PIN_WIRE_SDA                24
#endif
#ifndef PIN_WIRE_SCL
#define PIN_WIRE_SCL                23
#endif

static const uint32_t SDA = PIN_WIRE_SDA;
static const uint32_t SCL = PIN_WIRE_SCL;

#ifdef __cplusplus
extern "C" {
#endif

#define NOT_AN_INTERRUPT            NC // -1

// Convert a digital pin number Dxx to a PinName PX_n
// Note: Analog pin is also a digital pin.
#define digitalPinToPinName(p)      (((uint32_t)p < NUM_DIGITAL_PINS) ? digitalPin[p] : NC)
// Convert a PinName PX_n to a digital pin number
uint32_t pinNametoDigitalPin(PinName p);

// Convert an analog pin number to a digital pin number
// Used by analogRead api to have A0 == 0
#define analogInputToDigitalPin(p)  (((uint32_t)p < NUM_ANALOG_INPUTS) ? (p+A0) : p)
// Convert an analog pin number Axx to a PinName PX_n
#define analogInputToPinName(p)     (digitalPinToPinName(analogInputToDigitalPin(p)))
// All pins could manage EXTI
#define digitalPinToInterrupt(p)    (digitalPinIsValid(p) ? p : NOT_AN_INTERRUPT)

#define digitalPinHasI2C(p)         (pin_in_pinmap(digitalPinToPinName(p), PinMap_I2C_SDA) ||\
                                     pin_in_pinmap(digitalPinToPinName(p), PinMap_I2C_SCL))
#define digitalPinHasPWM(p)         (pin_in_pinmap(digitalPinToPinName(p), PinMap_PWM))
#define digitalPinHasSerial(p)      (pin_in_pinmap(digitalPinToPinName(p), PinMap_UART_RX) ||\
                                     pin_in_pinmap(digitalPinToPinName(p), PinMap_UART_TX))
#define digitalPinHasSPI(p)         (pin_in_pinmap(digitalPinToPinName(p), PinMap_SPI_MOSI) ||\
                                     pin_in_pinmap(digitalPinToPinName(p), PinMap_SPI_MISO) ||\
                                     pin_in_pinmap(digitalPinToPinName(p), PinMap_SPI_SCLK) ||\
                                     pin_in_pinmap(digitalPinToPinName(p), PinMap_SPI_SSEL))


#define digitalPinToPort(p)         (get_GPIO_Port(CH_PORT(digitalPinToPinName(p))))
#define digitalPinToBitMask(p)      (CH_GPIO_PIN(digitalPinToPinName(p)))

#define analogInPinToBit(p)         (CH_PIN(digitalPinToPinName(p)))
#define portOutputRegister(P)       (&(P->ODR))
#define portInputRegister(P)        (&(P->IDR))

#define portSetRegister(P)          (&(P->BSRR))
#if defined(CH32F2xx) || defined(CH32F4xx) || defined(CH32F7xx)
// For those series reset are in the high part so << 16U needed
#define portClearRegister(P)        (&(P->BSRR))
#else
#define portClearRegister(P)        (&(P->BRR))
#endif


#if defined(CH32F1xx)
// Config registers split in 2 registers:
// CRL: pin 0..7
// CRH: pin 8..15
// Return only CRL
#define portModeRegister(P)         (&(P->CRL))
#else
#define portModeRegister(P)         (&(P->MODER))
#endif
#define portConfigRegister(P)       (portModeRegister(P))


#define digitalPinIsValid(p)        (digitalPinToPinName(p) != NC)

// As some pin could be duplicated in digitalPin[]
// return first occurence of linked PinName (PYx)
#define digitalPinFirstOccurence(p) (pinNametoDigitalPin(digitalPinToPinName(p)))

// Specific for Firmata. As some pins could be duplicated,
// ensure 'p' is not one of the serial pins
#if defined(PIN_SERIAL_RX) && defined(PIN_SERIAL_TX)
#define pinIsSerial(p)              ((digitalPinFirstOccurence(p) == PIN_SERIAL_RX) ||\
                                     (digitalPinFirstOccurence(p) == PIN_SERIAL_TX))
#endif

#ifdef __cplusplus
}
#endif

// Default Definitions, could be redefined in variant.h
#ifndef ADC_RESOLUTION
#define ADC_RESOLUTION              12
#endif
#ifndef DACC_RESOLUTION
#define DACC_RESOLUTION             12
#endif
#ifndef PWM_RESOLUTION
#define PWM_RESOLUTION              8
#endif
#ifndef PWM_FREQUENCY
#define PWM_FREQUENCY               1000
#endif
#ifndef PWM_MAX_DUTY_CYCLE
#define PWM_MAX_DUTY_CYCLE          255
#endif

#endif /*_PINS_ARDUINO_H_*/
