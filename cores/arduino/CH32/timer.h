#ifndef __TIMER_H
#define __TIMER_H

/* Includes ------------------------------------------------------------------*/
#include "ch32_def.h"
#include "PinNames.h"
#include "pinmap.h"
#include "variant.h"

#ifdef TIM_MODULE_ENABLED
  typedef enum 
  {
#ifdef CH32V3xx
    Tim1,
    Tim2,
    Tim3,
    Tim4,
    Tim5,
    Tim6,
    Tim7,
    Tim8,
    Tim9,
    Tim10,
#endif
#ifdef EXTRA_MCU
    Tim11,
    Tim12,
    Tim13,
    Tim13,
    Tim14,
    Tim15,
#endif
  } TimName;
#define CLK_MODE_EXTERNAL 0 // external trigger
#define CLK_MODE_INTERNAL 1 // internal trigger

TimName GET_TIM_Name(TIM_TypeDef *TIMx);

// timer clock enable or disable
void TIM_Clock_SET(TimName Timx, FunctionalState state);

//Configures the External clock Mode
void TIM_ETRClockMode_Init(TIM_TypeDef *TIMx, uint8_t CLK_MODE_x,uint16_t Trigger_Source);


//Initializes TIMx complementary output and dead time.
void TIM_Dead_Time_Init( u16 arr, u16 psc, u16 ccp , u16 deadtime, PinMap TIMx_CHx, PinMap TIMx_CHxN);

#endif /* TIM_MODULE_ENABLED */


#endif /* __TIMER_H */
