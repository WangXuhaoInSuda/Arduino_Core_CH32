/*  *******************************************************************************
 * Copyright (c) 2016, STMicroelectronics
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *******************************************************************************

modified by wxh
20220523
to be done :

*/
#ifndef _PINNAMESTYPES_H
#define _PINNAMESTYPES_H

#ifdef __cplusplus
extern "C"
{
#endif

    /*  CH32 PIN data as used is coded on 16 bits as below
     *   [1:0]  GPIO Mode & Speed 00 input, 01 output 10MHz, 10 output 2MHz, 11 output 50MHz
     *   [3:2]  GPIO CNF at input mode£¨MODE=00b£©£º
                00£ºanalog input£»
                01£ºfloat input£»
                10£ºPUPD input¡£
                11£ºreserved¡£ 
                at output mode£¨MODE>00b£©£º
                00£ºPP£»
                01£ºOD£»
                10£ºAF_PP£»
                11£ºAF_OD¡£
     *   [4]  for AF config 0:AF OFF 1:AF ON
     *   [6:5]  for PUPD config 01:pull down 10:pull up
     *   [10:7]  Channel (Analog/Timer/USART specific)
     *   [15:9]  Reserved
     */

#define CH_PIN_MODE_MASK 0x03
#define CH_PIN_MODE_SHIFT 0
#define CH_PIN_MODE_BITS (CH_PIN_MODE_MASK << CH_PIN_MODE_SHIFT)

#define CH_PIN_CNF_MASK 0x03
#define CH_PIN_CNF_SHIFT 2
#define CH_PIN_CNF_BITS (CH_PIN_CNF_MASK << CH_PIN_CNF_SHIFT)

#define CH_PIN_AFCONFIG_MASK 0x01
#define CH_PIN_AFCONFIG_SHIFT 4
#define CH_PIN_AFCONFIG_BITS (CH_PIN_AFCONFIG_MASK << CH_PIN_AFCONFIG_SHIFT)

#define CH_PIN_PUPD_MASK 0x03
#define CH_PIN_PUPD_SHIFT 5
#define CH_PIN_PUPD_BITS (CH_PIN_PUPD_MASK << CH_PIN_PUPD_SHIFT)

#define CH_PIN_CHANNELCONFIG_MASK 0x0F
#define CH_PIN_CHANNELCONFIG_SHIFT 7
#define CH_PIN_CHANNELCONFIG_BITS (CH_PIN_CHANNELCONFIG_MASK << CH_PIN_CHANNELCONFIG_SHIFT)

#define CH_PIN_OD_MASK 0x01
#define CH_PIN_OD_SHIFT 2
#define CH_PIN_OD_BITS (CH_PIN_OD_MASK << CH_PIN_OD_SHIFT)

#define CH_PIN_FLOAT_MASK 0x01
#define CH_PIN_FLOAT_SHIFT 2
#define CH_PIN_FLOAT_BITS (CH_PIN_FLOAT_MASK << CH_PIN_FLOAT_SHIFT)

#define CH_PIN_MODE(X) (((X) >> CH_PIN_MODE_SHIFT) & CH_PIN_MODE_MASK)
#define CH_PIN_CNF(X) (((X) >> CH_PIN_CNF_SHIFT) & CH_PIN_CNF_MASK)
#define CH_PIN_AFCONFIG(X) (((X) >> CH_PIN_AFCONFIG_SHIFT) & CH_PIN_AFCONFIG_MASK)
#define CH_PIN_PUPD(X) (((X) >> CH_PIN_PUPD_SHIFT) & CH_PIN_PUPD_MASK)
#define CH_PIN_CHANNELCONFIG(X) (((X) >> CH_PIN_CHANNELCONFIG_SHIFT) & CH_PIN_CHANNELCONFIG_MASK)

#define CH_PIN_DEFINE(MODE, CNF, AFCONFIG, PUPD) ((int)(MODE) |                                     \
                                              ((CNF & CH_PIN_CNF_MASK) << CH_PIN_CNF_SHIFT) | \
                                              ((AFCONFIG & CH_PIN_AFCONFIG_MASK) << CH_PIN_AFCONFIG_SHIFT)| \
                                              ((PUPD & CH_PIN_PUPD_MASK) << CH_PIN_PUPD_SHIFT))

#define CH_PIN_DEFINE_EXT(MODE, CNF, AFCONFIG, PUPD, CHANNELCONFIG)  \
    ((int)(MODE) |                                        \
     ((CNF & CH_PIN_CNF_MASK) << CH_PIN_CNF_SHIFT) |    \
     ((AFCONFIG & CH_PIN_AFCONFIG_MASK) << CH_PIN_AFCONFIG_SHIFT) | \
     ((PUPD & CH_PIN_PUPD_MASK) << CH_PIN_PUPD_SHIFT) | \
     ((CHANNELCONFIG & CH_PIN_CHANNELCONFIG_MASK) << CH_PIN_CHANNELCONFIG_SHIFT))


#define CH_PIN_DATA(MODE, CNF, AFCONFIG, PUPD) CH_PIN_DEFINE(MODE, CNF, AFCONFIG, PUPD)
#define CH_PIN_DATA_EXT(MODE, CNF, AFCONFIG, PUPD, CHANNELCONFIG) \
    CH_PIN_DEFINE_EXT(MODE, CNF, AFCONFIG, PUPD, CHANNELCONFIG)

    typedef enum
    {
        CH_PIN_INPUT = 0x00,
        CH_PIN_OUTPUT = 0x03,
        CH_PIN_ANALOG = 0x00
    } CHPinFunction;

#define CH_MODE_ANALOG (CH_PIN_ANALOG)
#define CH_MODE_INPUT (CH_PIN_INPUT | GPIO_Mode_IN_FLOATING)
#define CH_MODE_OUTPUT_PP (CH_PIN_OUTPUT | GPIO_Mode_Out_PP)
#define CH_MODE_OUTPUT_OD (CH_PIN_OUTPUT | GPIO_Mode_Out_OD)
#define CH_MODE_AF_PP (CH_PIN_OUTPUT | GPIO_Mode_AF_PP)
#define CH_MODE_AF_OD (CH_PIN_OUTPUT | GPIO_Mode_AF_OD)


// High nibble = port number (FirstPort <= PortName <= LastPort)
// Low nibble  = pin number
#define CH_PORT(X) (((uint32_t)(X) >> 4) & 0xF)
#define CH_PIN(X) ((uint32_t)(X)&0xF)
// Check PinName is valid: FirstPort <= PortName <= LastPort
// As FirstPort is equal to 0 and STM_PORT cast as an unsigned
#define CH_VALID_PINNAME(X) (CH_PORT(X) <= LastPort)

#define CH_GPIO_PIN(X) ((uint16_t)(1 << CH_PIN(X)))
    /*  Defines to be used by application */
    typedef enum
    {
        PIN_INPUT = 0,
        PIN_OUTPUT
    } PinDirection;

    typedef enum
    {
        PullNone = 0,
        PullUp = 1,
        PullDown = 2,
        OpenDrainPullUp = 3,
        OpenDrainNoPull = 4,
        OpenDrainPullDown = 5,
        PushPullNoPull = PullNone,
        PushPullPullUp = PullUp,
        PushPullPullDown = PullDown,
        OpenDrain = OpenDrainPullUp,
        PullDefault = PullNone
    } PinMode;

#ifdef __cplusplus
}
#endif

#endif
