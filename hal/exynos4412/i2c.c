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
#include "i2c.h"
#include "hal_i2c.h"
#include "hal_interrupt.h"


/*****************************************************************************
 * Macro Definitions
 *****************************************************************************/
/*****************************************************************************
 * Type Definitions
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
static i2c_mng_t s_i2c_mng[EXYNOS_I2C_MAX_NUM];

/* ---------------------------------------------------------------------------
   - Function
 --------------------------------------------------------------------------- */
static void i2c_intr_handler ( void *p_id );


/*****************************************************************************
 * Extern Variables
 *****************************************************************************/
/* ---------------------------------------------------------------------------
   - Variable
 --------------------------------------------------------------------------- */
extern uint32_t TEST_I2C_ID;    //< Test I2C

/* ---------------------------------------------------------------------------
   - Function
 --------------------------------------------------------------------------- */
/*****************************************************************************
 * Global Variables
 *****************************************************************************/
/*****************************************************************************
 * Function Definitions
 *****************************************************************************/
static void i2c_intr_handler ( void *p_arg )
{
    // uint32_t *id = (uint32_t *)p_arg;
    i2c_mng_t *i2c = &s_i2c_mng[TEST_I2C_ID];
    reg_i2c_shifter_t *reg_shifter = i2c->regs.shifter;
    uint32_t *i = &i2c->loop_cnt;

    if ( i2c->stat.done & I2C_WRITE ) {
        if ( i2c->stat.done & I2C_SUB_ADDR ) {
            reg_shifter->bits.data_shift = i2c->sub;    //< Write sub address
            i2c->stat.done &= ~( I2C_SUB_ADDR );
        }
        else if ( i2c->stat.done & I2C_RESTART ) {
            reg_shifter->bits.data_shift = i2c->base | 0x1;
            i2c->regs.stat->bits.mode = I2C_MODE_MRX;
            i2c->regs.stat->bits.busy_trig = I2C_START;
            i2c->stat.done = I2C_READ;
        }
        else {
            if ( *i < i2c->buf_cnt )
                reg_shifter->bits.data_shift = i2c->buf[(*i)++];    //< Write new data
            else
                i2c->stat.done = I2C_DONE;
        }
    }
    else if ( i2c->stat.done == I2C_READ ) {
        if ( *i < i2c->buf_cnt )
            i2c->buf[(*i)++] = reg_shifter->bits.data_shift;    //< Read new data
        else
            i2c->stat.done = I2C_DONE;
    }

    i2c->regs.ctrl->bits.intr_pend = 0;    //< Clear to resume operation
}

void HAL_i2c_dev_open ( uint32_t id )
{
    i2c_init ( id );
}

void HAL_i2c_dev_close ( uint32_t id )
{
    i2c_deinit ( id );
}

void HAL_i2c_data_transmit ( uint32_t id, void *p_transaction )
{
    i2c_transmit ( id, p_transaction );
}

void HAL_i2c_data_receive ( uint32_t id, void *p_transaction )
{
    i2c_receive ( id, p_transaction );
}

void i2c_init ( uint32_t id )
{
    i2c_mng_t *i2c = NULL;
    i2c_cfg_t *cfg = NULL;
    regs_i2c_t *regs = NULL;

    i2c = &s_i2c_mng[id];
    cfg = &i2c->cfg;
    regs = &i2c->regs;

    memset ( i2c, 0, sizeof ( i2c_mng_t ));

    i2c->id = id;
    i2c->base = i2c_base_address_get ( i2c->id );
    i2c->intr_id = i2c_interrupt_number_get ( i2c->id );
    i2c->stat.done = I2C_READY;
    i2c->loop_cnt = 0;

    regs->ctrl = ( reg_i2c_ctrl_t * ) ( i2c->base + I2C_CON_OFFSET );
    regs->stat = ( reg_i2c_stat_t * ) ( i2c->base + I2C_STAT_OFFSET );
    regs->slave = ( reg_i2c_slave_t * ) ( i2c->base + I2C_ADD_OFFSET );
    regs->shifter = ( reg_i2c_shifter_t *) ( i2c->base + I2C_DS_OFFSET );
    regs->mmline_ctrl = ( reg_i2c_mmline_ctrl_t * ) ( i2c->base + I2C_LC_OFFSET );

    cfg->mode = I2C_MODE_NONE;
    cfg->ack_gen = I2C_ACK_ENABLE;    //< Enable acknowledge bit
    cfg->tx_clk_src_sel = 0;          //< I2CCLK = fPCL / 16
    cfg->tx_clk = 0xF;                //< Tx CLK = I2CCLK / (0 + 1)

    i2c_configure ( i2c->id );
}

void i2c_deinit ( uint32_t id )
{
    i2c_mng_t *i2c = &s_i2c_mng[id];

    i2c_interrupt_unregister ( i2c->id );
}

