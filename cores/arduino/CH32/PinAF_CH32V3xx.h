#ifndef _PINAF_CH32V3xx_H
#define _PINAF_CH32V3xx_H

#ifdef CH32V3xx

#ifdef __cplusplus
extern "C"
{
#endif
  // for remaps
  enum
  {
    AFIO_NONE,
    // ENABLE:
    /* GPIO_Remap_define */
    /* PCFR1 */
    AFIO_Remap_SPI1_ENABLE,             /* SPI1 Alternate Function mapping */
    AFIO_Remap_I2C1_ENABLE,             /* I2C1 Alternate Function mapping */
    AFIO_Remap_USART1_ENABLE,           /* USART1 Alternate Function mapping low bit */
    AFIO_Remap_USART2_ENABLE,           /* USART2 Alternate Function mapping */
    AFIO_PartialRemap_USART3_ENABLE,    /* USART3 Partial Alternate Function mapping */
    AFIO_FullRemap_USART3_ENABLE,       /* USART3 Full Alternate Function mapping */
    AFIO_PartialRemap_TIM1_ENABLE,      /* TIM1 Partial Alternate Function mapping */
    AFIO_FullRemap_TIM1_ENABLE,         /* TIM1 Full Alternate Function mapping */
    AFIO_PartialRemap1_TIM2_ENABLE,     /* TIM2 Partial1 Alternate Function mapping */
    AFIO_PartialRemap2_TIM2_ENABLE,     /* TIM2 Partial2 Alternate Function mapping */
    AFIO_FullRemap_TIM2_ENABLE,         /* TIM2 Full Alternate Function mapping */
    AFIO_PartialRemap_TIM3_ENABLE,      /* TIM3 Partial Alternate Function mapping */
    AFIO_FullRemap_TIM3_ENABLE,         /* TIM3 Full Alternate Function mapping */
    AFIO_Remap_TIM4_ENABLE,             /* TIM4 Alternate Function mapping */
    AFIO_Remap1_CAN1_ENABLE,            /* CAN1 Alternate Function mapping */
    AFIO_Remap2_CAN1_ENABLE,            /* CAN1 Alternate Function mapping */
    AFIO_Remap_PD01_ENABLE,             /* PD01 Alternate Function mapping */
    AFIO_Remap_TIM5CH4_LSI_ENABLE,      /* LSI connected to TIM5 Channel4 input capture for calibration */
    AFIO_Remap_ADC1_ETRGINJ_ENABLE,     /* ADC1 External Trigger Injected Conversion remapping */
    AFIO_Remap_ADC1_ETRGREG_ENABLE,     /* ADC1 External Trigger Regular Conversion remapping */
    AFIO_Remap_ADC2_ETRGINJ_ENABLE,     /* ADC2 External Trigger Injected Conversion remapping */
    AFIO_Remap_ADC2_ETRGREG_ENABLE,     /* ADC2 External Trigger Regular Conversion remapping */
    AFIO_Remap_ETH_ENABLE,              /* Ethernet remapping (only for Connectivity line devices) */
    AFIO_Remap_CAN2_ENABLE,             /* CAN2 remapping (only for Connectivity line devices) */
    AFIO_Remap_MII_RMII_SEL_ENABLE,     /* MII or RMII selection */
    AFIO_Remap_SWJ_NoJTRST_ENABLE,      /* Full SWJ Enabled (JTAG-DP + SW-DP) but without JTRST */
    AFIO_Remap_SWJ_JTAGDisable_ENABLE,  /* JTAG-DP Disabled and SW-DP Enabled */
    AFIO_Remap_SWJ_Disable_ENABLE,      /* Full SWJ Disabled (JTAG-DP + SW-DP) */
    AFIO_Remap_SPI3_ENABLE,             /* SPI3/I2S3 Alternate Function mapping (only for Connectivity line devices) */
    AFIO_Remap_TIM2ITR1_PTP_SOF_ENABLE, /* Ethernet PTP output or USB OTG SOF (Start of Frame) connected
                                                                to TIM2 Internal Trigger 1 for calibration
                                                            (only for Connectivity line devices) */
    AFIO_Remap_PTP_PPS_ENABLE,          /* Ethernet MAC PPS_PTS output on PB05 (only for Connectivity line devices) */

    /* PCFR2 */
    AFIO_Remap_TIM8_ENABLE,           /* TIM8 Alternate Function mapping */
    AFIO_PartialRemap_TIM9_ENABLE,    /* TIM9 Partial Alternate Function mapping */
    AFIO_FullRemap_TIM9_ENABLE,       /* TIM9 Full Alternate Function mapping */
    AFIO_PartialRemap_TIM10_ENABLE,   /* TIM10 Partial Alternate Function mapping */
    AFIO_FullRemap_TIM10_ENABLE,      /* TIM10 Full Alternate Function mapping */
    AFIO_Remap_FSMC_NADV_ENABLE,      /* FSMC_NADV Alternate Function mapping */
    AFIO_PartialRemap_USART4_ENABLE,  /* USART4 Partial Alternate Function mapping */
    AFIO_FullRemap_USART4_ENABLE,     /* USART4 Full Alternate Function mapping */
    AFIO_PartialRemap_USART5_ENABLE,  /* USART5 Partial Alternate Function mapping */
    AFIO_FullRemap_USART5_ENABLE,     /* USART5 Full Alternate Function mapping */
    AFIO_PartialRemap_USART6_ENABLE,  /* USART6 Partial Alternate Function mapping */
    AFIO_FullRemap_USART6_ENABLE,     /* USART6 Full Alternate Function mapping */
    AFIO_PartialRemap_USART7_ENABLE,  /* USART7 Partial Alternate Function mapping */
    AFIO_FullRemap_USART7_ENABLE,     /* USART7 Full Alternate Function mapping */
    AFIO_PartialRemap_USART8_ENABLE,  /* USART8 Partial Alternate Function mapping */
    AFIO_FullRemap_USART8_ENABLE,     /* USART8 Full Alternate Function mapping */
    AFIO_Remap_USART1_HighBit_ENABLE, /* USART1 Alternate Function mapping high bit */

    // DISABLE:
    /* GPIO_Remap_define */
    /* PCFR1 */
    AFIO_Remap_SPI1_DISABLE,             /* SPI1 Alternate Function mapping */
    AFIO_Remap_I2C1_DISABLE,             /* I2C1 Alternate Function mapping */
    AFIO_Remap_USART1_DISABLE,           /* USART1 Alternate Function mapping low bit */
    AFIO_Remap_USART2_DISABLE,           /* USART2 Alternate Function mapping */
    AFIO_PartialRemap_USART3_DISABLE,    /* USART3 Partial Alternate Function mapping */
    AFIO_FullRemap_USART3_DISABLE,       /* USART3 Full Alternate Function mapping */
    AFIO_PartialRemap_TIM1_DISABLE,      /* TIM1 Partial Alternate Function mapping */
    AFIO_FullRemap_TIM1_DISABLE,         /* TIM1 Full Alternate Function mapping */
    AFIO_PartialRemap1_TIM2_DISABLE,     /* TIM2 Partial1 Alternate Function mapping */
    AFIO_PartialRemap2_TIM2_DISABLE,     /* TIM2 Partial2 Alternate Function mapping */
    AFIO_FullRemap_TIM2_DISABLE,         /* TIM2 Full Alternate Function mapping */
    AFIO_PartialRemap_TIM3_DISABLE,      /* TIM3 Partial Alternate Function mapping */
    AFIO_FullRemap_TIM3_DISABLE,         /* TIM3 Full Alternate Function mapping */
    AFIO_Remap_TIM4_DISABLE,             /* TIM4 Alternate Function mapping */
    AFIO_Remap1_CAN1_DISABLE,            /* CAN1 Alternate Function mapping */
    AFIO_Remap2_CAN1_DISABLE,            /* CAN1 Alternate Function mapping */
    AFIO_Remap_PD01_DISABLE,             /* PD01 Alternate Function mapping */
    AFIO_Remap_TIM5CH4_LSI_DISABLE,      /* LSI connected to TIM5 Channel4 input capture for calibration */
    AFIO_Remap_ADC1_ETRGINJ_DISABLE,     /* ADC1 External Trigger Injected Conversion remapping */
    AFIO_Remap_ADC1_ETRGREG_DISABLE,     /* ADC1 External Trigger Regular Conversion remapping */
    AFIO_Remap_ADC2_ETRGINJ_DISABLE,     /* ADC2 External Trigger Injected Conversion remapping */
    AFIO_Remap_ADC2_ETRGREG_DISABLE,     /* ADC2 External Trigger Regular Conversion remapping */
    AFIO_Remap_ETH_DISABLE,              /* Ethernet remapping (only for Connectivity line devices) */
    AFIO_Remap_CAN2_DISABLE,             /* CAN2 remapping (only for Connectivity line devices) */
    AFIO_Remap_MII_RMII_SEL_DISABLE,     /* MII or RMII selection */
    AFIO_Remap_SWJ_NoJTRST_DISABLE,      /* Full SWJ DISABLEd (JTAG-DP + SW-DP) but without JTRST */
    AFIO_Remap_SWJ_JTAGDisable_DISABLE,  /* JTAG-DP Disabled and SW-DP DISABLEd */
    AFIO_Remap_SWJ_Disable_DISABLE,      /* Full SWJ Disabled (JTAG-DP + SW-DP) */
    AFIO_Remap_SPI3_DISABLE,             /* SPI3/I2S3 Alternate Function mapping (only for Connectivity line devices) */
    AFIO_Remap_TIM2ITR1_PTP_SOF_DISABLE, /* Ethernet PTP output or USB OTG SOF (Start of Frame) connected
                                                                to TIM2 Internal Trigger 1 for calibration
                                                            (only for Connectivity line devices) */
    AFIO_Remap_PTP_PPS_DISABLE,          /* Ethernet MAC PPS_PTS output on PB05 (only for Connectivity line devices) */

    /* PCFR2 */
    AFIO_Remap_TIM8_DISABLE,           /* TIM8 Alternate Function mapping */
    AFIO_PartialRemap_TIM9_DISABLE,    /* TIM9 Partial Alternate Function mapping */
    AFIO_FullRemap_TIM9_DISABLE,       /* TIM9 Full Alternate Function mapping */
    AFIO_PartialRemap_TIM10_DISABLE,   /* TIM10 Partial Alternate Function mapping */
    AFIO_FullRemap_TIM10_DISABLE,      /* TIM10 Full Alternate Function mapping */
    AFIO_Remap_FSMC_NADV_DISABLE,      /* FSMC_NADV Alternate Function mapping */
    AFIO_PartialRemap_USART4_DISABLE,  /* USART4 Partial Alternate Function mapping */
    AFIO_FullRemap_USART4_DISABLE,     /* USART4 Full Alternate Function mapping */
    AFIO_PartialRemap_USART5_DISABLE,  /* USART5 Partial Alternate Function mapping */
    AFIO_FullRemap_USART5_DISABLE,     /* USART5 Full Alternate Function mapping */
    AFIO_PartialRemap_USART6_DISABLE,  /* USART6 Partial Alternate Function mapping */
    AFIO_FullRemap_USART6_DISABLE,     /* USART6 Full Alternate Function mapping */
    AFIO_PartialRemap_USART7_DISABLE,  /* USART7 Partial Alternate Function mapping */
    AFIO_FullRemap_USART7_DISABLE,     /* USART7 Full Alternate Function mapping */
    AFIO_PartialRemap_USART8_DISABLE,  /* USART8 Partial Alternate Function mapping */
    AFIO_FullRemap_USART8_DISABLE,     /* USART8 Full Alternate Function mapping */
    AFIO_Remap_USART1_HighBit_DISABLE, /* USART1 Alternate Function mapping high bit */
    AFIO_Remap_USART1_Low_HighBit_ENABLE, /* USART1 Alternate Function*/
    AFIO_Remap_USART1_Low_HighBit_DISABLE,
  };

static inline void pinV3_DisconnectDebug(PinName pin)
{
  /** Enable this flag gives the possibility to use debug pins without any risk
    * to lose traces
    */
#ifndef CH32V3_LOCK_DEBUG
  // Enable AFIO clock
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

  // Disconnect JTAG-DP + SW-DP signals.
  // Warning: Need to reconnect under reset
  if ((pin == PA_13) || (pin == PA_14)) {
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE); // JTAG-DP Disabled and SW-DP Disabled
  }
  if ((pin == PA_15) || (pin == PB_3) || (pin == PB_4)) {
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); // JTAG-DP Disabled and SW-DP enabled
  }
