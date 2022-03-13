/**
* @file
* @author
* @date
* @brief
* @see
*/

#ifndef _EXYNOS_TIMER_H_
#define _EXYNOS_TIMER_H_

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
   - PWMn
 --------------------------------------------------------------------------- */
#define EXYNOS_PWM_MAX_NUM    ( 2 )

/* ---------------------------------------------------------------------------
   - Register Base Address
 --------------------------------------------------------------------------- */
#define EXYNOS_PWM_BASE        (( volatile uint32_t * ) 0x139D0000 )	//< PWM Register Base Address
#define EXYNOS_PWM_ISP_BASE    (( volatile uint32_t * ) 0x12160000 )	//< PWM ISP Register Base Address

/* ---------------------------------------------------------------------------
   - Register Offset
 --------------------------------------------------------------------------- */
#define OFFSET_TCFG0         ( 0x0000 )
#define OFFSET_TCFG1         ( 0x0004 )
#define OFFSET_TCON          ( 0x0008 )
#define OFFSET_TCNTB0        ( 0x000C )
#define OFFSET_TCMPB0        ( 0x0010 )
#define OFFSET_TCNTO0        ( 0x0014 )
#define OFFSET_TCNTB1        ( 0x0018 )
#define OFFSET_TCMPB1        ( 0x001C )
#define OFFSET_TCNTO1        ( 0x0020 )
#define OFFSET_TCNTB2        ( 0x0024 )
#define OFFSET_TCMPB2        ( 0x0028 )
#define OFFSET_TCNTO2        ( 0x002C )
#define OFFSET_TCNTB3        ( 0x0030 )
#define OFFSET_TCMPB3        ( 0x0034 )
#define OFFSET_TCNTO3        ( 0x0038 )
#define OFFSET_TCNTB4        ( 0x003C )
#define OFFSET_TCNTO4        ( 0x0040 )
#define OFFSET_TINT_CSTAT    ( 0x0044 )


/*****************************************************************************
 * Type Definitions
 *****************************************************************************/
typedef struct _timer_clk_freq_t timer_clk_freq_t;
typedef struct _timer_intr_stat_t timer_intr_stat_t;


/*****************************************************************************
 * Enumerations
 *****************************************************************************/
enum {
    PWM_TIMER_0 = 0,
    PWM_TIMER_1,
    PWM_TIMER_2,
    PWM_TIMER_3,
    PWM_TIMER_4 = 4
};


/*****************************************************************************
 * Structures
 *****************************************************************************/
/**
* @brief 
* @details Timer input clock frequency = PCLK / {prescaler value + 1} / {divider value}
*          - {prescaler value} = 1 to 255
*          - {divider value}   = 1, 2, 4, 8, 16
*          - Dead zone length  = 0 to 254
* @see 24.5.1.1 TCFG0
*/
typedef union _reg_TCFG0_t {
    uint32_t all;
    struct {
        uint32_t prescaler0:8;      //< Prescaler 0 value for timer 0 and 1
        uint32_t prescaler1:8;      //< Prescaler 0 value for timer 2, 3 and 4
        uint32_t dead_zone_len:8;   //< Dead zone length
        uint32_t rsvd0:8;
    } bits;
} reg_TCFG0_t;

/**
* @brief
* @details Select Mux input for PWM timer 0 ~ 4
*          - 0000 = 1/1
*          - 0001 = 1/2
*          - 0010 = 1/4
*          - 0011 = 1/8
*          - 0100 = 1/16
* @see 24.5.1.2 TCFG1
*/
typedef union _reg_TCFG1_t {
    uint32_t all;
    struct {
        uint32_t div_mux0:4;    //< 1/1, 1/2, 1/4, 1/8, 1/16
        uint32_t div_mux1:4;    //< 1/1, 1/2, 1/4, 1/8, 1/16
        uint32_t div_mux2:4;    //< 1/1, 1/2, 1/4, 1/8, 1/16
        uint32_t div_mux3:4;    //< 1/1, 1/2, 1/4, 1/8, 1/16
        uint32_t div_mux4:4;    //< 1/1, 1/2, 1/4, 1/8, 1/16
        uint32_t rsvd0:12;
    } bits;
} reg_TCFG1_t;