void i2c_configure ( uint32_t id )
{
    i2c_mng_t *i2c = &s_i2c_mng[id];
    i2c_cfg_t *cfg = &i2c->cfg;
    reg_i2c_ctrl_t *ctrl = i2c->regs.ctrl;

    ctrl->bits.ack_gen = cfg->ack_gen;

    i2c_interrupt_register ( i2c->id );

    i2c_clock_source_set ( i2c->id );

    return;
}

void i2c_mode_selection ( uint32_t id )
{
    i2c_mng_t *i2c = &s_i2c_mng[id];
    i2c_cfg_t *cfg = &i2c->cfg;
    reg_i2c_stat_t *stat = i2c->regs.stat;

    stat->bits.mode = cfg->mode;
}

void i2c_enable ( uint32_t id )
{
    i2c_mng_t *i2c = &s_i2c_mng[id];
    i2c_set_t *set = &i2c->set;
    reg_i2c_stat_t *stat = i2c->regs.stat;

    set->sda_en = I2C_SDA_ENABLE;
    stat->bits.output_en = set->sda_en;
}

void i2c_disable ( uint32_t id )
{
    i2c_mng_t *i2c = &s_i2c_mng[id];
    i2c_set_t *set = &i2c->set;
    reg_i2c_stat_t *stat = i2c->regs.stat;

    set->sda_en = I2C_SDA_DISABLE;
    stat->bits.output_en = set->sda_en;
}

void i2c_start ( uint32_t id )
{
    i2c_mng_t *i2c = &s_i2c_mng[id];
    reg_i2c_stat_t *stat = i2c->regs.stat;

    stat->bits.busy_trig = I2C_START;
}

void i2c_stop ( uint32_t id )
{
    i2c_mng_t *i2c = &s_i2c_mng[id];
    reg_i2c_stat_t *stat = i2c->regs.stat;

    stat->bits.busy_trig = I2C_STOP;
}

void i2c_busy ( uint32_t id )
{
    i2c_mng_t *i2c = &s_i2c_mng[id];
    i2c_stat_t *stat = &i2c->stat;
}

void i2c_transmit ( uint32_t id, void *p_transaction )
{
    i2c_mng_t *i2c = &s_i2c_mng[id];
    i2c_cfg_t *cfg = &i2c->cfg;
    i2c_stat_t *stat = &i2c->stat;
    i2c_transaction_t *transaction = ( i2c_transaction_t * ) p_transaction;
    reg_i2c_stat_t *reg_stat = i2c->regs.stat;
    reg_i2c_shifter_t *reg_shifter = i2c->regs.shifter;
    uint32_t i = 0;

    i2c->base = transaction->addr;
    i2c->sub = transaction->sub_addr;
    i2c->buf = transaction->buf;
    i2c->buf_cnt = transaction->cnt;

    /**
     * 1. Enable SDA pin ( Set I2CSTAT to enable Serial Output )
     */
    i2c_enable ( i2c->id );

    /**
     * 2. Write slave address to transmit buffer register
     */
    reg_shifter->bits.data_shift = i2c->base;

    /**
     * 3. Configure Tx mode
     */
    cfg->mode = I2C_MODE_MTX;
    i2c_mode_selection ( i2c->id );

    /**
     * 4. Generate START signal
     */
    stat->done = ( I2C_WRITE | I2C_SUB_ADDR );
    i2c_start ( i2c->id );

    /**
     * 5. Wait until the transfer complete
     */
    while ( i2c->stat.done & I2C_WRITE ) {
        //< Timeout exception handling is required
    }

    /**
     * 6. Generate STOP signal
     */
    i2c_stop ( i2c->id );
    while ( reg_stat->bits.busy_trig == I2C_BUSY ) {
        //< Timeout exception handling is required
    }

    stat->done = I2C_READY;
}

void i2c_receive ( uint32_t id, void *p_transaction )
{
    i2c_mng_t *i2c = &s_i2c_mng[id];
    i2c_cfg_t *cfg = &i2c->cfg;
    i2c_stat_t *stat = &i2c->stat;
    i2c_transaction_t *transaction = ( i2c_transaction_t * ) p_transaction;
    reg_i2c_stat_t *reg_stat = i2c->regs.stat;
    reg_i2c_shifter_t *reg_shifter = i2c->regs.shifter;
    uint32_t i = 0;

    i2c->base = transaction->addr;
    i2c->sub = transaction->sub_addr;
    i2c->buf = transaction->buf;
    i2c->buf_cnt = transaction->cnt;

    /**
     * 1. Enable SDA pin ( Set I2CSTAT to enable Serial Output )
     */
    i2c_enable ( i2c->id );

    /**
     * 2. Write slave address to read buffer register
     */
    reg_shifter->bits.data_shift = i2c->base;

    /**
     * 3. Configure Tx mode
     */
    cfg->mode = I2C_MODE_MTX;
    i2c_mode_selection ( i2c->id );

    /**
     * 4. Generate START ( with Repeat conditon ) signal
     */
    stat->done = ( I2C_WRITE | I2C_SUB_ADDR | I2C_RESTART );
    i2c_start ( i2c->id );

    /**
     * 5. Wait until the receive complete
     */
    while ( stat->done & I2C_WRITE ) {
        //< Timeout exception handling is required
    }
    while ( stat->done & I2C_READ ) {
        //< Timeout exception handling is required
    }

    /**
     * 6. Generate STOP signal
     */
    i2c_stop ( i2c->id );
    while ( reg_stat->bits.busy_trig == I2C_BUSY ) {}

    stat->done = I2C_READY;
}

