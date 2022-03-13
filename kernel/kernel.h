/**
* @file
* @author
* @date
* @brief
* @see
*/

#ifndef _KERNEL_KERNEL_H_
#define _KERNEL_KERNEL_H_

/*****************************************************************************
 * Header files
 *****************************************************************************/
#include "task.h"
#include "event.h"
#include "msg.h"


/*****************************************************************************
 * Macro definitions
 *****************************************************************************/
/*****************************************************************************
 * Enumerations
 *****************************************************************************/
/*****************************************************************************
 * Type definitions
 *****************************************************************************/
/*****************************************************************************
 * Structures
 *****************************************************************************/
/**
* @brief 
* @details 
* @see 
*/
/*****************************************************************************
 * Function prototypes
 *****************************************************************************/
/**
* @brief
* @param[in]
* @param[out]
* @return void
*/

void kernel_start( void );
void kernel_yield( void );

/**
* @brief
* @param[in]
* @param[out]
* @return void
*/
void kernel_send_events( uint32_t event_list );
uint32_t kernel_wait_events( uint32_t wait_list );

/**
* @brief
* @param[in]
* @param[out]
* @return void
*/
bool kernel_send_msg( kernel_msg_q_t q_name, void *data, uint32_t cnt );
uint32_t kernel_recv_msg( kernel_msg_q_t q_name, void *out_data, uint32_t cnt );

/**
* @brief
* @param[in]
* @param[out]
* @return void
*/
void kernel_lock_sem( void );
void kernel_unlock_sem( void );
void kernel_lock_mutex( void );
void kernel_unlock_mutex( void );

#endif /* _KERNEL_KERNEL_H_ */
