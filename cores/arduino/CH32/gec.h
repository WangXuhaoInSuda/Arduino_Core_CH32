//======================================================================
//文件名称：gec.h（GEC芯片引脚头文件）
//制作单位：苏大arm技术中心(sumcu.suda.edu.cn)
//更新记录：2018.12-20200627
//======================================================================
#ifndef _GEC_H    
#define _GEC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "flash.h"
#include "printf.h"

//【变动】GEC基本信息==================================================
#define GEC_USER_SECTOR_START       (452)
#define GEC_COMPONENT_LST_START     (276)   //构件库函数列表开始扇区号
#define BIOS_SYSTICK_IRQn           (12+14)
#define BIOS_SW_IRQn                (14+14)
#define BIOS_UPDATE_IRQn            (53+14)   //BIOS程序写入串口的中断号

//【变动】动态命令起始扇区、结束扇区
#define GEC_DYNAMIC_START        (260)
#define GEC_DYNAMIC_END          (275)
//【固定】构件库函数指针和系统功能函数声明===========================================
void **  component_fun;

#ifdef __cplusplus
}
#endif
//void  Vectors_Init();
#endif  //防止重复定义（GEC_H 结尾）