void i2c_interrupt_register ( uint32_t id )
{
    i2c_mng_t *i2c = &s_i2c_mng[id];
    
    HAL_interrupt_register_handler ( i2c_intr_handler, i2c->intr_id );	    //< Register GIC I2C interrupt handler
	HAL_interrupt_enable ( i2c->intr_id, &i2c->id );						//< Enable GIC I2C interrupt	

    i2c_interrupt_enable ( i2c->id );
}

void i2c_interrupt_unregister ( uint32_t id )
{
    i2c_mng_t *i2c = &s_i2c_mng[id];

    i2c_interrupt_disable ( i2c->id );

    HAL_interrupt_disable( i2c->intr_id, NULL );		   //< Disable GIC I2C interrupt
	HAL_interrupt_unregister_handler ( i2c->intr_id );	   //< Unregister GIC I2C interrupt handler    
}

void i2c_interrupt_enable ( uint32_t id )
{
    i2c_mng_t *i2c = &s_i2c_mng[id];
    i2c_cfg_t *cfg = &i2c->cfg;
    reg_i2c_ctrl_t *ctrl = i2c->regs.ctrl;

    cfg->intr_en = I2C_INTR_ENABLE;
    ctrl->bits.intr_en = cfg->intr_en;
}

void i2c_interrupt_disable ( uint32_t id )
{
    i2c_mng_t *i2c = &s_i2c_mng[id];
    i2c_cfg_t *cfg = &i2c->cfg;
    reg_i2c_ctrl_t *ctrl = i2c->regs.ctrl;

    cfg->intr_en = I2C_INTR_DISABLE;
    ctrl->bits.intr_en = cfg->intr_en;
}

void i2c_clock_source_set ( uint32_t id )
{
    i2c_mng_t *i2c = &s_i2c_mng[id];
    i2c_cfg_t *cfg = &i2c->cfg;
    reg_i2c_ctrl_t *ctrl = i2c->regs.ctrl;

    ctrl->bits.tx_clk_src_sel = cfg->tx_clk_src_sel;
    ctrl->bits.clk_val = cfg->tx_clk;
}

void i2c_clock_source_get ( uint32_t id )
{
    i2c_mng_t *i2c = &s_i2c_mng[id];
}

uint32_t i2c_base_address_get ( uint32_t id )
{
    i2c_mng_t *i2c = &s_i2c_mng[id];
    uint32_t addr = 0x0;

    switch ( i2c->id ) {
    case I2C_ID_0: addr = ( uint32_t ) EXYNOS_I2C0_BASE; break;
    case I2C_ID_1: addr = ( uint32_t ) EXYNOS_I2C1_BASE; break;
    case I2C_ID_2: addr = ( uint32_t ) EXYNOS_I2C2_BASE; break;
    case I2C_ID_3: addr = ( uint32_t ) EXYNOS_I2C3_BASE; break;
    case I2C_ID_4: addr = ( uint32_t ) EXYNOS_I2C4_BASE; break;
    case I2C_ID_5: addr = ( uint32_t ) EXYNOS_I2C5_BASE; break;
    case I2C_ID_6: addr = ( uint32_t ) EXYNOS_I2C6_BASE; break;
    case I2C_ID_7: addr = ( uint32_t ) EXYNOS_I2C7_BASE; break;
    case I2C_ID_HDMI: addr = ( uint32_t ) EXYNOS_I2C_HDMI_BASE; break;
    default: addr = 0x0; break;
    }

    return addr;
}

uint32_t i2c_interrupt_number_get ( uint32_t id )
{
    i2c_mng_t *i2c = &s_i2c_mng[id];
    int32_t intr_id = -1;

    switch ( i2c->id ) {
    case I2C_ID_0: intr_id = GIC_INT_I2C_0; break;
    case I2C_ID_1: intr_id = GIC_INT_I2C_1; break;
    case I2C_ID_2: intr_id = GIC_INT_I2C_2; break;
    case I2C_ID_3: intr_id = GIC_INT_I2C_3; break;
    case I2C_ID_4: intr_id = GIC_INT_I2C_4; break;
    case I2C_ID_5: intr_id = GIC_INT_I2C_5; break;
    case I2C_ID_6: intr_id = GIC_INT_I2C_6; break;
    case I2C_ID_7: intr_id = GIC_INT_I2C_7; break;
    case I2C_ID_HDMI: intr_id = GIC_INT_I2C_HDMI; break;
    default: intr_id = -1; break;
    }

    return intr_id;
}