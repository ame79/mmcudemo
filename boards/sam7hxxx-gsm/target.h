/** @file   target.h
    @author M. P. Hayes, UCECE
    @date   02 June 2007
    @brief 
*/
#ifndef TARGET_H
#define TARGET_H

#include "mat91lib.h"

/* CPU clocks  */
#define F_XTAL 18432000.0
#define CPU_PLL_MUL 125
#define CPU_PLL_DIV 24
#define CPU_USB_DIV 2
/* 96 MHz  */
#define F_PLL (F_XTAL / CPU_PLL_DIV * CPU_PLL_MUL)
/* 48 MHz  */
#define F_CPU (F_PLL / 2)


/* GSM modem  */
#define GSM_ONOFF_PIO PIO_DEFINE(PORT_A, 8)
#define GSM_PWRMON_PIO PIO_DEFINE(PORT_A, 9)
#define GSM_RESET_PIO PIO_DEFINE(PORT_A, 10)

#define GSM_DEBUG_PIO PIO_DEFINE(PORT_A, 11)

#endif /* TARGET_H  */
