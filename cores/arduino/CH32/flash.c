//===========================================================================
//文件名称：flash.c
//功能概要：Flash底层驱动构件源文件
//版权所有：SD-Arm(sumcu.suda.edu.cn)
//版本更新：20200831-20200904
//芯片类型：CH32V307
//===========================================================================
//包含头文件
#include "flash.h"


/*==================================内部调用函数声明=====================================*/
//======================================================================
//函数名称：flash_Best
//函数返回：0-成功 1-失败
//参数说明：sect:待写入扇区号
//            offset:待写入数据位置的偏移地址
//            N：待写入数据字节数
//            buf:待写入数据的首地址
//功能概要：首位地址都对齐的情况下的数据写入
//编程参考：暂无
//======================================================================
uint8_t flash_Best(uint16_t sect,uint16_t offset,uint16_t N,uint8_t *buf);
uint8_t flash_test(uint16_t addr, uint16_t offset,uint16_t N, uint8_t* buf);

//======================================================================
//函数名称：flash_Program_fast
//参数说明：address
//功能概要：声名快速写入的起始地址
//=======================================================================
void flash_Program_fast(uint32_t address);

//======================================================================
//函数名称：flash_init
//函数返回：无
//参数说明：无
//功能概要：初始化flash模块
//======================================================================
void flash_init(void)
{
    //清除所有错误标志位
    FLASH->STATR &= 0xFFFFFFFF;

    //解锁Flash控制寄存器
    if((FLASH->CTLR & FLASH_CTLR_LOCK )!= 0u)
    {
        FLASH->KEYR = (uint32_t)FLASH_KEY1;
        FLASH->KEYR = (uint32_t)FLASH_KEY2;

        FLASH->MODEKEYR = FLASH_KEY1;
        FLASH->MODEKEYR = FLASH_KEY2;

    }
    //等待之前最后一个flash操作完成
    while((FLASH->STATR & FLASH_STATR_BSY) != 0U);

    //清数据缓冲区
    FLASH->ACTLR &= ~FLASH_ACTLR_PRFTBE;
    //清flash快速编程位
    FLASH->CTLR &= ~FLASH_CTLR_PAGE_PG;

}

//======================================================================
//函数名称：flash_erase
//函数返回：函数执行执行状态：0=正常；1=异常。
//参数说明：sect：目标扇区号（范围取决于实际芯片，例如 STM32L433:0~127,每扇区2KB;
//功能概要：擦除flash存储器的sect扇区
//======================================================================
uint8_t flash_erase(uint32_t sect)
{
    uint32_t address;

    address = (uint32_t)(sect*FLASH_PAGE_SIZE + FLASH_ADDR_START);
    flash_init();
    //等待之前最后一个flash操作完成
    while((FLASH->STATR & STATR_BSY) != 0U);
    //清闪存即时编程位
    FLASH->CTLR &= ~FLASH_CTLR_PG_set;
    //使能扇区快速擦除
    FLASH->CTLR |= FLASH_CTLR_PAGE_SET;
    //设置擦除扇区
    FLASH->ADDR = address;
    //开始扇区擦除
    FLASH->CTLR |= FLASH_CTLR_START;
    //等待擦出完成
    while((FLASH->STATR & STATR_BSY) != 0U);
    //禁止扇区擦除
    FLASH->CTLR &= ~FLASH_CTLR_PAGE_SET;
    return 0;  //成功返回
}

//======================================================================
//函数名称：flash_erase_fast
//函数返回：函数执行执行状态：0=正常；1=异常。
//参数说明：sect：目标扇区号（范围取决于实际芯片，例如 STM32L433:0~127,每扇区2KB;
//功能概要：擦除flash存储器的sect扇区
//======================================================================
uint8_t flash_erase_fast(uint32_t sect)
{
    uint32_t address;
    flash_init();
    address = (uint32_t)(sect*FLASH_PAGE_SIZE + FLASH_ADDR_START);
    //等待之前最后一个flash操作完成
    while((FLASH->STATR & STATR_BSY) != 0U);
    //清闪存即时编程位
    FLASH->CTLR &= ~FLASH_CTLR_PG_set;
    //使能扇区快速擦除
    FLASH->CTLR |= FLASH_CTLR_PAGE_SET;
    //设置擦除扇区
    FLASH->ADDR = address;
    //开始扇区擦除
    FLASH->CTLR |= FLASH_CTLR_START;
    //等待擦出完成
    while((FLASH->STATR & STATR_BSY) != 0U);
    //禁止扇区擦除
    FLASH->CTLR &= ~FLASH_CTLR_PAGE_ER;
    return 0;  //成功返回
}

