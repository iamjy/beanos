/**
 * @author  iamjy1005@gmail.com
 * @date    12/15/2021
 * @brief   GIC Register Map
 * @see     Exynos4412_SCP_Users Manual_Ver.0.10.00_Preliminary0.pdf
 */

#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

/*****************************************************************************
 * Header files
 *****************************************************************************/
#include "interrupt_table.h"


/*****************************************************************************
 * Macro definitions
 *****************************************************************************/
/* ---------------------------------------------------------------------------
   - [GIC CPU I/F] GIC CPUn (0 ~ 3) Base Address
 --------------------------------------------------------------------------- */
#define EXYNOS_GIC_CPU_BASE     GIC_CPU0_BASE
#define EXYNOS_GIC_CPU0_BASE    0x10480000
#define EXYNOS_GIC_CPU1_BASE    0x10484000
#define EXYNOS_GIC_CPU2_BASE    0x10488000
#define EXYNOS_GIC_CPU3_BASE    0x1048C000

#define EXYNOS_GIC_ID_NUM_BASE  0x104800FC

#define EXYNOS_GIC_INTR_OUT_C_BASE     EXYNOS_GIC_INTR_OUT_C0_BASE
#define EXYNOS_GIC_INTR_OUT_C0_BASE    0x10480044
#define EXYNOS_GIC_INTR_OUT_C1_BASE    0x10484044
#define EXYNOS_GIC_INTR_OUT_C2_BASE    0x10488044
#define EXYNOS_GIC_INTR_OUT_C3_BASE    0x1048C044

/* ---------------------------------------------------------------------------
   - GIC Distributor Base Address
 --------------------------------------------------------------------------- */
#define EXYNOS_GIC_DIST_BASE                       0x10490000
#define EXYNOS_GIC_DIST_SECURITY_STATUS_BASE       0x10490080
#define EXYNOS_GIC_DIST_SET_ENABLE_BASE            0x10490100
#define EXYNOS_GIC_DIST_CLEAR_ENABLE_BASE          0x10490180
#define EXYNOS_GIC_DIST_SET_PENDING_BASE           0x10490200
#define EXYNOS_GIC_DIST_CLEAR_PENDING_BASE         0x10490280
#define EXYNOS_GIC_DIST_ACTIVE_BASE                0x10490300
#define EXYNOS_GIC_DIST_PRIORITY_BASE              0x10490400
#define EXYNOS_GIC_DIST_CPU_TARGET_BASE            0x10490800
#define EXYNOS_GIC_DIST_INTR_CONFIG_FIELD_BASE     0x10490C00
#define EXYNOS_GIC_DIST_INTR_SRC_STATUS_BASE       0x10490D00
#define EXYNOS_GIC_DIST_SGI_BASE                   0x10490F00

/* ---------------------------------------------------------------------------
   - GIC Priority Mask Initial Value
 --------------------------------------------------------------------------- */
#define GIC_PRIORITY_HIGHEST 0x00
#define GIC_PRIORITY_LOWEST  0xFF

/* ---------------------------------------------------------------------------
   - GIC Interrupt Table
 --------------------------------------------------------------------------- */
#define GIC_SGI_PORT_NUM_START  (0)
#define GIC_SGI_PORT_NUM_END    (15)
#define GIC_SGI_ID_START        (GIC_SGI_PORT_NUM_START)
#define GIC_SGI_ID_END          (GIC_SGI_PORT_NUM_END)
#define GIC_SGI_MAX             ((GIC_SGI_ID_END - GIC_SGI_ID_START) + 1)
#define GIC_PPI_PORT_NUM_START  (0)
#define GIC_PPI_PORT_NUM_END    (15)
#define GIC_PPI_ID_START        ((GIC_SGI_ID_END) + 1)
#define GIC_PPI_ID_END          (GIC_PPI_PORT_NUM_END + GIC_PPI_ID_START)
#define GIC_PPI_MAX             ((GIC_PPI_ID_END - GIC_PPI_ID_START) + 1)
#define GIC_SPI_PORT_NUM_START  (0)
#define GIC_SPI_PORT_NUM_END    (127)
#define GIC_SPI_ID_START        ((GIC_PPI_ID_END) + 1)
#define GIC_SPI_ID_END          (GIC_SPI_PORT_NUM_END + GIC_SPI_ID_START)
#define GIC_SPI_MAX             ((GIC_SPI_ID_END - GIC_SPI_ID_START) + 1)
#define GIC_ID_START            (GIC_SGI_ID_START)
#define GIC_ID_END              (GIC_SPI_ID_END)
#define GIC_ID_MAX              ((GIC_ID_END - GIC_ID_START) + 1)

