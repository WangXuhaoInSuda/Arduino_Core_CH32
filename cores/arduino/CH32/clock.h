/**
  ******************************************************************************
  * @file    clock.h
  * @author  WI6LABS
  * @version V1.0.0
  * @date    01-August-2016
  * @brief   Header for clock.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
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
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CLOCK_H
#define __CLOCK_H

/* Includes ------------------------------------------------------------------*/
#include "ch32_def.h"
#define SysTick_CTLR_COUNTFLAG_Pos 0U
#define SysTick_CTLR_COUNTFLAG_Msk (1UL << SysTick_CTLR_COUNTFLAG_Pos)


#ifdef __cplusplus
extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/
/* Clock source selection */
typedef enum {
  LSI_CLOCK,
  HSI_CLOCK,
  LSE_CLOCK,
  HSE_CLOCK
} sourceClock_t;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
uint64_t getCurrentMillis(void);
uint64_t getCurrentMicros(void);
uint32_t SYSTICK_IsActiveCounterFlag(void);
void SysTick_Handler(void)  __attribute__((interrupt()));
WEAK void IncTick(void);
WEAK uint64_t GetTick(void);
WEAK uint64_t GetTickPrio(void);
uint64_t SysTick_Config(uint64_t ticks);
WEAK uint8_t InitTick(uint32_t TickPriority);
#ifdef __cplusplus
}
#endif

#endif /* __CLOCK_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
