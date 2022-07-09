//===========================================================================
//文件名称：gpio.c
//功能概要：GPIO底层驱动构件源文件
//版权所有：SD-Arm(sumcu.suda.edu.cn)
//版本更新：20200831-20211027
//芯片类型：CH32V307
//===========================================================================

#include "gpio.h"

//GPIO口基地址放入常数数据组GPIO_ARR[0]~GPIO_ARR[5]中
GPIO_TypeDef * GPIO_ARR[] ={(GPIO_TypeDef *)GPIOA_BASE,(GPIO_TypeDef *)GPIOB_BASE,
                            (GPIO_TypeDef *)GPIOC_BASE,(GPIO_TypeDef *)GPIOD_BASE,(GPIO_TypeDef *)GPIOE_BASE};

//==============定义扩展中断IRQ号对应表================
IRQn_Type table_irq_exti[7] = {EXTI0_IRQn, EXTI1_IRQn, EXTI2_IRQn, EXTI3_IRQn,
                               EXTI4_IRQn, EXTI9_5_IRQn, EXTI15_10_IRQn};



//内部函数声明
void gpio_get_port_pin(uint16_t port_pin,uint8_t* port,uint8_t* pin);
void GPIO_EXTILineConfig(uint8_t port, uint8_t pin);

//=====================================================================
//函数名称：gpio_init
//函数返回：无
//参数说明：port_pin：(端口号)|(引脚号)（如：(PTB_NUM)|(9) 表示为B口9号脚）
//         dir：引脚方向（0=输入，1=输出,可用引脚方向宏定义）
//         state：端口引脚初始状态（0=低电平，1=高电平）
//功能概要：初始化指定端口引脚作为GPIO引脚功能，并定义为输入或输出，若是输出，
//         还指定初始状态是低电平或高电平
//=====================================================================
void gpio_init(uint16_t port_pin, uint8_t dir, uint8_t state)
{
    GPIO_TypeDef *gpio_ptr;    //声明gpio_ptr为GPIO结构体类型指针
    uint8_t port,pin;    //声明端口port、引脚pin变量
    uint32_t temp;       //临时存放寄存器里的值

    //根据带入参数port_pin，解析出端口与引脚分别赋给port,pin
    gpio_get_port_pin(port_pin,&port,&pin);
    //根据port，给局部变量gpio_ptr赋值（GPIO基地址）
    gpio_ptr = GPIO_ARR[port];

    //使能相应GPIO时钟
    RCC->APB2PCENR |= (RCC_IOPAEN << (port * 1u));

    if(pin <= 0x07)
    {
        temp = gpio_ptr->CFGLR;
        temp &= ~(GPIO_CFGLR_CNF0 << (pin * 4u));

        if(dir == 1)   // 定义为输出引脚
        {
            temp |= (GPIO_OUTPUT << (pin * 4u));
            gpio_ptr->CFGLR = temp;
            gpio_set(port_pin,state);
        }
        else           // 定义为输入引脚
        {
            temp |= (GPIO_INPUT << (pin * 4u));
            gpio_ptr->CFGLR = temp;
        }
    }
    if(pin > 0x07)
    {
        //清GPIO模式寄存器对应引脚位
        temp = gpio_ptr->CFGHR;
        temp &= ~(GPIO_CFGHR_CNF8 << (pin * 4u));

        if(dir == 1)   // 定义为输出引脚
        {
            temp |= (GPIO_OUTPUT << ((pin-8) * 4u));
            gpio_ptr->CFGHR = temp;
            gpio_set(port_pin,state);
        }
        else           // 定义为输入引脚
        {
            temp |= (GPIO_INPUT << ((pin-8) * 4u));
            gpio_ptr->CFGHR = temp;
        }

    }
}

//=====================================================================
//函数名称：gpio_set
//函数返回：无
//参数说明：port_pin：端口号|引脚号（如：(PTB_NUM)|(9) 表示为B口9号脚）
//       state：引脚初始状态（0=低电平，1=高电平）
//功能概要：设定引脚状态为低电平或高电平
//=====================================================================
void gpio_set(uint16_t port_pin, uint8_t state)
{
    //局部变量声明
    GPIO_TypeDef *gpio_ptr;                      //声明port_ptr为GPIO结构体类型指针（首地址）
    uint8_t port,pin;                          //声明端口port、引脚pin变量
    //根据带入参数port_pin，解析出端口与引脚分别赋给port,pin
    gpio_get_port_pin(port_pin,&port,&pin);

    //根据port，给局部变量gpio_ptr赋值（GPIO基地址）
    gpio_ptr = GPIO_ARR[port];

    //根据带入参数state，决定引脚为输出1还是0
    if(1==state)
    {
        gpio_ptr->BSHR = (uint16_t)(1u << pin);
    }
    else
    {
        gpio_ptr->BCR = (uint16_t)(1u << pin);
    }

}

