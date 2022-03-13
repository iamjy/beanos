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
#include "common.h"
#include "armcpu.h"
#include "memio.h"
#include "interrupt.h"
#include "hal_interrupt.h"


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
 * Static variables
 *****************************************************************************/
/* ---------------------------------------------------------------------------
   - Variable
 --------------------------------------------------------------------------- */
static intr_handler_fptr s_handlers[INTERRUPT_HANDLER_NUM];
// static uint32_t *(s_handlers_args[125])[4]

/* ---------------------------------------------------------------------------
   - Function
 --------------------------------------------------------------------------- */
/*****************************************************************************
 * Extern variables
 *****************************************************************************/
/* ---------------------------------------------------------------------------
   - Variable
 --------------------------------------------------------------------------- */
extern volatile regs_gic_cpu_t     *gic_cpu;
extern volatile regs_gic_dist_t    *gic_dist;
extern volatile regs_icciidr_t     *icciidr;
extern volatile regs_secur_stat_t  *dist_secur_stat;
extern volatile regs_set_en_t      *dist_set_en;
extern volatile regs_clear_en_t    *dist_clr_en;
extern volatile regs_icdispr_t     *dist_icdispr;
extern volatile regs_icdicpr_t     *dist_icdicpr;
extern volatile regs_icdabr_t      *dist_icdabr;
extern volatile regs_icdipr_t      *dist_icdipr;
extern volatile regs_icdiptr_t     *dist_icdiptr;
extern volatile regs_icdicfr_t     *dist_icdicfr;
extern volatile regs_intr_stat_t   *dist_intr_stat;
extern volatile regs_icdsgir_t     *dist_icdsgir;

/* ---------------------------------------------------------------------------
   - Function
 --------------------------------------------------------------------------- */
/*****************************************************************************
 * Global variables
 *****************************************************************************/
/*****************************************************************************
 * Function Definitons
 *****************************************************************************/
void HAL_interrupt_init( void *arg1 )
{
    debug_printf( "[GIC] HAL_interrupt_init - ENTER\n" );

    uint32_t i;
    uint32_t mask = *( uint32_t * ) arg1;

    for ( i = 0; i < INTERRUPT_HANDLER_NUM; i++)
        s_handlers[i] = NULL;

    /**
    * Configure DIST
    */
    gic_dist->dist_ctrl.bits.enable = ENABLE;    //< Enable distributor

    /**
    * Configure CPU I/F
    */
    gic_cpu->priority_mask.bits.mask = mask;    //< Determine range of interrupt priority - T.B.D Hard coding...
    gic_cpu->cpu_ctrl.bits.enable = ENABLE;     //< Enable CPU interface

    /**
    * Enable IRQ Mode in CPSR
    */
    enable_irq();

    debug_printf( "[GIC] HAL_interrupt_init - LEAVE\n" );
}

void HAL_interrupt_deinit( void )
{
    debug_printf( "[GIC] HAL_interrupt_deinit - ENTER\n" );

    uint32_t i;

    for ( i  = 0; i < INTERRUPT_HANDLER_NUM; i++ )
        s_handlers[i] = NULL;

    /**
    * Disable IRQ Mode in CPSR
    */
    disable_irq ();

    /**
    * Configure CPU I/F
    */
    gic_cpu->priority_mask.bits.mask = 0x00;
    gic_cpu->cpu_ctrl.bits.enable = DISABLE;    //< Disable CPU interface

    debug_printf( "[GIC] HAL_interrupt_deinit - LEAVE\n" );
}

