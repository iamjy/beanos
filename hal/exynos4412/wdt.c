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
#include "wdt.h"
#include "hal_wdt.h"
#include "hal_interrupt.h"


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
static void interrupt_handler( void *p_arg );

/*****************************************************************************
 * Extern variables
 *****************************************************************************/
/* ---------------------------------------------------------------------------
   - Variable
 --------------------------------------------------------------------------- */
extern volatile regs_wdt_t *g_wdt;


/*****************************************************************************
 * Global variables
 *****************************************************************************/
/*****************************************************************************
 * Function prototypes
 *****************************************************************************/
static void wdt_intr_handler( void *p_arg )
{
    g_wdt->wt_clrint.all = 1;   //< TODO: ( temporality hard-coded )

    return;
}

int32_t HAL_wdt_init( uint32_t intr_id )
{
    debug_printf( "[WDT] HAL_wdt_init - ENTER\n" );

    wdt_cfg_t wdt;

    memset( &wdt, 0, sizeof( wdt ));

    /**
	 * Configure PWM timer
	 */
    wdt.prescale = 0x80;    //< TODO: ( temporality hard-coded )
    wdt.clk_sel = WDT_CLK_SEL_16_DIV;
    wdt.intr_en = WDT_INTR_ENABLE;
    wdt.reset = WDT_RESET_DISABLE;
    wdt.timer_en = WDT_TIMER_ENABLE;

    HAL_wdt_configure( &wdt );

    /**
	 * Set PWM ( 0 ~ 4 ) Interrupt
	 */
    HAL_interrupt_register_handler( wdt_intr_handler, intr_id );    //< Register GIC PWM interrupt handler
    HAL_interrupt_enable( intr_id, &wdt );                          //< Enable GIC PWM interrupt

    debug_printf( "[WDT] HAL_wdt_init - LEAVE\n" );

    return 0;
}

void HAL_wdt_deinit( uint32_t intr_id )
{
    debug_printf( "[WDT] HAL_wdt_deinit - ENTER\n" );

    HAL_wdt_disable();

    /**
	 * Set PWM (0 ~ 4) Interrupt
	 */
    HAL_interrupt_disable( intr_id, NULL );         //< Disable GIC PWM Interrupt
    HAL_interrupt_unregister_handler( intr_id );    //< Unregister GIC PWM interrupt handler

    debug_printf( "[WDT] HAL_wdt_deinit - LEAVE\n" );

    return;
}

void HAL_wdt_configure( void *arg1 )
{
    debug_printf( "[WDT] HAL_wdt_configure - ENTER\n" );

    wdt_cfg_t *wdt_cfg = ( wdt_cfg_t * )arg1;

    g_wdt->wt_con.bits.prescale = wdt_cfg->prescale;
    g_wdt->wt_con.bits.clk_sel = wdt_cfg->clk_sel;
    g_wdt->wt_con.bits.intr_gen = wdt_cfg->intr_en;
    g_wdt->wt_con.bits.reset = wdt_cfg->reset;

    HAL_wdt_enable();

    debug_printf( "[WDT] HAL_wdt_configure - LEAVE\n" );

    return;
}

void HAL_wdt_enable( void )
{
    g_wdt->wt_con.bits.timer = WDT_TIMER_ENABLE;

    return;
}

void HAL_wdt_disable( void )
{
    g_wdt->wt_con.bits.timer = WDT_TIMER_DISABLE;

    return;
}