//=====================================================================
//函数名称：gpio_get
//函数返回：指定引脚的状态（1或0）
//参数说明：port_pin：端口号|引脚号（如：(PTB_NUM)|(9) 表示为B口9号脚）
//功能概要：获取指定引脚的状态（1或0）
//=====================================================================
uint8_t gpio_get(uint16_t port_pin)
{
    //局部变量声明
    GPIO_TypeDef *gpio_ptr;              //声明port_ptr为GPIO结构体类型指针（首地址）
    uint8_t port,pin;                    //声明端口port、引脚pin变量
    uint32_t temp;
    uint8_t value;

    //根据带入参数port_pin，解析出端口与引脚分别赋给port,pin
    gpio_get_port_pin(port_pin,&port,&pin);

    //根据port，给局部变量gpio_ptr赋值（GPIO基地址）
    gpio_ptr = GPIO_ARR[port];

    // 获得状态寄存器的值
    if(pin < 0x08)
    {
        temp =gpio_ptr->CFGLR;
        if((temp & (3u<<(pin*4)))==0x00u)   // GPIO输入
        {
            //读取InPut data寄存器对应引脚的值
            temp = gpio_ptr->INDR;
            if((temp & (1u<<pin)) != 0x00u)
                value = 1;
            else
                value = 0;
        }
        else
        {
            //读取OutPut data寄存器对应引脚的值
            temp = gpio_ptr->OUTDR;
            if((temp & (1u<<pin) )!= 0x00u)
                value = 1;
            else
                value = 0;
        }
    }
    else
    {
        temp = gpio_ptr->CFGHR;
        if((temp & (3u<<((pin-8)*4)))==0x00u)   // GPIO输入
        {
            //读取InPut data寄存器对应引脚的值
            temp = gpio_ptr->INDR;
            if((temp & (1u<<pin)) != 0x00u)
                value = 1;
            else
                value = 0;
        }
        else
        {
            //读取OutPut data寄存器对应引脚的值
            temp = gpio_ptr->OUTDR;
            if((temp & (1u<<pin)) != 0x00u)
                value = 1;
            else
                value = 0;
        }
    }
//    temp = (gpio_ptr->CFGLR | gpio_ptr->CFGHR);


    return value;
}

//=====================================================================
//函数名称：gpio_reverse
//函数返回：无
//参数说明：port_pin：端口号|引脚号（如：(PTB_NUM)|(9) 表示为B口9号脚）
//功能概要：当指定端口引脚被定义为GPIO功能且为输出时，反转指定引脚输出状态。
//=====================================================================
void gpio_reverse(uint16_t port_pin)
{
    //局部变量声明
    GPIO_TypeDef *gpio_ptr;              //声明port_ptr为GPIO结构体类型指针（首地址）
    uint8_t port,pin;                    //声明端口port、引脚pin变量

    //根据带入参数port_pin，解析出端口与引脚分别赋给port,pin
    gpio_get_port_pin(port_pin,&port,&pin);

    //根据port，给局部变量gpio_ptr赋值（GPIO基地址）
    gpio_ptr = GPIO_ARR[port];

    //判断引脚状态
    if((gpio_ptr->OUTDR & (1u<<pin)) != 0x00)
    {
        //高电平则反转为低电平
        gpio_ptr->BCR = (uint32_t)(1u<<pin);
    }
    else
    {
        // 低电平则反转为高电平
        gpio_ptr->BSHR = (uint32_t)(1u<<pin);
    }
}

