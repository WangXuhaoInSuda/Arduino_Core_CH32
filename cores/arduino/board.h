#ifndef _BOARD_H_
#define _BOARD_H_


#include "emuart.h"
#include "uart.h"
#include "gpio.h"
#include "flash.h"
#include "printf.h"
#include "interrupt.h"
#include "clock.h"
#include "digital_io.h"
#include "timer.h"


/*
 * Core and peripherals registers definitions
*/
#ifdef __cplusplus
extern "C" {
#endif

void init(void) ;

#ifdef __cplusplus
}
#endif


#endif /* _BOARD_H_ */
