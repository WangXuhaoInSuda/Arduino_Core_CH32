#ifdef CH32V3xx
/********************************** (C) COPYRIGHT *******************************
* File Name          : startup_ch32v30x.s
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/06/06
* Description        : CH32V30x vector table for eclipse toolchain.
*******************************************************************************/

	.section	.init,"ax",@progbits
	.global	_start
	.align	1
_start:
	j	handle_reset
	.word 0x00000013
	.word 0x00000013
	.word 0x00000013
	.word 0x00000013
	.word 0x00000013
	.word 0x00000013
	.word 0x00000013
	.word 0x00000013
	.word 0x00000013
	.word 0x00000013
	.word 0x00000013
	.word 0x00000013 /* nop */
	.word 0x00100073 /* ebreak */
    .section    .vector,"ax",@progbits
    .align  1
_vector_base:
    .option norvc;
    .word   _start
    .word   0
    .word   NMI_Handler                 /* NMI Handler */
    .word   HardFault_Handler           /* Hard Fault Handler */
    .word   0
    .word   Ecall_M_Mode_Handler
    .word   0
    .word   0
    .word   Ecall_U_Mode_Handler
    .word   Break_Point_Handler
    .word   0
    .word   0
    .word   SysTick_Handler            /* SysTick Handler */
    .word   0
    .word   SW_handler                 /* SW Handler */
    .word   0
    /* External Interrupts */
    .word   WWDG_IRQHandler            /* Window Watchdog */
    .word   PVD_IRQHandler             /* PVD through EXTI Line detect */
    .word   TAMPER_IRQHandler          /* TAMPER */
    .word   RTC_IRQHandler             /* RTC */
    .word   FLASH_IRQHandler           /* Flash */
    .word   RCC_IRQHandler             /* RCC */
    .word   EXTI0_IRQHandler           /* EXTI Line 0 */
    .word   EXTI1_IRQHandler           /* EXTI Line 1 */
    .word   EXTI2_IRQHandler           /* EXTI Line 2 */
    .word   EXTI3_IRQHandler           /* EXTI Line 3 */
    .word   EXTI4_IRQHandler           /* EXTI Line 4 */
    .word   DMA1_Channel1_IRQHandler   /* DMA1 Channel 1 */
    .word   DMA1_Channel2_IRQHandler   /* DMA1 Channel 2 */
    .word   DMA1_Channel3_IRQHandler   /* DMA1 Channel 3 */
    .word   DMA1_Channel4_IRQHandler   /* DMA1 Channel 4 */
    .word   DMA1_Channel5_IRQHandler   /* DMA1 Channel 5 */
    .word   DMA1_Channel6_IRQHandler   /* DMA1 Channel 6 */
    .word   DMA1_Channel7_IRQHandler   /* DMA1 Channel 7 */
    .word   ADC1_2_IRQHandler          /* ADC1_2 */
    .word   USB_HP_CAN1_TX_IRQHandler
    .word   USB_LP_CAN1_RX0_IRQHandler
    .word   CAN1_RX1_IRQHandler
    .word   CAN1_SCE_IRQHandler
    .word   EXTI9_5_IRQHandler         /* EXTI Line 9..5 */
    .word   TIM1_BRK_IRQHandler        /* TIM1 Break */
    .word   TIM1_UP_IRQHandler         /* TIM1 Update */
    .word   TIM1_TRG_COM_IRQHandler    /* TIM1 Trigger and Commutation */
    .word   TIM1_CC_IRQHandler         /* TIM1 Capture Compare */
    .word   TIM2_IRQHandler            /* TIM2 */
    .word   TIM3_IRQHandler            /* TIM3 */
    .word   TIM4_IRQHandler            /* TIM4 */
    .word   I2C1_EV_IRQHandler         /* I2C1 Event */
    .word   I2C1_ER_IRQHandler         /* I2C1 Error */
    .word   I2C2_EV_IRQHandler         /* I2C2 Event */
    .word   I2C2_ER_IRQHandler         /* I2C2 Error */
    .word   SPI1_IRQHandler            /* SPI1 */
    .word   SPI2_IRQHandler            /* SPI2 */
    .word   USART1_IRQHandler          /* USART1 */
    .word   USART2_IRQHandler          /* USART2 */
    .word   USART3_IRQHandler          /* USART3 */
    .word   EXTI15_10_IRQHandler       /* EXTI Line 15..10 */
    .word   RTCAlarm_IRQHandler        /* RTC Alarm through EXTI Line */
    .word   USBWakeUp_IRQHandler       /* USB Wakeup from suspend */
    .word   TIM8_BRK_IRQHandler
    .word   TIM8_UP_IRQHandler
    .word   TIM8_TRG_COM_IRQHandler
    .word   TIM8_CC_IRQHandler
    .word   RNG_IRQHandler
    .word   FSMC_IRQHandler
    .word   SDIO_IRQHandler
    .word   TIM5_IRQHandler
    .word   SPI3_IRQHandler
    .word   UART4_IRQHandler
    .word   UART5_IRQHandler
    .word   TIM6_IRQHandler
    .word   TIM7_IRQHandler
    .word   DMA2_Channel1_IRQHandler
    .word   DMA2_Channel2_IRQHandler
    .word   DMA2_Channel3_IRQHandler
    .word   DMA2_Channel4_IRQHandler
    .word   DMA2_Channel5_IRQHandler
    .word   ETH_IRQHandler
    .word   ETH_WKUP_IRQHandler
    .word   CAN2_TX_IRQHandler
    .word   CAN2_RX0_IRQHandler
    .word   CAN2_RX1_IRQHandler
    .word   CAN2_SCE_IRQHandler
    .word   OTG_FS_IRQHandler
    .word   USBHSWakeup_IRQHandler
    .word   USBHS_IRQHandler
    .word   DVP_IRQHandler
    .word   UART6_IRQHandler
    .word   UART7_IRQHandler
    .word   UART8_IRQHandler
    .word   TIM9_BRK_IRQHandler
    .word   TIM9_UP_IRQHandler
    .word   TIM9_TRG_COM_IRQHandler
    .word   TIM9_CC_IRQHandler
    .word   TIM10_BRK_IRQHandler
    .word   TIM10_UP_IRQHandler
    .word   TIM10_TRG_COM_IRQHandler
    .word   TIM10_CC_IRQHandler
    .word   DMA2_Channel6_IRQHandler
    .word   DMA2_Channel7_IRQHandler
    .word   DMA2_Channel8_IRQHandler
    .word   DMA2_Channel9_IRQHandler
    .word   DMA2_Channel10_IRQHandler
    .word   DMA2_Channel11_IRQHandler

    .option rvc;

    .section    .text.vector_handler, "ax", @progbits
    .weak   NMI_Handler
    .weak   HardFault_Handler
    .weak   Ecall_M_Mode_Handler
    .weak   Ecall_U_Mode_Handler
    .weak   Break_Point_Handler
    .weak   SysTick_Handler
    .weak   SW_handler
    .weak   WWDG_IRQHandler            /* Window Watchdog */
    .weak   PVD_IRQHandler             /* PVD through EXTI Line detect */
    .weak   TAMPER_IRQHandler          /* TAMPER */
    .weak   RTC_IRQHandler             /* RTC */
    .weak   FLASH_IRQHandler           /* Flash */
    .weak   RCC_IRQHandler             /* RCC */
    .weak   EXTI0_IRQHandler           /* EXTI Line 0 */
    .weak   EXTI1_IRQHandler           /* EXTI Line 1 */
    .weak   EXTI2_IRQHandler           /* EXTI Line 2 */
    .weak   EXTI3_IRQHandler           /* EXTI Line 3 */
    .weak   EXTI4_IRQHandler           /* EXTI Line 4 */
    .weak   DMA1_Channel1_IRQHandler   /* DMA1 Channel 1 */
    .weak   DMA1_Channel2_IRQHandler   /* DMA1 Channel 2 */
    .weak   DMA1_Channel3_IRQHandler   /* DMA1 Channel 3 */
    .weak   DMA1_Channel4_IRQHandler   /* DMA1 Channel 4 */
    .weak   DMA1_Channel5_IRQHandler   /* DMA1 Channel 5 */
    .weak   DMA1_Channel6_IRQHandler   /* DMA1 Channel 6 */
    .weak   DMA1_Channel7_IRQHandler   /* DMA1 Channel 7 */
    .weak   ADC1_2_IRQHandler          /* ADC1_2 */
    .weak   USB_HP_CAN1_TX_IRQHandler
    .weak   USB_LP_CAN1_RX0_IRQHandler
    .weak   CAN1_RX1_IRQHandler
    .weak   CAN1_SCE_IRQHandler
    .weak   EXTI9_5_IRQHandler         /* EXTI Line 9..5 */
    .weak   TIM1_BRK_IRQHandler        /* TIM1 Break */
    .weak   TIM1_UP_IRQHandler         /* TIM1 Update */
    .weak   TIM1_TRG_COM_IRQHandler    /* TIM1 Trigger and Commutation */
    .weak   TIM1_CC_IRQHandler         /* TIM1 Capture Compare */
    .weak   TIM2_IRQHandler            /* TIM2 */
    .weak   TIM3_IRQHandler            /* TIM3 */
    .weak   TIM4_IRQHandler            /* TIM4 */
    .weak   I2C1_EV_IRQHandler         /* I2C1 Event */
    .weak   I2C1_ER_IRQHandler         /* I2C1 Error */
    .weak   I2C2_EV_IRQHandler         /* I2C2 Event */
    .weak   I2C2_ER_IRQHandler         /* I2C2 Error */
    .weak   SPI1_IRQHandler            /* SPI1 */
    .weak   SPI2_IRQHandler            /* SPI2 */
    .weak   USART1_IRQHandler          /* USART1 */
    .weak   USART2_IRQHandler          /* USART2 */
    .weak   USART3_IRQHandler          /* USART3 */
    .weak   EXTI15_10_IRQHandler       /* EXTI Line 15..10 */
    .weak   RTCAlarm_IRQHandler        /* RTC Alarm through EXTI Line */
    .weak   USBWakeUp_IRQHandler       /* USB Wakeup from suspend */
    .weak   TIM8_BRK_IRQHandler
    .weak   TIM8_UP_IRQHandler
    .weak   TIM8_TRG_COM_IRQHandler
    .weak   TIM8_CC_IRQHandler
    .weak   RNG_IRQHandler
    .weak   FSMC_IRQHandler
    .weak   SDIO_IRQHandler
    .weak   TIM5_IRQHandler
    .weak   SPI3_IRQHandler
    .weak   UART4_IRQHandler
    .weak   UART5_IRQHandler
    .weak   TIM6_IRQHandler
    .weak   TIM7_IRQHandler
    .weak   DMA2_Channel1_IRQHandler
    .weak   DMA2_Channel2_IRQHandler
    .weak   DMA2_Channel3_IRQHandler
    .weak   DMA2_Channel4_IRQHandler
    .weak   DMA2_Channel5_IRQHandler
    .weak   ETH_IRQHandler
    .weak   ETH_WKUP_IRQHandler
    .weak   CAN2_TX_IRQHandler
    .weak   CAN2_RX0_IRQHandler
    .weak   CAN2_RX1_IRQHandler
    .weak   CAN2_SCE_IRQHandler
    .weak   OTG_FS_IRQHandler
    .weak   USBHSWakeup_IRQHandler
    .weak   USBHS_IRQHandler
    .weak   DVP_IRQHandler
    .weak   UART6_IRQHandler
    .weak   UART7_IRQHandler
    .weak   UART8_IRQHandler
    .weak   TIM9_BRK_IRQHandler
    .weak   TIM9_UP_IRQHandler
    .weak   TIM9_TRG_COM_IRQHandler
    .weak   TIM9_CC_IRQHandler
    .weak   TIM10_BRK_IRQHandler
    .weak   TIM10_UP_IRQHandler
    .weak   TIM10_TRG_COM_IRQHandler
    .weak   TIM10_CC_IRQHandler
    .weak   DMA2_Channel6_IRQHandler
    .weak   DMA2_Channel7_IRQHandler
    .weak   DMA2_Channel8_IRQHandler
    .weak   DMA2_Channel9_IRQHandler
    .weak   DMA2_Channel10_IRQHandler
    .weak   DMA2_Channel11_IRQHandler

	.section	.text.handle_reset,"ax",@progbits
	.weak	handle_reset
	.align	1
