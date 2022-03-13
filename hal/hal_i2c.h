/**
 * @file
 * @author
 * @date
 * @brief
 * @see
 */

#ifndef _HAL_I2C_H
#define _HAL_I2C_H

/*****************************************************************************
 * Headers
 *****************************************************************************/
#include "stdint.h"
#include "stdbool.h"
#include "stddef.h"


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
 * Structures
 *****************************************************************************/
 /* ---------------------------------------------------------------------------
    - I2C Configuration
 --------------------------------------------------------------------------- */
/**
* @brief 
* @details 
* @see 
*/
typedef struct _hal_i2c_transaction_t {
    uint32_t addr;      //< Specify slave address
    uint32_t sub_addr;  //< Specify register address
    uint8_t *buf;       //< Data buffer for Tx / Rx
    uint32_t cnt;       //< Data R / W count
} hal_i2c_transaction_t;


/*****************************************************************************
 * Function prototypes
 *****************************************************************************/
/**
* @brief
* @param[in]
* @param[out]
* @return void
*/
void HAL_i2c_dev_open ( uint32_t i2c_id );
void HAL_i2c_dev_close ( uint32_t i2c_id );

/**
* @brief
* @param[in]
* @param[out]
* @return void
*/
void HAL_i2c_data_transmit ( uint32_t i2c_id, void *p_transaction );
void HAL_i2c_data_receive ( uint32_t i2c_id, void *p_transaction );


#endif /* _HAL_UART_H */