/* ---------------------------------------------------------------------------
   - Edge-triggered or Level-sensitive
 --------------------------------------------------------------------------- */
#define GIC_INRT_EDGE_TRIGGERED    1
#define GIC_INTR_LEVEL_SENSITIVE   0


/*****************************************************************************
 * Enumerations
 *****************************************************************************/
/* ---------------------------------------------------------------------------
   - GIC CPUn (0 ~ 3) Interface
 --------------------------------------------------------------------------- */
enum {
    GIC_CPU_IF_0 = 0,
    GIC_CPU_IF_1,
    GIC_CPU_IF_2,
    GIC_CPU_IF_3 = 3
};

/* ---------------------------------------------------------------------------
   - GIC Distributor Interrupt Source Type
 --------------------------------------------------------------------------- */
enum {
    GIC_DIST_INTR_SRC_SGI = 0,
    GIC_DIST_INTR_SRC_PPI,
    GIC_DIST_INTR_SRC_SPI = 2
};


/*****************************************************************************
 * Type definition
 *****************************************************************************/
/*****************************************************************************
 * Structures (struct, union)
 *****************************************************************************/
/* ---------------------------------------------------------------------------
   - GIC Controller Register Map
 --------------------------------------------------------------------------- */
/**
* @brief 
* @details 
* @see ICCICR_CPUn (0x0000)
*/
typedef union _reg_cpu_ctrl_t {
    uint32_t all;
    struct {
        uint32_t enable:1;  //< [0]
        uint32_t rsvd:31;   //< [31:1] - Reserved
    } bits;
} reg_cpu_ctrl_t;

/**
* @brief
* @details 
* @see ICCPMR_CPUn (0x0004)
*/
typedef union _reg_priority_mask_t {
    uint32_t all;
    struct {
        uint32_t mask:8;    //< [0:7]
        uint32_t rsvd:24;   //< [31:8]
    } bits;
} reg_priority_mask_t;

/**
* @brief
* @details 
* @see ICCBPR_CPUn (0x0008)
*/
typedef union _reg_binary_point_t {
    uint32_t all;
    struct {
        uint32_t bin_point:3;   //< [0:2]
        uint32_t rsvd:29;       //< [31:3]
    } bits;
} reg_binary_point_t;

/**
* @brief
* @details 
* @see ICCIAR_CPUn (0x000C, 0x400C, 0x800C, 0xC00C)
*/
typedef union _reg_intr_ack_t {
    uint32_t all;
    struct {
        uint32_t ack_id:10; //< [9:0] - The interrupt ID
        uint32_t cpu_id:3;  //< [12:10]
        uint32_t rsvd:19;   //< [31:13]
    } bits;
} reg_intr_ack_t;

/**
* @brief
* @details 
* @see (0x0010, 0x4010, 0x8010, 0xC010) 
*/
typedef union _reg_end_of_intr_t {
    uint32_t all;
    struct {
        uint32_t eo_id:10;  //< [9:0]
        uint32_t cpu_id:3;  //< [12:10]
        uint32_t rsvd:19;   //< [31:13]
    } bits;
} reg_end_of_intr_t;

/**
* @brief
* @details 
* @see (0x0014, 0x4014, 0x8014, 0xC014)
*/
typedef union _reg_run_priority_t {
    uint32_t all;
    struct {
        uint32_t priority:8;    //< [7:0]
        uint32_t rsvd:24;       //< [31:8]
    } bits;
} reg_run_priority_t;

/**
* @brief
* @details 
* @see (0x0018, 0x4018, 0x8018, 0xC018)
*/
typedef union _reg_highest_pend_intr_t {
    uint32_t all;
    struct {
        uint32_t pend_id:10;    //< [9:0]
        uint32_t cpu_id:3;      //< [12:10]
        uint32_t rsvd:19;       //< [31:13]
    } bits;
} reg_pend_intr_t;

/**
* @brief  
* @details 
* @see ICCABPR (0x001C, 0x401C, 0x801C, 0xC01C)
*/
typedef union _reg_iccabpr_t {
    uint32_t all;
    struct {
        uint32_t bin_pt:3;  //< [2:0]
        uint32_t rsvd:29;   //< [31:3]
    } bits;
} reg_iccabpr_t; //< ##### T.B.D - Need to rename ######

