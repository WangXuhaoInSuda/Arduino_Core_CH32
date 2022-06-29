/**
  ******************************************************************************
  * @file    interrupt.c
  * @author  WI6LABS
  * @version V1.0.0
  * @date    01-August-2016
  * @brief   provide an interface to enable/disable interruptions
  *
  ******************************************************************************
  */
#include "interrupt.h"

#if !defined(EXTI_MODULE_DISABLED)

/* Private Types */

/*As we can have only one interrupt/pin id, don't need to get the port info*/
typedef struct {
  IRQn_Type irqnb;
  std::function<void(void)> callback;
} gpio_irq_conf_str;

/* Private_Defines */
#define NB_EXTI   (16)

/* Private Variables */
static gpio_irq_conf_str gpio_irq_conf[NB_EXTI] = {

  {.irqnb = EXTI0_IRQn,     .callback = NULL}, //GPIO_PIN_0
  {.irqnb = EXTI1_IRQn,     .callback = NULL}, //GPIO_PIN_1
  {.irqnb = EXTI2_IRQn,     .callback = NULL}, //GPIO_PIN_2
  {.irqnb = EXTI3_IRQn,     .callback = NULL}, //GPIO_PIN_3
  {.irqnb = EXTI4_IRQn,     .callback = NULL}, //GPIO_PIN_4
  {.irqnb = EXTI9_5_IRQn,   .callback = NULL}, //GPIO_PIN_5
  {.irqnb = EXTI9_5_IRQn,   .callback = NULL}, //GPIO_PIN_6
  {.irqnb = EXTI9_5_IRQn,   .callback = NULL}, //GPIO_PIN_7
  {.irqnb = EXTI9_5_IRQn,   .callback = NULL}, //GPIO_PIN_8
  {.irqnb = EXTI9_5_IRQn,   .callback = NULL}, //GPIO_PIN_9
  {.irqnb = EXTI15_10_IRQn, .callback = NULL}, //GPIO_PIN_10
  {.irqnb = EXTI15_10_IRQn, .callback = NULL}, //GPIO_PIN_11
  {.irqnb = EXTI15_10_IRQn, .callback = NULL}, //GPIO_PIN_12
  {.irqnb = EXTI15_10_IRQn, .callback = NULL}, //GPIO_PIN_13
  {.irqnb = EXTI15_10_IRQn, .callback = NULL}, //GPIO_PIN_14
  {.irqnb = EXTI15_10_IRQn, .callback = NULL}  //GPIO_PIN_15

};

/* Private Functions */
/**
  * @brief  This function returns the pin ID function of the HAL PIN definition
  * @param  pin : one of the GPIO_Pin_x
  * @retval None
  */
static uint8_t get_pin_id(uint16_t pin)
{
  uint8_t id = 0;

  while (pin != 0x0001) {
    pin = pin >> 1;
    id++;
  }

  return id;
}
/* Private Functions */
/**
  * @brief  This function returns the pin ID function of the HAL PIN definition
  * @param  prot : GPIO_Typedef
  * @param  pin : one of the GPIO_Pin_x
  * @param  callback : callback function to be called
  * @param  pin : one of the GPIO_Pin_x
  * @retval None
  */
void ch32_interrupt_enable(GPIO_TypeDef *port, GPIOMode_TypeDef io_mode,uint16_t pin, callback_function_t callback,EXTIMode_TypeDef it_mode, EXTITrigger_TypeDef trigger)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  uint8_t id = get_pin_id(pin);
  EXTI_InitTypeDef EXTI_InitStruct;

  GPIO_InitStruct.GPIO_Pin  = pin;
  GPIO_InitStruct.GPIO_Mode = io_mode;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(port, &GPIO_InitStruct);

  EXTI_InitStruct.EXTI_Line = pin;
  EXTI_InitStruct.EXTI_LineCmd = ENABLE;
  EXTI_InitStruct.EXTI_Mode = it_mode;
  EXTI_InitStruct.EXTI_Trigger = trigger;
  EXTI_Init(&EXTI_InitStruct);

  gpio_irq_conf[id].callback = callback;

  // Enable and set EXTI Interrupt
  NVIC_SetPriority(gpio_irq_conf[id].irqnb, EXTI_IRQ_PRIO);
  NVIC_EnableIRQ(gpio_irq_conf[id].irqnb);
}

