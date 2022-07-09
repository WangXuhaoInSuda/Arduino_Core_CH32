#include "core_debug.h"
#include "timer.h"
#include "board.h"

#ifdef __cplusplus
extern "C"
{
#endif
#ifdef TIM_MODULE_ENABLED
  /*********************************************************************
   * @fn      TIM_Clock_SET
   *
   * @brief   Configures TIM RCC setup
   *
   * @param Timx  any enum type in timer.h TimName.
   *
   * @param state  ENABLE or DISABLE
   *
   * @return  none
   */
  void TIM_Clock_SET(TimName Timx, FunctionalState state)
  {
    switch (Timx)
    {
    case Tim1:
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, state);
      break;
    case Tim2:
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, state);
      break;
    case Tim3:
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, state);
      break;
    case Tim4:
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, state);
      break;
    case Tim5:
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, state);
      break;
    case Tim6:
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, state);
      break;
    case Tim7:
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, state);
      break;
    case Tim8:
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, state);
      break;
    case Tim9:
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, state);
      break;
    case Tim10:
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, state);
      break;
    default:
      break;
    }
  }

  /*********************************************************************
   * @fn      TIM_Clock_SET
   *
   * @brief   Configures TIM RCC setup
   *
   * @param TIMx
   *
   * @return  TimName
   */
  TimName GET_TIM_Name(TIM_TypeDef *TIMx)
  {
#ifdef CH32V3xx
    if (TIMx == TIM1)
    {
      return Tim1;
    }
    else if (TIMx == TIM2)
    {
      return Tim2;
    }
    else if (TIMx == TIM3)
    {
      return Tim3;
    }
    else if (TIMx == TIM4)
    {
      return Tim4;
    }
    else if (TIMx == TIM5)
    {
      return Tim5;
    }
    else if (TIMx == TIM6)
    {
      return Tim6;
    }
    else if (TIMx == TIM7)
    {
      return Tim7;
    }
    else if (TIMx == TIM8)
    {
      return Tim8;
    }
    else if (TIMx == TIM9)
    {
      return Tim9;
    }
    else if (TIMx == TIM10)
    {
      return Tim10;
    }
#endif
#ifdef EXTRA_MCU
    else if (TIMx == TIM11)
    {
      return Tim11;
    }
    else if (TIMx == TIM12)
    {
      return Tim12;
    }
    else if (TIMx == TIM13)
    {
      return Tim13;
    }
    else if (TIMx == TIM14)
    {
      return Tim14;
    }
    else if (TIMx == TIM15)
    {
      return Tim15;
    }
#endif
  }
  /*********************************************************************
   * @fn      TIM_ETRClockMode_Init
   *
   * @brief   Configures the External clock Mode.
   *
   * @param Timx  any enum type in timer.h TimName.
   *
   * @param TIMx  defined TIMx.
   *
   * @param CLK_MODE_x  Specifies the source.
   *           @arg @ref CLK_MODE_EXTERNAL.
   *           @arg @ref CLK_MODE_INTERNAL.
   *
   * @param Trigger_Source TIM_TIxExternalCLK1Source_x
   *                       TIM_TS_x
   *
   * @return  none
   */
  void TIM_ETRClockMode_Init(TIM_TypeDef *TIMx, uint8_t CLK_MODE_x, uint16_t Trigger_Source)
  {

    TIM_Clock_SET(GET_TIM_Name(TIMx), ENABLE);
    TIM_CounterModeConfig(TIMx, TIM_CounterMode_Up);
    TIM_SetAutoreload(TIMx, 0x3EB);
    TIM_ETRClockMode1Config(TIMx, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_Inverted, 0x0);
    if (CLK_MODE_EXTERNAL == CLK_MODE_x)
    {
      TIM_TIxExternalClockConfig(TIMx, TIM_TIxExternalCLK1Source_TI1, TIM_ICPolarity_Rising, 0x00);
      TIM_Cmd(TIMx, ENABLE);
    }
    else if (CLK_MODE_INTERNAL == CLK_MODE_x)
    {
      TIM_SelectInputTrigger(TIMx, TIM_TS_ETRF);
      TIM_Cmd(TIMx, ENABLE);
    }
  }

  /*********************************************************************
   * @fn      TIM1_Dead_Time_Init
   *
   * @brief   Initializes TIM1 complementary output and dead time.
   *
   * @param   arr - the period value.
   *          psc - the prescaler value.
   *          ccp - the pulse value.
   *
   * @return  none
   *
   * @details example:
   *          Dead-time waveforms with delay greater than the negative pulse
   *          TIM1_Dead_Time_Init( 100, 48-1, 10 );
   *          Dead-time waveforms with delay greater than the positive pulse.
   *          TIM1_Dead_Time_Init( 100, 48-1, 90 );
   */
  void TIM_Dead_Time_Init(u16 arr, u16 psc, u16 ccp, u16 deadtime, PinMap TIMx_CHx, PinMap TIMx_CHxN)
  {
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    TIM_OCInitTypeDef TIM_OCInitStructure = {0};
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = {0};
    TIM_BDTRInitTypeDef TIM_BDTRInitStructure = {0};

    pin_function(TIMx_CHx.pin, TIMx_CHx.function);
    pin_function(TIMx_CHxN.pin, TIMx_CHxN.function);
    TIM_Clock_SET(GET_TIM_Name((TIM_TypeDef *)(TIMx_CHx.peripheral)), ENABLE);

    TIM_TimeBaseInitStructure.TIM_Period = arr;
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit((TIM_TypeDef *)(TIMx_CHx.peripheral), &TIM_TimeBaseInitStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
    TIM_OCInitStructure.TIM_Pulse = ccp;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
    switch (TIMx_CHx.function >> 1 & 0x03)
    {
    case 0:
      TIM_OC1Init((TIM_TypeDef *)(TIMx_CHx.peripheral), &TIM_OCInitStructure);
      break;
    case 1:
      TIM_OC2Init((TIM_TypeDef *)(TIMx_CHx.peripheral), &TIM_OCInitStructure);
      break;
    case 2:
      TIM_OC3Init((TIM_TypeDef *)(TIMx_CHx.peripheral), &TIM_OCInitStructure);
      break;
    }

    TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Disable;
    TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Disable;
    TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
    TIM_BDTRInitStructure.TIM_DeadTime = deadtime;
    TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable;
    TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
    TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
    TIM_BDTRConfig((TIM_TypeDef *)(TIMx_CHx.peripheral), &TIM_BDTRInitStructure);

    TIM_CtrlPWMOutputs((TIM_TypeDef *)(TIMx_CHx.peripheral), ENABLE);
    TIM_OC1PreloadConfig((TIM_TypeDef *)(TIMx_CHx.peripheral), TIM_OCPreload_Disable);
    TIM_ARRPreloadConfig((TIM_TypeDef *)(TIMx_CHx.peripheral), ENABLE);
    TIM_Cmd((TIM_TypeDef *)(TIMx_CHx.peripheral), ENABLE);
  }

#endif /* TIM_MODULE_ENABLED */

#ifdef __cplusplus
}
#endif
