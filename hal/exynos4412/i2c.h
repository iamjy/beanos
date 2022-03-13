/**
* @file
* @author
* @date
* @brief
* @see
*/

#ifndef _EXYNOS_I2C_H_
#define _EXYNOS_I2C_H_

/*****************************************************************************
 * Header Files
 *****************************************************************************/
#include "stdint.h"
#include "stdbool.h"
#include "stddef.h"


/*****************************************************************************
 * Macro Definitions
 *****************************************************************************/
/* ---------------------------------------------------------------------------
   - I2Cn
 --------------------------------------------------------------------------- */
#define EXYNOS_I2C_MAX_NUM    ( 9 )

/* ---------------------------------------------------------------------------
   - Register Base Address
 --------------------------------------------------------------------------- */
#define EXYNOS_I2C0_BASE     ( ( volatile uint32_t * ) 0x13860000 )    //< I2C0 Register Base Address
#define EXYNOS_I2C1_BASE     ( ( volatile uint32_t * ) 0x13870000 )    //< I2C1 Register Base Address
#define EXYNOS_I2C2_BASE     ( ( volatile uint32_t * ) 0x13880000 )    //< I2C2 Register Base Address
#define EXYNOS_I2C3_BASE     ( ( volatile uint32_t * ) 0x13890000 )    //< I2C3 Register Base Address
#define EXYNOS_I2C4_BASE     ( ( volatile uint32_t * ) 0x138A0000 )    //< I2C4 Register Base Address
#define EXYNOS_I2C5_BASE     ( ( volatile uint32_t * ) 0x138B0000 )    //< I2C5 Register Base Address
#define EXYNOS_I2C6_BASE     ( ( volatile uint32_t * ) 0x138C0000 )    //< I2C6 Register Base Address
#define EXYNOS_I2C7_BASE     ( ( volatile uint32_t * ) 0x138D0000 )    //< I2C7 Register Base Address
#define EXYNOS_I2C_HDMI_BASE ( ( volatile uint32_t * ) 0x138E0000 )    //< I2C-HDMI Register Base Address

/* ---------------------------------------------------------------------------
   - Register Offset
 --------------------------------------------------------------------------- */
#define I2C_CON_OFFSET     ( 0x0 )
#define I2C_STAT_OFFSET    ( 0x4 )
#define I2C_ADD_OFFSET     ( 0x8 )
#define I2C_DS_OFFSET      ( 0xC )
#define I2C_LC_OFFSET      ( 0x10 )


/*****************************************************************************
 * Type definition
 *****************************************************************************/
/*****************************************************************************
 * Enumerations
 *****************************************************************************/
/* ---------------------------------------------------------------------------
   - IDn
 --------------------------------------------------------------------------- */
enum {
    I2C_ID_0 = 0,
    I2C_ID_1,
    I2C_ID_2,
    I2C_ID_3,
    I2C_ID_4,
    I2C_ID_5,
    I2C_ID_6,
    I2C_ID_7,
    I2C_ID_HDMI = 8
};

/* ---------------------------------------------------------------------------
   - Bitrate
 --------------------------------------------------------------------------- */
enum {
    I2C_100KHz = 0,
    I2C_400KHz = 1
};

/* ---------------------------------------------------------------------------
   - Operation Mode
 --------------------------------------------------------------------------- */
enum {
    I2C_MODE_NONE = -1,
    I2C_MODE_SRX = 0,   //< Slave / Receive mode
    I2C_MODE_STX,       //< Slave / Transmitter mode
    I2C_MODE_MRX,       //< Master / Receive mode
    I2C_MODE_MTX = 3    //< Master / Transmitter mode
};

/* ---------------------------------------------------------------------------
   - Transaction Status
 --------------------------------------------------------------------------- */
enum {
    I2C_STOP = 0,
    I2C_START,
};

