/**
  ******************************************************************************
  * @file    clock.c
  * @author  WI6LABS
  * @version V1.0.0
  * @date    01-August-2016
  * @brief   provide clock services for time purpose
  *
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
#include "clock.h"
#include "core_riscv.h"
#ifdef __cplusplus
extern "C" {
#endif
//////////////////////////////
#define NVIC_PRIO_BITS 4 //ch32v3xx uses 4 bits for the priority levels
__IO uint64_t mTick;
uint64_t mTickPrio =  (1UL << NVIC_PRIO_BITS);
uint64_t mTickFreq = TICK_FREQ_DEFAULT;

WEAK void IncTick(void)
{
  mTick += mTickFreq;
}

WEAK uint64_t GetTick(void)
{
  return mTick;
}

WEAK uint64_t GetTickPrio(void)
{
  return mTickPrio;
}



#define SysTick_LOAD_RELOAD_Msk   0xFFFFFFFF
#define SysTick_CTLR_STE_Msk      0x00000001
#define SysTick_CTLR_STIE_Msk     0x00000002
#define SysTick_CTLR_STCLK_Msk    0x00000004
#define SysTick_CTLR_STRE_Msk     0x00000008
#define SysTick_CTLR_MODE_Msk     0x00000010
#define SysTick_CTLR_INIT_Msk     0x00000020
#define SysTick_CTLR_SWIE_Msk     0x80000000
uint64_t SysTick_Config(uint64_t ticks)
{
  if ((ticks - 1UL) > SysTick_LOAD_RELOAD_Msk)
  {
    return (1UL);                                                   /* Reload value impossible */
  }

  SysTick->CMP  = (uint64_t)(ticks - 1UL);  
  NVIC_EnableIRQ(SysTicK_IRQn);                       /* set reload register */
  NVIC_SetPriority (SysTicK_IRQn, (1UL << NVIC_PRIO_BITS) - 1UL); /* set Priority for Systick Interrupt */
  SysTick->CNT   = 0UL;                                             /* Load the SysTick Counter Value */
  SysTick->CTLR  = SysTick_CTLR_STE_Msk   |
                   SysTick_CTLR_STIE_Msk  |
                   SysTick_CTLR_STCLK_Msk |
                   SysTick_CTLR_STRE_Msk  |
                   SysTick_CTLR_INIT_Msk
                   ;                         /* Enable SysTick IRQ and SysTick Timer */
  return (0UL);                                                     /* Function successful */
}

#define STATUS_OK 1
#define STATUS_ERROR 0
WEAK uint8_t InitTick(uint32_t TickPriority)
{
  uint8_t  status = STATUS_OK;

  if (mTickFreq != 0U)
  {
    /*Configure the SysTick to have interrupt in 1ms time basis*/
    if (SysTick_Config(SystemCoreClock / (1000U / mTickFreq)) == 0U)
    {
      /* Configure the SysTick IRQ priority */
      if (TickPriority < (1UL << NVIC_PRIO_BITS))
      {
        NVIC_SetPriority(SysTicK_IRQn, TickPriority);
        mTickPrio = TickPriority;
      }
      else
      {
        status = STATUS_ERROR;
      }
    }
    else
    {
      status = STATUS_ERROR;
    }
  }
  else
  {
    status = STATUS_ERROR;
  }

  /* Return function status */
  return status;
}

void SysTick_Handler(void){
  IncTick();
}


//////////////////////////////////
uint32_t SYSTICK_IsActiveCounterFlag(void)
{
  return ((SysTick->CTLR & SysTick_CTLR_COUNTFLAG_Msk) == (SysTick_CTLR_COUNTFLAG_Msk));
}


/**
  * @brief  Function called to read the current micro second
  * @param  None
  * @retval None
  */
uint64_t getCurrentMicros(void)
{
  /* Ensure COUNTFLAG is reset by reading SysTick control and status register */
  SYSTICK_IsActiveCounterFlag();
  uint64_t m = GetTick();
  uint64_t u = SysTick->CMP - SysTick->CNT;
  if (SYSTICK_IsActiveCounterFlag()) {
    m = GetTick();
    u = SysTick->CMP - SysTick->CNT;
  }
  return (m * 1000 + (u * 1000) / SysTick->CMP);
}

/**
  * @brief  Function called wto read the current millisecond
  * @param  None
  * @retval None
  */
uint64_t getCurrentMillis(void)
{
  return GetTick();
}

#ifdef __cplusplus
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/