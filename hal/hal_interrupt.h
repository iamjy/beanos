/**
 * @file
 * @author
 * @date
 * @brief
 * @see
 */

#ifndef _HAL_INTERRUPT_H
#define _HAL_INTERRUPT_H

/*****************************************************************************
 * Headers
 *****************************************************************************/
#include "stdint.h"
#include "stdbool.h"
#include "stddef.h"
#include "interrupt.h"


/*****************************************************************************
 * Macro Definitions
 *****************************************************************************/
/* ---------------------------------------------------------------------------
   - 
 --------------------------------------------------------------------------- */
#define INTERRUPT_HANDLER_NUM    ( 255 )


/*****************************************************************************
 * Type Definition
 *****************************************************************************/
typedef void ( *intr_handler_fptr )( void * );


/*****************************************************************************
 * Structures
 *****************************************************************************/
/**
* @brief 
* @details 
* @see 
*/
/*****************************************************************************
 * Function Prototypes
 *****************************************************************************/
/**
* @brief
* @param[in]
* @param[out]
* @return void
*/
void HAL_interrupt_init( void *arg1 );
void HAL_interrupt_deinit( void );
int32_t HAL_interrupt_enable( uint32_t intr_id, void *arg2 );
int32_t HAL_interrupt_disable( uint32_t intr_id, void *arg2 );
void HAL_interrupt_register_handler( intr_handler_fptr hdl, uint32_t intr_id );
void HAL_interrupt_unregister_handler( uint32_t intr_id );
void HAL_interrupt_run_handler( uint32_t irq_num, void *arg2 );

#endif /* _HAL_INTERRUPT_H */