//=====================================================================
//函数名称：gpio_pull
//函数返回：无
//参数说明：port_pin：端口号|引脚号（如：(PTB_NUM)|(9) 表示为B口9号脚）
//        pullselect：引脚拉高低电平（ 0=拉低电平，1=拉高电平）
//功能概要：使指定引脚上拉高电平或下拉低电平
//=====================================================================
void gpio_pull(uint16_t port_pin, uint8_t pullselect)
{
    //局部变量声明
    GPIO_TypeDef *gpio_ptr;              //声明port_ptr为GPIO结构体类型指针（首地址）
    uint8_t port,pin;                    //声明端口port、引脚pin变量

    //根据带入参数port_pin，解析出端口与引脚分别赋给port,pin
    gpio_get_port_pin(port_pin,&port,&pin);

    //根据port，给局部变量gpio_ptr赋值（GPIO基地址）
    gpio_ptr = GPIO_ARR[port];

    if(pin<=0x07)
    {
        //设定为速度10MHz
        gpio_ptr->CFGLR |= (GPIO_CFGLR_MODE0 <<(4u * pin));

        if(1 == pullselect)
        {
            //引脚拉高
            gpio_ptr->OUTDR = (uint32_t)(PULL_UP<<(1u*pin));
        }
        else
        {
            //引脚拉低
            gpio_ptr->OUTDR = (uint32_t)(PULL_DOWN<<(1u*pin));
        }
    }
    if(pin>0x07)
    {
        //设定为速度10MHz
        gpio_ptr->CFGHR |= (GPIOSpeed_10MHz <<(4u * pin));

        if(1 == pullselect)
        {
            //引脚拉高
            gpio_ptr->OUTDR = (uint32_t)(PULL_UP<<(1u*pin));
        }
        else
        {
            //引脚拉低
            gpio_ptr->OUTDR = (uint32_t)(PULL_DOWN<<(1u*pin));

        }
    }
}

//=====================================================================
//函数名称：gpio_disable_int
//函数返回：无
//参数说明：port_pin：(端口号)|(引脚号)（如：(PTB_NUM)|(9) 表示为B口9号脚）
//         irqtype:引脚中断类型，由宏定义给出，再次列举如下；
//功能概要：当指定端口引脚被定义为GPIO功能且为输入时，本函数关闭引脚中断
//注          意： KL25芯片，只有PORTA、PORTD口具有GPIO类中断功能
//           KW01芯片，只有PORTA、PORTC、PORTD口具有GPIO类中断功能
//           KL36芯片，只有PORTA、PORTC、PORTD口具有GPIO类中断功能
//           CH32v103，PORTA、PORTB、PORTC、PORTD口具有GPIO类中断功能
//=====================================================================
void gpio_enable_int(uint16_t port_pin, uint8_t irqtype)
{
    //局部变量声明
    uint8_t port,pin;                    //声明端口port、引脚pin变量
    uint32_t temp = 0;                       //临时存放寄存器的值
    //根据带入参数port_pin，解析出端口与引脚分别赋给port,pin
    gpio_get_port_pin(port_pin,&port,&pin);

    //使能AFIO时钟
    RCC->APB2PCENR|=RCC_AFIOEN;

    //配置对应引脚的扩展中断
    GPIO_EXTILineConfig(port,pin);

    temp = (uint32_t)EXTI_BASE;
    //清零
    EXTI->INTENR &= ~(EXTI_INTENR_MR0 << pin);
    EXTI->EVENR &= ~(EXTI_EVENR_MR0 << pin);
    EXTI->RTENR &= ~(EXTI_RTENR_TR0 << pin);
    EXTI->FTENR &= ~(EXTI_FTENR_TR0 << pin);

    //设置当前是触发中断
    temp += EXTI_Mode_Interrupt;
    //允许对应扩展中断行的请求
    *(__IO uint32_t *) temp |= (EXTI_INTENR_MR0 << pin);

    //若是双边沿
    if(DOUBLE_EDGE == irqtype)
    {
        EXTI->RTENR |= (EXTI_RTENR_TR0 << pin);
        EXTI->FTENR |= (EXTI_FTENR_TR0 << pin);
    }
    //否则
    else
    {
        temp = (uint32_t)EXTI_BASE;
        temp += irqtype;
        *(__IO uint32_t *) temp |= (EXTI_FTENR_TR0 << pin);
    }

    if(pin>=0 && pin<=4)
        // 开中断控制器IRQ中断(EXTIx,x=0-4)
        NVIC_EnableIRQ(table_irq_exti[pin]);
    else if(pin>=5 && pin<=9)
        // 开中断控制器IRQ中断(EXTI9-5)
        NVIC_EnableIRQ(table_irq_exti[5]);
    else
        // 开中断控制器IRQ中断(EXTI15-10)
        NVIC_EnableIRQ(table_irq_exti[6]);

}