enum {
    I2C_READY    = ( 0x0 ),
    I2C_DONE     = ( 0x1 << 0 ),
    I2C_WRITE    = ( 0x1 << 1 ),
    I2C_READ     = ( 0x1 << 2 ),
    I2C_SUB_ADDR = ( 0x1 << 3 ),
    I2C_RESTART  = ( 0x1 << 4 ),
};

enum {
    I2C_IDLE = 0,
    I2C_BUSY = 1
};

/* ---------------------------------------------------------------------------
   - Enable / Disable
 --------------------------------------------------------------------------- */
enum {
    I2C_INTR_DISABLE = 0,
    I2C_INTR_ENABLE = 1
};

enum {
    I2C_ACK_DISABLE = 0,
    I2C_ACK_ENABLE = 1
};

enum {
    I2C_SDA_DISABLE = 0,
    I2C_SDA_ENABLE = 1
};

/* ---------------------------------------------------------------------------
   - Error Status
 --------------------------------------------------------------------------- */
enum {
    I2C_FAIL    = -1,
    I2C_SUCCESS =  0
};


/*****************************************************************************
 * Type Definitions
 *****************************************************************************/
/*****************************************************************************
 * Structures
 *****************************************************************************/
/* ---------------------------------------------------------------------------
   - I2C Registers
 --------------------------------------------------------------------------- */
/**
* @brief 
* @details 
* @see 
*/
typedef union _reg_i2c_ctrl_t {
    uint32_t all;
    struct {
        uint32_t clk_val:4;         //< [RW] 
        uint32_t intr_pend:1;       //< [S] Check interrupt pending flag and clear interrupt
        uint32_t intr_en:1;         //< [RW] 
        uint32_t tx_clk_src_sel:1;  //< [RW] 
        uint32_t ack_gen:1;         //< [RW] 
        uint32_t rsvd:24;
    } bits;
} reg_i2c_ctrl_t;

/**
* @brief 
* @details 
* @see 
*/
typedef union _reg_i2c_stat_t {
    uint32_t all;
    struct {
        uint32_t last_stat:1;       //< [RO] 
        uint32_t zaddr_stat:1;      //< [RO] 
        uint32_t saddr_stat:1;      //< [RO] 
        uint32_t arbitration:1;     //< [RO] 
        uint32_t output_en:1;       //< [S] 
        uint32_t busy_trig:1;       //< [S] 
        uint32_t mode:2;            //< [RWX] 
        uint32_t rsvd:24;
    } bits;
} reg_i2c_stat_t;

/**
* @brief 
* @details 
* @see 
*/
typedef union _reg_i2c_slave_t {
    uint32_t all;
    struct {
        uint32_t slave_addr:8;        //< [RWX] 
        uint32_t rsvd:24;
    } bits;
} reg_i2c_slave_t;

/**
* @brief 
* @details 
* @see 
*/
typedef union _reg_i2c_shifter_t {
    uint32_t all;
    struct {
        uint32_t data_shift:8;        //< [RWX] 
        uint32_t rsvd:24;
    } bits;
} reg_i2c_shifter_t;

/**
* @brief 
* @details 
* @see 
*/
typedef union _reg_i2c_mmline_ctrl_t {
    uint32_t all;
    struct {
        uint32_t sda_out_delay:2;    //< [RW] 
        uint32_t filter_en:1;        //< [RW] 
        uint32_t rsvd:29;
    } bits;
} reg_i2c_mmline_ctrl_t;

/**
* @brief
* @details 
* @see
*/
typedef struct _regs_i2c_t {
    reg_i2c_ctrl_t *ctrl;
    reg_i2c_stat_t *stat;
    reg_i2c_slave_t *slave;
    reg_i2c_shifter_t *shifter;
    reg_i2c_mmline_ctrl_t *mmline_ctrl;
} regs_i2c_t;

/* ---------------------------------------------------------------------------
   - I2C Configuration Parameters
 --------------------------------------------------------------------------- */