int32_t HAL_interrupt_enable( uint32_t intr_id, void *arg2 )
{
    // config_dist_t *cfg_dist = ( config_dist_t * )arg2;
    config_dist_t cfg_dist;
    int32_t port_num = -1;
    int32_t field_num = -1;
    int32_t bit_num = -1;
    int32_t src = -1;

    memset ( &cfg_dist, 0, sizeof( cfg_dist ));

    if (( intr_id < GIC_ID_START ) || ( intr_id > GIC_ID_END )) {
        debug_printf("[GIC_ENABLE] Invalid interrupt number! ( %u )\n", intr_id);
        return -1;
    }

    if (( intr_id >= GIC_SGI_ID_START ) && ( intr_id <= GIC_SGI_ID_END )) {
        port_num = intr_id;                     //< Convert to SGI port number
        src = GIC_DIST_INTR_SRC_SGI;
    }
    else if (( intr_id >= GIC_PPI_ID_START ) && ( intr_id <= GIC_PPI_ID_END )) {
        port_num = intr_id - GIC_PPI_ID_START;  //< Convert to PPI port number
        src = GIC_DIST_INTR_SRC_PPI;
    }
    else if (( intr_id >= GIC_SPI_ID_START ) && ( intr_id <= GIC_SPI_ID_END )) {
        port_num = intr_id - GIC_SPI_ID_START;  //< Convert to SPI port number
        src = GIC_DIST_INTR_SRC_SPI;
    }
    else {
        debug_printf( "[GIC_ERR] Unexpected error! ( % u )\n", intr_id );
        return -1;
    }

    switch (src) {
    case GIC_DIST_INTR_SRC_SGI:
        debug_printf( "[GIC] Enable SIG! ( %u )\n", intr_id );
        break;
    case GIC_DIST_INTR_SRC_PPI:
        debug_printf( "[GIC] Enable PPI! ( %u )\n", intr_id);
        break;
    case GIC_DIST_INTR_SRC_SPI:
        /**
        * Find INTR_ID for SPI bit number ( ICDSER_CPUn )
        */
        if ( port_num >= 0 && port_num <= 31 ) {
            cfg_dist.set_en_f = 1;
            bit_num = port_num;
        }
        else if ( port_num >= 32 && port_num <= 63 ) {
            cfg_dist.set_en_f = 2;
            bit_num = port_num - 32;
        }
        else if ( port_num >= 64 && port_num <= 95 ) {
            cfg_dist.set_en_f = 3;
            bit_num = port_num - 64;
        }
        else if ( port_num >= 96 && port_num <= 127 ) {
            cfg_dist.set_en_f = 4;
            bit_num = port_num - 127;
        }
        else {
            debug_printf( "[GIC] Failed to enable SPI! - Check interrupt ID.. ( %u )", intr_id );
            return -1;
        }

        if ( bit_num >= 0 && bit_num <= 31 ) {
            SET_BIT( dist_set_en->icdiser[cfg_dist.set_en_f].enable, bit_num );  //< Config DIST - Enable corresponding interrupt

            bit_num = -1;
        }

        /**
        * Find INTR_ID for SPI field (ICDICFR_CPUn)
        */
        if ( port_num >= 0 && port_num <= 15 ) {
            cfg_dist.trig_f = 2;
            field_num = port_num;
        }
        else if ( port_num >= 16 && port_num <= 31 ) {
            cfg_dist.trig_f = 3;
            field_num = port_num - 16;
        }
        else if ( port_num >= 32 && port_num <= 47 ) {
            cfg_dist.trig_f = 4;
            field_num = port_num - 32;
        }
        else if ( port_num >= 48 && port_num <= 63 ) {
            cfg_dist.trig_f = 5;
            field_num = port_num - 48;
        }
        else if ( port_num >= 64 && port_num <= 81 ) {
            cfg_dist.trig_f = 6;
            field_num = port_num - 64;
        }
        else if ( port_num >= 80 && port_num <= 95 ) {
            cfg_dist.trig_f = 7;
            field_num = port_num - 80;
        }
        else if ( port_num >= 96 && port_num <= 111 ) {
            cfg_dist.trig_f = 8;
            field_num = port_num - 96;
        }
        else if ( port_num >= 112 && port_num <= 127 ) {
            cfg_dist.trig_f = 9;
            field_num = port_num - 112;
        }
        else {
            debug_printf( "[GIC] Failed to enable SPI! - Check interrupt ID.. ( %u )", intr_id );
            return -1;
        }

        if ( field_num > -1 ) {
            bit_num = field_num << 1;

            CLR_BIT( dist_icdicfr->icdicfr[cfg_dist.trig_f].all, bit_num + 1 );   //< Config DIST - Identifies whether the corresponding interrupt is edge-triggered or level-sensitive
        }

        dist_icdipr->icdipr[intr_id].priority = 0xA0; // cfg_dist->prio;    //< Config DIST - Configure corresponding interrupt priority
        dist_icdiptr->icdiptr[intr_id].target = 1; // cfg_dist->target;     //< Config DIST - Enable target CPU I/F

        debug_printf( "[GIC] Enable SPI! ( %u )\n", intr_id );
        break;
    default:
        debug_printf("[GIC_ERR] Invalid interrupt source! ( %u )\n", intr_id);
        break;            
    }

    return 0;    
}

