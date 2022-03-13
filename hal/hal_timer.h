/**
 * @file
 * @author
 * @date
 * @brief
 * @see
 */

#ifndef _HAL_UART_H
#define _HAL_UART_H

/*****************************************************************************
 * Headers
 *****************************************************************************/
#include "stdint.h"
#include "stdbool.h"
#include "stddef.h"
#include "interrupt.h"


/*****************************************************************************
 * Macro definitions
 *****************************************************************************/
/* ---------------------------------------------------------------------------
   - 
 --------------------------------------------------------------------------- */
/*****************************************************************************
 * Type definition
 *****************************************************************************/
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
/*****************************************************************************
 * Function prototypes
 *****************************************************************************/
/**
* @brief
* @param[in]
* @param[out]
* @return void
*/
int32_t HAL_timer_init( uint32_t intr_id );
void HAL_timer_deinit( uint32_t intr_id );
void HAL_timer_configure( uint32_t tm_num, void *arg2 );
void HAL_timer_enable( uint32_t tm_num, void *arg2 );
void HAL_timer_disable( uint32_t tm_num );
uint32_t HAL_timer_get_1ms_counter( void );   //< TODO: 

#endif /* _HAL_UART_H */