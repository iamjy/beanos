/**
* @file
* @author
* @date
* @brief
* @see
*/

#ifndef _EXYNOS_WDT_H_
#define _EXYNOS_WDT_H_

/*****************************************************************************
 * Header files
 *****************************************************************************/
#include "stdint.h"
#include "stdbool.h"
#include "stddef.h"


/*****************************************************************************
 * Macro definitions
 *****************************************************************************/
/* ---------------------------------------------------------------------------
   - Register Base Address
 --------------------------------------------------------------------------- */
#define EXYNOS_WDT_BASE    (( volatile uint32_t * ) 0x10060000 )    //< WDT Register Base Address

/* ---------------------------------------------------------------------------
   - Register Offset
 --------------------------------------------------------------------------- */
#define OFFSET_WTCON       ( 0x0000 )
#define OFFSET_WTDAT       ( 0x0004 )
#define OFFSET_WTCNT       ( 0x0008 )
#define OFFSET_WTClrint    ( 0x000C )


/*****************************************************************************
 * Type definitions
 *****************************************************************************/
/*****************************************************************************
 * Enumerations
 *****************************************************************************/
/* ---------------------------------------------------------------------------
   - Timer setting value
 --------------------------------------------------------------------------- */
enum {
    WDT_TIMER_DISABLE = 0,
    WDT_TIMER_ENABLE  = 1
};

enum {
    WDT_RESET_DISABLE = 0,
    WDT_RESET_ENABLE  = 1
};

/* ---------------------------------------------------------------------------
   - Clock divider setting value
 --------------------------------------------------------------------------- */
enum {
    WDT_CLK_SEL_16_DIV  = 0,    //< 16
    WDT_CLK_SEL_32_DIV  = 1,    //< 32
    WDT_CLK_SEL_64_DIV  = 2,    //< 64
    WDT_CLK_SEL_128_DIV = 3     //< 128
};

/* ---------------------------------------------------------------------------
   - Interret setting value
 --------------------------------------------------------------------------- */
enum {
    WDT_INTR_DISABLE = 0,   
    WDT_INTR_ENABLE  = 1,   
    WDT_INTR_CLR     = 2     //< Writing any values on the register clears the interrupt
};


/*****************************************************************************
 * Structures
 *****************************************************************************/
/**
* @brief 
* @details 
* @see WTCON
*/
typedef union _reg_WTCON_t {
    uint32_t all;
    struct {
        uint32_t reset:1;       //< Enables or disables WDT output bit for reset signal
        uint32_t rsvd0:1;
        uint32_t intr_gen:1;    //< Enables or disables interrupt bit
        uint32_t clk_sel:2;     //< Determins the clock division factor (16, 32, 64, 128)
        uint32_t timer:1;       //< Enables or disables WDT bit
        uint32_t rsvd1:2;
        uint32_t prescale:8;    //< Prescaler value (2^8-1)
        uint32_t rsvd2:16;
    } bits;
} reg_WTCON_t;

/**
* @brief 
* @details 
* @see WTDAT
*/
typedef union _reg_WTDAT_t {
    uint32_t all;
    struct {
        uint32_t reload_cnt:16;    //< WDT count value for reload
        uint32_t rsvd0:16;
    } bits;
} reg_WTDAT_t;

/**
* @brief 
* @details 
* @see WTCNT
*/
typedef union _reg_WTCNT_t {
    uint32_t all;
    struct {
        uint32_t cnt_val:16;    //< The current count value of the WDT
        uint32_t rsvd:16;
    } bits;
} reg_WTCNT_t;

/**
* @brief 
* @details 
* @see WTCCLRINT
*/
typedef union _reg_WTCLRINT_t {
    uint32_t all;
    struct {
        uint32_t intr_clr;    //< Write any value to clear the interrupt
    } bits;
} reg_WTCLRINT_t;

/* ---------------------------------------------------------------------------
 * WDT Registers
 --------------------------------------------------------------------------- */
/**
* @brief 
* @details 
* @see 
*/
typedef struct _regs_wdt_t {
    reg_WTCON_t wt_con;
    reg_WTDAT_t wt_dat;
    reg_WTCNT_t wt_cnt;
    reg_WTCLRINT_t wt_clrint;
} regs_wdt_t;

 /* ---------------------------------------------------------------------------
    - WDT Configuration Parameters
 --------------------------------------------------------------------------- */
/**
* @brief 
* @details 
* @see 
*/
typedef struct _wdt_cfg_t {
    uint32_t timer_en;    //< reg_WTCON - Timer enable / disable
    uint32_t prescale;    //< reg_WTCON - Prescaler value
    uint32_t clk_sel;     //< reg_WTCON - Clock select
    uint32_t intr_en;     //< reg_WTCON - Interrupt generation
    uint32_t cnt_val;     //< reg_WTDAT
    uint32_t reset;       //< reg_WTCON - Reset enable / disable
} wdt_cfg_t;

/**
 * @brief 
 * @details 
 * @see 
 */
typedef struct _wdt_mng_t {

} wdt_mng_t;


/*****************************************************************************
 * Function prototypes
 *****************************************************************************/
/**
* @brief
* @param[in]
* @param[out]
* @return void
*/
void wdt_init ( void );
void wdt_deinit ( void );

/**
* @brief
* @param[in]
* @param[out]
* @return void
*/
void wdt_configure ( void );
uint32_t wdt_base_address_get ( void );

/**
* @brief
* @param[in]
* @param[out]
* @return void
*/
void wdt_interrupt_register ( void );
void wdt_interrupt_unregister ( void );
void wdt_interrupt_enable ( void );
void wdt_interrupt_disable ( void );
void wdt_interrupt_clear ( void );
uint32_t wdt_interrupt_number_get ( void );

#endif /* _EXYNOS_WDT_H_ */
