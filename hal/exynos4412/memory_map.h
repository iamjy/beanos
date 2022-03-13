/**
* @file
* @author
* @date
* @brief
* @see
*/

#ifndef ARM_EXYNOS4412_MEMORY_MAP_H
#define ARM_EXYNOS4412_MEMORY_MAP_H

/*****************************************************************************
 * Header files
 *****************************************************************************/
/*****************************************************************************
 * Macro definitions
 *****************************************************************************/
#define INST_ADDR_START     0x40000000
#define USRSYS_STACK_START  0x40100000 //< ~ 0x402FFFFF - 4 (0x402FFFFC)
#define SVC_STACK_START     0x40300000 //< ~ 0x403FFFFF - 4 (0x403FFFFC)
#define IRQ_STACK_START     0x40400000 //< ~ 0x404FFFFF - 4 (0x404FFFFC)
#define FIQ_STACK_START     0x40500000 //< ~ 0x405FFFFF - 4 (0x405FFFFC)
#define ABT_STACK_START     0x40600000 //< ~ 0x406FFFFF - 4 (0x406FFFFC)
#define UND_STACK_START     0x40700000 //< ~ 0x407FFFFF - 4 (0x407FFFFC)
#define TASK_STACK_START    0x40800000 //< ~ 0x408FFFFF - 4 (0x408FFFFC)
#define GLOBAL_STACK_START  0x44800000 //< ~ 0x448FFFFF - 4 (0x448FFFFC)
#define DALLOC_STACK_START  0x44900000

#define INST_MEM_SIZE (USRSYS_STACK_START - INST_ADDR_STATRT)
#define USRSYS_STACK_SIZE (SVC_STACK_START - USRSYS_STACK_START)
#define SVC_STACK_SIZE (IRQ_STACK_START - SVC_STACK_START)
#define IRQ_STACK_SIZE (FIQ_STACK_START - IRQ_STACK_START)
#define FIQ_STACK_SIZE (ABT_STACK_START - FIQ_STACK_START)
#define ABT_STACK_SIZE (UND_STACK_START - ABT_STACK_START)
#define UND_STACK_SIZE (TASK_STACK_START - UND_STACK_START)
#define TASK_STACK_SIZE (GLOBAL_STACK_START - TASK_STACK_START)
#define DALLOC_MEM_SIZE (55 * 1024 * 1024)

#define USRSYS_STACK_TOP (USRSYS_STACK_START + USRSYS_STACK_SIZE - 4)
#define SVC_STACK_TOP (SVC_STACK_START + SVC_STACK_SIZE - 4)
#define IRQ_STACK_TOP (IRQ_STACK_START + IRQ_STACK_SIZE - 4)
#define FIQ_STACK_TOP (FIQ_STACK_START + FIQ_STACK_SIZE - 4)
#define ABT_STACK_TOP (ABT_STACK_START + ABT_STACK_SIZE - 4)
#define UND_STACK_TOP (UND_STACK_START + UND_STACK_SIZE - 4)


/*****************************************************************************
 * Type definition
 *****************************************************************************/
/*****************************************************************************
* Enumerations
*****************************************************************************/
/*****************************************************************************
* Structures
*****************************************************************************/
/*****************************************************************************
 * Function prototypes
 *****************************************************************************/
/**
* @brief
* @param[in]
* @param[out]
* @return void
*/

#endif /* ARM_EXYNOS4412_MEMORY_MAP_H */