//======================================================================
//函数名称：flash_write
//函数返回：函数执行状态：0=正常；1=异常。
//参数说明：sect：扇区号（范围取决于实际芯片，例如 STM32L433:0~127,每扇区2KB）
//        offset:写入扇区内部偏移地址（0~2044，要求为0,4,8,12，......）
//        N：写入字节数目（4~2048,要求为4,8,12,......）
//        buf：源数据缓冲区首地址
//功能概要：将buf开始的N字节写入到flash存储器的sect扇区的 offset处
//=======================================================================
uint8_t flash_write(uint16_t sect, uint16_t offset, uint16_t N,uint8_t *buf)
{
    uint8_t i;

    //写入字节数后会跨扇区
    if(offset+N>MCU_SECTORSIZE)
    {
        //先写入第一个扇区
        flash_write(sect,offset,MCU_SECTORSIZE-offset,buf);
        //再写入第二个扇区
        flash_write(sect+1,0,N-(MCU_SECTORSIZE-offset),buf+(MCU_SECTORSIZE-offset));
    }
    //写入字节数不会跨扇区
    else
    {
        //如果前后地址都是32位对齐，直接写入
        if(offset%4==0&&N%4==0)
        {
            flash_Best(sect,offset,N,buf);
        }
        //前后地址只要有一个不对齐
        else
        {
            uint8_t data[MCU_SECTORSIZE]; //存储当前扇区的全部值
            flash_read_logic(data,sect,0,MCU_SECTORSIZE); //将当前扇区的全部值读入数组中
            //将要写入的数据依照对应位置写入数组中
            for(i = 0;i<N;i++)
            {
                data[offset+i] = buf[i];
            }
            //擦除扇区
            flash_erase(sect);
            //将数组写入扇区
            flash_Best(sect,0,MCU_SECTORSIZE,data);
        }
    }
    return 0;  //成功执行
}


uint8_t flash_test(uint16_t addr, uint16_t offset,uint16_t N, uint8_t* buf)
{
    uint8_t i = 0;
    uint32_t address;

    address = (uint32_t)(addr*128+0x08000000 + offset);

    FLASH->KEYR = FLASH_KEY1;
    FLASH->KEYR = FLASH_KEY2;

        while(i < N)
       {
            while((FLASH->STATR & FLASH_STATR_BSY) != 0U);
            FLASH->CTLR |= FLASH_CTLR_PG_set;
           *(__IO uint16_t*)address = (buf[i]|(buf[i+1]<<8));
           while((FLASH->STATR & FLASH_STATR_BSY) != 0U);
           FLASH->CTLR &= ((uint32_t)0x00001FFE) ;
           *(__IO uint32_t*)0x40022034 = *(__IO uint32_t*)((address & 0xFFFFFFFC) ^ 0x00001000);
          i=i+2;
          address = address + 2;
       }

//    FLASH_Lock();
    FLASH->CTLR |= (uint32_t)FLASH_CTLR_LOCK;

    return 0;
}

//==========================================================================
//函数名称：flash_write_physical
//函数返回：函数执行状态：0=正常；非0=异常。
//参数说明： addr：目标地址，要求为4的倍数且大于Flash首地址
//              （例如：0x08000004，Flash首地址为0x08000000）
//       N：写入字节数目（8~512）
//       buf：源数据缓冲区首地址
//功能概要：flash写入操作
//==========================================================================
uint8_t flash_write_physical(uint32_t addr,uint16_t N,uint8_t buf[])
{
    //（1）定义变量。sect-扇区号，offset-扇区地址
    uint16_t sect;   //扇区号
    uint16_t offset;    // 偏移地址

    //（2）变量赋值，将物理地址转换为逻辑地址（扇区和偏移量）
    sect = (addr-MCU_FLASH_ADDR_START)/MCU_SECTORSIZE;
    offset = addr-(sect*MCU_SECTORSIZE)-MCU_FLASH_ADDR_START;
    //（3）调用写入函数写入数据
    flash_write(sect,offset,N,buf);
    //（4）等待写入操作完成
    while( (FLASH->STATR & STATR_BSY) != 0U);
    return 0;  //成功执行
}

