/**
 * @file
 * @author
 * @date
 * @brief
 * @see
 */

#ifndef _HAL_WDT_H
#define _HAL_WDT_H

/*****************************************************************************
 * Headers
 *****************************************************************************/
#include "stdint.h"
#include "stdbool.h"
#include "stddef.h"


/*****************************************************************************
 * Macro definitions
 *****************************************************************************/
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
* @see 
*/
/*****************************************************************************
 * Function prototypes
 *****************************************************************************/
/**
* @brief
* @param
* @return
*/
int32_t HAL_wdt_init ( uint32_t intr_id );
void HAL_wdt_deinit  (uint32_t intr_id );
void HAL_wdt_configure ( void *arg1 );
void HAL_wdt_enable ( void );
void HAL_wdt_disable( void );

#endif /* _HAL_WDT_H */