/**
* @brief Integration Test Logic
* @details 
* @see INTEG_EN_C_CPUn (0x0040, 0x0040, 0x0040, 0x0040)
*/
typedef union _reg_integ_en_c_t {
    uint32_t all;
    struct {
        uint32_t integ_en_c:1;  //< [0]
        uint32_t rsvd:31;       //< [31:1]
    } bits;
} reg_integ_en_c_t; //< ##### T.B.D - Need to rename ######

/**
* @brief Interrupt Output Logic
* @details 
* @see INTERRUPT_OUT_CPUn (0x0044, 0x4044, 0x8044, 0xC044) 
*/
typedef union _reg_intr_out_t {
    uint32_t all;
    struct {
        uint32_t set_nirq_c:1;  //< [0]
        uint32_t set_nfiq_c:1;  //< [1]
        uint32_t rsvd:30;       //< [31:2]
    } bits;
} reg_intr_out_t; //< ##### T.B.D - Need to rename ######

/**
* @brief GIC Identification Number
* @details 
* @see ICCIIDR (0x00FC) 
*/
typedef union _reg_icciidr_t {
    uint32_t id;    //< [RO] GIC ID
} reg_icciidr_t; //< ##### T.B.D - Need to rename ######

/* ---------------------------------------------------------------------------
   - GIC Distributor Register Map
 --------------------------------------------------------------------------- */
/**
* @brief Distributor control register
* @details
* @see ICDDCR (0x1049_0000) 
*/
typedef union _reg_dist_ctrl_t {
    uint32_t all;
    struct {
        uint32_t enable:1;  //< [0]
        uint32_t rsvd:31;   //< [31:1]
    } bits;
} reg_dist_ctrl_t;

/**
* @brief Interrupt controller type register
* @details
* @see ICDICTR (0x0004)
*/
typedef union _reg_ctrl_type_t {
    uint32_t all;
    struct {
        uint32_t line_num:5;        //< [4:0, RO]
        uint32_t cpu_num:3;         //< [7:5, RO]
        uint32_t rsvd0:2;           //< [9:8]
        uint32_t security_ext:1;    //< [10]
        uint32_t lock_spi:5;        //< [15:11]
        uint32_t rsvd1:16;          //< [31:16]
    } bits;
} reg_ctrl_type_t;

/**
* @brief 
* @details 
* @see  ICDIIDR (0x0008)
*/
typedef union _reg_icdiidr_t {
    uint32_t all;
    struct {
        uint32_t impl:12;   //< [11:0, RO]
        uint32_t rev:12;    //< [23:12, RO]
        uint32_t rsvd:8;    //< [31:24]
    } bits;
} reg_icdiidr_t; //< ##### T.B.D - Need to rename ######

/**
* @brief 
* @details 
* @see ICDISR (0x0080 ~ 008C, 0x4080, 0x8080, 0xC080)
*/
typedef union _reg_icdisr_t {
    uint32_t secur_stat; //< Security status bits
} reg_icdisr_t; //< ##### T.B.D - Need to rename ######

/**
* @brief 
* @details 
* @see ICDISER (0x0100 ~ 0110, 0x4100, 0x8100, 0xC100)
*/
typedef union _reg_icdiser_t {
    uint32_t enable;    //< Set enable bits
} reg_icdiser_t; //< ##### T.B.D - Need to rename ######

/**
* @brief 
* @details 
* @see ICDICER (0x0180 ~ 0190, 0x4180, 0x8180, 0xC180)
*/
typedef union _reg_icdicer_t {
    uint32_t enable[5];    //< Clear enable bits
} reg_icdicer_t; //< ##### T.B.D - Need to rename ######

/**
* @brief 
* @details 
* @see ICDISPR (0x0200 ~ 0210, 0x4200, 0x8200, 0xC200)
*/
typedef union _reg_icdispr_t {
    uint32_t set_pend;  //< Set pending bits
} reg_icdispr_t; //< ##### T.B.D - Need to rename ######

/**
* @brief 
* @details 
* @see ICDICPR (0x0280 ~ 0290, 0x4280, 0x8280, 0xC280)
*/
typedef union _reg_icdicpr_t {
    uint32_t clr_pend;  //< Clear pending bits
} reg_icdicpr_t; //< ##### T.B.D - Need to rename ######

