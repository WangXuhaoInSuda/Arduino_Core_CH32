//======================================================================
//文件名称：cpu.h（cpu头文件）
//制作单位：SD-Arm(sumcu.suda.edu.cn)
//更新记录：20200831-20200903
//======================================================================

#ifndef  CPU_H   //防止重复定义（开头）
#define  CPU_H

//（1）【变动】包含所有芯片头文件，因CPU不同而异
#include "core_riscv.h"
#include "ch32v30x.h"

//（3）【变动】复位相关
// 按键复位
#define IS_PIN_RESET_OCCURED    ((RCC->RSTSCKR & RCC_PINRSTF) \
                                 && (!(RCC->RSTSCKR & 0xFB000000)))
// 上电复位
#define IS_POWERON_RESET        (RCC->RSTSCKR & RCC_PORRSTF)
//写1清引脚复位标志位
#define CLEAR_PIN_RESET_FLAG    (RCC->RSTSCKR |= RCC_RMVF)

//（3）【因内核而更改】中断宏定义
#define ENABLE_INTERRUPTS   __asm volatile ("csrw mstatus, %0" : : "r" (0x88) )    // 开总中断()
#define DISABLE_INTERRUPTS  __asm volatile ("csrw mstatus, %0" : : "r" (0x00) )     // 关总中断()
//（4）【固定】不优化类型别名宏定义
typedef volatile uint8_t      vuint8_t;   // 不优化无符号8位数，字节
typedef volatile uint16_t     vuint16_t;  // 不优化无符号16位数，字
typedef volatile uint32_t     vuint32_t;  // 不优化无符号32位数，长字
//（5）【固定】位操作宏函数（置位、清位、获得寄存器一位的状态）
#define BSET(bit,Register)  ((Register)|= (1<<(bit)))    //置寄存器的一位
#define BCLR(bit,Register)  ((Register) &= ~(1<<(bit)))  //清寄存器的一位
#define BGET(bit,Register)  (((Register) >> (bit)) & 1)  //获得寄存器一位的状态

#endif     //防止重复定义（结尾）