//======================================================================
//函数名称：flash_read_logic
//函数返回：无
//参数说明：dest：读出数据存放处（传地址，目的是带出所读数据，RAM区）
//       sect：扇区号（范围取决于实际芯片，例如 CH32V103R8T6:0~512,每扇区128B）
//       offset:扇区内部偏移地址（0~2024，要求为0,4,8,12，......）
//       N：读字节数目（4~2048,要求为4,8,12,......）//
//功能概要：读取flash存储器的sect扇区的 offset处开始的N字节，到RAM区dest处
//=======================================================================
void flash_read_logic(uint8_t *dest,uint16_t sect,uint16_t offset,uint16_t N)
{
    uint8_t *src;
    src = (uint8_t *)(FLASH_BASE + ((uint32_t)(sect*FLASH_PAGE_SIZE)) + offset);
    memcpy(dest,src,N);
}

//======================================================================
//函数名称：flash_read
//函数返回：无
//参数说明：dest：读出数据存放处（传地址，目的是带出所读数据，RAM区）
//       sect：扇区号（范围取决于实际芯片，例如 CH32V103R8T6:0~512,每扇区128B）
//       offset:扇区内部偏移地址（0~2024，要求为0,4,8,12，......）
//       N：读字节数目（4~2048,要求为4,8,12,......）//
//功能概要：读取flash存储器的sect扇区的 offset处开始的N字节，到RAM区dest处
//=======================================================================
void flash_read(uint8_t* Buffer,uint16_t sect,uint16_t offset,uint32_t N)
{
    uint32_t i, Length = ( N + 3 ) >> 2;
    uint32_t* pCode = ( uint32_t* ) (sect * FLASH_PAGE_SIZE + offset + FLASH_BASE);
    uint32_t* pBuf = ( uint32_t* ) Buffer;

    for ( i = 0; i < Length; i++ )
    {
      *pBuf++ = *pCode++;
    }
}

//======================================================================
//函数名称：flash_read_physical
//函数返回：无
//参数说明：dest：读出数据存放处（传地址，目的是带出所读数据，RAM区）
//       addr：目标地址，要求为4的倍数（例如：0x00000004）
//       N：读字节数目（0~1020,要求为4，8,12,......）
//功能概要：读取flash指定地址的内容
//======================================================================
void flash_read_physical(uint8_t *dest,uint32_t addr,uint16_t N)
{

    uint8_t *src;
    src=(uint8_t *)addr;
    memcpy(dest,src,N);
}

//======================================================================
//函数名称：flash_protect
//函数返回：无
//参数说明：M：(0---511)待保护区域的扇区号入口值，实际保护所有扇区
//功能概要：flash保护操作
//======================================================================
uint8_t flash_protect(void)
{
    //因为在配置寄存器中LOCK位为写1，使FPEC 和 FLASH_CTLR 被锁住不可写，所以要进行解除密钥lock
    if((FLASH->CTLR | FLASH_CTLR_OPTWRE) !=0U)
    {
        //配置选项密钥寄存器
        FLASH->OBKEYR = FLASH_KEY1;
        FLASH->OBKEYR = FLASH_KEY2;
        
        //等待操作完成
        while( (FLASH->STATR & STATR_BSY) != 0U);

        FLASH->CTLR |= FLASH_CTLR_OBPG;
    //配置相关寄存器


        OB->WRPR0 = 0x007F;
    }

    FLASH->KEYR = FLASH_KEY1;
    FLASH->KEYR = FLASH_KEY2;

    if((FLASH->WPR) == FLASH_WPR_WRP)
        return 1;

    return 0;
}

