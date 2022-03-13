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
#include "stdio.h"
#include "stdlib.h"
#include "interrupt.h"
#include "hal_interrupt.h"


/*****************************************************************************
 * Macro definitions
 *****************************************************************************/
/*****************************************************************************
 * Enumerations
 *****************************************************************************/
/*****************************************************************************
 * Type definitions
 *****************************************************************************/
/*****************************************************************************
 * Extern variables
 *****************************************************************************/
extern volatile regs_gic_cpu_t     *gic_cpu;


/*****************************************************************************
 * Functions
 *****************************************************************************/
 __attribute__ ((interrupt ("IRQ"))) void irq_Handler(void)
{
    uint32_t irq_num = gic_cpu->intr_ack.bits.ack_id;

    HAL_interrupt_run_handler(irq_num, NULL);

    gic_cpu->end_of_intr.bits.eo_id |= (gic_cpu->intr_ack.bits.ack_id & 0x3FF);
    gic_cpu->end_of_intr.bits.eo_id |= irq_num;
}

 __attribute__ ((interrupt ("FIQ"))) void fiq_Handler(void)
{
    while(true);
}
