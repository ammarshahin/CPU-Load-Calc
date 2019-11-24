/*
 * UART_Lcfg.h
 *
 * Created: 11/12/2019 11:31:50 AM
 *  Author: Ammar Shahin
 */ 


#ifndef UART_LCFG_H_
#define UART_LCFG_H_

/************************************************************************/
/*                            Files Includes                            */
/************************************************************************/
#include "Typedefs.h"

/************************************************************************/
/*                               Macros                                 */
/************************************************************************/


/************************************************************************/
/*                          Linking Structure                            */
/************************************************************************/
typedef struct UART_CFG_S{
	uint32 BaudRate;
	uint8 Enable_Receiver;
	uint8 Enable_Transmitter;
	uint8 Enable_Parity;
	uint8 StopBits;
	uint8 Interrupt_Receive;
	uint32 MCU_Freq;
}UART_CFG_S;


/************************************************************************/
/*                       Extern Global variables                        */
/************************************************************************/
extern UART_CFG_S UART_Cfg_s;


#endif /* UART_LCFG_H_ */
