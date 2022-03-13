/**
* @file
* @author
* @date
* @brief
* @see
*/

/*****************************************************************************
 * Header Files
 *****************************************************************************/
#include "stdarg.h"
#include "stdint.h"
#include "stdlib.h"
#include "event.h"
#include "msg.h"
#include "kernel.h"
#include "regs.h"
#include "uart.h"
#include "hal_uart.h"
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
 * Global variables
 *****************************************************************************/
/*****************************************************************************
 * Static variables
 *****************************************************************************/
/* ---------------------------------------------------------------------------
   - Variable
 --------------------------------------------------------------------------- */
static uart_mng_t s_uart_mng[EXYNOS_UART_MAX_NUM];

/* ---------------------------------------------------------------------------
   - Function
 --------------------------------------------------------------------------- */
static void interrupt_handler( void *p_uart );    //< UART interrupt handler


/*****************************************************************************
 * Extern variables
 *****************************************************************************/
/* ---------------------------------------------------------------------------
   - Variable
 --------------------------------------------------------------------------- */
extern volatile regs_uart_t *g_uart;

/* ---------------------------------------------------------------------------
   - Function
 --------------------------------------------------------------------------- */
extern int vsprintf( char *buf, const char *fmt, va_list args );


/*****************************************************************************
 * Function definitions
 *****************************************************************************/
static void interrupt_handler( void *p_uart )
{
	uart_cfg_t *uart = ( uart_cfg_t * )p_uart;

	HAL_uart_debug_printf( "[GIC] UART interrupt!\n" );

	uint8_t ch = HAL_uart_get_char();

	/**
	* Sync Test (Mutex)
	*/
	if ( ch == 'U' )
		kernel_send_events( KERNEL_EVENT_FLAG_UNLOCK );
	else if ( ch == 'X' )
		kernel_send_events( KERNEL_EVENT_FLAG_CMD_OUT );
	else {
		HAL_uart_put_char( ch );

		kernel_send_msg( KERNEL_MSGQ_TASK_0, &ch, 1 );
		kernel_send_events( KERNEL_EVENT_FLAG_UART_IN );
	}

	/**
	* Sync Test ( Semaphore )
	*/
	#if 0
	if ( ch != 'X' ) {
		HAL_uart_put_char( ch );

		kernel_send_msg( KERNEL_MSGQ_TASK_0, &ch, 1 );
		kernel_send_events( KERNEL_EVENT_FLAG_UART_IN );
	}
	else
		kernel_send_events( KERNEL_EVENT_FLAG_CMD_OUT );
	#endif

	/**
	* Message Queue Test
	*/
	#if 0
	HAL_uart_put_char( ch );

	kernel_send_msg( KERNEL_MSGQ_TASK_0, &ch, 1 );
	kernel_send_events( KERNEL_EVENT_FLAG_UART_IN );
	#endif

	/**
	* Event Test
	*/
	#if 0
	HAL_uart_put_char( ch );

	kernel_send_events( KERNEL_EVENT_FLAG_UART_IN
					   | KERNEL_EVENT_FLAG_CMD_IN );

	if ( ch == 'X' )
		kernel_send_events( KERNEL_EVENT_FLAG_CMD_OUT );
	#endif

	g_uart->intrpt_pend.bits.rxd = 1;	//< Corresponding interrupt clear..

	return;
}