//=====================================================================
//函数名称：gpio_disable_int
//函数返回：无
//参数说明：port_pin：(端口号)|(引脚号)（如：(PTB_NUM)|(9) 表示为B口9号脚）
//功能概要：当指定端口引脚被定义为GPIO功能且为输入时，本函数关闭引脚中断
//注          意： KL25芯片，只有PORTA、PORTD口具有GPIO类中断功能
//           KW01芯片，只有PORTA、PORTC、PORTD口具有GPIO类中断功能
//           KL36芯片，只有PORTA、PORTC、PORTD口具有GPIO类中断功能
//=====================================================================
void gpio_disable_int(uint16_t port_pin)
{

    //局部变量声明
    uint8_t port,pin;                    //声明端口port、引脚pin变量
    //uint32_t temp;                       //临时存放寄存器的值
    //根据带入参数port_pin，解析出端口与引脚分别赋给port,pin
    gpio_get_port_pin(port_pin,&port,&pin);

    //禁止AFIO时钟
    RCC->APB2PCENR &=~RCC_AFIOEN;

    //清对应引脚的扩展中断
    AFIO->EXTICR[pin >> 2u] &= ~(0x0FuL << (4u * (pin & 0x03u)));

    //屏蔽对应扩展中断行的请求
    EXTI->INTENR &= ~(EXTI_INTENR_MR0<<pin);

    //禁止上升沿下降沿触发
    EXTI->RTENR &= ~(EXTI_RTENR_TR0 << pin);
    EXTI->FTENR &= ~(EXTI_FTENR_TR0 << pin);

    if(pin>=0 && pin<=4)
        // 关中断控制器IRQ中断(EXTIx,x=0-4)
        NVIC_DisableIRQ(table_irq_exti[pin]);
    else if(pin>=5 && pin<=9)
        // 关中断控制器IRQ中断(EXTI9-5)
        NVIC_DisableIRQ(table_irq_exti[5]);
    else
        // 关中断控制器IRQ中断(EXTI15-10)
        NVIC_DisableIRQ(table_irq_exti[6]);

}

//=====================================================================
//函数名称：gpio_drive_strength
//函数返回：无
//参数说明：port_pin：(端口号)|(引脚号)（如：(PTB_NUM)|(9) 表示为B口9号脚）
//       control：控制引脚的驱动能力，1=高驱动，0=正常驱动
//         （引脚被配置为数字输出时，引脚控制寄存器的DSE=1：高驱动， DSE=0：正常驱动）
//功能概要：（引脚驱动能力：指引脚输入或输出电流的承受力，一般用mA单位度量
//            ，正常驱动能力5mA,高驱动能力18mA。）当引脚被配置为数字输出时,
//            对引脚的驱动能力进行设置，只有PTB0,PTB1,PTD6,PTD7同时具有高驱
//            动能力和正常驱动能力,这些引脚可用于直接驱动LED或给MOSFET（金氧
//            半场效晶体管）供电，该函数只适用于上述4个引脚。
//=====================================================================
void gpio_drive_strength(uint16_t port_pin, uint8_t control)
{
   //局部变量声明
   GPIO_TypeDef *gpio_ptr;              //声明port_ptr为GPIO结构体类型指针（首地址）
   uint8_t port,pin;                    //声明端口port、引脚pin变量

   //根据带入参数port_pin，解析出端口与引脚分别赋给port,pin
   gpio_get_port_pin(port_pin,&port,&pin);

   //根据port，给局部变量gpio_ptr赋值（GPIO基地址）
   gpio_ptr = GPIO_ARR[port];

   //配置引脚的驱动能力
   if(pin <= 0x07)
   {
       gpio_ptr->CFGLR |= (uint32_t)(control<<(pin * 4u));
   }
   if(pin > 0x07)
   {
       gpio_ptr->CFGHR |= (uint32_t)(control<<(pin * 4u));
   }

}

