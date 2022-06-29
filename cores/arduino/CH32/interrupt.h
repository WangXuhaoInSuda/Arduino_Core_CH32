/**
  ******************************************************************************
  * @file    interrupt.h
  * @author  WI6LABS
  * @version V1.0.0
  * @date    01-August-2016
  * @brief   Header for interrupt module
  ******************************************************************************
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __INTERRUPT_H
#define __INTERRUPT_H

/* Includes ------------------------------------------------------------------*/
#include "ch32_def.h"
#include "Arduino.h"
#if !defined(EXTI_MODULE_DISABLED)



#ifndef EXTI_IRQ_PRIO
#if (__CORTEX_M == 0x00U)
#define EXTI_IRQ_PRIO       3
#else
#define EXTI_IRQ_PRIO       6
#endif /* __CORTEX_M */
#endif /* EXTI_IRQ_PRIO */
#ifndef EXTI_IRQ_SUBPRIO
#define EXTI_IRQ_SUBPRIO    0
#endif

#ifdef __cplusplus
#include <functional>

typedef std::function<void(void)> callback_function_t;
void ch32_interrupt_enable(GPIO_TypeDef *port,  GPIOMode_TypeDef io_mode,uint16_t pin, callback_function_t callback,EXTIMode_TypeDef mode, EXTITrigger_TypeDef trigger);
#endif

/* Exported functions ------------------------------------------------------- */
void ch32_interrupt_enable(GPIO_TypeDef *port, uint16_t pin, void (*callback)(void), EXTIMode_TypeDef mode, EXTITrigger_TypeDef trigger);
void ch32_interrupt_disable(GPIO_TypeDef *port, uint16_t pin);
#endif /* !HAL_EXTI_MODULE_DISABLED */

#endif /* __INTERRUPT_H */

/************************ (C) COPYRIGHT chicroelectronics *****END OF FILE****/
