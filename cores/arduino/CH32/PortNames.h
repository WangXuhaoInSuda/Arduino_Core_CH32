#ifndef _PORTNAMES_H
#define _PORTNAMES_H

#include "ch32_def.h"

#ifdef __cplusplus
extern "C" {
#endif

extern GPIO_TypeDef *GPIOPort[];

typedef enum {
  FirstPort = 0x00,
  PortA = FirstPort,
  PortB,
#if defined GPIOC_BASE
  PortC,
#endif
#if defined GPIOD_BASE
  PortD,
#endif
#if defined GPIOE_BASE
  PortE,
#endif
#if defined GPIOF_BASE
  PortF,
#endif
#if defined GPIOG_BASE
  PortG,
#endif
#if defined GPIOH_BASE
  PortH,
#endif
#if defined GPIOI_BASE
  PortI,
#endif
#if defined GPIOJ_BASE
  PortJ,
#endif
#if defined GPIOK_BASE
  PortK,
#endif
#if defined GPIOZ_BASE
  PortZ,
#endif
  PortEND,
  LastPort = PortEND - 1
} PortName;

#define MAX_NB_PORT (LastPort-FirstPort+1)

/* Return GPIO base address */
#define get_GPIO_Port(p) ((p < MAX_NB_PORT) ? GPIOPort[p] : (GPIO_TypeDef *)NULL)
/* Enable GPIO clock and return GPIO base address */
GPIO_TypeDef *set_GPIO_Port_Clock(uint32_t port_idx);

#ifdef __cplusplus
}
#endif
#endif