/**
* @brief 
* @details 
* @see 
*/
typedef struct _i2c_cfg_t {
    uint32_t ack_gen;           //< Acknowledge generation
    uint32_t tx_clk_src_sel;    //< Tx clock source selection ( fPCLK / [16, 512] )
    uint32_t tx_clk;            //< Tx CLK = I2CCLK / ( I2CCON[3:0] + 1 )
    uint32_t sda_delay;         //< SDA output delay ( 0 / 5 / 10 / 15 clocks )
    uint32_t intr_en;           //< Tx / Rx interrupt
    uint32_t filter_en;         //< Filter enable
    int32_t mode;               //< Master and Slave ( Rx / Tx )
} i2c_cfg_t;

/**
* @brief 
* @details 
* @see 
*/
typedef struct _i2c_stat_t {
    uint32_t done;          //< Busy signal status ( START / STOP condition )
    uint32_t arbitration;
    uint32_t addr_slave;
    uint32_t addr_zero;
    uint32_t last_bit;
} i2c_stat_t;

/**
* @brief 
* @details 
* @see 
*/
typedef struct _i2c_set_t {
    uint32_t sda_en;            //< Serial output ( Tx / Rx ) enable / disable    
    uint32_t trig;              //< Start / Stop condition
    uint32_t intr_clr;          //< Clears interrupt pending condition and resumes the operation
} i2c_set_t;

/**
* @brief 
* @details 
* @see 
*/
typedef struct _i2c_slave_t {
    uint8_t slave_addr;         //< Set own slave address ( if as slave mode )
} i2c_slave_t;

/**
* @brief 
* @details 
* @see 
*/
typedef struct _i2c_transaction_t {
    uint32_t addr;      //< Specify slave address
    uint32_t sub_addr;  //< Specify register address
    uint8_t *buf;       //< Data buffer for Tx / Rx
    uint32_t cnt;       //< Data R / W count
} i2c_transaction_t;

/**
* @brief 
* @details 
* @see 
*/
typedef struct _i2c_mng_t {
    i2c_cfg_t cfg;
    i2c_stat_t stat;
    i2c_set_t set;
    i2c_slave_t slave;
    regs_i2c_t regs;
    int32_t id;         //< I2C ID
    int32_t intr_id;    //< I2C interrupt ID
    uint32_t base;      //< I2C Base address
    uint32_t sub;       //< I2C Sub address
    uint8_t *buf;       //< Data buffer for Tx / Rx
    uint32_t buf_cnt;   //< Data R / W count
    uint32_t loop_cnt;  //< Loop count
} i2c_mng_t;


/*****************************************************************************
 * Function Prototypes
 *****************************************************************************/
/**
* @brief
* @param[in]
* @param[out]
* @return void
*/
void i2c_init ( uint32_t id );
void i2c_deinit ( uint32_t id );

/**
* @brief
* @param[in]
* @param[out]
* @return void
*/
void i2c_configure ( uint32_t id );
void i2c_mode_selection ( uint32_t id );
void i2c_enable ( uint32_t id );
void i2c_disable ( uint32_t id);
uint32_t i2c_base_address_get ( uint32_t id );

/**
* @brief
* @param[in]
* @param[out]
* @return void
*/
void i2c_start ( uint32_t id );
void i2c_stop ( uint32_t id );
void i2c_busy ( uint32_t id );

/**
* @brief
* @param[in]
* @param[out]
* @return void
*/
void i2c_transmit ( uint32_t id, void *p_transaction );
void i2c_receive ( uint32_t id, void *p_transaction );

/**
* @brief
* @param[in]
* @param[out]
* @return void
*/
void i2c_interrupt_register ( uint32_t id );
void i2c_interrupt_unregister ( uint32_t id );
void i2c_interrupt_enable ( uint32_t id );
void i2c_interrupt_disable ( uint32_t id );
void i2c_interrupt_clear ( uint32_t id );
uint32_t i2c_interrupt_number_get ( uint32_t id );

/**
* @brief
* @param[in]
* @param[out]
* @return void
*/
void i2c_clock_source_get ( uint32_t id );
void i2c_clock_source_set ( uint32_t id );


#endif /* _EXYNOS_SPI_H_ */