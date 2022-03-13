/**
* @file
* @author
* @date
* @brief
* @see
*/

/*****************************************************************************
 * Headers
 *****************************************************************************/
#include "stdint.h"
#include "stdbool.h"
#include "stddef.h"
#include "stdio.h"
#include "stdlib.h"
#include "memio.h"
#include "armv7ar.h"
#include "msg.h"


/*****************************************************************************
 * Macro definitions
 *****************************************************************************/
/*****************************************************************************
 * Type definitions
 *****************************************************************************/
/*****************************************************************************
 * Enumerations
 *****************************************************************************/
/*****************************************************************************
 * Static variables
 *****************************************************************************/
/* ---------------------------------------------------------------------------
   - Variable
 --------------------------------------------------------------------------- */
 kernel_cir_q_t    s_msgq[KERNEL_MSGQ_NUM];

/* ---------------------------------------------------------------------------
   - Function
 --------------------------------------------------------------------------- */
/*****************************************************************************
 * Extern variables
 *****************************************************************************/
/* ---------------------------------------------------------------------------
   - Variable
 --------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------
   - Function
 --------------------------------------------------------------------------- */
/*****************************************************************************
 * Global variables
 *****************************************************************************/
/*****************************************************************************
 * Function prototypes
 *****************************************************************************/
void kernel_msgq_init( void )
{
    uint32_t i = 0;

    memset( s_msgq, 0, sizeof( s_msgq ));

    for ( ; i < KERNEL_MSGQ_NUM; i++ ) {
        s_msgq[i].front = 0;
        s_msgq[i].rear  = 0;
        memclr( s_msgq[i].queue, MSG_Q_SIZE_BYTE );
    }
}

bool kernel_msgq_is_empty( kernel_msg_q_t q_name )
{
    if ( q_name >= KERNEL_MSGQ_NUM )
        return false;

    if ( s_msgq[q_name].front == s_msgq[q_name].rear )
        return true;

    return false;
}

bool kernel_msgq_is_full( kernel_msg_q_t q_name )
{
    if ( q_name >= KERNEL_MSGQ_NUM )
        return false;

    if ((( s_msgq[q_name].rear + 1 ) % MSG_Q_SIZE_BYTE ) == s_msgq[q_name].front )
        return true;

    return false;
}

bool kernel_msgq_enqueue( kernel_msg_q_t q_name, uint8_t data )
{
    int32_t idx = -1;

    if ( q_name >= KERNEL_MSGQ_NUM )
        return false;

    if ( kernel_msgq_is_full( q_name ))
        return false;

    s_msgq[q_name].rear++;
    s_msgq[q_name].rear %= MSG_Q_SIZE_BYTE;
    
    idx = s_msgq[q_name].rear;
    s_msgq[q_name].queue[idx] = data;

    return true;
}

bool kernel_msgq_dequeue( kernel_msg_q_t q_name, uint8_t *out_data )
{
    int32_t idx = -1;

    if ( q_name >= KERNEL_MSGQ_NUM )
        return false;

    if ( kernel_msgq_is_empty( q_name ))
        return false;

    s_msgq[q_name].front++;
    s_msgq[q_name].front %= MSG_Q_SIZE_BYTE;
    
    idx = s_msgq[q_name].front;
    *out_data = s_msgq[q_name].queue[idx];

    return true;
}