//======================================================================
//函数名称：flash_unprotect
//函数返回：无
//参数说明：M：待保护区域的扇区号入口值，实际保护所有扇区
//功能概要：flash解保护操作
//说   明：
//======================================================================
void flash_unprotect(uint32_t M)
{
    uint32_t temp;

    temp = FLASH_WPR_WRP;

    //如果选项锁定操作完成，则进行选项密钥寄存器配置
    if((FLASH->CTLR & FLASH_CTLR_LOCK) != 0U)
    {
        //配置选项密钥寄存器
        FLASH->OBKEYR = FLASH_KEY1;
        FLASH->OBKEYR = FLASH_KEY2;
    }
    while( (FLASH->STATR & FLASH_STATR_BSY) != 0U);
    //配置相关寄存器
    FLASH->WPR &= 0x0;
    FLASH->WPR |= temp;
    FLASH->CTLR |= FLASH_CTLR_OBPG;
    while( (FLASH->STATR & FLASH_STATR_BSY) != 0U);
    FLASH->CTLR &= ~FLASH_CTLR_OBPG;
}

//========================================================================
//函数名称：flashCtl_isSectorProtected
//函数返回：1=扇区被保护；0=扇区未被保护
//参数说明：所要检测的扇区
//功能概要：判断flash扇区是否被保护
//=========================================================================
uint8_t flash_isSectorProtected(void)
{

    uint32_t temp;
    temp = (uint32_t)(FLASH->WPR);

    if(temp != FLASH_WPR_WRP)
    {
        return 1;
    }
    else
        return 0;
}

//========================================================================
//函数名称：flash_isempty
//函数返回：1=目标区域为空；0=目标区域非空。
//参数说明：所要探测的flash区域扇区号及字节数
//功能概要：flash判空操作
//========================================================================
uint8_t flash_isempty(uint16_t sect, uint16_t N)
{
    uint16_t i,flag;
    uint32_t* buff;

    flag = 1;
    for(i = 0; i<N; i++)   //遍历区域内字节
    {
        buff=(uint32_t*)(sect*FLASH_PAGE_SIZE + FLASH_ADDR_START );

        if(buff[i]!=0xFFFFFFFF)   //非空
        {
            return flag=0;
            break;
        }
    }
    return flag;
}

//==========================================================================
//函数名称：flash_write_physical_fast
//函数返回：函数执行状态：0=正常；非0=异常。
//参数说明： addr：目标地址，要求为4的倍数且大于Flash首地址
//              （例如：0x08000004，Flash首地址为0x08000000）
//       N：写入字节数目（8~512）
//       buf：源数据缓冲区首地址
//功能概要：flash写入操作
//==========================================================================
uint8_t flash_write_physical_fast(uint32_t Addr,uint16_t N, uint8_t *buf)
{
    uint8_t i, flag=0;
    uint32_t address, addr;
    uint32_t data_0,data_1,data_2,data_3;

    address=Addr;

    flash_init();
    /* 闪存缓冲区负载 */
    FLASH_bufreset();
    addr = address;

    for(i=0;i<N;i+=16)
    {
        data_0  = (buf[i]    | buf[i+1]<<8  | buf[i+2]<<16  | buf[i+3] << 24);
        data_1 = (buf[i+4]  | buf[i+5]<<8  | buf[i+6]<<16  | buf[i+7] << 24);
        data_2  = (buf[i+8]  | buf[i+9]<<8  | buf[i+10]<<16 | buf[i+11] << 24);
        data_3 = (buf[i+12] | buf[i+13]<<8 | buf[i+14]<<16 | buf[i+15] << 24);
        flash_write_Word(addr + (uint32_t)i,data_0,data_1,data_2,data_3);
        addr= addr+0x10;
    }
    flash_Program_fast(address);

    FLASH->CTLR |= FLASH_CTLR_LOCK_set;

    for(i=0;i<N;i++)
    {
        if(buf[i] == *(uint32_t*)(address + i))
        {
            flag = 0;
        }
        else
            flag = 1;
            break;
    }
    return flag;

}

