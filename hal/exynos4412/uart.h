/**
* @file
* @author
* @date
* @brief
* @see
*/

#ifndef _EXYNOS_UART_H_
#define _EXYNOS_UART_H_

/*****************************************************************************
 * Header files
 *****************************************************************************/
/*****************************************************************************
 * Macro definitions
 *****************************************************************************/
/* ---------------------------------------------------------------------------
   - UARTn
 --------------------------------------------------------------------------- */
#define EXYNOS_UART_MAX_NUM    ( 5 )

/* ---------------------------------------------------------------------------
 * Base Address
 --------------------------------------------------------------------------- */
#define EXYNOS_UART0_BASE    (( volatile uint32_t * ) 0x13800000 )	//< UART Channel 0 Line Control Register
#define EXYNOS_UART1_BASE    (( volatile uint32_t * ) 0x13810000 )	//< UART Channel 1 Line Control Register
#define EXYNOS_UART2_BASE    (( volatile uint32_t * ) 0x13820000 )	//< UART Channel 2 Line Control Register
#define EXYNOS_UART3_BASE    (( volatile uint32_t * ) 0x13830000 )	//< UART Channel 3 Line Control Register
#define EXYNOS_UART4_BASE    (( volatile uint32_t * ) 0x13840000 )	//< UART Channel 4 Line Control Register

/* ---------------------------------------------------------------------------
   - Register Offset
 --------------------------------------------------------------------------- */
#define OFFSET_ULCON       ( 0x0000 )
#define OFFSET_UCON        ( 0x0004 )
#define OFFSET_UFLCON      ( 0x0008 )
#define OFFSET_UMLCON      ( 0x000C )
#define OFFSET_UTRSTAT     ( 0x0010 )
#define OFFSET_UERSTAT     ( 0x0014 )
#define OFFSET_UFSTAT      ( 0x0018 )
#define OFFSET_UMSTAT      ( 0x001C )
#define OFFSET_UTX         ( 0x0020 )
#define OFFSET_URX         ( 0x0024 )
#define OFFSET_UBRDIV      ( 0x0028 )
#define OFFSET_UFRACVAL    ( 0x002C )
#define OFFSET_UINTP       ( 0x0030 )
#define OFFSET_UINTSP      ( 0x0034 )
#define OFFSET_UINTM       ( 0x0038 )

/* ---------------------------------------------------------------------------
 * Interrupt table
 --------------------------------------------------------------------------- */
#define UART_INTR_RX    ( 1 << 0 )
#define UART_INTR_ERR   ( 1 << 1 )
#define UART_INTR_TX    ( 1 << 2 )
#define UART_INTR_MD    ( 1 << 3 )
#define UART_INTR_MASK  ( 0xF )


/*****************************************************************************
 * Type definition
*****************************************************************************/
/*****************************************************************************
 * Enumerations
*****************************************************************************/
/*****************************************************************************
 * Structures ( typedef struct, struct, union )
 *****************************************************************************/
/* ---------------------------------------------------------------------------
   - Registers - Exynos UARTn
 --------------------------------------------------------------------------- */
/**
* @brief Specifies line control
* @details 
* @see ULCONn (0x00)
*/
typedef union reg_uart_line_ctrl_t {
    uint32_t all;
    struct {
        uint32_t len:2;         //< [1:0, RW]
        uint32_t stop:1;        //< [2, RW]
        uint32_t parity:3;      //< [5:3, RW]
        uint32_t infrared:1;    //< [6, RW]
        uint32_t rsvd:25;       //< [31:7, RW]
    } bits;
} reg_uart_line_ctrl;

/**
* @brief Specifies control
* @details 
* @see UCONn (0x04)
*/
typedef union reg_uart_ctrl_t {
    uint32_t all;
    struct {
        uint32_t rx_mode:2;         //< [0:1, RW]
        uint32_t tx_mode:2;         //< [3:2, RW]
        uint32_t tx_break:1;        //< [4, RW]
        uint32_t loop_back:1;       //< [5, RW]
        uint32_t rx_error:1;        //< [6, RW]
        uint32_t rx_timeout:1;      //< [7, RW]
        uint32_t rx_intrpt:1;       //< [8, RW]
        uint32_t tx_intrpt:1;       //< [9, RW]
        uint32_t rx_suspend:1;      //< [10, RW]
        uint32_t rx_empty:1;        //< [11, RW]
        uint32_t rx_intrpt_intv:4;  //< [15:12, RW]
        uint32_t rx_burst:3;        //< [18:16, RW]
        uint32_t rsvd0:1;           //< [19, WO]
        uint32_t tx_burst:3;        //< [22:20, RW]
        uint32_t rsvd1:1;           //< [23, WO]
        uint32_t rsvd2:8;           //< [31:24]
    } bits;
} reg_uart_ctrl;

