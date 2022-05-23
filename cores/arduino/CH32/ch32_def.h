/*
modified by wxh
20220523
to be done : line 18-46
*/
#ifndef _CH32_DEF_
#define _CH32_DEF_

#define F_CPU SystemCoreClock

#ifdef CH32V3xx
#include "ch32v30x.h"
#else
#error "Chip series is not defined in boards.txt."
#endif

// Here define some compatibility
#ifndef CAN1
#define CAN1 CAN
#endif

/**
 * Libc porting layers
 */
#if defined (  __GNUC__  ) /* GCC CS3 */
#include <syscalls.h> /** RedHat Newlib minimal stub */
#define WEAK __attribute__ ((weak))
#endif

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

// weaked functions declaration
void SystemClock_Config(void);

void _Error_Handler(const char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif //_CH32_DEF_