/**
* @brief Timer Configuration Register
* @details 
* @see 24.5.1.3 TCON
*/
typedef union _reg_TCON_t {
    uint32_t all;
    struct {
        uint32_t t0_start:1;        //< 0 : Start, 1 : Stop
        uint32_t t0_m_update:1;     //< 0 : No operation, 1 : Updates TCNTB0 and TCMPB0
        uint32_t t0_out_invt:1;     //< 0 : Inverter Off, 1 : TOUT_0 inverter-on
        uint32_t t0_auto_reload:1;  //< 0 : One-shot, 1 : Interval mode (auto-reload)
        uint32_t dead_zone_en:1;    //< Enables / Disables Dead zone generator
        uint32_t rsvd0:3;
        uint32_t t1_start:1;        //<
        uint32_t t1_m_update:1;     //<
        uint32_t t1_out_invt:1;     //<
        uint32_t t1_auto_reload:1;  //<
        uint32_t t2_start:1;        //<
        uint32_t t2_m_update:1;     //<
        uint32_t t2_out_invt:1;     //<
        uint32_t t2_auto_reload:1;  //<
        uint32_t t3_start:1;        //<
        uint32_t t3_m_update:1;     //<
        uint32_t t3_out_invt:1;     //<
        uint32_t t3_auto_reload:1;  //<
        uint32_t t4_start:1;        //<
        uint32_t t4_m_update:1;     //<
        uint32_t t4_auto_reload:1;  //<
        uint32_t rsvd1:9;
    } bits;
} reg_TCON_t;

/**
* @brief 
* @details
* @see 
*/
typedef union _reg_TCNTB0_t {
    uint32_t cnt;   //< Timer 0 Count Buffer
} reg_TCNTB0_t;

/**
* @brief 
* @details
* @see 
*/
typedef union _reg_TCMPB0_t {
    uint32_t cmp;   //< Timer 0 Compare Buffer
} reg_TCMPB0_t;

/**
* @brief 
* @details
* @see 
*/
typedef union _reg_TCNTO0_t {
    uint32_t obs;   //< Timer 0 Count Observation
} reg_TCNTO0_t;

/**
* @brief 
* @details
* @see 
*/
typedef union _reg_TCNTB1_t {
    uint32_t cnt;   //< Timer 1 Count Buffer
} reg_TCNTB1_t;

/**
* @brief 
* @details
* @see 
*/
typedef union _reg_TCMPB1_t {
    uint32_t cmp;   //< Timer 1 Compare Buffer
} reg_TCMPB1_t;

/**
* @brief 
* @details
* @see 
*/
typedef union _reg_TCNTO1_t {
    uint32_t obs;   //< Timer 1 Count Observation
} reg_TCNTO1_t;

/**
* @brief 
* @details
* @see 
*/
typedef union _reg_TCNTB2_t {
    uint32_t cnt;   //< Timer 2 Count Buffer
} reg_TCNTB2_t;

/**
* @brief 
* @see 
*/
typedef union _reg_TCMPB2_t {
    uint32_t cmp;   //< Timer 2 Compare Buffer
} reg_TCMPB2_t;

/**
* @brief 
* @see 
*/
typedef union _reg_TCNTO2_t {
    uint32_t obs;   //< Timer 2 Count Observation
} reg_TCNTO2_t;

/**
* @brief 
* @see 
*/
typedef union _reg_TCNTB3_t {
    uint32_t cnt;   //< Timer 3 Count Buffer
} reg_TCNTB3_t;

/**
* @brief 
* @see 
*/
typedef union _reg_TCMPB3_t {
    uint32_t cmp;   //< Timer 3 Compare Buffer
} reg_TCMPB3_t;

/**
* @brief 
* @see 
*/
typedef union _reg_TCNTO3_t {
    uint32_t obs;   //< Timer 3 Count Observation
} reg_TCNT03_t;

/**
* @brief 
* @see 
*/
typedef union _reg_TCNTB4_t {
    uint32_t cnt;   //< Timer 4 Count Buffer
} reg_TCNTB4_t;

/**
* @brief 
* @see 
*/
typedef union _reg_TCNTO4_t {
    uint32_t obs;   //< Timer 4 Count Observation
} reg_TCNTO4_t;