/**
* @brief Specifies FIFO Control
* @details 
* @see UFCONn (0x08)
*/
typedef union reg_uart_fifo_ctrl_t {
    uint32_t all;
    struct {
        uint32_t enable:1;      //< [0] - FIFO enable
        uint32_t rx_reset:1;    //< [1] - Rx FIFO reset
        uint32_t tx_reset:1;    //< [2] - Tx FIFO reset
        uint32_t rsvd0:1;       //< [3]
        uint32_t rx_trig_lv:3;  //< [6:4] - Rx Trigger Level
        uint32_t rsvd1:1;       //< [7]
        uint32_t tx_trig_lv:3;  //< [10:8] - Tx Trigger Level
        uint32_t rsvd2:21;      //< [31:11]
    } bits;
} reg_uart_fifo_ctrl;

/**
* @brief Specifies modem control
* @details 
* @see ULCONn (0x0C)
*/
typedef union reg_uart_modem_ctrl_t {
    uint32_t all;
    struct {
        uint32_t tbd;    //< TODO: (temporality hard-coded)
    } bits;
} reg_uart_modem_ctrl;

/**
* @brief Specifies Tx/Rx status
* @details 
* @see ULCONn (0x10)
*/
typedef union reg_uart_txrx_stat_t {
    uint32_t all;
    struct {
        uint32_t rx_ready:1;            //< [0, R]
        uint32_t tx_buf_empty:1;        //< [1, R]
        uint32_t tx_empty:1;            //< [2, R]
        uint32_t rx_status_clear:1;     //< [3, RWX]
        uint32_t rsvd0:4;               //< [7:4, R]
        uint32_t rx_dma_fsm_stat:4;     //< [11:8, R]
        uint32_t tx_dma_fsm_stat:4;     //< [15:12, R]
        uint32_t rx_timeout_cnt:8;      //< [23:16, R]
        uint32_t rsvd1:8;               //< [31:24, R]
    } bits;
} reg_uart_txrx_stat;

/**
* @brief Specifies Rx error status
* @details 
* @see ULCONn (0x14)
*/
typedef union reg_uart_rx_err_stat_t {
    uint32_t all;
    struct {
        uint32_t overrun:1;         //< [0, R] - Overrun Error
        uint32_t parity:1;          //< [1, R] - Parity Error
        uint32_t frame:1;           //< [2, R] - Frame Error
        uint32_t break_detect:1;    //< [3, R] - Break Detect
        uint32_t rsvd:28;           //< [31:4]
    } bits;
} reg_uart_rx_err_stat;

/**
* @brief Specifies FIFO status
* @details 
* @see ULCONn (0x18)
*/
typedef union reg_uart_fifo_stat__t {
    uint32_t all;
    struct {
        uint32_t rx_cnt:8;      //< [7:0, R]
        uint32_t rx_full:1;     //< [8, R]
        uint32_t rx_err:1;      //< [9, R]
        uint32_t rsvd0:6;       //< [15:10]
        uint32_t tx_cnt:8;      //< [23:16, R]
        uint32_t tx_full:1;     //< [24, R]
        uint32_t rsvd1:6;       //< [31:25]
    } bits;
} reg_uart_fifo_stat;

/**
* @brief Specifies modem status
* @details 
* @see ULCONn (0x1C)
*/
typedef union reg_uart_modem_stat_t {
    uint32_t all;
    struct {
        uint32_t tbd;    //< TODO: (temporality hard-coded)
    } bits;
} reg_uart_modem_stat;

/**
* @brief Specifies transmit buffer
* @details 
* @see ULCONn (0x20)
*/
typedef union reg_uart_transmit_buf_t {
    uint32_t all;
    struct {
        uint32_t data:8;    //< [7:0] - Transmits data for UARTn
        uint32_t rsvd:24;   //< [31:8]
    } bits;
} reg_uart_transmit_buf;

/**
* @brief Specifies receive buffer
* @details 
* @see ULCONn (0x24)
*/
typedef union reg_uart_receive_buf_t {
    uint32_t all;
    struct {
        uint32_t data:8;    //< [7:0, R] - Receives data for UARTn
        uint32_t rsvd:24;   //< [31:8]
    } bits;
} reg_uart_receive_buf;

/**
* @brief Specifies baud rate divisor
* @details 
* @see ULCONn (0x28)
*/
typedef union reg_uart_baudrate_div_t {
    uint32_t all;
    struct {
        uint32_t div_val:16;   //< [15:0, RW] - Baud-rate division value
        uint32_t rsvd:16;      //< [31:16]
    } bits;
} reg_uart_baudrate_div;

