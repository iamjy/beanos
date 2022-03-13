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
#include "interrupt.h"
#include "wdt.h"
#include "uart.h"
#include "timer.h"
#include "gpio.h"
#include "spi.h"
#include "i2c.h"


/*****************************************************************************
 * Global variables
 *****************************************************************************/
volatile regs_gic_cpu_t     *gic_cpu            = (regs_gic_cpu_t *)EXYNOS_GIC_CPU0_BASE;
volatile regs_gic_dist_t    *gic_dist           = (regs_gic_dist_t *)EXYNOS_GIC_DIST_BASE;
volatile reg_icciidr_t      *icciidr            = (reg_icciidr_t *)EXYNOS_GIC_ID_NUM_BASE;
volatile regs_secur_stat_t  *dist_secur_stat    = (regs_secur_stat_t *)EXYNOS_GIC_DIST_SECURITY_STATUS_BASE;
volatile regs_set_en_t      *dist_set_en        = (regs_set_en_t *)EXYNOS_GIC_DIST_SET_ENABLE_BASE;
volatile regs_clear_en_t    *dist_clr_en        = (regs_clear_en_t *)EXYNOS_GIC_DIST_CLEAR_ENABLE_BASE;
volatile regs_icdispr_t     *dist_icdispr       = (regs_icdispr_t *)EXYNOS_GIC_DIST_SET_PENDING_BASE;
volatile regs_icdicpr_t     *dist_icdicpr       = (regs_icdicpr_t *)EXYNOS_GIC_DIST_CLEAR_PENDING_BASE;
volatile regs_icdabr_t      *dist_icdabr        = (regs_icdabr_t *)EXYNOS_GIC_DIST_ACTIVE_BASE;
volatile regs_icdipr_t      *dist_icdipr        = (regs_icdipr_t *)EXYNOS_GIC_DIST_PRIORITY_BASE;
volatile regs_icdiptr_t     *dist_icdiptr       = (regs_icdiptr_t *)EXYNOS_GIC_DIST_CPU_TARGET_BASE;
volatile regs_icdicfr_t     *dist_icdicfr       = (regs_icdicfr_t *)EXYNOS_GIC_DIST_INTR_CONFIG_FIELD_BASE;
volatile regs_intr_stat_t   *dist_intr_stat     = (regs_intr_stat_t *)EXYNOS_GIC_DIST_INTR_SRC_STATUS_BASE;
volatile regs_icdsgir_t     *dist_icdsgir       = (regs_icdsgir_t *)EXYNOS_GIC_DIST_SGI_BASE;
volatile regs_uart_t        *g_uart             = (regs_uart_t *)EXYNOS_UART2_BASE;
volatile regs_pwm_t         *g_timer            = (regs_pwm_t *)EXYNOS_PWM_BASE;
volatile regs_pwm_stat_t    *g_timer_isp        = (regs_pwm_stat_t *)EXYNOS_PWM_ISP_BASE;
volatile regs_wdt_t         *g_wdt              = (regs_wdt_t *)EXYNOS_WDT_BASE;
volatile regs_gpioa2j_t     *g_gpioa2j          = (regs_gpioa2j_t *)EXYNOS_GPIO_A2J_BASE;
volatile regs_gpiok2x_t     *g_gpiok2x          = (regs_gpiok2x_t *)EXYNOS_GPIO_K2X_BASE;
volatile regs_gpioz2z_t     *g_gpioz2z          = (regs_gpioz2z_t *)EXYNOS_GPIO_Z2Z_BASE;
volatile regs_gpiov2v_t     *g_gpiov2v          = (regs_gpiov2v_t *)EXYNOS_GPIO_V2V_BASE;
volatile regs_spi_t         *g_spi0             = (regs_spi_t *)EXYNOS_SPI0_BASE;
volatile regs_spi_t         *g_spi1             = (regs_spi_t *)EXYNOS_SPI1_BASE;
volatile regs_spi_t         *g_spi2             = (regs_spi_t *)EXYNOS_SPI2_BASE;
volatile regs_i2c_t         *g_i2c[EXYNOS_I2C_MAX_NUM] = {NULL,};