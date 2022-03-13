/**
* @file
* @author
* @date
* @brief
* @see
*/

#ifndef _EXYNOS_SPI_H_
#define _EXYNOS_SPI_H_

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
   - SPIn
 --------------------------------------------------------------------------- */
#define EXYNOS_SPI_MAX_NUM    ( 3 )

/* ---------------------------------------------------------------------------
   - Register Base Address
 --------------------------------------------------------------------------- */
#define EXYNOS_SPI0_BASE (( volatile uint32_t * ) 0x13920000 )    //< SPI0 Register Base Address
#define EXYNOS_SPI1_BASE (( volatile uint32_t * ) 0x13930000 )	  //< SPI1 Register Base Address
#define EXYNOS_SPI2_BASE (( volatile uint32_t * ) 0x13940000 )	  //< SPI2 Register Base Address

/* ---------------------------------------------------------------------------
   - Register Offset
 --------------------------------------------------------------------------- */
#define OFFSET_CH_CFG            ( 0x0000 )
#define OFFSET_MODE_CFG          ( 0x0008 )
#define OFFSET_CS_REG            ( 0x000C )
#define OFFSET_SPI_INT_EN        ( 0x0010 )
#define OFFSET_SPI_STATUS        ( 0x0014 )
#define OFFSET_SPI_TX_DATA       ( 0x0018 )
#define OFFSET_SPI_RX_DATA       ( 0x001C )
#define OFFSET_PACKET_CNT_REG    ( 0x0020 )
#define OFFSET_PENDING_CLR_REG   ( 0x0024 )
#define OFFSET_SWAP_CFG          ( 0x0028 )
#define OFFSET_FB_CLK_SEL        ( 0x002C )


/*****************************************************************************
 * Type Definitions
 *****************************************************************************/
/*****************************************************************************
 * Enumerations
 *****************************************************************************/
/*****************************************************************************
 * Structures
 *****************************************************************************/
/* ---------------------------------------------------------------------------
   - SPI Registers
 --------------------------------------------------------------------------- */
/**
* @brief Specifies SPI configuration
* @details 
* @see 30.5.1.1 CH_CFG_n ( n = 0 to 2 )
*/
typedef union _reg_CH_CFGn_t {
    uint32_t all;
    struct {
        uint32_t tx_ch_on:1;        //< [RW] SPI Tx Channel On / Off
        uint32_t rx_ch_on:1;        //< [RW] SPI Rx Channel On / Off
        uint32_t cpha:1;            //< [RW] Format A / B
        uint32_t cpol:1;            //< [RW] Active High / Low
        uint32_t slave:1;           //< [RW] Master / Slave
        uint32_t sw_rst:1;          //< [RW] Inactive / Active
        uint32_t high_speed_en:1;   //< [RW] Disable / Enable
        uint32_t rsvd0:25;

    } bits;
} reg_CH_CFGn_t;

/**
* @brief Specifies FIFO Control
* @details 
* @see 30.5.1.2 MODE_CFGn (n = 0 to 2)
*/
typedef union _reg_MODE_CFGn_t {
    uint32_t all;
    struct {
        uint32_t dma_type:1;        //< [RW]
        uint32_t tx_dma_sw:1;       //< [RW]
        uint32_t rx_dma_sw:1;       //< [RW]
        uint32_t rsvd0:2;
        uint32_t tx_rdy_lvl:6;      //< [RW]
        uint32_t rx_rdy_lvl:6;      //< [RW]
        uint32_t bus_width:2;       //< [RW]
        uint32_t trailing_cnt:10;   //< [RW]
        uint32_t ch_width:2;        //< [RW]
        uint32_t rsvd1:1;
    } bits;
} reg_MODE_CFGn_t;

/**
* @brief Specifies Slave Selection Control
* @details 
* @see 30.5.1.3 CS_REGn (n = 0 to 2)
*/
typedef union _reg_CS_REGn_t {
    uint32_t all;
    struct {
        uint32_t nssout:1;
        uint32_t auto_n_manual:1;      //< [RW] 
        uint32_t rsvd0:2;
        uint32_t ncs_time_cnt:6;       //< [RW] 
        uint32_t rsvd1:22;
    } bits;
} reg_CS_REGn_t;

/**
* @brief Specifies Interrupt Enable
* @details 
* @see 30.5.1.4 SPI_INT_ENn (n = 0 to 2)
*/
typedef union _reg_SPI_INT_ENn_t {
    uint32_t all;
    struct {
        uint32_t intr_en_rx_fifo_rdyl:1;    //< [RW] 
        uint32_t intr_en_rx_fifo_rdy:1;     //< [RW] 
        uint32_t intr_en_tx_underrun:1;     //< [RW] 
        uint32_t intr_en_tx_overrun:1;      //< [RW] 
        uint32_t intr_en_rx_underrun:1;     //< [RW] 
        uint32_t intr_en_rx_overrun:1;      //< [RW] 
        uint32_t intr_en_trailing:1;        //< [RW] 
        uint32_t rsvd:25;
    } bits;
} reg_SPI_INT_ENn_t;

