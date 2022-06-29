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

//for Pinmap 
/*
#define MODULE_ENABLED
#define ADC_MODULE_ENABLED
#define CAN_MODULE_ENABLED
#define CAN_LEGACY_MODULE_ENABLED
#define COMP_MODULE_ENABLED
#define CORTEX_MODULE_ENABLED
#define CRC_MODULE_ENABLED
#define CRYP_MODULE_ENABLED
#define DAC_MODULE_ENABLED
#define DCMI_MODULE_ENABLED
#define DFSDM_MODULE_ENABLED
#define DMA_MODULE_ENABLED
#define DMA2D_MODULE_ENABLED
#define DSI_MODULE_ENABLED
#define EXTI_MODULE_ENABLED
#define FIREWALL_MODULE_ENABLED
#define FLASH_MODULE_ENABLED
#define GFXMMU_MODULE_ENABLED
#define GPIO_MODULE_ENABLED
#define HASH_MODULE_ENABLED
#define HCD_MODULE_ENABLED
#define I2C_MODULE_ENABLED
#define IRDA_MODULE_ENABLED
#define IWDG_MODULE_ENABLED
#define LCD_MODULE_ENABLED
#define LPTIM_MODULE_ENABLED
#define LTDC_MODULE_ENABLED
#define MMC_MODULE_ENABLED
#define NAND_MODULE_ENABLED
#define NOR_MODULE_ENABLED
#define OPAMP_MODULE_ENABLED
#define OSPI_MODULE_ENABLED
#define PCD_MODULE_ENABLED
#define PWR_MODULE_ENABLED
#define QSPI_MODULE_ENABLED
#define RCC_MODULE_ENABLED
#define RNG_MODULE_ENABLED
#define RTC_MODULE_ENABLED
#define SAI_MODULE_ENABLED
#define SD_MODULE_ENABLED
#define SMARTCARD_MODULE_ENABLED
#define SMBUS_MODULE_ENABLED
#define SPI_MODULE_ENABLED
#define SRAM_MODULE_ENABLED
#define SWPMI_MODULE_ENABLED
#define TIM_MODULE_ENABLED
#define TSC_MODULE_ENABLED
#define UART_MODULE_ENABLED
#define USART_MODULE_ENABLED
#define WWDG_MODULE_ENABLED
*/
#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

  /*----------------------------------------------------------------------------
   *        Pins
   *----------------------------------------------------------------------------*/
  extern const PinName digitalPin[];

__attribute__((weak)) void SystemClock_Config(void);
#define CH32V30x_D8C
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
