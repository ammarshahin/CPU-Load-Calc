/*
 * UART.h
 *
 * Created: 11/12/2019 11:35:13 AM
 *  Author: Ammar Shahin
 */ 


#ifndef UART_H_
#define UART_H_

/************************************************************************/
/*                            Files Includes                            */
/************************************************************************/
#include "Typedefs.h"
#include "UART_Lcfg.h"

/************************************************************************/
/*                               Macros                                 */
/************************************************************************/
/* Baud rate values */
#define  BAUDRATE_9600 9600

#define  DISABLED       0
#define  ENABLED        1

/* the Parity options */
#define  ENABLED_EVEN    1
#define  ENABLED_ODD     2

/* the Stop Bits options */
#define  SINGLE_STOPBIT     1
#define  DOUBLE_STOPBIT     2

typedef void (*ptrUARTFunCallBk_t)(void);
/************************************************************************/
/*                   UART Functions Prototypes                          */
/************************************************************************/
/**
 * Function : UART_Init
 * Description: this function is to initialize the UART 
 * @param cfg_s the Configuration Structure which include:
 * 								1- the baud rate of the UART
 *								2- the Enable Receiver state
 * 								3- the Enable Transmitter state
 * 								4- the Enable Parity state
 * 								5- the Enable 2StopBits state
 * 								6- the Enable Interrupt_Receive state
 *                              7- the MCU Frequency
 * @return the Status of the initialization [OK Or NOT_OK] 
 */
uint8 UART_Init();


/**
 * Function : UART_Send
 * Description: this function is to send a data(8 bits) by the UART 
 * @param data the symbol to be sent
 * @return the Status of the function [OK Or NOT_OK] 
 */
uint8 UART_Send(uint8 data);

/**
 * Function : UART_Receive
 * Description: this function is to Receive a data(8 bits) by the UART 
 * @return the Received data
 */
uint8 UART_Receive();

/**
 * Function : UART_Read
 * Description: this function is to Read a data(8 bits) by the UART 
 * @return the Received data
 */
uint8 UART_Read();
/**
 * Function : UART_Write_string
 * Description: this function is to Send a String(array of char) by the UART 
 * @param data the pointer to the string to be sent
 * @return the Status of the function [OK Or NOT_OK] 
 */
uint8 UART_SendString(uint8 *data);
/**
 * Function : UART_SendToTTL
 * Description: this function is to Send a String(array of char) by the UART to the TTL
 * @param Send_String the string to be sent
 * @return the Status of the function [OK Or NOT_OK] 
 */
uint8 UART_SendToTTL(uint32 Send_String);

/**
 * Function : UART_SetCallBack
 * Description: this function is to set the Call back of the UART ISR
 * @param Send_String the string to be sent
 * @return the Status of the function [OK Or NOT_OK] 
 */
void UART_SetCallBack(ptrUARTFunCallBk_t FunName); 
#endif /* UART_H_ */