/**
* @brief Specifies SPI Status
* @details 
* @see 30.5.1.5 SPI_STATUSn (n = 0 to 2)
*/
typedef union _reg_SPI_STATUSn_t {
    uint32_t all;
    struct {
        uint32_t tx_fifo_rdy:1;     //< [RW] 
        uint32_t rx_fifo_rdy:1;     //< [RW] 
        uint32_t tx_underrun:1;     //< [RW] 
        uint32_t tx_overrun:1;      //< [RW] 
        uint32_t rx_underrun:1;     //< [RW] 
        uint32_t rx_overrun:1;      //< [RW] 
        uint32_t tx_fifo_lvl:9;     //< [RW] 
        uint32_t rx_fifo_lvl:9;     //< [RW] 
        uint32_t trailing_byte:1;   //< [RW] 
        uint32_t tx_done:1;         //< [RW] 
        uint32_t rsvd:6;
    } bits;
} reg_SPI_STATUSn_t;

/**
* @brief Specifies Packet Count
* @details 
* @see 30.5.1.8 PACKET_CNT_REGn (n = 0 to 2)
*/
typedef union _reg_PACKET_CNT_REGn_t {
    uint32_t all;
    struct {
        uint32_t cnt_val:16;         //< [RW] 
        uint32_t packet_cnt_en:1;    //< [RW] 
        uint32_t rsvd:15;
    } bits;
} reg_PACKET_CNT_REGn_t;

/**
* @brief Specifies Interrupt Pending Clear
* @details 
* @see 30.5.1.9 PENDING_CLR_REGn (n = 0 to 2)
*/
typedef union _reg_PENDING_CLR_REGn_t {
    uint32_t all;
    struct {
        uint32_t trailing_clr:1;       //< [RW] 
        uint32_t rx_overrun_clr:1;     //< [RW] 
        uint32_t rx_underrun_clr:1;    //< [RW] 
        uint32_t tx_overrun_clr:1;     //< [RW] 
        uint32_t tx_underrun_clr:1;    //< [RW] 
        uint32_t rsvd:27;
    } bits;
} reg_PENDING_CLR_REGn_t;

/**
* @brief Specifies Swap Configuration
* @details 
* @see 30.5.1.10 SWAP_CFGn (n = 0 to 2)
*/
typedef union _reg_SWAP_CFGn_t {
    uint32_t all;
    struct {
        uint32_t tx_swap_en:1;      //< [RW] 
        uint32_t tx_bit_swap:1;     //< [RW] 
        uint32_t tx_byte_swap:1;    //< [RW] 
        uint32_t tx_hword_swap:1;   //< [RW] 
        uint32_t rx_swap_en:1;      //< [RW] 
        uint32_t rx_bit_swap:1;     //< [RW] 
        uint32_t rx_byte_swap:1;    //< [RW] 
        uint32_t rx_hword_swap:1;   //< [RW] 
        uint32_t rsvd:24;
    } bits;
} reg_SWAP_CFGn_t;

/**
* @brief Specifies Feedback Clock Selection
* @details 
* @see 30.5.1.11 FB_CLK_SELn (n = 0 to 2)
*/
typedef union _reg_FB_CLK_SELn_t {
    uint32_t all;
    struct {
        uint32_t fb_clk_sel:2;     //< [RW] 
        uint32_t rsvd:30;
    } bits;
} reg_FB_CLK_SELn_t;

/**
* @brief
* @details 
* @see
*/
typedef struct _regs_spi_t {
    reg_CH_CFGn_t ch_cfg;
    reg_MODE_CFGn_t mode_cfg;
    reg_CS_REGn_t cs_reg;
    reg_SPI_INT_ENn_t intr_en;
    reg_SPI_STATUSn_t status;
    uint32_t tx_data;
    uint32_t rx_data;
    reg_PACKET_CNT_REGn_t packet_cnt;
    reg_PENDING_CLR_REGn_t pend_clr;
    reg_SWAP_CFGn_t swap_cfg;
} regs_spi_t;

/* ---------------------------------------------------------------------------
   - SPI Configuration Parameters
 --------------------------------------------------------------------------- */
/**
 * @brief 
 * @details 
 * @see 
 */
typedef struct _spi_cfg_t {

} spi_cfg_t;

/**
 * @brief 
 * @details 
 * @see 
 */
typedef struct _spi_mng_t {

} spi_mng_t;


/*****************************************************************************
 * Function prototypes
 *****************************************************************************/
/**
* @brief
* @details 
* @param[in]
* @param[out]
* @return void
*/
void spi_init();
void spi_deinit();

/**
* @brief
* @details 
* @param[in]
* @param[out]
* @return void
*/
void spi_data_get();
void spi_data_put();
void spi_busy();

/**
* @brief
* @details 
* @param[in]
* @param[out]
* @return void
*/
void spi_dma_enable();
void spi_dma_disable();

/**
* @brief
* @details 
* @param[in]
* @param[out]
* @return void
*/
void spi_intr_enable();
void spi_intr_disable();
void spi_intr_clear();
void spi_intr_status();
void spi_intr_register();
void spi_intr_unregister();
void spi_intr_handler();

/**
* @brief
* @details 
* @param[in]
* @param[out]
* @return void
*/
void spi_clk_src_get();
void spi_clk_src_set();

#endif /* _EXYNOS_SPI_H_ */