//=====================================================================
//函数名称：gpio_get_int
//函数返回：引脚GPIO中断标志（1或0）1表示引脚有GPIO中断，0表示引脚没有GPIO中断。
//参数说明：port_pin：(端口号)|(引脚号)（如：(PTB_NUM)|(9) 表示为B口9号脚）
//功能概要：当指定端口引脚被定义为GPIO功能且为输入时,获取中断标志。
//注          意： KL25芯片，只有PORTA、PORTD口具有GPIO类中断功能
//           KW01芯片，只有PORTA、PORTC、PORTD口具有GPIO类中断功能
//           KL36芯片，只有PORTA、PORTC、PORTD口具有GPIO类中断功能
//           CH32芯片，只有GPIOA、GPIOB、GPIOC、GPIOD口具有GPIO类中断功能
//=====================================================================
uint8_t gpio_get_int(uint16_t port_pin)
{
    uint8_t port,pin;           //声明端口port、引脚pin变量

    //根据带入参数port_pin，解析出端口与引脚分别赋给port,pin
    gpio_get_port_pin(port_pin,&port,&pin);

    // 获取GPIO中断标志
    if((EXTI->INTFR & (1u << pin)) == (1u << pin))
    {
        return 1;
    }
    else
        return 0;
}

//=====================================================================
//函数名称：gpio_clear_int
//函数返回：无
//参数说明：port_pin：(端口号)|(引脚号)（如：(PTB_NUM)|(9) 表示为B口9号脚）
//功能概要：当指定端口引脚被定义为GPIO功能且为输入时,清除中断标志。
//注          意： KL25芯片，只有PORTA、PORTD口具有GPIO类中断功能
//           KW01芯片，只有PORTA、PORTC、PORTD口具有GPIO类中断功能
//           KL36芯片，只有PORTA、PORTC、PORTD口具有GPIO类中断功能
//           CH32芯片，只有GPIOA、GPIOB、GPIOC、GPIOD口具有GPIO类中断功能
//=====================================================================
void gpio_clear_int(uint16_t port_pin)
{
    uint8_t port,pin;           //声明端口port、引脚pin变量

   //根据带入参数port_pin，解析出端口与引脚分别赋给port,pin
   gpio_get_port_pin(port_pin,&port,&pin);

   // 获取GPIO中断标志
   EXTI->INTFR |= (1u << pin);

}

//=====================================================================
//函数名称：gpio_clear_allint
//函数返回：无
//参数说明：无
//功能概要：清除所有端口的GPIO中断
//注          意： KL25芯片，只有PORTA、PORTD口具有GPIO类中断功能
//           KW01芯片，只有PORTA、PORTC、PORTD口具有GPIO类中断功能
//           KL36芯片，只有PORTA、PORTC、PORTD口具有GPIO类中断功能
//=====================================================================
void gpio_clear_allint(void)
{
    EXTI->INTFR |= 0xFFFF;  // pin可取0-15

}


//----------------------以下为内部函数存放处-----------------
//=====================================================================
//函数名称：gpio_get_port_pin
//函数返回：无
//参数说明：port_pin：端口号|引脚号（如：(PTB_NUM)|(9) 表示为B口9号脚）
//       port：端口号（传指带出参数）
//       pin:引脚号（0~15，实际取值由芯片的物理引脚决定）（传指带出参数）
//功能概要：将传进参数port_pin进行解析，得出具体端口号与引脚号，分别赋值给port与pin,返回。
//       （例：(PTB_NUM)|(9)解析为PORTB与9，并将其分别赋值给port与pin）。
//=====================================================================
void gpio_get_port_pin(uint16_t port_pin,uint8_t* port,uint8_t* pin)
{
    *port = (port_pin>>8);
    *pin = port_pin;
}

//=====================================================================
//函数名称：GPIO_EXTILineConfig
//函数返回：无
//参数说明：
//       port：端口号（传指带出参数）
//       pin:引脚号（0~15，实际取值由芯片的物理引脚决定）（传指带出参数）
//功能概要：选择用作EXTI线的GPIO引脚。
//=====================================================================
void GPIO_EXTILineConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource)
{
  uint32_t tmp = 0x00;

  tmp = ((uint32_t)0x0F) << (0x04 * (GPIO_PinSource & (uint8_t)0x03));
  AFIO->EXTICR[GPIO_PinSource >> 0x02] &= ~tmp;
  AFIO->EXTICR[GPIO_PinSource >> 0x02] |= (((uint32_t)GPIO_PortSource) << (0x04 * (GPIO_PinSource & (uint8_t)0x03)));
}

//【20211027-hsc】gpio_get测试后，发现存在问题：需要区分高低位。
