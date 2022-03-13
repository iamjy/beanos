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
#include "kernel.h"
#include "task.h"
#include "synch.h"
#include "event.h"


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
/*****************************************************************************
 * Extern variables
 *****************************************************************************/
/*****************************************************************************
 * Global variables
 *****************************************************************************/
/*****************************************************************************
 * Function prototypes
 *****************************************************************************/
void kernel_start( void )
{
    kernel_task_start();
}

void kernel_yield( void )
{
    kernel_task_scheduler();
}

void kernel_send_events( uint32_t event_list )
{
    uint32_t send_evt = KERNEL_EVENT_FLAG_EMPTY;
    uint32_t i = 0;

    for ( i = 0; i < 32; i++ ) {
        if (( event_list >> i ) & 1 ) {
            SET_BIT( send_evt, i );
            
            kernel_event_flag_set(( kernel_event_flag_t )send_evt );
        }
    }
}

uint32_t kernel_wait_events( uint32_t wait_list )
{
    uint32_t wait_evt = KERNEL_EVENT_FLAG_EMPTY;
    uint32_t i = 0;

    for ( i = 0; i < 32; i++ ) {
        if (( wait_list >> i ) & 1 ) {
            SET_BIT( wait_evt, i );
            
            if ( kernel_event_flag_check(( kernel_event_flag_t )wait_evt ))
                return wait_evt;
            else
                CLR_BIT( wait_evt, i );   //< No pending event or done event must be clear in here..
        }
    }

    return KERNEL_EVENT_FLAG_EMPTY;
}


bool kernel_send_msg( kernel_msg_q_t q_name, void *data, uint32_t cnt )
{
    uint8_t *write = ( uint8_t * )data;
    uint32_t w_cnt = 0, r_cnt = 0;

    for ( ; w_cnt < cnt; w_cnt++ ) {
        if ( false == kernel_msgq_enqueue(q_name, *write )) {
            for ( ; r_cnt < w_cnt; r_cnt++ ) {
                uint8_t rollback;
                kernel_msgq_dequeue( q_name, &rollback );
            }

            return false;
        }

        write++;
    }

    return true;
}

uint32_t kernel_recv_msg( kernel_msg_q_t q_name, void *out_data, uint32_t cnt )
{
    uint8_t *read = ( uint8_t * )out_data;
    uint32_t r_cnt = 0;

    for ( ; r_cnt < cnt; r_cnt++ ) {
        if ( false == kernel_msgq_dequeue( q_name, read ))
            return r_cnt;
        
        read++;
    }

    return r_cnt;
}

void kernel_lock_sem( void )
{
    while ( false == kernel_sem_lock() ) {
        kernel_yield();
    }
}

void kernel_unlock_sem( void )
{
    kernel_sem_unlock();
}

void kernel_lock_mutex( void )
{
    while ( true ) {
        uint32_t cur_task_id = Kernel_task_get_current_task_id();

        if ( false == kernel_mutex_lock( cur_task_id ))
            kernel_yield();
        else
            break;
    }
}

void kernel_unlock_mutex( void )
{
    while ( true ) {
        uint32_t cur_task_id = Kernel_task_get_current_task_id();

        if ( false == kernel_mutex_unlock( cur_task_id ))
            kernel_yield();
        else
            break;
    }
}
