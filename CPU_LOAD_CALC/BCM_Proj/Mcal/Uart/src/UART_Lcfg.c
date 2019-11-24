/*
 * UART_Lcfg.c
 * Description : This File is used to control the UART Peripheral in the MCAL layer
 * Created: 11/12/2019 2:04:16 PM
 *  Author: Ammar Shahin
 */ 

/************************************************************************/
/*                            Files Includes                            */
/************************************************************************/
#include "UART_Lcfg.h"
#include "UART.h"
#include "MCU_Frequency.h"

/* Baud rate values */
#define  BAUDRATE_9600 9600


/* the Parity options */
#define  DISABLED        0
#define  ENABLED_EVEN    1
#define  ENABLED_ODD     2

/* the Stop Bits options */
#define  SINGLE_STOPBIT     1
#define  DOUBLE_STOPBIT     2

/************************************************************************/
/*                     Linking Structures Definitions                    */
/************************************************************************/

/* UART Structure */
UART_CFG_S UART_Cfg_s = {
    BAUDRATE_9600,  /* BaudRate */
    DISABLED,       /* Enable_Receiver */
    ENABLED,       /* Enable_Transmitter */
	DISABLED,       /* Enable_Parity */
    SINGLE_STOPBIT, /* StopBits */
	ENABLED,       /* Interrupt_Receive */
	F_CPU,          /* MCU_Freq */
};