/**
* @brief 
* @details 
* @see ICDABR (0x0300 ~ 0310, 0x4300, 0x8300, 0xC300)
*/
typedef union _reg_icdabr_t {
    uint32_t active;    //< Active bits
} reg_icdabr_t; //< ##### T.B.D - Need to rename ######

/**
* @brief
* @details
* @see ICDIPR (0x0400 ~ 049C, 0x4400, 0x8400, 0xC400)
*/
typedef union _reg_icdipr_t {
    uint8_t priority;
} reg_icdipr_t; //< ##### T.B.D - Need to rename ######

/**
* @brief 
* @details 
* @see ICDIPTR (0x0800 ~ 089C, 0x4800, 0x8800, 0xC800)
*/
typedef union _reg_icdiptr_t {
    uint8_t target;
} reg_icdiptr_t; //< ##### T.B.D - Need to rename ######

/**
* @brief 
* @details 
* @see ICDICFR (0x0C00 ~ 0C24, 0x4C00, 0x8C00, 0xCC00)
*/
typedef union _reg_icdicfr_t {
    uint32_t all;
    struct {
        uint32_t field0:2;   //< [1:0]
        uint32_t field1:2;   //< [3:2]
        uint32_t field2:2;   //< [5:4]
        uint32_t field3:2;   //< [7:6]
        uint32_t field4:2;   //< [9:8]
        uint32_t field5:2;   //< [11:10]
        uint32_t field6:2;   //< [13:12]
        uint32_t field7:2;   //< [15:14]
        uint32_t field8:2;   //< [17:16]
        uint32_t field9:2;   //< [19:18]
        uint32_t field10:2;  //< [21:20]
        uint32_t field11:2;  //< [23:22]
        uint32_t field12:2;  //< [25:24]
        uint32_t field13:2;  //< [27:26]
        uint32_t field14:2;  //< [29:28]
        uint32_t field15:2;  //< [31:30]
    } bits;
} reg_icdicfr_t; //< ##### T.B.D - Need to rename ######

/**
* @brief
* @details 
* @see PPI_STATUS (0x0D00, 0x4D00, 0x8D00, 0xCD00)
*/
typedef union _reg_ppi_stat_t {
    uint32_t all;
    struct {
        uint32_t ppi_stat:16;   //< [15:0, RO] - PPI status
        uint32_t rsvd:16;       //< [31:16]
    } bits;
} reg_ppi_stat_t; //< ##### T.B.D - Need to rename ######

/**
* @brief
* @details 
* @see SPI_STATUS (0x0D04, 0x0D08, 0x0D0C, 0x0D10)
*/
typedef union _reg_spi_stat_t {
    uint32_t spi_stat;  //< [RO] SPI status
} reg_spi_stat_t; //< ##### T.B.D - Need to rename ######

/** 
* @brief 
* @details 
* @see ICDSGIR (0x0F00)
*/
typedef union _reg_icdsgir_t {
    uint32_t all;
    struct {
        uint32_t sgintid:4;             //< [3:0]
        uint32_t rsvd0:11;              //< [14:4]
        uint32_t satt:1;                //< [15]
        uint32_t cpu_target_list:8;     //< [23:16]
        uint32_t target_list_filter:2;  //< [25:24]
        uint32_t rsvd1:6;               //< [31:26]
    } bits;
} reg_icdsgir_t; //< ##### T.B.D - Need to rename ######

/* ---------------------------------------------------------------------------
   - GIC CPU I/F Registers
 --------------------------------------------------------------------------- */
/**
* @brief [GIC CPU I/F] Block Control Registers
* @details 
* @see 
*/
typedef struct _regs_gic_cpu_t {
    reg_cpu_ctrl_t        cpu_ctrl;           //< ICCICR_CPUn
    reg_priority_mask_t   priority_mask;      //< ICCPMR_CPUn
    reg_binary_point_t    binary_point;       //< ICCBPR_CPUn
    reg_intr_ack_t        intr_ack;           //< ICCIAR_CPUn
    reg_end_of_intr_t     end_of_intr;        //< ICCEOIR_CPUn
    reg_run_priority_t    run_priority;       //< ICCRPR_CPUn
    reg_pend_intr_t       pend_intr;          //< ICCHPIR_CPUn
    reg_iccabpr_t         iccabpr;
} regs_gic_cpu_t;