/**
* @brief Specifies divisor fractional value
* @details 
* @see ULCONn (0x2C)
*/
typedef union reg_uart_div_val_t {
    uint32_t all;
    struct {
        uint32_t div_val:4;    //< [3:0, RW] Fractional part of Baud-rate divisor
        uint32_t rsvd:28;      //< [31:4]
    } bits;
} reg_uart_div_val;

/**
* @brief Specifies interrupt pending
* @details 
* @see ULCONn (0x30)
*/
typedef union reg_uart_intrpt_pend_t {
    uint32_t all;
    struct {
        uint32_t rxd:1;     //< [0, RW] - Generates receive interrupt
        uint32_t error:1;   //< [1, RW] - Generates error interrupt
        uint32_t txd:1;     //< [2, RW] - Generates transmit interrupt
        uint32_t modem:1;   //< [3, RW] - Generates modem interrupt
        uint32_t rsvd:28;   //< [31:4, RW]
    } bits;
} reg_uart_intrpt_pend;

/**
* @brief Specifies interrupt source pending
* @details 
* @see ULCONn (0x34)
*/
typedef union reg_uart_intrpt_src_pend_t {
    uint32_t all;
    struct {
        uint32_t rxd:1;     //< [0, RW] - Generates receive interrupt
        uint32_t error:1;   //< [1, RW] - Generates error interrupt
        uint32_t txd:1;     //< [2, RW] - Generates transmit interrupt
        uint32_t modem:1;   //< [3, RW] - Generates modem interrupt
        uint32_t rsvd:28;   //< [31:4, RW]
    } bits;
} reg_uart_intrpt_src_pend;

/**
* @brief Specifies interrupt mask
* @details 
* @see ULCONn (0x38)
*/
typedef union reg_uart_intrpt_mask_t {
    uint32_t all;
    struct {
        uint32_t rxd:1;     //< [0, RW] - Masks receive interrupt
        uint32_t error:1;   //< [1, RW] - Masks error interrupt
        uint32_t txd:1;     //< [2, RW] - Masks transmit interrupt
        uint32_t modem:1;   //< [3, RW] - Masks modem interrupt
        uint32_t rsvd:28;   //< [31:4, RW]
    } bits;
} reg_uart_intrpt_mask;

/* ---------------------------------------------------------------------------
   - UART Registers
 --------------------------------------------------------------------------- */
/**
* @brief 
* @details 
* @see 
*/
typedef struct _regs_uart_t {
    reg_uart_line_ctrl          line_ctrl;
    reg_uart_ctrl               ctrl;
    reg_uart_fifo_ctrl          fifo_ctrl;
    reg_uart_modem_ctrl         modem_ctrl;
    reg_uart_txrx_stat          txrx_stat;
    reg_uart_rx_err_stat        rx_err_stat;
    reg_uart_fifo_stat          fifo_stat;
    reg_uart_modem_stat         modem_stat;
    reg_uart_transmit_buf       tx_buf;
    reg_uart_receive_buf        rx_buf;
    reg_uart_baudrate_div       baudrate_div;
    reg_uart_div_val            div_val;
    reg_uart_intrpt_pend        intrpt_pend;
    reg_uart_intrpt_src_pend    intrpt_src_pend;
    reg_uart_intrpt_mask        intrpt_mask;
} regs_uart_t;

/* ---------------------------------------------------------------------------
   - UART Configuration Parameters
 --------------------------------------------------------------------------- */
/**
* @brief 
* @details 
* @see 
*/
typedef struct _uart_cfg_t {
    uint32_t intr_mask; //< Interrupt mask (Rx, Tx, Error, Modem)
    uint32_t prio;      //< Interrupt priority
    uint32_t target;    //< Target CPU I/F
} uart_cfg_t;

/**
* @brief 
* @details 
* @see 
*/
typedef struct _uart_mng_t {
    uart_cfg_t cfg;
} uart_mng_t;


/*****************************************************************************
 * Function prototypes
 *****************************************************************************/
/**
* @brief
* @param[in]
* @param[out]
* @return void
*/
void uart_init ( void );
void uart_deinit ( void );

/**
* @brief
* @param[in]
* @param[out]
* @return void
*/
void uart_configure ( void );
uint32_t uart_base_address_get ( uint32_t id );

/**
* @brief
* @param[in]
* @param[out]
* @return void
*/
void uart_interrupt_register ( uint32_t id );
void uart_interrupt_unregister ( uint32_t id );
void uart_interrupt_enable ( uint32_t id );
void uart_interrupt_disable ( uint32_t id );
void uart_interrupt_clear ( uint32_t id );
uint32_t uart_interrupt_number_get ( uint32_t id );

#endif /* _EXYNOS_UART_H_ */
