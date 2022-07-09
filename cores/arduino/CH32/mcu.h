//================================================================
//文件名称：mcu.h(mcu头文件)
//制作单位：苏州大学嵌入式
//更新记录：20200831--20200903
//================================================================

#ifndef __MCU_H         
#define __MCU_H

//(1)【变动】包含芯片头文件
#include "ch32v30x.h"

//(2)【固定】包含cpu头文件
#include "cpu.h"

//（3）【变动】MCU基本信息相关宏常数
//                            "1234567890123456789"
#define MCU_TYPE              "AHL-CH32V307-V1.6 "  //MCU型号（19字节）
//                            "123456789"
#define BIOS_TYPE             "20220126 "       //BIOS版本号（9字节）
#define MCU_SECTORSIZE        256              //扇区大小（B）
#define MCU_SECTOR_NUM        1920             //MCU扇区总数
#define MCU_STACKTOP          0x2001ffff        //栈顶地址（RAM最高地址）
#define MCU_FLASH_ADDR_START  0x08000000        //MCU的FLASH起始地址
#define MCU_FLASH_ADDR_LENGTH 0x00078000        //MCU的FLASH长度（480KB）
#define MCU_RAM_ADDR_START    0x20000000        //MCU的RAM起始地址
#define MCU_RAM_ADDR_LENGTH   0x00020000        //MCU的RAM长度（128KB）


#endif /* __MCU_H */
