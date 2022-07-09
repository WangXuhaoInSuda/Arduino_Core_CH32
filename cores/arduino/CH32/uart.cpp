//======================================================================
//文件名称：uart.c
//功能概要：uart底层驱动构件源文件
//版权所有：苏州大学嵌入式系统与物联网研究所(sumcu.suda.edu.cn)
//更新记录：2020-0918 V1.0 GXY
//         2022-0124    修改串口引脚初始化
//======================================================================

#include "uart.h"

#ifdef __cplusplus
extern "C" {

#endif

USART_TypeDef *USART_ARR[] =  {(USART_TypeDef*)USART1_BASE, (USART_TypeDef*)USART2_BASE, (USART_TypeDef*)USART3_BASE,
        (USART_TypeDef*)UART4_BASE,(USART_TypeDef*)UART5_BASE,(USART_TypeDef*)UART6_BASE,(USART_TypeDef*)UART7_BASE,
        (USART_TypeDef*)UART8_BASE,};

//====定义串口IRQ号对应表====
IRQn_Type table_irq_uart[8] = {USART1_IRQn, USART2_IRQn, USART3_IRQn,UART4_IRQn,UART5_IRQn,UART6_IRQn,UART7_IRQn,UART8_IRQn};


//内部函数声明
uint8_t uart_is_uartNo(uint8_t uartNo);


//======================================================================
//函数名称：uart_init
//功能概要：初始化uart模块
//参数说明：uartNo:串口号：UART_1、UART_2、UART_3
//          baud:波特率：300、600、1200、2400、4800、9600、19200、115200...
//函数返回：无
//======================================================================
void uart_init(uint8_t uartNo, uint32_t baud_rate)
{
    uint16_t  DIV_M,DIV_F; //BRR寄存器应赋的值

    //判断传入串口号参数是否有误,有误直接退出
    if(!uart_is_uartNo(uartNo))
    {
        return;
    }

    //开启UART模块和GPIO模块的外围时钟，并使能引脚的UART功能
    switch(uartNo)
    {
    case UART_1:  //若为串口1
#ifdef UART1_GROUP
        //依据选择使能对应时钟，并配置对应引脚为UART_1
        switch(UART1_GROUP)
        {
        case 0:
            //使能USART1和GPIOA时钟
            RCC->APB2PCENR |= RCC_USART1EN;
            RCC->APB2PCENR |= RCC_AFIOEN;
            RCC->APB2PCENR |= RCC_IOPAEN;
            //使能PTA9,PTA10为USART(Tx,Rx)功能
            GPIOA->CFGHR &= ~(GPIO_CFGHR_MODE9|GPIO_CFGHR_CNF9|GPIO_CFGHR_CNF10|GPIO_CFGHR_MODE10);
            GPIOA->CFGHR |= ((GPIO_CFGHR_MODE9_1|GPIO_CFGHR_CNF9_1)|(GPIO_CFGHR_CNF10_1));
            AFIO->PCFR1 |= 0;

            break;
        case 1:
            //使能USART1和GPIOB时钟
            RCC->APB2PCENR |= RCC_USART1EN;
            RCC->APB2PCENR |= RCC_IOPBEN;
            RCC->APB2PCENR |= RCC_AFIOEN;
            //使能PTB6,PTB7为USART(Tx,Rx)功能
            GPIOB->CFGLR &= ~(GPIO_CFGLR_MODE6|GPIO_CFGLR_MODE7|GPIO_CFGLR_CNF6|GPIO_CFGLR_CNF7);
            GPIOB->CFGLR |= ((GPIO_CFGLR_CNF6_1|GPIO_CFGLR_MODE6_1)|GPIO_CFGLR_CNF7_0);
            AFIO->PCFR1 |= AFIO_PCFR1_USART1_REMAP;
            break;
        default:
            break;
        }
#endif
        break;

    case UART_2:  //若为串口2
#ifdef UART2_GROUP
        //依据选择使能对应时钟，并配置对应引脚为UART_2
        switch(UART2_GROUP)
        {
        case 0:
            //使能USART2和GPIOA时钟
            RCC->APB1PCENR |= RCC_USART2EN;
            RCC->APB2PCENR |= RCC_IOPAEN;
            //使能PTA2,PTA3为USART(Tx,Rx)功能
            GPIOA->CFGLR &= ~(GPIO_CFGLR_MODE2|GPIO_CFGLR_MODE3|GPIO_CFGLR_CNF2|GPIO_CFGLR_CNF3);
            GPIOA->CFGLR |= ((GPIO_CFGLR_CNF2_1|GPIO_CFGLR_MODE2)|(GPIO_CFGLR_CNF3_0));
            break;
        case 1:
            //使能USART1和GPIOB时钟
            RCC->APB2PCENR |= RCC_USART2EN;
            RCC->APB2PCENR |= RCC_IOPDEN;
            RCC->APB2PCENR |= RCC_AFIOEN;
            //使能PTD5,PTD6为USART(Tx,Rx)功能
            GPIOD->CFGLR &= ~(GPIO_CFGLR_MODE5|GPIO_CFGLR_MODE6|GPIO_CFGLR_CNF5|GPIO_CFGLR_CNF6);
            GPIOD->CFGLR |= ((GPIO_CFGLR_CNF5_1|GPIO_CFGLR_MODE5_1)|GPIO_CFGLR_CNF6_0);
            AFIO->PCFR1 |= AFIO_PCFR1_USART2_REMAP;

            break;
        default:
            break;
        }
#endif
        break;

    case UART_3:  //若为串口3
#ifdef UART3_GROUP
        //依据选择使能对应时钟，并配置对应引脚为UART_3
        switch(UART3_GROUP)
        {
        case 0:
            //使能USART3和GPIOB时钟
            RCC->APB1PCENR |= RCC_USART3EN;
            RCC->APB2PCENR |= RCC_IOPBEN;
            //使能PTB10,PTB11为USART(Tx,Rx)功能
            GPIOB->CFGHR &= ~(GPIO_CFGHR_MODE10|GPIO_CFGHR_MODE11|GPIO_CFGHR_CNF10|GPIO_CFGHR_CNF11);
            GPIOB->CFGHR |= ((GPIO_CFGHR_CNF10_1|GPIO_CFGHR_MODE10_1)|(GPIO_CFGHR_CNF11_0));
            break;
        case 1:
            //使能USART1和GPIOC时钟
            RCC->APB1PCENR |= RCC_USART3EN;
            RCC->APB2PCENR |= RCC_IOPCEN;
            RCC->APB2PCENR |= RCC_AFIOEN;
            //使能PTC10,P11为USART(Tx,Rx)功能
            GPIOC->CFGHR &= ~(GPIO_CFGHR_MODE10|GPIO_CFGHR_MODE11|GPIO_CFGHR_CNF10|GPIO_CFGHR_CNF11);
            GPIOC->CFGHR |= ((GPIO_CFGHR_CNF10_1|GPIO_CFGHR_MODE10_1)|(GPIO_CFGHR_CNF11_0));
            AFIO->PCFR1 |= (AFIO_PCFR1_USART3_REMAP_0);

            break;
        default:
            break;
        }
#endif
        break;

    case UART_4:  //若为串口4
#ifdef UART4_GROUP
        //依据选择使能对应时钟，并配置对应引脚为UART_3
        switch(UART4_GROUP)
        {
        case 0:
            //使能UART4和GPIOC时钟
            RCC->APB1PCENR |= RCC_UART4EN;
            RCC->APB2PCENR |= RCC_IOPCEN;
            //使能PTC10,PTC11为UART4(Tx,Rx)功能
            GPIOC->CFGHR &= ~(GPIO_CFGHR_MODE10|GPIO_CFGHR_MODE11|GPIO_CFGHR_CNF10|GPIO_CFGHR_CNF11);
            GPIOC->CFGHR |= ((GPIO_CFGHR_CNF10_1|GPIO_CFGHR_MODE10_1)|(GPIO_CFGHR_CNF11_0));
            break;
        case 1:
            //使能UART4和GPIOB时钟
            RCC->APB1PCENR |= RCC_UART4EN;
            RCC->APB2PCENR |= RCC_IOPBEN;
            RCC->APB2PCENR |= RCC_AFIOEN;
            //使能PTB0,PTB1为USART(Tx,Rx)功能
            GPIOB->CFGLR &= ~(GPIO_CFGLR_MODE0|GPIO_CFGLR_MODE1|GPIO_CFGLR_CNF0|GPIO_CFGLR_CNF1);
            GPIOB->CFGLR |= ((GPIO_CFGLR_CNF0_1|GPIO_CFGLR_MODE0_1)|(GPIO_CFGLR_CNF1_0));
            AFIO->PCFR2 |= ((uint32_t)0x00010000);

            break;
        case 2:
            //使能UART4和GPIOE时钟
            RCC->APB1PCENR |= RCC_UART4EN;
            RCC->APB2PCENR |= RCC_IOPEEN;
            RCC->APB2PCENR |= RCC_AFIOEN;
            //使能PTE0,PTE1为USART(Tx,Rx)功能
            GPIOE->CFGLR &= ~(GPIO_CFGLR_MODE0|GPIO_CFGLR_MODE1|GPIO_CFGLR_CNF0|GPIO_CFGLR_CNF1);
            GPIOE->CFGLR |= ((GPIO_CFGLR_CNF0_1|GPIO_CFGLR_MODE0_1)|(GPIO_CFGLR_CNF1_0));
            AFIO->PCFR2 |= ((uint32_t)0x00020000);

            break;
        default:
            break;
        }
#endif
        break;

    case UART_5:  //若为串口5
#ifdef UART5_GROUP
        //依据选择使能对应时钟，并配置对应引脚为UART_5
        switch(UART5_GROUP)
        {
        case 0:
            //使能UART5和GPIOC，GPIOD时钟
            RCC->APB1PCENR |= RCC_UART5EN;
            RCC->APB2PCENR |= RCC_IOPCEN;
            RCC->APB2PCENR |= RCC_IOPDEN;
            //使能PTC12,PTD2为UART4(Tx,Rx)功能
            GPIOC->CFGHR &= ~(GPIO_CFGHR_MODE12|GPIO_CFGHR_CNF12);
            GPIOD->CFGLR &= ~(GPIO_CFGLR_MODE2|GPIO_CFGLR_CNF2);
            GPIOC->CFGHR |= ((GPIO_CFGHR_CNF12_1|GPIO_CFGHR_MODE12_1));
            GPIOD->CFGLR |= (GPIO_CFGLR_CNF2_1);
            break;
        case 1:
            //使能UART5和GPIOB时钟
            RCC->APB1PCENR |= RCC_UART5EN;
            RCC->APB2PCENR |= RCC_IOPBEN;
            RCC->APB2PCENR |= RCC_AFIOEN;
            //使能PTB4,PTB5为USART(Tx,Rx)功能
            GPIOB->CFGLR &= ~(GPIO_CFGLR_MODE4|GPIO_CFGLR_MODE5|GPIO_CFGLR_CNF4|GPIO_CFGLR_CNF5);
            GPIOB->CFGLR |= ((GPIO_CFGLR_CNF4_1|GPIO_CFGLR_MODE4_1)|(GPIO_CFGLR_CNF5_1));
            AFIO->PCFR2 |= ((uint32_t)0x00040000);
            break;
        case 2:
            //使能UART5和GPIOE时钟
            RCC->APB1PCENR |= RCC_UART5EN;
            RCC->APB2PCENR |= RCC_IOPEEN;
            RCC->APB2PCENR |= RCC_AFIOEN;
            //使能PTE8,PTE9为USART(Tx,Rx)功能
            GPIOE->CFGHR &= ~(GPIO_CFGHR_MODE8|GPIO_CFGHR_MODE9|GPIO_CFGHR_CNF8|GPIO_CFGHR_CNF9);
            GPIOE->CFGHR |= ((GPIO_CFGHR_CNF8_1|GPIO_CFGHR_MODE8_1)|(GPIO_CFGHR_CNF9_0));
            AFIO->PCFR2 |= ((uint32_t)0x00080000);
            break;
        default:
            break;
        }
#endif
        break;
    case UART_6:  //若为串口6
#ifdef UART6_GROUP
        //依据选择使能对应时钟，并配置对应引脚为UART_6
        switch(UART6_GROUP)
        {
        case 0:
            //使能UART6和GPIOC时钟
            RCC->APB1PCENR |= RCC_UART6EN;
            RCC->APB2PCENR |= RCC_IOPCEN;
            //使能PTC0,PTC1为USART(Tx,Rx)功能
            GPIOC->CFGLR &= ~(GPIO_CFGLR_MODE0|GPIO_CFGLR_MODE1|GPIO_CFGLR_CNF0|GPIO_CFGLR_CNF1);
            GPIOC->CFGLR |= ((GPIO_CFGLR_CNF0_1|GPIO_CFGLR_MODE0_1)|(GPIO_CFGLR_CNF1_0));
            break;
        case 1:
            //使能UART6和GPIOB时钟
            RCC->APB1PCENR |= RCC_UART6EN;
            RCC->APB2PCENR |= RCC_IOPBEN;
            RCC->APB2PCENR |= RCC_AFIOEN;
            //使能PTB8,PTB9为USART(Tx,Rx)功能
            GPIOB->CFGHR &= ~(GPIO_CFGHR_MODE8|GPIO_CFGHR_MODE9|GPIO_CFGHR_CNF8|GPIO_CFGHR_CNF9);
            GPIOB->CFGHR |= ((GPIO_CFGHR_CNF8_1|GPIO_CFGHR_MODE8_1)|(GPIO_CFGHR_CNF9_0));
            AFIO->PCFR2 |= ((uint32_t)0x00100000);
            break;
        case 2:
            //使能UART6和GPIOE时钟
            RCC->APB1PCENR |= RCC_UART6EN;
            RCC->APB2PCENR |= RCC_IOPEEN;
            RCC->APB2PCENR |= RCC_AFIOEN;
            //使能PTE10,PTE11为USART(Tx,Rx)功能
            GPIOE->CFGHR &= ~(GPIO_CFGHR_MODE10|GPIO_CFGHR_MODE11|GPIO_CFGHR_CNF10|GPIO_CFGHR_CNF11);
            GPIOE->CFGHR |= ((GPIO_CFGHR_CNF10_1|GPIO_CFGHR_MODE10_1)|(GPIO_CFGHR_CNF11_0));
            AFIO->PCFR2 |= ((uint32_t)0x00200000);
            break;
        default:
            break;
        }
#endif
        break;

    case UART_7:  //若为串口7
#ifdef UART7_GROUP
      //依据选择使能对应时钟，并配置对应引脚为UART_7
      switch(UART7_GROUP)
      {
      case 0:
          //使能UART7和GPIOC时钟
          RCC->APB1PCENR |= RCC_UART7EN;
          RCC->APB2PCENR |= RCC_IOPCEN;
          //使能PTC2,PTC3为USART(Tx,Rx)功能
          GPIOC->CFGLR &= ~(GPIO_CFGLR_MODE2|GPIO_CFGLR_MODE3|GPIO_CFGLR_CNF2|GPIO_CFGLR_CNF3);
          GPIOC->CFGLR |= ((GPIO_CFGLR_CNF2_1|GPIO_CFGLR_MODE2_1)|(GPIO_CFGLR_CNF3_0));
          break;
      case 1:
          //使能UART7和GPIOA时钟
          RCC->APB1PCENR |= RCC_UART7EN;
          RCC->APB2PCENR |= RCC_IOPAEN;
          RCC->APB2PCENR |= RCC_AFIOEN;
          //使能PTA6,PTA7为USART(Tx,Rx)功能
          GPIOA->CFGLR &= ~(GPIO_CFGLR_MODE6|GPIO_CFGLR_MODE7|GPIO_CFGLR_CNF6|GPIO_CFGLR_CNF7);
          GPIOA->CFGLR |= ((GPIO_CFGLR_CNF6_1|GPIO_CFGLR_MODE6_1)|(GPIO_CFGLR_CNF7_0));
          AFIO->PCFR2 |= ((uint32_t)0x00400000);
          break;
      case 2:
          //使能UART7和GPIOE时钟
          RCC->APB1PCENR |= RCC_UART7EN;
          RCC->APB2PCENR |= RCC_IOPEEN;
          RCC->APB2PCENR |= RCC_AFIOEN;
          //使能PTE12,PTE13为USART(Tx,Rx)功能
          GPIOE->CFGHR &= ~(GPIO_CFGHR_MODE12|GPIO_CFGHR_MODE13|GPIO_CFGHR_CNF12|GPIO_CFGHR_CNF13);
          GPIOE->CFGHR |= ((GPIO_CFGHR_CNF12_1|GPIO_CFGHR_MODE12_1)|(GPIO_CFGHR_CNF13_0));
          AFIO->PCFR2 |= ((uint32_t)0x00800000);
          break;
      default:
          break;
      }
#endif
      break;

    case UART_8:  //若为串口8
#ifdef UART8_GROUP
        //依据选择使能对应时钟，并配置对应引脚为UART_8
        switch(UART8_GROUP)
        {
        case 0:
            //使能UART8和GPIOC时钟
            RCC->APB1PCENR |= RCC_UART8EN;
            RCC->APB2PCENR |= RCC_IOPCEN;
            //使能PTC4,PTC5为USART(Tx,Rx)功能
            GPIOC->CFGLR &= ~(GPIO_CFGLR_MODE4|GPIO_CFGLR_MODE5|GPIO_CFGLR_CNF4|GPIO_CFGLR_CNF5);
            GPIOC->CFGLR |= ((GPIO_CFGLR_CNF4_1|GPIO_CFGLR_MODE4_1)|(GPIO_CFGLR_CNF5_0));
            break;
        case 1:
            //使能UART8和GPIOA时钟
            RCC->APB1PCENR |= RCC_UART8EN;
            RCC->APB2PCENR |= RCC_IOPAEN;
            RCC->APB2PCENR |= RCC_AFIOEN;
            //使能PTA14,PTA15为USART(Tx,Rx)功能
            GPIOA->CFGHR &= ~(GPIO_CFGHR_MODE14|GPIO_CFGHR_MODE15|GPIO_CFGHR_CNF14|GPIO_CFGHR_CNF15);
            GPIOA->CFGHR |= ((GPIO_CFGHR_CNF14_1|GPIO_CFGHR_MODE14_1)|(GPIO_CFGHR_CNF15_0));
            AFIO->PCFR2 |= ((uint32_t)0x01000000);
            break;
        case 2:
            //使能UART8和GPIOE时钟
            RCC->APB1PCENR |= RCC_UART8EN;
            RCC->APB2PCENR |= RCC_IOPEEN;
            RCC->APB2PCENR |= RCC_AFIOEN;
            //使能PTE14,PTE15为USART(Tx,Rx)功能
            GPIOE->CFGHR &= ~(GPIO_CFGHR_MODE14|GPIO_CFGHR_MODE15|GPIO_CFGHR_CNF14|GPIO_CFGHR_CNF15);
            GPIOE->CFGHR |= ((GPIO_CFGHR_CNF14_1|GPIO_CFGHR_MODE14_1)|(GPIO_CFGHR_CNF15_0));
            AFIO->PCFR2 |= ((uint32_t)0x02000000);
            break;
        default:
            break;
        }
#endif
    break;

    }
    //暂时禁用UART功能
    USART_ARR[uartNo-1]->CTLR1 &= ~USART_CTLR1_UE;
    //暂时关闭串口发送与接收功能
    USART_ARR[uartNo-1]->CTLR1 &= ~(USART_CTLR1_TE|USART_CTLR1_RE);
    //配置串口波特率

    if(USART_ARR[uartNo-1]==(USART_TypeDef*)USART1_BASE)
    {
        DIV_M = (uint16_t)(SYSCLK_FREQ_72MHz/(16*baud_rate));
        DIV_F = (uint8_t)(((((((SYSCLK_FREQ_72MHz/16)*100)/baud_rate)%100)*16)+50)/100);
        USART_ARR[uartNo-1]->BRR = (uint16_t)(DIV_M<<4|DIV_F);
    }
    else
    {
        DIV_M = (uint16_t)(SYSCLK_FREQ_72MHz/(16*2*baud_rate));
        DIV_F = (uint8_t)((((((SYSCLK_FREQ_72MHz/2/16)*100)/baud_rate)%100)*16)/100);
        USART_ARR[uartNo-1]->BRR = (uint32_t)(((DIV_M)<<4)|DIV_F);
    }
    //初始化控制寄存器和中断状态寄存器、清标志位
    USART_ARR[uartNo-1]->STATR = 0;
    USART_ARR[uartNo-1]->CTLR2 &= ~(USART_CTLR2_LINEN | USART_CTLR2_CLKEN);
    USART_ARR[uartNo-1]->CTLR3 &= ~(USART_CTLR3_SCEN | USART_CTLR3_HDSEL | USART_CTLR3_IREN);
    //启动串口发送与接收功能
    USART_ARR[uartNo-1]->CTLR1 |= (USART_CTLR1_TE|USART_CTLR1_RE);

    //开启UART功能
    USART_ARR[uartNo-1]->CTLR1 |= USART_CTLR1_UE;

}

//======================================================================
//函数名称：uart_send1
//参数说明：uartNo: 串口号:UART_1、UART_2、UART_3
//          ch:要发送的字节
//函数返回：函数执行状态：1=发送成功；0=发送失败。
//功能概要：串行发送1个字节
//======================================================================
uint8_t uart_send1(uint8_t uartNo, uint8_t ch)
{
    uint32_t t;

    //判断串口号参数是否有误，有误直接退出
    if(!uart_is_uartNo(uartNo))
    {
        return 0;
    }
    for(t = 0; t< 0xFBBB; t++)
    {
        //发送缓冲区为空则发送数据
        if(USART_ARR[uartNo-1]->STATR & USART_STATR_TXE)
        {
            USART_ARR[uartNo-1]->DATAR = (ch & USART_DATAR_DR);
            break;
        }
    }
    if(t >= 0xFBBB)
    {
        return 0; //发送超时，发送失败

    }
    else
        return 1;
}

//======================================================================
//函数名称：uart_sendN
//参数说明：uartNo: 串口号:UART_1、UART_2、UART_3
//         buff: 发送缓冲区
//         len:发送长度
//函数返回： 函数执行状态：1=发送成功；0=发送失败
//功能概要：串行 接收n个字节
//======================================================================
uint8_t uart_sendN(uint8_t uartNo ,uint16_t len ,uint8_t* buff)
{
    uint16_t i;

    //判断串口号参数是否有误，有误直接退出
    if(!uart_is_uartNo(uartNo))
    {
        return 0;
    }
    for(i=0;i<len;i++)
    {
        if(!uart_send1(uartNo, buff[i]))   //发送一个字节数据，失败则跳出循环
        {
            break;
        }
    }
    if(i<len)
    {
        return 0;   //发送出错
    }
    else
        return 1;  //发送成功

}

//======================================================================
//函数名称：uart_send_string
//参数说明：uartNo:UART模块号:UART_1、UART_2、UART_3
//          buff:要发送的字符串的首地址
//函数返回： 函数执行状态：1=发送成功；0=发送失败
//功能概要：从指定UART端口发送一个以'\0'结束的字符串
//======================================================================
uint8_t uart_send_string(uint8_t uartNo, uint8_t* buff)
{
    uint16_t i = 0;
    uint8_t *buff_ptr = (uint8_t *)buff;     //定义指针指向要发送字符串首地址

    //判断传入串口号参数是否有误，有误直接退出
    if(!uart_is_uartNo(uartNo))
    {
        return 0;
    }

    for(i = 0; buff_ptr[i] != '\0'; i++)   //遍历字符串里的字符
    {
        if (!uart_send1(uartNo,buff_ptr[i]))//发送指针对应的字符
            return 0;  //发送失败,返回
    }
    return 1;          //发送成功
}

//======================================================================
//函数名称：uart_re1
//参数说明：uartNo: 串口号:UART_1、UART_2、UART_3
//        *fp:接收成功标志的指针:*fp=1:接收成功；*fp=0:接收失败
//函数返回：接收返回字节
//功能概要：串行接收1个字节
//======================================================================
uint8_t uart_re1(uint8_t uartNo,uint8_t *fp)
{
    uint32_t t;
    uint8_t dat;

    //判断传入串口号参数是否有误，有误直接退出
    if(!uart_is_uartNo(uartNo))
    {
        *fp = 0;
        return 0;
    }

    for(t=0; t< 0xFBBB; t++)
    {
        //判断缓冲区是否满
        if(USART_ARR[uartNo-1]->STATR & USART_STATR_RXNE)
        {
            dat = (USART_ARR[uartNo-1]->DATAR & USART_DATAR_DR); // 获取数据，清接收中断位
            *fp = 1; //接收成功
            break;
        }
    }//结束
    if(t>=0xFBBB)
    {
        dat = 0xFF;
        *fp = 0;
    }

    return dat;

}

//======================================================================
//函数名称：uart_reN
//参数说明：uartNo: 串口号:UART_1、UART_2、UART_3
//          buff: 接收缓冲区
//          len:接收长度
//函数返回：函数执行状态 1=接收成功;0=接收失败
//功能概要：串行 接收n个字节,放入buff中
//======================================================================
uint8_t uart_reN(uint8_t uartNo ,uint16_t len ,uint8_t* buff)
{
    uint16_t i;
    uint8_t flag = 0;

    //判断传入串口号参数是否有误，有误直接退出
    if(!uart_is_uartNo(uartNo))
    {
        return 0;
    }
    //判断是否能接受数据
    for(i=0;i<len && flag == 1;i++)
    {
        buff[i] = uart_re1(uartNo, &flag);  //接收数据

    }
    if(i<len)
    {
        return 0;
    }
    else
        return 1;

}

//======================================================================
//函数名称：uart_enable_re_int
//参数说明：uartNo: 串口号:UART_1、UART_2、UART_3
//函数返回：无
//功能概要：开串口接收中断
//======================================================================
void uart_enable_re_int(uint8_t uartNo)
{
    //判断传入串口号参数是否有误，有误直接退出
    if(!uart_is_uartNo(uartNo))
    {
        return;
    }

    USART_ARR[uartNo-1]->CTLR1 |= USART_CTLR1_RXNEIE;    //开放UART接收中断
//    USART_ARR[uartNo-1]->CTLR1 |= USART_CTLR1_TXEIE;
//    USART_ARR[uartNo-1]->CTLR1 |= ((uint16_t)0x0525);    //开放UART接收中断
    NVIC_EnableIRQ(table_irq_uart[uartNo-1]);            //开中断控制器IRQ中断
    //USART_ARR[uartNo-1]->CTLR1 |= USART_CTLR1_RXNEIE;    //开放UART接收中断
}

//======================================================================
//函数名称：uart_disable_re_int
//参数说明：uartNo: 串口号 :UART_1、UART_2、UART_3
//函数返回：无
//功能概要：关串口接收中断
//======================================================================
void uart_disable_re_int(uint8_t uartNo)
{
    //判断传入串口号参数是否有误，有误直接退出
    if(!uart_is_uartNo(uartNo))
    {
        return;
    }

    USART_ARR[uartNo-1]->CTLR1 &= ~USART_CTLR1_RXNEIE;    //禁止UART接收中断
    NVIC_DisableIRQ(table_irq_uart[uartNo-1]);    //禁止中断控制器IRQ中断
}

//======================================================================
//函数名称：uart_get_re_int
//参数说明：uartNo: 串口号 :UART_1、UART_2、UART_3
//函数返回：接收中断标志 1=有接收中断;0=无接收中断
//功能概要：获取串口接收中断标志,同时禁用发送中断
//======================================================================
uint8_t uart_get_re_int(uint8_t uartNo)
{
    //判断传入串口号参数是否有误，有误直接退出
    if(!uart_is_uartNo(uartNo))
    {
        return 0;
    }

    //获取接收中断标志，需同时判断RXNE和RXNEIE
    if(((USART_ARR[uartNo-1]->STATR & USART_STATR_RXNE) == USART_STATR_RXNE)
       && ((USART_ARR[uartNo-1]->CTLR1 & USART_CTLR1_RXNEIE) == USART_CTLR1_RXNEIE))
        return 1;
    else
        return 0;
}


//======================================================================
//函数名称：uart_deinit
//参数说明：uartNo: 串口号 :UART_1、UART_2、UART_3
//函数返回：无
//功能概要：uart反初始化，关闭串口时钟
//======================================================================
void uart_deinit(uint8_t uartNo)
{
    //判断传入串口号参数是否有误,有误直接退出
    if(!uart_is_uartNo(uartNo))
    {
        return;
    }

    //开启UART模块和GPIO模块的外围时钟，并使能引脚的UART功能
    switch(uartNo)
    {
    case UART_1:  //若为串口1
#ifdef UART1_GROUP
        //依据选择使能对应时钟，并配置对应引脚为UART_1
        switch(UART1_GROUP)
        {
        case 0:
            //使能USART1和GPIOA时钟
            RCC->APB2PCENR &= ~RCC_USART1EN;
            RCC->APB2PCENR &= ~RCC_IOPAEN;
            //使能PTA9,PTA10为USART(Tx,Rx)功能
            GPIOA->CFGHR &= ~(GPIO_CFGHR_MODE9|GPIO_CFGHR_MODE10);
//            AFIO->PCFR1 &= ~(AFIO_PCFR1_USART1_REMAP);
//            AFIO->PCFR1 |= (AFIO_PCFR1_USART1_REMAP);
            break;
        case 1:
            //使能USART1和GPIOB时钟
            RCC->APB2PCENR &= ~RCC_USART1EN;
            RCC->APB2PCENR &= ~RCC_AFIOEN;
            //使能PTB6,PTB7为USART(Tx,Rx)功能
            GPIOB->CFGLR &= ~(GPIO_CFGLR_CNF6_1|GPIO_CFGLR_CNF7_1);
            AFIO->PCFR1 &= ~AFIO_PCFR1_USART1_REMAP;
            break;
        default:
            break;
        }
#endif
        break;

    case UART_2:  //若为串口2
#ifdef UART2_GROUP
        //依据选择使能对应时钟，并配置对应引脚为UART_2
        switch(UART2_GROUP)
        {
        case 0:
            //使能USART2和GPIOA时钟
            RCC->APB1PCENR &= ~RCC_USART2EN;
            RCC->APB2PCENR &= ~RCC_IOPAEN;
            //使能PTA9,PTA10为USART(Tx,Rx)功能
            GPIOA->CFGLR &= ~(GPIO_CFGLR_CNF3|GPIO_CFGLR_CNF2);

            break;
        case 1:
            //使能USART1和GPIOB时钟
            RCC->APB2PCENR &= ~RCC_USART2EN;
            RCC->APB2PCENR &= ~RCC_IOPDEN;
            //使能PTB6,PTB7为USART(Tx,Rx)功能
            GPIOD->CFGLR &= ~(GPIO_CFGLR_CNF5_1|GPIO_CFGLR_CNF6_1);
            AFIO->PCFR1 &= ~AFIO_PCFR1_USART2_REMAP;

            break;
        default:
            break;
        }
#endif
        break;

    case UART_3:  //若为串口3
#ifdef UART3_GROUP
        //依据选择使能对应时钟，并配置对应引脚为UART_3
        switch(UART3_GROUP)
        {
        case 0:
            //使能USART2和GPIOA时钟
            RCC->APB1PCENR &= ~RCC_USART3EN;
            RCC->APB2PCENR &= ~RCC_IOPBEN;
            //使能PTA9,PTA10为USART(Tx,Rx)功能
            GPIOB->CFGHR &= ~(GPIO_CFGHR_CNF10|GPIO_CFGHR_CNF11);
            //GPIOB->CFGHR |= ((GPIO_CFGHR_CNF10_1|GPIO_CFGHR_MODE10_1)|(GPIO_CFGHR_CNF11_0));
            break;
        case 1:
            //使能USART1和GPIOB时钟
            RCC->APB2PCENR &= ~RCC_USART3EN;
            RCC->APB2PCENR &= ~RCC_AFIOEN;
            //使能PTB6,PTB7为USART(Tx,Rx)功能
            AFIO->PCFR1 &= ~AFIO_PCFR1_USART3_REMAP;
            GPIOD->CFGHR &= ~(GPIO_CFGHR_CNF8|GPIO_CFGHR_CNF9);
            //GPIOD->CFGHR |= ((GPIO_CFGHR_CNF8_1|GPIO_CFGHR_MODE8_1)|(GPIO_CFGHR_CNF9_0));

            break;
        default:
            break;
        }
#endif
        break;
    }

}


//----------------------以下为内部函数存放处--------------------------------------
//=====================================================================
//函数名称：uart_is_uartNo
//函数返回：1:串口号在合理范围内，0：串口号不合理
//参数说明：串口号uartNo  :UART_1、UART_2、UART_3
//功能概要：为程序健壮性而判断uartNo是否在串口数字范围内
//=====================================================================
uint8_t uart_is_uartNo(uint8_t uartNo)
{
    if(uartNo < UART_1 || uartNo > UART_8)
        return 0;
    else
        return 1;
}

#ifdef __cplusplus
}
#endif
