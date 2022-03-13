/**
* @file
* @author
* @date
* @brief
* @see
*/

#ifndef _KERNEL_MSG_H_
#define _KERNEL_MSG_H_

/*****************************************************************************
 * Header files
 *****************************************************************************/
#include "stdbool.h"


/*****************************************************************************
 * Macro definitions
 *****************************************************************************/
#define MSG_Q_SIZE_BYTE    512


/*****************************************************************************
 * Type definitions
 *****************************************************************************/
 /*****************************************************************************
 * Enumerations
 *****************************************************************************/
typedef enum _kernel_msg_q_t {
    KERNEL_MSGQ_TASK_0,
    KERNEL_MSGQ_TASK_1,
    KERNEL_MSGQ_TASK_2,
    KERNEL_MSGQ_NUM
} kernel_msg_q_t;


/*****************************************************************************
 * Structures
 *****************************************************************************/
/* ---------------------------------------------------------------------------
   - 
 --------------------------------------------------------------------------- */
/**
* @brief 
* @details 
* @see 
*/
typedef struct _kernel_cir_q_t {
    uint32_t front;
    uint32_t rear;
    uint8_t queue[MSG_Q_SIZE_BYTE];
} kernel_cir_q_t;


/*****************************************************************************
 * Function prototypes
 *****************************************************************************/
/**
* @brief
* @param[in]
* @param[out]
* @return void
*/
void kernel_msgq_init( void );
bool kernel_msgq_is_empty( kernel_msg_q_t q_name );
bool kernel_msgq_is_full( kernel_msg_q_t q_name );
bool kernel_msgq_enqueue( kernel_msg_q_t q_name, uint8_t data );
bool kernel_msgq_dequeue( kernel_msg_q_t q_name, uint8_t *out_data );

#endif /* _KERNEL_MSG_H_ */