int32_t HAL_interrupt_disable( uint32_t intr_id, void *arg2 )
{
    // config_dist_t *cfg_dist = ( config_dist_t * )arg2;
    config_dist_t cfg_dist;
    int32_t port_num = -1;
    int32_t bit_num = -1;
    int32_t src = -1;

    memset( &cfg_dist, 0, sizeof( cfg_dist ));

    if (( intr_id < GIC_ID_START ) || ( intr_id > GIC_ID_END )) {
        debug_printf("[GIC_DISABLE] Invalid interrupt number! ( %u )\n", intr_id);
        return -1;
    }

    if (( intr_id >= GIC_SGI_ID_START ) && ( intr_id <= GIC_SGI_ID_END )) {
        port_num = intr_id;                       //< Convert to SGI port number
        src = GIC_DIST_INTR_SRC_SGI;
    }
    else if (( intr_id >= GIC_PPI_ID_START) && (intr_id <= GIC_PPI_ID_END )) {
        port_num = intr_id - GIC_PPI_ID_START;    //< Convert to PPI port number
        src = GIC_DIST_INTR_SRC_PPI;
    }
    else if (( intr_id >= GIC_SPI_ID_START) && (intr_id <= GIC_SPI_ID_END )) {
        port_num = intr_id - GIC_SPI_ID_START;    //< Convert to SPI port number
        src = GIC_DIST_INTR_SRC_SPI;
    }
    else {
        debug_printf( "[GIC_ERR] Unexpected error! ( %u )\n", intr_id );
        return -1;
    }

    switch ( src ) {
    case GIC_DIST_INTR_SRC_SGI:
        debug_printf( "[GIC] Enable SIG! ( %u )", intr_id );
        break;
    case GIC_DIST_INTR_SRC_PPI:
        debug_printf( "[GIC] Enable PPI! ( %u )", intr_id );
        break;
    case GIC_DIST_INTR_SRC_SPI:
        /**
        * Find INTR_ID for SPI bit number ( ICDSER_CPUn )
        */
        if ( port_num >= 0 && port_num <= 31 ) {
            cfg_dist.set_en_f = 1;
            bit_num = port_num;
        }
        else if ( port_num >= 32 && port_num <= 63 ) {
            cfg_dist.set_en_f = 2;
            bit_num = port_num - 32;
        }
        else if ( port_num >= 64 && port_num <= 95 ) {
            cfg_dist.set_en_f = 3;
            bit_num = port_num - 64;
        }
        else if ( port_num >= 96 && port_num <= 127 ) {
            cfg_dist.set_en_f = 4;
            bit_num = port_num - 127;
        }
        else {
            debug_printf( "[GIC] Failed to disable SPI! - Check interrupt ID.. ( %u )", intr_id );
            return -1;
        }

        /**
        * Configure DIST
        */
        if ( bit_num >= 0 && bit_num <= 31 )
            SET_BIT( dist_clr_en->icdicer.enable[cfg_dist.clr_en_f], bit_num );    //< Disable corresponding interrupt

        // dist_icdiptr->icdiptr[intr_id].target = 0; // cfg_dist->target;     //< Config DIST - Disable target CPU I/F
    }

    return 0;
}

void HAL_interrupt_register_handler( intr_handler_fptr hdl, uint32_t intr_id )
{
    s_handlers[intr_id] = hdl;
}

void HAL_interrupt_unregister_handler( uint32_t intr_id )
{
    s_handlers[intr_id] = NULL;
}

void HAL_interrupt_run_handler( uint32_t irq_num, void *arg2 )
{
    if ( s_handlers[irq_num] != NULL )
        s_handlers[irq_num](arg2);

    gic_cpu->end_of_intr.bits.eo_id |= ( gic_cpu->intr_ack.bits.ack_id & 0x3FF );
    gic_cpu->end_of_intr.bits.eo_id = irq_num;
}
