//======================================================================
//文件名称：Os_United_API.h（RTOS函数通用接口头文件）
//框架提供：苏州大学嵌入式系统与物联网研究所（sumcu.suda.edu.cn）
//更新记录：20220525
//文件内容：宏定义RTOS的通用接口
//======================================================================
#ifndef Os_United_API_H   //防止重复定义
#define Os_United_API_H 

#include "Os_Self_API.h"
#define Thread_Start         RTThread_Start
#define thread_block()               //RT中为空

//（1）RT-Thread相关宏常数声明===================================================
//事件
#define EVENT_FLAG_AND               RT_EVENT_FLAG_AND 
#define EVENT_FLAG_OR                RT_EVENT_FLAG_OR
#define EVENT_FLAG_CLEAR             RT_EVENT_FLAG_CLEAR
//IPC相关标志
#define IPC_FLAG_FIFO                RT_IPC_FLAG_FIFO
#define IPC_FLAG_PRIO                RT_IPC_FLAG_PRIO
#define IPC_CMD_UNKNOWN              RT_IPC_CMD_UNKNOWN
#define IPC_CMD_RESET                RT_IPC_CMD_RESET
#define WAITING_FOREVER              RT_WAITING_FOREVER
#define WAITING_NO                   RT_WAITING_NO

#define EOK                          RT_EOK

//（2）RT-Thread相关函数声明===================================================
#define delay_ms             rt_thread_delay
#define thread_create        rt_thread_create
#define thread_startup       rt_thread_startup
//#define heap_init          heap_init
#define thread_self          rt_thread_self
//事件
#define event_create         rt_event_create
#define event_recv           rt_event_recv
#define event_send           rt_event_send
//信号量
#define sem_create           rt_sem_create
#define sem_take             rt_sem_take
#define sem_release          rt_sem_release
//#define sem_getNum         sem_getNum
//互斥量
#define mutex_create         rt_mutex_create
#define mutex_take           rt_mutex_take
#define mutex_release        rt_mutex_release
//消息队列
#define mq_create            rt_mq_create
#define mq_send              rt_mq_send
#define mq_recv              rt_mq_recv
#define OS_malloc            rt_malloc
#define sprintf              rt_sprintf
//#define mq_getIndex        mq_getIndex
//系统时间函数
#define tick_get             rt_tick_get

//（3）rt-thread源文件相关===================================================
#define TIMER_SKIP_LIST_LEVEL    RT_TIMER_SKIP_LIST_LEVEL
#define NAME_MAX                 RT_NAME_MAX

#define object_class_type   rt_object_class_type

#define base_t           rt_base_t            
#define uint32_t         rt_uint32_t           
#define base_t           rt_base_t        
#define ubase_t          rt_ubase_t     
       
#define True             RT_TRUE
#define False            RT_FALSE

#define OS_UINT8_MAX        RT_UINT8_MAX              
#define OS_UINT16_MAX       RT_UINT16_MAX          
#define OS_UINT32_MAX       RT_UINT32_MAX        
#define OS_TICK_MAX         RT_TICK_MAX        

#define OS_NULL             RT_NULL            

#define list_t  rt_list_t
#define slist_t rt_slist_t

#define OBJECT_FLAG_MODULE  RT_OBJECT_FLAG_MODULE

//（4）相关结构体的宏定义===================================================
#define object_t  rt_object_t
#define object_information rt_object_information
#define timer_t  rt_timer_t
#define thread_t  rt_thread_t
#define ipc_object rt_ipc_object
#define sem_t  rt_sem_t
#define mutex_t rt_mutex_t 
#define event_t rt_event_t
#define mailbox_t rt_mailbox_t
#define mq_t rt_mq_t

#endif    
