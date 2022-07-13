//===========================================================================
//�ļ����ƣ�gpio.h
//���ܸ�Ҫ��GPIO�ײ���������ͷ�ļ�
//��Ȩ���У�SD-Arm(sumcu.suda.edu.cn)
//�汾���£�20190520-20200221
//оƬ���ͣ�CH32
//===========================================================================
#ifndef _GPIO_H_
#define _GPIO_H_

#include "mcu.h"

//  �˿ںŵ�ַƫ�����궨��
#define PTA_NUM    (0<<8)
#define PTB_NUM    (1<<8)
#define PTC_NUM    (2<<8)
#define PTD_NUM    (3<<8)
#define PTE_NUM    (4<<8)

//#define LED1    (PTA_NUM|0)
//#define PTF_NUM    (5<<8)
//#define PTG_NUM    (6<<8)

// GPIO���ŷ���궨��
#define GPIO_INPUT  (4)      //GPIO����
#define GPIO_OUTPUT (1)      //GPIO���?
// GPIO�������ߵ�״̬�궨��
#define PULL_UP    (0x01u)   //����
#define PULL_DOWN  (0x00u)   //����
// GPIO�����ж����ͺ궨��
#define RISING_EDGE  (0x08)     //�����ش���
#define FALLING_EDGE (0x0C)     //�½��ش���
#define DOUBLE_EDGE  (0x10)     //˫���ش���

// GPIO������ʺ궨��
#define GPIOSpeed_2MHz     (0x02u)  //����
#define GPIOSpeed_10MHz    (0x01u)  //����
#define GPIOSpeed_50MHz    (0x03u)  //����

//EXTIģʽ�궨��
#define EXTI_Mode_Interrupt     (0x00)  //�ж�
#define EXTI_Mode_Event     (0x04)  //�¼�

//=====================================================================
//�������ƣ�gpio_init
//�������أ���
//����˵����port_pin��(�˿ں�)|(���ź�)���磺(PTB_NUM)|(9) ��ʾΪB��9�Žţ�
//         dir�����ŷ���0=���룬1=���,�������ŷ���궨�壩
//         state���˿����ų�ʼ״̬��0=�͵�ƽ��1=�ߵ�ƽ��
//���ܸ�Ҫ����ʼ��ָ���˿�������ΪGPIO���Ź��ܣ�������Ϊ�������������������
//         ��ָ����ʼ״̬�ǵ͵�ƽ��ߵ�ƽ
//=====================================================================
void gpio_init(uint16_t port_pin, uint8_t dir, uint8_t state);

//=====================================================================
//�������ƣ�gpio_set
//�������أ���
//����˵����port_pin��(�˿ں�)|(���ź�)���磺(PTB_NUM)|(9) ��ʾΪB��9�Žţ�
//          state��ϣ�����õĶ˿�����״̬��0=�͵�ƽ��1=�ߵ�ƽ��
//���ܸ�Ҫ����ָ���˿����ű�����ΪGPIO������Ϊ���ʱ���������趨����״̬
//=====================================================================
void gpio_set(uint16_t port_pin, uint8_t state);

//=====================================================================
//�������ƣ�gpio_get
//�������أ�ָ���˿����ŵ�״̬��1��0��
//����˵����port_pin��(�˿ں�)|(���ź�)���磺(PTB_NUM)|(9) ��ʾΪB��9�Žţ�
//���ܸ�Ҫ����ָ���˿����ű�����ΪGPIO������Ϊ����ʱ����������ȡָ������״̬
//=====================================================================
uint8_t gpio_get(uint16_t port_pin);

//=====================================================================
//�������ƣ�gpio_reverse
//�������أ���
//����˵����port_pin��(�˿ں�)|(���ź�)���磺(PTB_NUM)|(9) ��ʾΪB��9�Žţ�
//���ܸ�Ҫ����ָ���˿����ű�����ΪGPIO������Ϊ���ʱ����������ת����״̬
//=====================================================================
void gpio_reverse(uint16_t port_pin);

//=====================================================================
//�������ƣ�gpio_pull
//�������أ���
//����˵����port_pin��(�˿ں�)|(���ź�)���磺(PTB_NUM)|(9) ��ʾΪB��9�Žţ�
//       pullselect������/������PULL_DOWN=������PULL_UP=������
//���ܸ�Ҫ����ָ���˿����ű�����ΪGPIO������Ϊ����ʱ��������������������/����
void gpio_pull(uint16_t port_pin, uint8_t pullselect);

//=====================================================================
//�������ƣ�gpio_enable_int
//�������أ���
//����˵����port_pin��(�˿ں�)|(���ź�)���磺(PTB_NUM)|(9) ��ʾΪB��9�Žţ�
//          irqtype�������ж����ͣ��ɺ궨��������ٴ��о����£�
//                  RISING_EDGE  9      //�����ش���
//                  FALLING_EDGE 10     //�½��ش���
//                  DOUBLE_EDGE  11     //˫���ش���
//���ܸ�Ҫ����ָ���˿����ű�����ΪGPIO������Ϊ����ʱ�����������������жϣ���
//          �����жϴ���������
//ע          �⣺ KL25оƬ��ֻ��PORTA��PORTD�ھ���GPIO���жϹ���
//         KW01оƬ��ֻ��PORTA��PORTC��PORTD�ھ���GPIO���жϹ���
//         KL36оƬ��ֻ��PORTA��PORTC��PORTD�ھ���GPIO���жϹ���
//        STM32L433оƬ��PORTA��PORTB��PORTC��PORTH�ھ���GPIO���жϹ���,��EXIT(��չ
//                     �ж�)�����ã���ֻ���������ش������½��ش�����˫���ش������������ж�����
void gpio_enable_int(uint16_t port_pin,uint8_t irqtype);

