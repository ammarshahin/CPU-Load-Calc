/*
 * BCM.h
 *
 * Created: 11/17/2019 7:27:33 PM
 *  Author: Ammar Shahin
 */ 


#ifndef BCM_H_
#define BCM_H_

/************************************************************************/
/*				              Files Includes                            */
/************************************************************************/
#include "Typedefs.h"

/************************************************************************/
/*                               CONSTANTS                               */
/************************************************************************/

#define BCM_ID				'A'
#define MAX_DATA_SEND		1000

/************************************************************************/
/*                          PRIMITIVE TYPES                             */
/************************************************************************/
typedef void (*ptrBCMFunCallBk_t)(void);

/************************************************************************/
/*                               ENUMS                                  */
/************************************************************************/

/* error Enum */
typedef enum{
	OK_BCM						,	
	INVALID_ARGUMENT			,
	BUFFER_UNLOCKED				,
	BUFFER_LOCKED				,
	NULLPTR						,
	INVALID_COM_TYPE			,
	INVALID_DATA_LENGTH			,
	INVALID_CHECK_SUM			,
	INVALID_POINTER_TO_BUFFER	,
	INVALID_POINTER_TO_FUNCTION ,
	INVALID_ID                  ,
}EnmBCMError_t;


typedef enum{
	UART  ,
	SPI   ,
	I2C   ,
}EnumBCM_ComPeriph_type;


typedef enum{
	SEND_MODE         ,
	RECEIVE_MODE      ,
	SEND_RECEIVE_MODE ,
}EnumBCM_ComMode_type;

/************************************************************************/
/*                       FUNCTION PROTOTYPES                            */
/************************************************************************/
/**
 * Function : BCM_Init
 * Description: this function is to initialize the BCM
 * @param ConfigPtr pointer to the Configuration Structure which include:
 * 								1- BCM_ID: the ID of the Communication
 *								2- BCM_Rx_or_Tx the Mode of communication [Sending or receiving]
 *								3- BCMPtr_Rx_FuncCallBk: A pointer to the end function to be called when receiving/Sending Finish
 * @return Status: of the initialization according to the Error handling macros 
 **/
EnmBCMError_t BCM_Init( ptrBCMFunCallBk_t CallBkFun );

/**
 * Function : BCM_Rx_SetupRxBuffer
 * Description: This Function is used to setup the Rx buffer
 * @param Buffer : A pointer to the Buffer in the App Layer
 * @param Size : the Size of the Buffer in the App Layer
 * @return Status: of the Setup according to the Error handling
 **/
EnmBCMError_t BCM_Rx_SetupBuffer(uint8 *Buffer,uint16 Size);

/**
 * Function : BCM_RxDispatcher
 * Description: This Function is used to handling the receiving in run time
 * @return Status: of the Setup according to the Error handling
 **/
EnmBCMError_t BCM_RxDispatcher(void);

/**
 * Function : BCM_Rx_Callback
 * Description: This Function will called in when ISR fires By the Call back Mechnism
 * @return Void
 **/
void BCM_Rx_Callback(void);

/**
 * Function : BCM_Tx_Callback
 * Description: This Function will called in when ISR fires By the Call back Mechanism
 * @return Void
 **/
void BCM_Tx_Callback(void);

/**
 * Function : BCM_TxSend
 * Description: This Function is used to Send a Byte of data By the Communication Peripheral
 * @return Status: of the Function according to the Error handling
 **/
EnmBCMError_t BCM_TxSend(uint8 data);

/**
 * Function : BCM_TxDispatcher
 * Description: This Function is used to handle the Sending in the run time
 * @return Void
 **/
void BCM_TxDispatcher(void);

/**
 * Function : BCM_RxDispatch
 * Description: This Function is used to construct the frame by initializing every element in the structure used
 * Then we lock buffer to make sure that no INITIAL_VALUE_ONE corrupts the data which will be sent
 * @return Status: of the Function according to the Error handling
 **/
EnmBCMError_t BCM_Tx_SetupBuffer(uint8 *Buffer,uint16 Size);

/**
 * Function : BCM_DeInit
 * Description: This Function will called to return the BCM to it's Default state
 * @return Status: of the Function according to the Error handling
 **/
EnmBCMError_t BCM_DeInit(void);
#endif /* BCM_H_ */