/**
* @brief 
* @see 
*/
typedef union _reg_TINT_CSTAT_t {
    uint32_t all;
    struct {
        uint32_t t0_intr_en:1;      //< Enables Timer 0 Interrupt
        uint32_t t1_intr_en:1;      //< Enables Timer 1 Interrupt
        uint32_t t2_intr_en:1;      //< Enables Timer 2 Interrupt
        uint32_t t3_intr_en:1;      //< Enables Timer 3 Interrupt
        uint32_t t4_intr_en:1;      //< Enables Timer 4 Interrupt
        uint32_t t0_intr_stat:1;    //< Timer 0 Interrupt Status
        uint32_t t1_intr_stat:1;    //< Timer 1 Interrupt Status
        uint32_t t2_intr_stat:1;    //< Timer 2 Interrupt Status
        uint32_t t3_intr_stat:1;    //< Timer 3 Interrupt Status
        uint32_t t4_intr_stat:1;    //< Timer 4 Interrupt Status
        uint32_t rsvd0:12;
    } bits;
} reg_TINT_CSTAT_t;

/* ---------------------------------------------------------------------------
 * PWM Registers
 --------------------------------------------------------------------------- */
/**
* @brief 
* @details 
* @see 
*/
typedef struct _regs_pwm_t {
    reg_TCFG0_t         tm_cfg0;
    reg_TCFG1_t         tm_cfg1;
    reg_TCON_t          tm_conf;
    reg_TCNTB0_t        tm0_cnt;
    reg_TCMPB0_t        tm0_cmp;
    reg_TCNTO0_t        tm0_obs;
    reg_TCNTB1_t        tm1_cnt;
    reg_TCMPB1_t        tm1_cmp;
    reg_TCNTO1_t        tm1_obs;
    reg_TCNTB2_t        tm2_cnt;
    reg_TCMPB2_t        tm2_cmp;
    reg_TCNTO2_t        tm2_obs;
    reg_TCNTB3_t        tm3_cnt;
    reg_TCMPB3_t        tm3_cmp;
    reg_TCNT03_t        tm3_obs;
    reg_TCNTB4_t        tm4_cnt;
    reg_TCNTO4_t        tm4_obs;
    reg_TINT_CSTAT_t    intr_stat;
} regs_pwm_t;

/**
* @brief 
* @details 
* @see 
*/
typedef struct _regs_pwm_timer_t {
    uint32_t all;   //< 
} regs_pwm_stat_t;


/* ---------------------------------------------------------------------------
 * PWM Configuration Parameters
 --------------------------------------------------------------------------- */
/**
* @brief 
* @details 
* @see 
*/
typedef struct _timer_clk_freq_t {
    uint8_t prescaler;  //< Prescaler value (1 ~ 255)
    uint8_t div;        //< Divider MUXn (0 ~ 4)
    uint8_t dz_len;     //< Dead zone length
} timer_clk_freq_t;

/**
* @brief 
* @details 
* @see 
*/
typedef struct _timer_intr_stat_t {
    uint32_t en;    //< Enable / Disable interrupt
    uint32_t stat;  //< Read interrupt status
} timer_intr_stat_t;

/**
* @brief 
* @details 
* @see 
*/
typedef struct _timer_cfg_t {
    timer_clk_freq_t clk_freq;      //< Timer input clock frequency
    timer_intr_stat_t intr_stat;    //< Interrupt status
    uint32_t start;                 //< Timer Start / Stop
    uint32_t m_update;              //< Updates TNTBn, TCMPBn
    uint32_t o_invt;                //< TOUT_n Output inverter
    uint32_t a_reload;              //< TCNTBn auto reload (down-counter)
    uint32_t cnt;                   //< Timer N (0 ~ 4) count buffer
    uint32_t cmp;                   //< Timer N (0 ~ 4) compare buffer
    uint32_t obs;                   //< Timer N (0 ~ 4) count observation
} timer_cfg_t;

/**
 * @brief 
 * @details 
 * @see 
 */
typedef struct _timer_mng_t {

} timer_mng_t;


/*****************************************************************************
 * Function prototypes
 *****************************************************************************/
/**
* @brief
* @param[in]
* @param[out]
* @return void
*/
void pwm_init ( void );
void pwm_deinit ( void );

/**
* @brief
* @param[in]
* @param[out]
* @return void
*/
void pwm_configure ( void );
uint32_t pwm_base_address_get ( uint32_t id );

/**
* @brief
* @param[in]
* @param[out]
* @return void
*/
void pwm_interrupt_register ( uint32_t id );
void pwm_interrupt_unregister ( uint32_t id );
void pwm_interrupt_enable ( uint32_t id );
void pwm_interrupt_disable ( uint32_t id );
void pwm_interrupt_clear ( uint32_t id );
uint32_t pwm_interrupt_number_get ( uint32_t id );

#endif /* _API_H_ */
