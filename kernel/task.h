/**
* @file
* @author
* @date
* @brief
* @see
*/

#ifndef _KERNEL_TASK_H_
#define _KERNEL_TASK_H_

/*****************************************************************************
 * Header files
 *****************************************************************************/
#include "memory_map.h"


/*****************************************************************************
 * Macro definitions
 *****************************************************************************/
#define NOT_ENOUGH_TASK_NUM     0xFFFFFFFF

#define USR_TASK_STACK_SIZE     0x100000                                //< 1MiB
#define MAX_TASK_NUM            (TASK_STACK_SIZE / USR_TASK_STACK_SIZE) //< Total task : 64


/*****************************************************************************
 * Type definitions
 *****************************************************************************/
typedef void (*kernel_task_func_t)(void);


/*****************************************************************************
 * Enumerations
 *****************************************************************************/
/*****************************************************************************
 * Structures
 *****************************************************************************/
/**
* @brief 
* @details 
* @see 
*/
typedef struct _kernel_task_context_t {
    uint32_t spsr;
    uint32_t r0_r12[13];
    uint32_t pc;
} kernel_task_context_t;

/**
* @brief 
* @details 
* @see 
*/
typedef struct _kernel_tcb_t {
    uint32_t sp;
    uint8_t *stack_base;
} kernel_tcb_t;


/*****************************************************************************
 * Function prototypes
 *****************************************************************************/
/**
* @brief
* @param[in]
* @param[out]
* @return void
*/
void kernel_task_init( void );
void kernel_task_start( void );
uint32_t kernel_task_create( kernel_task_func_t start_func );
void kernel_task_scheduler( void );
uint32_t Kernel_task_get_current_task_id( void );

#endif /* _KERNEL_TASK_H_ */
