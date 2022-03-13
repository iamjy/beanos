/**
* @file
* @author
* @date
* @brief
* @see
*/

#ifndef _KERNEL_EVENT_H_
#define _KERNEL_EVENT_H_

/*****************************************************************************
 * Header files
 *****************************************************************************/
#include "stdbool.h"


/*****************************************************************************
 * Macro definitions
 *****************************************************************************/
/*****************************************************************************
 * Type definitions
 *****************************************************************************/
/*****************************************************************************
 * Enumerations
 *****************************************************************************/
typedef enum _kernel_event_flag_t {
    KERNEL_EVENT_FLAG_UART_IN     = 0x00000001,
    KERNEL_EVENT_FLAG_CMD_IN      = 0x00000002,
    KERNEL_EVENT_FLAG_CMD_OUT     = 0x00000004,
    KERNEL_EVENT_FLAG_UNLOCK      = 0x00000008,
    KERNEL_EVENT_FLAG_RESERVED_04 = 0x00000010,
    KERNEL_EVENT_FLAG_RESERVED_05 = 0x00000020,
    KERNEL_EVENT_FLAG_RESERVED_06 = 0x00000040,
    KERNEL_EVENT_FLAG_RESERVED_07 = 0x00000080,
    KERNEL_EVENT_FLAG_RESERVED_08 = 0x00000100,
    KERNEL_EVENT_FLAG_RESERVED_09 = 0x00000200,
    KERNEL_EVENT_FLAG_RESERVED_10 = 0x00000400,
    KERNEL_EVENT_FLAG_RESERVED_11 = 0x00000800,
    KERNEL_EVENT_FLAG_RESERVED_12 = 0x00001000,
    KERNEL_EVENT_FLAG_RESERVED_13 = 0x00002000,
    KERNEL_EVENT_FLAG_RESERVED_14 = 0x00004000,
    KERNEL_EVENT_FLAG_RESERVED_15 = 0x00008000,
    KERNEL_EVENT_FLAG_RESERVED_16 = 0x00010000,
    KERNEL_EVENT_FLAG_RESERVED_17 = 0x00020000,
    KERNEL_EVENT_FLAG_RESERVED_18 = 0x00040000,
    KERNEL_EVENT_FLAG_RESERVED_19 = 0x00080000,
    KERNEL_EVENT_FLAG_RESERVED_20 = 0x00100000,
    KERNEL_EVENT_FLAG_RESERVED_21 = 0x00200000,
    KERNEL_EVENT_FLAG_RESERVED_22 = 0x00400000,
    KERNEL_EVENT_FLAG_RESERVED_23 = 0x00800000,
    KERNEL_EVENT_FLAG_RESERVED_24 = 0x01000000,
    KERNEL_EVENT_FLAG_RESERVED_25 = 0x02000000,
    KERNEL_EVENT_FLAG_RESERVED_26 = 0x04000000,
    KERNEL_EVENT_FLAG_RESERVED_27 = 0x08000000,
    KERNEL_EVENT_FLAG_RESERVED_28 = 0x10000000,
    KERNEL_EVENT_FLAG_RESERVED_29 = 0x20000000,
    KERNEL_EVENT_FLAG_RESERVED_30 = 0x40000000,
    KERNEL_EVENT_FLAG_RESERVED_31 = 0x80000000,
    KERNEL_EVENT_FLAG_EMPTY       = 0x00000000,
} kernel_event_flag_t;


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
void kernel_event_flag_init( void );
void kernel_event_flag_set( kernel_event_flag_t event );
void kernel_event_flag_clear( kernel_event_flag_t event );
bool kernel_event_flag_check( kernel_event_flag_t event );

#endif /* _KERNEL_EVENT_H_ */