#else
  UNUSED(pin);
#endif /* CH32V3_FORCE_DEBUG */

}

  static inline void pin_SetV3AFPin(uint32_t afnum)
  {
    // Enable AFIO clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    switch (afnum)
    {
    case AFIO_Remap_SPI1_ENABLE:
      GPIO_PinRemapConfig(GPIO_Remap_SPI1, ENABLE);
      break;
    case AFIO_Remap_SPI1_DISABLE:
      GPIO_PinRemapConfig(GPIO_Remap_SPI1, DISABLE);
      break;
    case AFIO_Remap_I2C1_ENABLE:
      GPIO_PinRemapConfig(GPIO_Remap_I2C1, ENABLE);
      break;
    case AFIO_Remap_I2C1_DISABLE:
      GPIO_PinRemapConfig(GPIO_Remap_I2C1, DISABLE);
      break;
    case AFIO_Remap_USART1_ENABLE:
      GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);
      break;
    case AFIO_Remap_USART1_DISABLE:
      GPIO_PinRemapConfig(GPIO_Remap_USART1, DISABLE);
      break;
    case AFIO_Remap_USART2_ENABLE:
      GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);
      break;
    case AFIO_Remap_USART2_DISABLE:
      GPIO_PinRemapConfig(GPIO_Remap_USART2, DISABLE);
      break;
    case AFIO_PartialRemap_USART3_ENABLE:
      GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);
      break;
    case AFIO_PartialRemap_USART3_DISABLE:
      GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, DISABLE);
      break;
    case AFIO_FullRemap_USART3_ENABLE:
      GPIO_PinRemapConfig(GPIO_FullRemap_USART3, ENABLE);
      break;
    case AFIO_FullRemap_USART3_DISABLE:
      GPIO_PinRemapConfig(GPIO_FullRemap_USART3, DISABLE);
      break;
    case AFIO_PartialRemap_TIM1_ENABLE:
      GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE);
      break;
    case AFIO_PartialRemap_TIM1_DISABLE:
      GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, DISABLE);
      break;
    case AFIO_FullRemap_TIM1_ENABLE:
      GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE);
      break;
    case AFIO_FullRemap_TIM1_DISABLE:
      GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, DISABLE);
      break;
    case AFIO_PartialRemap1_TIM2_ENABLE:
      GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);
      break;
    case AFIO_PartialRemap1_TIM2_DISABLE:
      GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, DISABLE);
      break;
    case AFIO_PartialRemap2_TIM2_ENABLE:
      GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2, ENABLE);
      break;
    case AFIO_PartialRemap2_TIM2_DISABLE:
      GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2, DISABLE);
      break;
    case AFIO_FullRemap_TIM2_ENABLE:
      GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);
      break;
    case AFIO_FullRemap_TIM2_DISABLE:
      GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, DISABLE);
      break;
    case AFIO_PartialRemap_TIM3_ENABLE:
      GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);
      break;
    case AFIO_PartialRemap_TIM3_DISABLE:
      GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, DISABLE);
      break;
    case AFIO_FullRemap_TIM3_ENABLE:
      GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);
      break;
    case AFIO_FullRemap_TIM3_DISABLE:
      GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, DISABLE);
      break;
    case AFIO_Remap_TIM4_ENABLE:
      GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);
      break;
    case AFIO_Remap_TIM4_DISABLE:
      GPIO_PinRemapConfig(GPIO_Remap_TIM4, DISABLE);
      break;
    case AFIO_Remap1_CAN1_ENABLE:
      GPIO_PinRemapConfig(GPIO_Remap1_CAN1, ENABLE);
      break;
    case AFIO_Remap1_CAN1_DISABLE:
      GPIO_PinRemapConfig(GPIO_Remap1_CAN1, DISABLE);
      break;
    case AFIO_Remap2_CAN1_ENABLE:
      GPIO_PinRemapConfig(GPIO_Remap2_CAN1, ENABLE);
      break;
    case AFIO_Remap2_CAN1_DISABLE:
      GPIO_PinRemapConfig(GPIO_Remap2_CAN1, DISABLE);
      break;
    case AFIO_Remap_PD01_ENABLE:
      GPIO_PinRemapConfig(GPIO_Remap_PD01, ENABLE);
      break;
    case AFIO_Remap_PD01_DISABLE:
      GPIO_PinRemapConfig(GPIO_Remap_PD01, DISABLE);
      break;
    case AFIO_Remap_TIM5CH4_LSI_ENABLE:
      GPIO_PinRemapConfig(GPIO_Remap_TIM5CH4_LSI, ENABLE);
      break;
    case AFIO_Remap_TIM5CH4_LSI_DISABLE:
      GPIO_PinRemapConfig(GPIO_Remap_TIM5CH4_LSI, DISABLE);
      break;
    case AFIO_Remap_ADC1_ETRGINJ_ENABLE:
      GPIO_PinRemapConfig(GPIO_Remap_ADC1_ETRGINJ, ENABLE);
      break;
    case AFIO_Remap_ADC1_ETRGINJ_DISABLE:
      GPIO_PinRemapConfig(GPIO_Remap_ADC1_ETRGINJ, DISABLE);
      break;
    case AFIO_Remap_ADC1_ETRGREG_ENABLE:
      GPIO_PinRemapConfig(GPIO_Remap_ADC1_ETRGREG, ENABLE);
      break;
    case AFIO_Remap_ADC1_ETRGREG_DISABLE:
      GPIO_PinRemapConfig(GPIO_Remap_ADC1_ETRGREG, DISABLE);
      break;
    case AFIO_Remap_ADC2_ETRGINJ_ENABLE:
      GPIO_PinRemapConfig(GPIO_Remap_ADC2_ETRGINJ, ENABLE);
      break;
    case AFIO_Remap_ADC2_ETRGINJ_DISABLE:
      GPIO_PinRemapConfig(GPIO_Remap_ADC2_ETRGINJ, DISABLE);
      break;
    case AFIO_Remap_ADC2_ETRGREG_ENABLE:
      GPIO_PinRemapConfig(GPIO_Remap_ADC2_ETRGREG, ENABLE);
      break;
    case AFIO_Remap_ADC2_ETRGREG_DISABLE:
      GPIO_PinRemapConfig(GPIO_Remap_ADC2_ETRGREG, DISABLE);
      break;
    case AFIO_Remap_ETH_ENABLE:
      GPIO_PinRemapConfig(GPIO_Remap_ETH, ENABLE);
      break;
    case AFIO_Remap_ETH_DISABLE:
      GPIO_PinRemapConfig(GPIO_Remap_ETH, DISABLE);
      break;
    case AFIO_Remap_CAN2_ENABLE:
      GPIO_PinRemapConfig(GPIO_Remap_CAN2, ENABLE);
      break;
    case AFIO_Remap_CAN2_DISABLE:
      GPIO_PinRemapConfig(GPIO_Remap_CAN2, DISABLE);
      break;
    case AFIO_Remap_MII_RMII_SEL_ENABLE:
      GPIO_PinRemapConfig(GPIO_Remap_MII_RMII_SEL, ENABLE);
      break;
    case AFIO_Remap_MII_RMII_SEL_DISABLE:
      GPIO_PinRemapConfig(GPIO_Remap_MII_RMII_SEL, DISABLE);
      break;
    case AFIO_Remap_SWJ_NoJTRST_ENABLE:
      GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST, ENABLE);
      break;
    case AFIO_Remap_SWJ_NoJTRST_DISABLE:
      GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST, DISABLE);
      break;
    case AFIO_Remap_SWJ_JTAGDisable_ENABLE:
      GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
      break;
    case AFIO_Remap_SWJ_JTAGDisable_DISABLE:
      GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, DISABLE);
      break;
    case AFIO_Remap_SWJ_Disable_ENABLE:
      GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
      break;
    case AFIO_Remap_SWJ_Disable_DISABLE:
      GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, DISABLE);
      break;
    case AFIO_Remap_SPI3_ENABLE:
      GPIO_PinRemapConfig(GPIO_Remap_SPI3, ENABLE);
      break;
    case AFIO_Remap_SPI3_DISABLE:
      GPIO_PinRemapConfig(GPIO_Remap_SPI3, DISABLE);
      break;
    case AFIO_Remap_TIM2ITR1_PTP_SOF_ENABLE:
      GPIO_PinRemapConfig(GPIO_Remap_TIM2ITR1_PTP_SOF, ENABLE);
      break;
    case AFIO_Remap_TIM2ITR1_PTP_SOF_DISABLE:
      GPIO_PinRemapConfig(GPIO_Remap_TIM2ITR1_PTP_SOF, DISABLE);
      break;
    case AFIO_Remap_PTP_PPS_ENABLE:
      GPIO_PinRemapConfig(GPIO_Remap_PTP_PPS, ENABLE);
      break;
    case AFIO_Remap_PTP_PPS_DISABLE:
      GPIO_PinRemapConfig(GPIO_Remap_PTP_PPS, DISABLE);
      break;
    case AFIO_Remap_TIM8_ENABLE:
      GPIO_PinRemapConfig(GPIO_Remap_TIM8, ENABLE);
      break;
    case AFIO_Remap_TIM8_DISABLE:
      GPIO_PinRemapConfig(GPIO_Remap_TIM8, DISABLE);
      break;
    case AFIO_PartialRemap_TIM9_ENABLE:
      GPIO_PinRemapConfig(GPIO_PartialRemap_TIM9, ENABLE);
      break;
    case AFIO_PartialRemap_TIM9_DISABLE:
      GPIO_PinRemapConfig(GPIO_PartialRemap_TIM9, DISABLE);
      break;
    case AFIO_FullRemap_TIM9_ENABLE:
      GPIO_PinRemapConfig(GPIO_FullRemap_TIM9, ENABLE);
      break;
    case AFIO_FullRemap_TIM9_DISABLE:
      GPIO_PinRemapConfig(GPIO_FullRemap_TIM9, DISABLE);
      break;
    case AFIO_PartialRemap_TIM10_ENABLE:
      GPIO_PinRemapConfig(GPIO_PartialRemap_TIM10, ENABLE);
      break;
    case AFIO_PartialRemap_TIM10_DISABLE:
      GPIO_PinRemapConfig(GPIO_PartialRemap_TIM10, DISABLE);
      break;
    case AFIO_FullRemap_TIM10_ENABLE:
      GPIO_PinRemapConfig(GPIO_FullRemap_TIM10, ENABLE);
      break;
    case AFIO_FullRemap_TIM10_DISABLE:
      GPIO_PinRemapConfig(GPIO_FullRemap_TIM10, DISABLE);
      break;
    case AFIO_Remap_FSMC_NADV_ENABLE:
      GPIO_PinRemapConfig(GPIO_Remap_FSMC_NADV, ENABLE);
      break;
    case AFIO_Remap_FSMC_NADV_DISABLE:
      GPIO_PinRemapConfig(GPIO_Remap_FSMC_NADV, DISABLE);
      break;
    case AFIO_PartialRemap_USART4_ENABLE:
      GPIO_PinRemapConfig(GPIO_PartialRemap_USART4, ENABLE);
      break;
    case AFIO_PartialRemap_USART4_DISABLE:
      GPIO_PinRemapConfig(GPIO_PartialRemap_USART4, DISABLE);
      break;
    case AFIO_FullRemap_USART4_ENABLE:
      GPIO_PinRemapConfig(GPIO_FullRemap_USART4, ENABLE);
      break;
    case AFIO_FullRemap_USART4_DISABLE:
      GPIO_PinRemapConfig(GPIO_FullRemap_USART4, DISABLE);
      break;
    case AFIO_PartialRemap_USART5_ENABLE:
      GPIO_PinRemapConfig(GPIO_PartialRemap_USART5, ENABLE);
      break;
    case AFIO_PartialRemap_USART5_DISABLE:
      GPIO_PinRemapConfig(GPIO_PartialRemap_USART5, DISABLE);
      break;
    case AFIO_FullRemap_USART5_ENABLE:
      GPIO_PinRemapConfig(GPIO_FullRemap_USART5, ENABLE);
      break;
    case AFIO_FullRemap_USART5_DISABLE:
      GPIO_PinRemapConfig(GPIO_FullRemap_USART5, DISABLE);
      break;
    case AFIO_PartialRemap_USART6_ENABLE:
      GPIO_PinRemapConfig(GPIO_PartialRemap_USART6, ENABLE);
      break;
    case AFIO_PartialRemap_USART6_DISABLE:
      GPIO_PinRemapConfig(GPIO_PartialRemap_USART6, DISABLE);
      break;
    case AFIO_FullRemap_USART6_ENABLE:
      GPIO_PinRemapConfig(GPIO_FullRemap_USART6, ENABLE);
      break;
    case AFIO_FullRemap_USART6_DISABLE:
      GPIO_PinRemapConfig(GPIO_FullRemap_USART6, DISABLE);
      break;
    case AFIO_PartialRemap_USART7_ENABLE:
      GPIO_PinRemapConfig(GPIO_PartialRemap_USART7, ENABLE);
      break;
    case AFIO_PartialRemap_USART7_DISABLE:
      GPIO_PinRemapConfig(GPIO_PartialRemap_USART7, DISABLE);
      break;
    case AFIO_FullRemap_USART7_ENABLE:
      GPIO_PinRemapConfig(GPIO_FullRemap_USART7, ENABLE);
      break;
    case AFIO_FullRemap_USART7_DISABLE:
      GPIO_PinRemapConfig(GPIO_FullRemap_USART7, DISABLE);
      break;
    case AFIO_PartialRemap_USART8_ENABLE:
      GPIO_PinRemapConfig(GPIO_PartialRemap_USART8, ENABLE);
      break;
    case AFIO_PartialRemap_USART8_DISABLE:
      GPIO_PinRemapConfig(GPIO_PartialRemap_USART8, DISABLE);
      break;
    case AFIO_FullRemap_USART8_ENABLE:
      GPIO_PinRemapConfig(GPIO_FullRemap_USART8, ENABLE);
      break;
    case AFIO_FullRemap_USART8_DISABLE:
      GPIO_PinRemapConfig(GPIO_FullRemap_USART8, DISABLE);
      break;
    case AFIO_Remap_USART1_HighBit_ENABLE:
      GPIO_PinRemapConfig(GPIO_Remap_USART1_HighBit, ENABLE);
      break;
    case AFIO_Remap_USART1_HighBit_DISABLE:
      GPIO_PinRemapConfig(GPIO_Remap_USART1_HighBit, DISABLE);
      break;
    case AFIO_Remap_USART1_Low_HighBit_ENABLE:
      GPIO_PinRemapConfig(GPIO_Remap_USART1_HighBit, ENABLE);
      GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);
      break;
    case AFIO_Remap_USART1_Low_HighBit_DISABLE:
      GPIO_PinRemapConfig(GPIO_Remap_USART1_HighBit, DISABLE);
      GPIO_PinRemapConfig(GPIO_Remap_USART1, DISABLE);
      break;
    default:
    case AFIO_NONE:
      break;
    }
  }

#ifdef __cplusplus
}
#endif

#endif /* CH32V3xx */

#endif /* _PINAF_CH32V3xx_H */
