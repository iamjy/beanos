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
#include "timer.h"
#include "hal_timer.h"
#include "hal_interrupt.h"


/*****************************************************************************
 * Macro Definitions
 *****************************************************************************/
/*****************************************************************************
 * Type definitions
 *****************************************************************************/
/*****************************************************************************
 * Enumerations
 *****************************************************************************/
/*****************************************************************************
 * Static Variables
 *****************************************************************************/
/* ---------------------------------------------------------------------------
  - Variable
--------------------------------------------------------------------------- */
static uint32_t internal_1ms_counter;

/* ---------------------------------------------------------------------------
   - Function
 --------------------------------------------------------------------------- */
static void interrupt_handler( void *p_arg );


/*****************************************************************************
 * Extern Variables
 *****************************************************************************/
/* ---------------------------------------------------------------------------
  - Variable
--------------------------------------------------------------------------- */
extern volatile regs_pwm_t *g_timer;
extern volatile regs_pwm_stat_t *g_timer_isp;

/* ---------------------------------------------------------------------------
   - Function
 --------------------------------------------------------------------------- */
/*****************************************************************************
 * Global Variables
 *****************************************************************************/
/*****************************************************************************
 * Function Prototypes
 *****************************************************************************/
static void interrupt_handler( void *p_arg )
{
    internal_1ms_counter++;

    g_timer->intr_stat.bits.t4_intr_stat = 1;   //< TODO: ( temporality hard-coded )

    return;
}

int32_t HAL_timer_init( uint32_t intr_id )
{
    debug_printf( "[PWM] HAL_timer_init - ENTER\n" );

    timer_cfg_t tm;
    int32_t tm_num = -1;

    memset( &tm, 0, sizeof( tm ));

    if ( intr_id == GIC_INTID_TIMER_0 ) tm_num = PWM_TIMER_0;
    else if ( intr_id == GIC_INTID_TIMER_1 ) tm_num = PWM_TIMER_1;
    else if ( intr_id == GIC_INTID_TIMER_2 ) tm_num = PWM_TIMER_2;
    else if ( intr_id == GIC_INTID_TIMER_3 ) tm_num = PWM_TIMER_3;
    else if ( intr_id == GIC_INTID_TIMER_4 ) tm_num = PWM_TIMER_4;
    else {
        debug_printf( "[PWM][ERR] Invalid timer id! - LEAVE\n" );

        return -1;
    }

    internal_1ms_counter = 0;

    /**
	 * Configure PWM timer
	 */
    tm.clk_freq.prescaler = 1;
    tm.clk_freq.div       = 0;
    tm.clk_freq.dz_len    = 0;
    tm.cnt                = 1000;
    tm.a_reload           = 1;      //< TODO: ( temporality hard-coded )
    tm.m_update           = 0;      //< TODO: ( temporality hard-coded )
    tm.start              = 1;      //< TODO: ( temporality hard-coded )

    HAL_timer_configure( tm_num, &tm );

    /**
	 * Set PWM ( 0 ~ 4 ) Interrupt
	 */
    HAL_interrupt_register_handler( interrupt_handler, intr_id );    //< Register GIC PWM interrupt handler
    HAL_interrupt_enable( intr_id, &tm );                            //< Enable GIC PWM interrupt

    return 0;
}

void HAL_timer_deinit( uint32_t intr_id )
{
    debug_printf( "[PWM] HAL_timer_deinit - ENTER\n" );

    /**
	 * Set PWM ( 0 ~ 4 ) Interrupt
	 */
    HAL_interrupt_disable( intr_id, NULL );	        //< Disable GIC PWM Interrupt
    HAL_interrupt_unregister_handler( intr_id );    //< Unregister GIC PWM interrupt handler

    debug_printf( "[PWM] HAL_timer_deinit - LEAVE\n" );
}

void HAL_timer_enable( uint32_t tm_num, void *arg2 )
{
    timer_cfg_t *tm_cfg = ( timer_cfg_t * )arg2;

    g_timer->tm_conf.bits.t4_auto_reload = tm_cfg->a_reload;    //< TODO: ( temporality hard-coded )
    g_timer->tm_conf.bits.t4_m_update    = 0;                   //< TODO: ( temporality hard-coded )
    g_timer->intr_stat.bits.t4_intr_en   = 1;                   //< TODO: ( temporality hard-coded )
    g_timer->tm_conf.bits.t4_start       = tm_cfg->start;       //< TODO: ( temporality hard-coded )

    return;
}

void HAL_timer_disable( uint32_t tm_num )
{
    g_timer->tm_conf.bits.t4_start = 0;    //< TODO: (temporality hard-coded)

    return;
}

void HAL_timer_configure( uint32_t tm_num, void *arg2 )
{
    debug_printf( "[PWM] HAL_timer_configure - ENTER\n" );

    timer_cfg_t *tm_cfg = ( timer_cfg_t * )arg2;

    g_timer->tm_cfg0.bits.prescaler1    = tm_cfg->clk_freq.prescaler;    //< TODO: ( temporality hard-coded )
    g_timer->tm_cfg1.bits.div_mux4      = tm_cfg->clk_freq.div;          //< TODO: ( temporality hard-coded )
    g_timer->tm_cfg0.bits.dead_zone_len = tm_cfg->clk_freq.dz_len;       //< TODO: ( temporality hard-coded )
    g_timer->tm4_cnt.cnt                = tm_cfg->cnt;                   //< TODO: ( temporality hard-coded )
    g_timer->tm_conf.bits.t4_m_update   = 1;                             //< TODO: ( temporality hard-coded )

    HAL_timer_enable( tm_num, tm_cfg );

    debug_printf( "[PWM] HAL_timer_configure - LEAVE\n" );

    return;
}

uint32_t HAL_timer_get_1ms_counter( void )
{
    return internal_1ms_counter;
}