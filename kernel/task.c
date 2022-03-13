/**
* @file
* @author
* @date
* @brief
* @see
*/

/*****************************************************************************
 * Header files
 *****************************************************************************/
#include "stdint.h"
#include "stdbool.h"
#include "stddef.h"
#include "stdlib.h"
#include "armv7ar.h"
#include "task.h"


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
   - Task Control Block
 --------------------------------------------------------------------------- */
static kernel_tcb_t     s_task_list[MAX_TASK_NUM];
static uint32_t         s_allocated_tcb_idx;

/* ---------------------------------------------------------------------------
   - Task Scheduling
 --------------------------------------------------------------------------- */
static uint32_t         s_cur_tcb_idx;
static kernel_tcb_t    *s_scheduler_round_robin_algo(void);

/* ---------------------------------------------------------------------------
   - Task Context Switching
 --------------------------------------------------------------------------- */
static kernel_tcb_t *s_cur_tcb = NULL;
static kernel_tcb_t *s_next_tcb = NULL;

static __attribute__ ((naked)) void s_kernel_task_context_switching(void);
static __attribute__ ((naked)) void s_save_context(void);
static __attribute__ ((naked)) void s_restore_context(void);

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
 * Global Variables
 *****************************************************************************/
/*****************************************************************************
 * Function prototypes
 *****************************************************************************/
void kernel_task_init( void )
{
    kernel_task_context_t *ctx = NULL;
    s_allocated_tcb_idx = 0;
    s_cur_tcb_idx = 0;

    memset( s_task_list, 0, sizeof( s_task_list ));

    for ( uint32_t i = 0; i < MAX_TASK_NUM; i++ ) {
        s_task_list[i].stack_base = ( uint8_t * )( TASK_STACK_START + ( i * USR_TASK_STACK_SIZE ));
        s_task_list[i].sp = ( uint32_t )s_task_list[i].stack_base + USR_TASK_STACK_SIZE - 4;

        s_task_list[i].sp -= sizeof( kernel_task_context_t );
        ctx = ( kernel_task_context_t * )s_task_list[i].sp;
        ctx->pc = 0;
        ctx->spsr = ARM_MODE_BIT_SYS;
    }

    return;
}

uint32_t kernel_task_create( kernel_task_func_t start_func )
{
    kernel_tcb_t *new_tcb = &s_task_list[s_allocated_tcb_idx++];

    if ( s_allocated_tcb_idx > MAX_TASK_NUM )
        return NOT_ENOUGH_TASK_NUM;

    kernel_task_context_t *ctx = ( kernel_task_context_t * )new_tcb->sp;
    ctx->pc = ( uint32_t )start_func;

    return ( s_allocated_tcb_idx - 1 );
}

void kernel_task_scheduler( void )
{
    s_cur_tcb = &s_task_list[s_cur_tcb_idx];
    s_next_tcb = s_scheduler_round_robin_algo();

    s_kernel_task_context_switching();
}

static kernel_tcb_t *s_scheduler_round_robin_algo( void )
{
    s_cur_tcb_idx++;
    s_cur_tcb_idx %= s_allocated_tcb_idx;

    return &s_task_list[s_cur_tcb_idx];
}

static __attribute__ (( naked )) void s_kernel_task_context_switching( void )
{
    __asm__ ( "B s_save_context" );
    __asm__ ( "B s_restore_context" );
}

static __attribute__ (( naked )) void s_save_context( void )
{
    /**
     * Save current task context into the current task stack
     */
    __asm__ ( "PUSH {lr}" );
    __asm__ ( "PUSH {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}" );
    __asm__ ( "MRS r0, cpsr" );
    __asm__ ( "PUSH {r0}" );

    /**
     * Save current task stack pointer into the current TCB 
     */
    __asm__ ( "LDR r0, =s_cur_tcb" );
    __asm__ ( "LDR r0, [r0]" );
    __asm__ ( "STMIA r0!, {sp}" );
}

static __attribute__ (( naked )) void s_restore_context( void )
{
    /**
     * Restore next task stack pointer from the next TCB
     */
    __asm__ ( "LDR r0, =s_next_tcb" );
    __asm__ ( "LDR r0, [r0]" );
    __asm__ ( "LDMIA r0!, {sp}" );
    
    /**
     * Restore next task context from the next task stack 
     */
    __asm__ ( "POP {r0}" );
    __asm__ ( "MSR cpsr, r0" );
    __asm__ ( "POP {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}" );
    __asm__ ( "POP {pc}" );
}

void kernel_task_start( void )
{
    s_next_tcb = &s_task_list[s_cur_tcb_idx];

    s_restore_context();
}

uint32_t Kernel_task_get_current_task_id( void )
{
    return s_cur_tcb_idx;
}
