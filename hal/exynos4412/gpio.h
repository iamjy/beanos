/**
 * @file
 * @author
 * @date
 * @brief
 * @see
 */

#ifndef _EXYNOS_GPIO_H_
#define _EXYNOS_GPIO_H_

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
   - Base Address
 --------------------------------------------------------------------------- */
#define EXYNOS_GPIO_A2J_BASE    (( volatile uint32_t * ) 0x11400000 )   //< GPIO GPA0CON ~ PDNEN Register Base Address
#define EXYNOS_GPIO_K2X_BASE    (( volatile uint32_t * ) 0x11000000 )   //< GPIO GPK0CON ~ PDNEN Register Base Address
#define EXYNOS_GPIO_Z2Z_BASE    (( volatile uint32_t * ) 0x106E0000 )   //< GPIO GPZCON ~ PDNEN Register Base Address
#define EXYNOS_GPIO_V2V_BASE    (( volatile uint32_t * ) 0x03860000 )   //< GPIO GPV0CON ~ PDNEN Register Base Address

/* ---------------------------------------------------------------------------
   - Number of Ports
 --------------------------------------------------------------------------- */
#define GPIO_GRP_A_NUM_PORTS    ( 14 )
#define GPIO_GRP_A0_NUM_PORTS   ( 8 )
#define GPIO_GRP_A1_NUM_PORTS   ( 6 )
#define GPIO_GRP_B_NUM_PORTS    ( 8 )
#define GPIO_GRP_C_NUM_PORTS    ( 10 )
#define GPIO_GRP_C0_NUM_PORTS   ( 5 )
#define GPIO_GRP_C1_NUM_PORTS   ( 5 )
#define GPIO_GRP_D_NUM_PORTS    ( 8 )
#define GPIO_GRP_D0_NUM_PORTS   ( 4 )
#define GPIO_GRP_D1_NUM_PORTS   ( 4 )
#define GPIO_GRP_M_NUM_PORTS    ( 35 )
#define GPIO_GRP_M0_NUM_PORTS   ( 8 )
#define GPIO_GRP_M1_NUM_PORTS   ( 7 )
#define GPIO_GRP_M2_NUM_PORTS   ( 5 )
#define GPIO_GRP_M3_NUM_PORTS   ( 8 )
#define GPIO_GRP_M4_NUM_PORTS   ( 8 )
#define GPIO_GRP_F_NUM_PORTS    ( 30 )
#define GPIO_GRP_F0_NUM_PORTS   ( 8 )
#define GPIO_GRP_F1_NUM_PORTS   ( 8 )
#define GPIO_GRP_F2_NUM_PORTS   ( 8 )
#define GPIO_GRP_F3_NUM_PORTS   ( 6 )
#define GPIO_GRP_J_NUM_PORTS    ( 13 )
#define GPIO_GRP_J0_NUM_PORTS   ( 8 )
#define GPIO_GRP_J1_NUM_PORTS   ( 5 )
#define GPIO_GRP_K_NUM_PORTS    ( 28 )
#define GPIO_GRP_K0_NUM_PORTS   ( 7 )
#define GPIO_GRP_K1_NUM_PORTS   ( 7 )
#define GPIO_GRP_K2_NUM_PORTS   ( 7 )
#define GPIO_GRP_K3_NUM_PORTS   ( 7 )
#define GPIO_GRP_L_NUM_PORTS    ( 19 )
#define GPIO_GRP_L0_NUM_PORTS   ( 7 )
#define GPIO_GRP_L1_NUM_PORTS   ( 2 )
#define GPIO_GRP_L2_NUM_PORTS   ( 8 )
#define GPIO_GRP_X_NUM_PORTS    ( 32 )
#define GPIO_GRP_X0_NUM_PORTS   ( 8 )
#define GPIO_GRP_X1_NUM_PORTS   ( 8 )
#define GPIO_GRP_X2_NUM_PORTS   ( 8 )
#define GPIO_GRP_X3_NUM_PORTS   ( 8 )


/*****************************************************************************
 * Enumerations
 *****************************************************************************/
/*****************************************************************************
 * Type definitions
 *****************************************************************************/
/*****************************************************************************
 * Structures
 *****************************************************************************/
/* ---------------------------------------------------------------------------
   - GPIO Register
 --------------------------------------------------------------------------- */
/**
* @brief 
* @details 
* @see 
*/
typedef union _regs_gpio__t {
  uint32_t all;
  struct {
    uint32_t val:32;  //< []
  } bits;
} regs_gpio__t;

/**
* @brief 
* @details 
* @see 
*/
typedef struct _regs_gpioa2j_t {
} regs_gpioa2j_t;

/**
* @brief 
* @details 
* @see 
*/
typedef struct _regs_gpiok2x_t {
} regs_gpiok2x_t;

/**
* @brief 
* @details 
* @see 
*/
typedef struct _regs_gpioz2z_t {
} regs_gpioz2z_t;

/**
* @brief 
* @details 
* @see 
*/
typedef struct _regs_gpiov2v_t {
} regs_gpiov2v_t;


/* ---------------------------------------------------------------------------
   - GPIO Configuration Prameters
 --------------------------------------------------------------------------- */
/**
* @brief 
* @details 
* @see 
*/
typedef struct _gpio_cfg_t {
} gpio_cfg_t;

/**
* @brief 
* @details 
* @see 
*/
typedef struct _gpio_mng_t {
} gpio_mng_t;


/*****************************************************************************
 * Function prototypes
 *****************************************************************************/
/**
* @brief
* @param[in]
* @param[out]
* @return void
*/

#endif /* _EXYNOS_GPIO_H_ */