//=====================================================================
//�������ƣ�gpio_disable_int
//�������أ���
//����˵����port_pin��(�˿ں�)|(���ź�)���磺(PTB_NUM)|(9) ��ʾΪB��9�Žţ�
//���ܸ�Ҫ����ָ���˿����ű�����ΪGPIO������Ϊ����ʱ���������ر������ж�
//ע          �⣺ KL25оƬ��ֻ��PORTA��PORTD�ھ���GPIO���жϹ���
//         KW01оƬ��ֻ��PORTA��PORTC��PORTD�ھ���GPIO���жϹ���
//         KL36оƬ��ֻ��PORTA��PORTC��PORTD�ھ���GPIO���жϹ���
//        STM32L433оƬ��PORTA��PORTB��PORTC��PORTH�ھ���GPIO���жϹ���,��EXIT(��չ
//                     �ж�)�����ã���ֻ���������ش������½��ش�����˫���ش������������ж�����
//=====================================================================
void gpio_disable_int(uint16_t port_pin);

//=====================================================================
//�������ƣ�gpio_drive_strength
//�������أ���
//����˵����port_pin��(�˿ں�)|(���ź�)���磺(PTB_NUM)|(9) ��ʾΪB��9�Žţ�
//       control���������ŵ�����������LOW_SPEED=����,MSDIUM_SPEED=����
//               HIGH_SPEED=����,VERY_HIGH_SPEED=������
//���ܸ�Ҫ������������������ָ�����������������ĳ�������һ����mA��λ����
//        ��������������5mA,����������18mA���������ű�����Ϊ�������ʱ,
//        �����ŵ�����������������
//=====================================================================
void gpio_drive_strength(uint16_t port_pin, uint8_t control);

//=====================================================================
//�������ƣ�gpio_get_int
//�������أ�����GPIO�жϱ�־��1��0��1��ʾ������GPIO�жϣ�0��ʾ����û��GPIO�жϡ�
//����˵����port_pin��(�˿ں�)|(���ź�)���磺(PTB_NUM)|(9) ��ʾΪB��9�Žţ�
//���ܸ�Ҫ����ָ���˿����ű�����ΪGPIO������Ϊ����ʱ,��ȡ�жϱ�־��
//ע          �⣺ KL25оƬ��ֻ��PORTA��PORTD�ھ���GPIO���жϹ���
//        KW01оƬ��ֻ��PORTA��PORTC��PORTD�ھ���GPIO���жϹ���
//        KL36оƬ��ֻ��PORTA��PORTC��PORTD�ھ���GPIO���жϹ���
//        STM32L433оƬ��PORTA��PORTB��PORTC��PORTH�ھ���GPIO���жϹ���,��EXIT(��չ
//                     �ж�)�����ã���ֻ���������ش������½��ش�����˫���ش������������ж�����
//=====================================================================
uint8_t gpio_get_int(uint16_t port_pin);

//=====================================================================
//�������ƣ�gpio_clear_int
//�������أ���
//����˵����port_pin��(�˿ں�)|(���ź�)���磺(PTB_NUM)|(9) ��ʾΪB��9�Žţ�
//���ܸ�Ҫ����ָ���˿����ű�����ΪGPIO������Ϊ����ʱ,����жϱ�־��
//ע          �⣺ KL25оƬ��ֻ��PORTA��PORTD�ھ���GPIO���жϹ���
//         KW01оƬ��ֻ��PORTA��PORTC��PORTD�ھ���GPIO���жϹ���
//         KL36оƬ��ֻ��PORTA��PORTC��PORTD�ھ���GPIO���жϹ���
//        STM32L433оƬ��PORTA��PORTB��PORTC��PORTH�ھ���GPIO���жϹ���,��EXIT(��չ
//                     �ж�)�����ã���ֻ���������ش������½��ش�����˫���ش������������ж�����
//=====================================================================
void gpio_clear_int(uint16_t port_pin);

//=====================================================================
//�������ƣ�gpio_clear_allint
//�������أ���
//����˵������
//���ܸ�Ҫ��������ж˿ڵ�GPIO�ж�
//ע          �⣺ KL25оƬ��ֻ��PORTA��PORTD�ھ���GPIO���жϹ���
//         KW01оƬ��ֻ��PORTA��PORTC��PORTD�ھ���GPIO���жϹ���
//         KL36оƬ��ֻ��PORTA��PORTC��PORTD�ھ���GPIO���жϹ���
//        STM32L433оƬ��PORTA��PORTB��PORTC��PORTH�ھ���GPIO���жϹ���,��EXIT(��չ
//                     �ж�)�����ã���ֻ���������ش������½��ش�����˫���ش������������ж�����
//=====================================================================
void gpio_clear_allint(void);


#endif /* 05_USERBOARD_GPIO_H_ */