handle_reset:
.option push 
.option	norelax 
    csrw mepc, t0
	la gp, __global_pointer$
.option	pop 
1:
	la sp, _eusrstack
2:
	/* 【固定】将data段数据复制到RAM中 */
	/* data段存放有初值的全局变量和静态变量 */
	la a0, _data_lma
	la a1, _data_vma
	la a2, _edata
	bgeu a1, a2, 2f
1:
	lw t0, (a0)
	sw t0, (a1)
	addi a0, a0, 4
	addi a1, a1, 4
	bltu a1, a2, 1b
2:
	/* 【固定】将BSS段数据清零 */
	/* BSS段存放有未初始化的全局变量 */
	la a0, _sbss
	la a1, _ebss
	bgeu a0, a1, 2f
1:
	sw zero, (a0)
	addi a0, a0, 4
	bltu a0, a1, 1b
2:
	/* 【固定】将芯片运行模式设置机器模式 */
   	li t0, 0x7888				
   	csrs mstatus, t0
   	
   	jal  SystemInit

	/* 【固定】中断继承，.s文件仅修改此处 */
	/* 将中断向量表基址赋值给机器模式异常入口基地址寄存器 */
    jal  Vectors_Init			
 	la t0, _vector_base
    ori t0, t0, 3
	csrw mtvec, t0				

    /*jal  SystemInit*/
	la t0, main
	csrw mepc, t0
	mret



#endif