void HAL_uart_init( uint32_t baud_rate, uint32_t intr_id )
{
	debug_printf( "[PWM] HAL_uart_init - ENTER\n" );

	#if 1
	uart_cfg_t uart;
	#else
	uart_mng_t *uart = NULL;
	uart_cfg_t *cfg = NULL;
	regs_uart_t *regs = NULL;

	uart = &s_uart_mng[id];
    cfg = &uart->cfg;
    regs = &uart->regs;
	#endif
	
	memset( &uart, 0, sizeof( uart ));

	/**
	* Configure UART
	*/
	uart.prio = 0xA0;
	uart.target = 1;

	/**
	* Set UART ( Rx, Tx, Error, Modem ) Interrupt 
	*/
	uart.intr_mask = UART_INTR_MASK;
	g_uart->intrpt_mask.all = uart.intr_mask;    //< Mask all UART interrupt
	g_uart->intrpt_pend.all = uart.intr_mask;    //< Clear all UART interrupt

	HAL_interrupt_register_handler( interrupt_handler, intr_id );    //< Register GIC UART interrupt handler
	HAL_interrupt_enable( intr_id, &uart );						     //< Enable GIC UART interrupt	

	uart.intr_mask = UART_INTR_MASK & ~( UART_INTR_RX );
	g_uart->intrpt_mask.all = uart.intr_mask;    //< Unmask Rx interrupt

	debug_printf( "[PWM] HAL_uart_init - LEAVE\n" );

    return;
}

void HAL_uart_deinit( uint32_t intr_id )
{
	debug_printf( "[PWM] HAL_uart_deinit - ENTER\n" );

	uart_cfg_t uart;

	memset( &uart, 0, sizeof( uart ));

	/**
	* Set UART ( Rx, Tx, Error, Modem ) Interrupt 
	*/
	uart.intr_mask = UART_INTR_MASK;
	g_uart->intrpt_mask.all = uart.intr_mask;    //< Mask all UART interrupt
	g_uart->intrpt_pend.all = uart.intr_mask;    //< Clear all UART interrupt

	HAL_interrupt_disable( intr_id, NULL );		    //< Disable GIC UART interrupt
	HAL_interrupt_unregister_handler( intr_id );    //< Unregister GIC UART interrupt handler

	debug_printf( "[PWM] HAL_uart_deinit - LEAVE\n" );

	return;
}

void HAL_uart_put_char( char ch )
{
	if ( ch == '\n' ) {
		while (( rUTRSTAT2 & ( 1 << 1 )) == 0 );    //< Wait Tx Buffer Empty
		rUTXH2 = '\r';
	}

	while (( rUTRSTAT2 & ( 1 << 1 )) == 0 );    //< Wait Tx Buffer Empty
	rUTXH2 = ch;
}

void HAL_uart_put_string( char *str )
{
	while (*str) {
		HAL_uart_put_char(*(str++));
	}
}

void HAL_uart_debug_printf( const char *fmt, ... )
{
    va_list ap;
    char str[256];

    va_start( ap, fmt );
    vsprintf( str, fmt, ap );
    HAL_uart_put_string( str );
    va_end( ap );
}

char HAL_uart_get_char( void )
{
	while (( rUTRSTAT2 & 0x1 ) == 0 );    //< Wait Rx Buffer Data Ready
	return rURXH2;
}

char HAL_uart_get_key( void )
{
	if (( rUTRSTAT2 & 0x1 ) == 0 )    //< Check Rx Buffer Data Ready
		return 0;
	else
		return rURXH2;
}

void HAL_uart_get_string( char *str )
{
	char *str2 = str;
	char c;
	
	while (( c = HAL_uart_get_char() ) != '\r' ) {
		if ( c == '\b' ) {
			if ( (int)str2 < (int)str ) {
				HAL_uart_debug_printf( "\b \b" );
				str--;
			}
        }
        else {
			*( str++ ) = c;
			HAL_uart_put_char( c );
		}
	}

	( *str ) = '\0';
	HAL_uart_put_char( '\n' );
}

void uart_init ( void )
{

}

void uart_deinit ( void )
{

}

void uart_configure ( void )
{

}

uint32_t uart_base_address_get ( uint32_t id )
{

}

void uart_interrupt_register ( uint32_t id )
{

}

void uart_interrupt_unregister ( uint32_t id )
{

}

void uart_interrupt_enable ( uint32_t id )
{

}

void uart_interrupt_disable ( uint32_t id )
{

}

void uart_interrupt_clear ( uint32_t id )
{

}

uint32_t uart_interrupt_number_get ( uint32_t id )
{

}