/**
* @brief [GIC CPU I/F] Interrupt Output Logic
* @details
* @see
*/
typedef struct _regs_intr_out_t {
    reg_intr_out_t      cpu;
    reg_integ_en_c_t    tst;    //< Use it to modify the status of the nfiq_c<n> and nirq_c<n> output signals.
} regs_intr_out_t; //< ##### T.B.D - Need to rename #####

/**
* @brief [GIC CPU I/F] GIC ID Number
* @details
* @see
*/
typedef struct _regs_icciidr_t {    
    reg_icciidr_t    icciidr;
} regs_icciidr_t; //< ##### T.B.D - Need to rename #####

/* ---------------------------------------------------------------------------
   - GIC Distributor Registers
 --------------------------------------------------------------------------- */
/**
* @brief [GIC Distributor] Block Control Registers
* @details
* @see 
*/
typedef struct _regs_gic_dist_t {
    reg_dist_ctrl_t    dist_ctrl;
    reg_ctrl_type_t    ctrl_type;
} regs_gic_dist_t;

/**
* @brief
* @details
* @see 
*/
typedef struct _regs_icdiidr_t {
    reg_icdiidr_t    icdiidr;
} regs_icdiidr_t; //< ##### T.B.D - Need to rename #####

/**
* @brief
* @details
* @see 
*/
typedef struct _regs_secur_stat_t {
    reg_icdisr_t     icdisr;
} regs_secur_stat_t;

/**
* @brief
* @details
* @see 
*/
typedef struct _regs_set_en_t {
    reg_icdiser_t    icdiser[5];
} regs_set_en_t;

/**
* @brief
* @details
* @see 
*/
typedef struct _regs_clear_en_t {
    reg_icdicer_t    icdicer;
} regs_clear_en_t;

/**
* @brief
* @details
* @see 
*/
typedef struct _regs_icdispr_t {
    reg_icdispr_t    icdispr;
} regs_icdispr_t; //< ##### T.B.D - Need to rename #####

/**
* @brief
* @details
* @see 
*/
typedef struct _regs_icdicpr_t {
    reg_icdicpr_t    icdicpr;
} regs_icdicpr_t; //< ##### T.B.D - Need to rename #####

/**
* @brief
* @details
* @see 
*/
typedef struct _regs_icdabr_t {
    reg_icdabr_t     icdabr;
} regs_icdabr_t; //< ##### T.B.D - Need to rename #####

/**
* @brief
* @details
* @see 
*/
typedef struct _regs_icdipr_t {
    reg_icdipr_t     icdipr[160];
} regs_icdipr_t; //< ##### T.B.D - Need to rename #####

/**
* @brief
* @details
* @see 
*/
typedef struct _regs_icdiptr_t {    
    reg_icdiptr_t    icdiptr[28];
} regs_icdiptr_t; //< ##### T.B.D - Need to rename #####

/**
* @brief
* @details
* @see 
*/
typedef struct _regs_icdicfr_t {
    reg_icdicfr_t    icdicfr[10];
} regs_icdicfr_t; //< ##### T.B.D - Need to rename #####

/**
* @brief
* @details
* @see 
*/
typedef struct _regs_intr_stat_t {
    reg_ppi_stat_t    ppi_stat;
    reg_spi_stat_t    spi_stat[4];
} regs_intr_stat_t; //< ##### T.B.D - Need to rename #####

/**
* @brief
* @details
* @see 
*/
typedef struct _regs_icdsgir_t {
    reg_icdsgir_t     icdsgir;
} regs_icdsgir_t; //< ##### T.B.D - Need to rename #####

/* ---------------------------------------------------------------------------
   - GIC Configuration
 --------------------------------------------------------------------------- */
/**
* @brief [GIC] Configure CPU I/F
* @details
* @see
*/
typedef struct _config_dist_t {
    uint32_t    prio;       //< Priority
    uint32_t    target;     //< CPU target
    uint32_t    set_en_f;   //< Field offset - a bit field for each INTR
    uint32_t    clr_en_f;   //< Field offset - a bit field for each INTR
    uint32_t    trig_f;     //< Field offset - a 2-bit field for each INTR
} config_dist_t;

/**
* @brief [GIC] Configure distributor
* @details
* @see
*/
typedef struct _config_cpu_if_t {
    uint32_t   val; //<
} config_cpu_if_t;


/*****************************************************************************
 * Function prototypes
 *****************************************************************************/
/**
* @brief
* @param[in]
* @param[out]
* @return void
 */

#endif /* _INTERRUPT_H_ */
