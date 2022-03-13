/**
* @file
* @author
* @date
* @brief
* @see
*/

#ifndef _EXYNOS_REG_ADDR_H_
#define _EXYNOS_REG_ADDR_H_

/*****************************************************************************
 * Header files
 *****************************************************************************/
/*****************************************************************************
 * Macro definitions
 *****************************************************************************/
#define rULCON0		(*((volatile unsigned int   *)0x13800000))	//< UART Channel 0 Line Control Register 0x00
#define rUCON0		(*((volatile unsigned int   *)0x13800004))	//< UART Channel 0 Control Register 0x00
#define rUFCON0		(*((volatile unsigned int   *)0x13800008))	//< UART Channel 0 FIFO Control Register 0x0
#define rUMCON0		(*((volatile unsigned int   *)0x1380000C))	//< UART Channel 0 Modem Control Register 0x0
#define rUTRSTAT0	(*((volatile unsigned int   *)0x13800010))	//< UART Channel 0 Tx/Rx Status Register 0x6
#define rUERSTAT0	(*((volatile unsigned int   *)0x13800014))	//< UART Channel 0 Rx Error Status Register 0x0
#define rUFSTAT0	(*((volatile unsigned int   *)0x13800018))	//< UART Channel 0 FIFO Status Register 0x00
#define rUMSTAT0	(*((volatile unsigned int   *)0x1380001C))	//< UART Channel 0 Modem Status Register 0x0
#define rUTXH0		(*((volatile unsigned char  *)0x13800020))	//< UART Channel 0 Transmit Buffer Register -
#define rURXH0		(*((volatile unsigned char  *)0x13800024))	//< UART Channel 0 Receive Buffer Register 0x00
#define rUBRDIV0	(*((volatile unsigned int   *)0x13800028))	//< UART Channel 0 Baud Rate Divisior Register 0x0000
#define rUDIVSLOT0	(*((volatile unsigned int   *)0x1380002C))	//< UART Channel 0 Dividing Slot Register 0x0000
#define rUINTP0		(*((volatile unsigned int   *)0x13800030))	//< UART Channel 0 Interrupt Pending Register 0x0
#define rUINTSP0	(*((volatile unsigned int   *)0x13800034))	//< UART Channel 0 Interrupt Source Pending Register 0x0
#define rUINTM0		(*((volatile unsigned int   *)0x13800038))	//< UART Channel 0 Interrupt Mask Register 0x0

#define rULCON1		(*((volatile unsigned int   *)0x13810000))	//< UART Channel 1 Line Control Register 0x00
#define rUCON1		(*((volatile unsigned int   *)0x13810004))	//< UART Channel 1 Control Register 0x00
#define rUFCON1		(*((volatile unsigned int   *)0x13810008))	//< UART Channel 1 FIFO Control Register 0x0
#define rUMCON1		(*((volatile unsigned int   *)0x1381000C))	//< UART Channel 1 Modem Control Register 0x0
#define rUTRSTAT1	(*((volatile unsigned int   *)0x13810010))	//< UART Channel 1 Tx/Rx Status Register 0x6
#define rUERSTAT1	(*((volatile unsigned int   *)0x13810014))	//< UART Channel 1 Rx Error Status Register 0x0
#define rUFSTAT1	(*((volatile unsigned int   *)0x13810018))	//< UART Channel 1 FIFO Status Register 0x00
#define rUMSTAT1	(*((volatile unsigned int   *)0x1381001C))	//< UART Channel 1 Modem Status Register 0x0
#define rUTXH1		(*((volatile unsigned char  *)0x13810020))	//< UART Channel 1 Transmit Buffer Register -
#define rURXH1		(*((volatile unsigned char  *)0x13810024))	//< UART Channel 1 Receive Buffer Register 0x00
#define rUBRDIV1	(*((volatile unsigned int   *)0x13810028))	//< UART Channel 1 Baud Rate Divisior Register 0x0000
#define rUDIVSLOT1	(*((volatile unsigned int   *)0x1381002C))	//< UART Channel 1 Dividing Slot Register 0x0000
#define rUINTP1		(*((volatile unsigned int   *)0x13810030))	//< UART Channel 1 Interrupt Pending Register 0x0
#define rUINTSP1	(*((volatile unsigned int   *)0x13810034))	//< UART Channel 1 Interrupt Source Pending Register 0x0
#define rUINTM1		(*((volatile unsigned int   *)0x13810038))	//< UART Channel 1 Interrupt Mask Register 0x0

#define rULCON2		(*((volatile unsigned int   *)0x13820000))	//< UART Channel 2 Line Control Register 0x00
#define rUCON2		(*((volatile unsigned int   *)0x13820004))	//< UART Channel 2 Control Register 0x00
#define rUFCON2		(*((volatile unsigned int   *)0x13820008))	//< UART Channel 2 FIFO Control Register 0x0
#define rUMCON2		(*((volatile unsigned int   *)0x1382000C))	//< UART Channel 2 Modem Control Register 0x0
#define rUTRSTAT2	(*((volatile unsigned int   *)0x13820010))	//< UART Channel 2 Tx/Rx Status Register 0x6
#define rUERSTAT2	(*((volatile unsigned int   *)0x13820014))	//< UART Channel 2 Rx Error Status Register 0x0
#define rUFSTAT2	(*((volatile unsigned int   *)0x13820018))	//< UART Channel 2 FIFO Status Register 0x00
#define rUMSTAT2	(*((volatile unsigned int   *)0x1382001C))	//< UART Channel 2 Modem Status Register 0x0
#define rUTXH2		(*((volatile unsigned char  *)0x13820020))	//< UART Channel 2 Transmit Buffer Register -
#define rURXH2		(*((volatile unsigned char  *)0x13820024))	//< UART Channel 2 Receive Buffer Register 0x00
#define rUBRDIV2	(*((volatile unsigned int   *)0x13820028))	//< UART Channel 2 Baud Rate Divisior Register 0x0000
#define rUDIVSLOT2	(*((volatile unsigned int   *)0x1382002C))	//< UART Channel 2 Dividing Slot Register 0x0000
#define rUINTP2		(*((volatile unsigned int   *)0x13820030))	//< UART Channel 2 Interrupt Pending Register 0x0
#define rUINTSP2	(*((volatile unsigned int   *)0x13820034))	//< UART Channel 2 Interrupt Source Pending Register 0x0
#define rUINTM2		(*((volatile unsigned int   *)0x13820038))	//< UART Channel 2 Interrupt Mask Register 0x0

/*****************************************************************************
 * Enumerations
 *****************************************************************************/

#endif /* _EXYNOS_REG_ADDR_H_ */