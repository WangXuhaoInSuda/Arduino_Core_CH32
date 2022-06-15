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
  ****************************************************
  ****************************************************
  modified by WangXuhao
  20220521
  completed work:
  rewrite digitalPin[]
  To be done:
  Confirm sysclock
*/

#include "variant.h"

#ifdef __cplusplus
extern "C"
{
#endif

  // wxh: digital Pin number need to be edited according to core Pin manual
 const PinName digitalPin[] = {
      PA_0,  // PA0/WKUP/ADC0
      PA_1,  // PA1/ADC1
      PA_2,  // PA2/ADC2
      PA_3,  // PA3/ADC3
      PA_4,  // PA4/ADC4/DAC0
      PA_5,  // PA5/ADC5/DAC1
      PA_6,  // PA6/ADC6
      PA_7,  // PA7/ADC7
      PA_8,  // PA8/MCO
      PA_9,  // PA9
      PA_10, // PA10
      PA_11, // PA11/USB1DM
      PA_12, // PA12/USB1DP
      PA_13, // PA13/SWDIO
      PA_14, // PA14/SWCLK
      PA_15, // PA15

      PB_0,  // PB0/ADC8
      PB_1,  // PB1/ADC9
      PB_2,  // PB2
      PB_3,  // PB3
      PB_4,  // PB4
      PB_5,  // PB5
      PB_6,  // PB6/USB2DM
      PB_7,  // PB7/USB2DP
      PB_8,  // PB8
      PB_9,  // PB9
      PB_10, // PB10
      PB_11, // PB11
      PB_12, // PB12
      PB_13, // PB13
      PB_14, // PB14
      PB_15, // PB15

      PC_0,  // PC0/ADC10
      PC_1,  // PC1/ADC11
      PC_2,  // PC2/ADC12
      PC_2,  // PC2/ADC12
      PC_3,  // PC3/ADC13
      PC_4,  // PC4/ADC14
      PC_5,  // PC5/ADC15
      PC_6,  // PC6/ERXP
      PC_7,  // PC7/ERXN
      PC_8,  // PC8/ETXP
      PC_9,  // PC9/ETXN
      PC_10, // PC10
      PC_11, // PC11
      PC_12, // PC12
      PC_13, // PC13/TAMPER-RTC
      PC_14, // PC14/OSC32IN
      PC_15, // PC15/OSC32OUT

      PD_0,  // PD0
      PD_1,  // PD1
      PD_2,  // PD2
      PD_3,  // PD3
      PD_4,  // PD4
      PD_5,  // PD5
      PD_6,  // PD6
      PD_7,  // PD7
      PD_8,  // PD8
      PD_9,  // PD9
      PD_10, // PD10
      PD_11, // PD11
      PD_12, // PD12
      PD_13, // PD13
      PD_14, // PD14
      PD_15, // PD15

      PE_0,     // PE0
      PE_1,      // PE1
      PE_2,     // PE2
      PE_3,     // PE3
      PE_4,     // PE4
      PE_5,     // PE5
      PE_6,     // PE6
      PE_7,     // PE7
      PE_8,     // PE8
      PE_9,     // PE9
      PE_10,    // PE10
      PE_11,    // PE11
      PE_12,    // PE12
      PE_13,    // PE13
      PE_14,    // PE14
      PE_15    // PE15

  };

#ifdef __cplusplus
}
#endif

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif

//below modified on 20220614, no need to edit
//----------------------------
WEAK void SystemClock_Config(void)
{
  SystemInit();
}
//----------------------------
#ifdef __cplusplus
}
#endif
