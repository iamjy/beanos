/**
 * @file
 * @author
 * @date
 * @brief
 * @see
 */

#ifndef _HAL_GPIO_H
#define _HAL_GPIO_H

/*****************************************************************************
 * Headers
 *****************************************************************************/
#include "stdint.h"
#include "stdbool.h"
#include "stddef.h"


/*****************************************************************************
 * Macro Definitions
 *****************************************************************************/
/* ---------------------------------------------------------------------------
   - 
 --------------------------------------------------------------------------- */
/*****************************************************************************
 * Type Definition
 *****************************************************************************/
/*****************************************************************************
* Enumerations
*****************************************************************************/
/*****************************************************************************
 * Structures
 *****************************************************************************/
/**
* @brief 
* @details 
* @see 
*/
/*****************************************************************************
 * Function Prototypes
 *****************************************************************************/
/**
* @brief
* @param[in]
* @param[out]
* @return void
*/
void HAL_gpio_pin_cfg( void );
void HAL_gpio_pin_read( void );
void HAL_gpio_pin_type_input( void );
void HAL_gpio_pin_type_output( void );
void HAL_gpio_pin_type_output_pud( void );

/**
* @brief
* @param[in]
* @param[out]
* @return void
*/
void HAL_gpio_pad_cfg_get( void );
void HAL_gpio_pad_cfg_set( void );

/**
* @brief
* @param[in]
* @param[out]
* @return void
*/
void HAL_gpio_dir_mode_get( void );
void HAL_gpio_dir_mode_set( void );

/**
* @brief
* @param[in]
* @param[out]
* @return void
*/
void HAL_gpio_intr_enable( void );
void HAL_gpio_intr_disable( void );
void HAL_gpio_intr_clear( void );
void HAL_gpio_intr_status( void );
void HAL_gpio_intr_hdl_register( void );
void HAL_gpio_intr_hdl_unregister( void );
void HAL_gpio_intr_type_get( void );
void HAL_gpio_intr_type_set( void );

/**
* @brief
* @param[in]
* @param[out]
* @return void
*/
void HAL_gpio_drv_strength_ctrl( void );

/**
* @brief
* @param[in]
* @param[out]
* @return void
*/
void HAL_gpio_sleep_mode_ctrl( void );
void HAL_gpio_pwr_down_mode_cfg( void );
void HAL_gpio_pwr_down_mode_pud( void );


#endif /* _HAL_INTERRUPT_H */