//==========================================================================
//函数名称：flash_write_physical_halbit
//函数返回：函数执行状态：0=正常；非0=异常。
//参数说明： Addr：目标地址，要求为4的倍数且大于Flash首地址
//              （例如：0x08000004，Flash首地址为0x08000000）
//       N：写入字节数目（8~512）
//       buf：源数据缓冲区首地址
//功能概要：flash写入操作
//==========================================================================
uint8_t flash_write_physical_halbit(uint32_t Addr,uint16_t N, uint8_t buf[])
{
    uint8_t i, flag=0;
    uint32_t address;
    uint8_t * data;

    data=(uint8_t*)buf;

    FLASH->KEYR = FLASH_KEY1;
    FLASH->KEYR = FLASH_KEY2;

    address = Addr;

    if((address>=FLASH_ADDR_START)&&(address<FLASH_ADDR_END))
    {
        for(i=0;i<N;i++)
        {
            FLASH->CTLR |= FLASH_CTLR_PG_set;
            *(__IO uint16_t*)address = (uint16_t)(data[i]);
            FLASH->CTLR &= 0x00001FFE;
            *(__IO uint32_t*)0x40022034 = *(__IO uint32_t*)((address & 0xFFFFFFFC) ^ 0x00001000);
            address = address + 0x02;
        }
    }
    for(i=0;i<N;i++)
    {
        if((*(__IO uint16_t*) Addr) != data[i])
        {
            flag = 1;
            break;
        }
        Addr += 2;
    }
    return flag;
}

/* ***********************************内部函数************************************** */
//======================================================================
//函数名称：flash_Best
//函数返回：0-成功 1-失败
//参数说明：sect:待写入扇区号
//            offset:待写入数据位置的偏移地址
//            N：待写入数据字节数
//            buf:待写入数据的首地址
//功能概要：首位地址都对齐的情况下的数据写入
//======================================================================
uint8_t flash_Best(uint16_t sect,uint16_t offset,uint16_t N,uint8_t *buf)
{
    uint32_t temp;
    uint32_t addr;
    uint16_t i;
    addr = (uint32_t)(sect * FLASH_PAGE_SIZE + FLASH_ADDR_START + offset);

    FLASH->CTLR |= FLASH_CTLR_FTPG_PG;
    while(FLASH->STATR & STATR_BSY);
    while(FLASH->STATR & STATR_SW_BSY);

    for(i = 0; i < N; i+=4)
    {
      //低位字赋值
      temp = (uint32_t)((buf[i])|(buf[i+1]<<8)|(buf[i+2]<<16)|(buf[i+3]<<24));
      //在绝对地址(addr+i)，实现双字写入
      *(vuint32_t*)addr = temp;
      addr += 4;
      while (FLASH->STATR & STATR_SW_BSY);
    }

    FLASH->CTLR |= FLASH_CTLR_PG_STRT;
    while(FLASH->STATR & STATR_BSY);
    FLASH->CTLR &= ~FLASH_CTLR_FTPG_PG;

    return 0;
}

//======================================================================
//函数名称：flash_write_Word
//函数返回：0-成功 1-失败
//参数说明：addr：目标地址，要求为4的倍数且大于Flash首地址
//              （例如：0x08000004，Flash首地址为0x08000000）
//       data：写入的双字
//功能概要：Flash双字写入操作（STM32L433每次只能实现双字写入，先写低位字，再写高位字）
//======================================================================
void flash_write_Word(uint32_t addr, uint32_t data_0, uint32_t data_1,uint32_t data_2,uint32_t data_3)
{

    //清数据缓冲区
    if((FLASH->ACTLR & FLASH_ACTLR_PRFTBE) != 0U)
    {
        FLASH->ACTLR &= ~FLASH_ACTLR_PRFTBE;
    }
    //使能Flash即时编程
    FLASH->CTLR |= FLASH_CTLR_FTPG_PG;

    //写入数据
    *(__IO uint32_t*)(addr+0x00) = data_0;
    *(__IO uint32_t*)(addr+0x04) = data_1;
    *(__IO uint32_t*)(addr+0x08) = data_2;
    *(__IO uint32_t*)(addr+0x0C) = data_3;

    //执行数据加载到内部缓冲区
    FLASH->CTLR |= FLASH_CTLR_BUFLOAD;

    while( (FLASH->STATR & STATR_BSY) != 0U);       //------------20210617 会在这里卡死

    //禁止Flash即时编程
    FLASH->CTLR &= ~FLASH_CTLR_FTPG_PG;

}