/**
  * @brief  This function enable the interruption on the selected port/pin
  * @param  port : one of the gpio port
  * @param  pin : one of the gpio pin
  **@param  callback : callback to call when the interrupt falls
  * @param  mode : one of the supported interrupt mode defined in ch32_hal_gpio
  * @retval None
  */
void ch32_interrupt_enable(GPIO_TypeDef *port, GPIOMode_TypeDef io_mode, uint16_t pin, void (*callback)(void),EXTIMode_TypeDef it_mode, EXTITrigger_TypeDef trigger)
{
  std::function<void(void)> _c = callback;
  ch32_interrupt_enable(port,io_mode, pin, _c, it_mode,trigger);
}

/**
  * @brief  This function disable the interruption on the selected port/pin
  * @param  port : one of the gpio port
  * @param  pin : one of the gpio pin
  * @retval None
  */
void ch32_interrupt_disable(GPIO_TypeDef *port, uint16_t pin)
{
  UNUSED(port);
  uint8_t id = get_pin_id(pin);
  gpio_irq_conf[id].callback = NULL;

  for (int i = 0; i < NB_EXTI; i++) {
    if (gpio_irq_conf[id].irqnb == gpio_irq_conf[i].irqnb
        && gpio_irq_conf[i].callback != NULL) {
      return;
    }
  }
  NVIC_DisableIRQ(gpio_irq_conf[id].irqnb);
}

/**
  * @brief This function his called by the HAL if the IRQ is valid
  * @param  GPIO_Pin : one of the gpio pin
  * @retval None
  */
void GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  uint8_t irq_id = get_pin_id(GPIO_Pin);

  if (gpio_irq_conf[irq_id].callback != NULL) {
    gpio_irq_conf[irq_id].callback();
  }
}

#if defined (CH32V3xx)
/**
  * @brief  EXTI line detection callback.
  * @param  GPIO_Pin Specifies the port pin connected to corresponding EXTI line.
  * @retval None
  */
void GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin)
{
  GPIO_EXTI_Callback(GPIO_Pin);
}

/**
  * @brief  EXTI line detection callback.
  * @param  GPIO_Pin Specifies the port pin connected to corresponding EXTI line.
  * @retval None
  */
void GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
{
  GPIO_EXTI_Callback(GPIO_Pin);
}
#endif

/**
  * @brief This function handles external line 0 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI0_IRQHandler(void)
{
  GPIO_EXTI_IRQHandler(GPIO_Pin_0);
}

/**
  * @brief This function handles external line 1 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI1_IRQHandler(void)
{
  GPIO_EXTI_IRQHandler(GPIO_Pin_1);
}

/**
  * @brief This function handles external line 2 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI2_IRQHandler(void)
{
  GPIO_EXTI_IRQHandler(GPIO_Pin_2);
}

/**
  * @brief This function handles external line 3 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI3_IRQHandler(void)
{
  GPIO_EXTI_IRQHandler(GPIO_Pin_3);
}

/**
  * @brief This function handles external line 4 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI4_IRQHandler(void)
{
  GPIO_EXTI_IRQHandler(GPIO_Pin_4);
}


/**
  * @brief This function handles external line 5 to 9 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI9_5_IRQHandler(void)
{
  uint32_t pin;
  for (pin = GPIO_Pin_5; pin <= GPIO_Pin_9; pin = pin << 1) {
    GPIO_EXTI_IRQHandler(pin);
  }
}

/**
  * @brief This function handles external line 10 to 15 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI15_10_IRQHandler(void)
{
  uint32_t pin;
  for (pin = GPIO_Pin_10; pin <= GPIO_Pin_15; pin = pin << 1) {
    GPIO_EXTI_IRQHandler(pin);
  }
}

#endif /* !EXTI_MODULE_DISABLED */

/************************ (C) COPYRIGHT chicroelectronics *****END OF FILE****/
