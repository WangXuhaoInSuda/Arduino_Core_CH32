//=====================================================================
//文件名称：gec.c文件
//制作单位：SD-Arm(sumcu.suda.edu.cn)
//更新记录：20181201-20200627
//移植规则：【固定】
//=====================================================================
#include "gec.h"
//======================================================================
//函数名称：Vectors_Init
//函数返回：无
//参数说明：无
//功能概要：User对BIOS中断向量表的部分继承,构件库函数指针初始化
//修改信息：WYH，20200805，规范
//======================================================================
void  Vectors_Init()
{
    //有用户程序，编译本段代码
    #if (GEC_USER_SECTOR_START!=0)
    //（1）若Flash倒数1扇区的前24字节为空，则写入设备序列号及软件版本号初值
    if(flash_isempty(MCU_SECTOR_NUM-1,24))
    {
        flash_write_physical((MCU_SECTOR_NUM-1)*MCU_SECTORSIZE+
        MCU_FLASH_ADDR_START,24,(uint8_t *)"0123456789ABCDEF20200716");
    }

    //（2）继承BIOS的中断
    void ** bios = (void *)MCU_FLASH_ADDR_START;    //BIOS向量表起始地址
    uint32_t user[MCU_SECTORSIZE];                 //User向量表变量数组
    //（2.1）读取User程序的中断向量表各中断处理程序首地址赋并给user数组
    flash_read_physical((uint8_t *)user,GEC_USER_SECTOR_START*
               MCU_SECTORSIZE+MCU_FLASH_ADDR_START,MCU_SECTORSIZE*2);
 	//（2.2）读取User程序的中断向量表各中断处理程序首地址赋并给user数组
    if (user[BIOS_UPDATE_IRQn] != (uint32_t)bios[BIOS_UPDATE_IRQn])
    {
        printf("  【User提示】：中断继承\r\n");
        //（2.2.1）改变User中断向量表中BIOS_UART中断向量
        flash_erase(GEC_USER_SECTOR_START);
        flash_erase(GEC_USER_SECTOR_START+1);
//        flash_erase(GEC_USER_SECTOR_START+2);
//        flash_erase(GEC_USER_SECTOR_START+3);
        //（2.2.2）修改USER中断向量表中BIOS更新串口的中断处理程序地址
        user[BIOS_UPDATE_IRQn]=(uint32_t)bios[BIOS_UPDATE_IRQn];
//        //【变  动】驻留操作系统时使用
//        //（2.2.3）修改USER中断向量表中SYSTICK和SW中断处理程序地址
//        user[BIOS_SYSTICK_IRQn] = (uint32_t)bios[BIOS_SYSTICK_IRQn];
//        user[BIOS_SW_IRQn]=(uint32_t)bios[BIOS_SW_IRQn];

        //（2.2.3）将修改后的user数组写回User中断向量表
        flash_write_physical(GEC_USER_SECTOR_START*MCU_SECTORSIZE+
               MCU_FLASH_ADDR_START,MCU_SECTORSIZE*2,(uint8_t *)user);
    }

    //（3）给component_fun赋值，SYSTEM_FUNCTION函数用
    component_fun=(void **)(MCU_FLASH_ADDR_START+GEC_COMPONENT_LST_START*MCU_SECTORSIZE);

    //（4）printf提示
    printf("  【User提示】：将进入User的main函数执行...\r\n\n");

    #endif
}