//======================================================================
//函数名称：flash_write_one
//函数返回：0-成功 1-失败
//参数说明：addr：目标地址，要求为4的倍数且大于Flash首地址
//              （例如：0x08000004，Flash首地址为0x08000000）
//       data：写入的1字
//功能概要：Flash双字写入操作（STM32L433每次只能实现双字写入，先写低位字，再写高位字）
//======================================================================
uint8_t flash_write_one(uint32_t addr,uint32_t data_l)
{
    //清数据缓冲区
    if((FLASH->ACTLR & FLASH_ACTLR_PRFTBE) != 0U)
    {
        FLASH->ACTLR &= ~FLASH_ACTLR_PRFTBE;
    }

    //使能Flash即时编程
    FLASH->CTLR |= FLASH_CTLR_PG_set;
    //先写入低位字
    *(__IO uint16_t*)addr = data_l;

    //执行数据加载到内部缓冲区
    FLASH->CTLR |= FLASH_CTLR_BUFLOAD;

    while( (FLASH->STATR & STATR_BSY) != 0U);

    //禁止Flash即时编程
    FLASH->CTLR &= ((uint32_t)0x00001FFE);

    return 0;    //返回成功
}

//======================================================================
//函数名称：FLASH_bufreset
//参数说明：对快速写入时执行清除内部 128 字节缓存区操作
//功能概要：Flash进行16字节写入时，执行清除内部 128 字节缓存区操作
//======================================================================
void FLASH_bufreset(void)
{
    FLASH->CTLR |= FLASH_CTLR_FTPG_PG;
    FLASH->CTLR |= FLASH_CTLR_BUF_rst;
    while( (FLASH->STATR & STATR_BSY) != 0U);
    FLASH->CTLR &= ~FLASH_CTLR_FTPG_PG;
}

//======================================================================
//函数名称：flash_write_fast
//函数返回：函数执行状态：0=正常；1=异常。
//参数说明：sect：扇区号（范围取决于实际芯片，例如 STM32L433:0~127,每扇区2KB）
//        offset:写入扇区内部偏移地址（0~2044，要求为0,4,8,12，......）
//        N：写入字节数目（4~2048,要求为4,8,12,......）
//        buf：源数据缓冲区首地址
//功能概要：将buf开始的N字节写入到flash存储器的sect扇区的 offset处
//=======================================================================
uint8_t flash_write_fast(uint32_t sect,uint32_t N, uint8_t *buf)
{
    uint8_t i, flag=0;
    uint32_t address, addr;
    uint32_t data_L;
    uint32_t data_LL,data_H,data_HH;
    address = (uint32_t)(sect * FLASH_PAGE_SIZE + FLASH_ADDR_START);

    /* 闪存缓冲区负载 */
    flash_init();
    FLASH_bufreset();
    addr = address;

    for(i=0;i<N;i+=16)
    {
        data_L  = (buf[i]    | buf[i+1]<<8  | buf[i+2]<<16  | buf[i+3] << 24);
        data_LL = (buf[i+4]  | buf[i+5]<<8  | buf[i+6]<<16  | buf[i+7] << 24);
        data_H  = (buf[i+8]  | buf[i+9]<<8  | buf[i+10]<<16 | buf[i+11] << 24);
        data_HH = (buf[i+12] | buf[i+13]<<8 | buf[i+14]<<16 | buf[i+15] << 24);
        flash_write_Word(addr + (uint32_t)i,data_L,data_LL,data_H,data_HH);
    }

    flash_Program_fast(address);

    FLASH->CTLR |= FLASH_CTLR_LOCK_set;

    for(i=0;i<N;i++)
    {
        if(buf[i] == *(uint32_t*)(address + i))
        {
            flag = 0;
        }
        else
            flag = 1;
            break;
    }
    return flag;

}

//======================================================================
//函数名称：flash_Program_fast
//参数说明：address
//功能概要：声名快速写入的起始地址
//=======================================================================
void flash_Program_fast(uint32_t address)
{
    if((address>=FLASH_ADDR_START) && (address<FLASH_ADDR_END))
    {
        FLASH->CTLR |= FLASH_CTLR_FTPG_PG;
        FLASH->ADDR = address;
        FLASH->CTLR |= FLASH_CTLR_START;
        while((FLASH->STATR & STATR_BSY) != 0U);
        FLASH->CTLR &= ~FLASH_CTLR_FTPG_PG;
    }
}






