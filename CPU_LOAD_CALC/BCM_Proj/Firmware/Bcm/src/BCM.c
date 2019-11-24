/*
 * BCM.c
 *
 * Created: 11/17/2019 7:27:02 PM
 *  Author: Ammar Shahin
 */ 
/************************************************************************/
/*				              Files Includes                            */
/************************************************************************/
#include "BCM.h"
#include "Bcm_PBCfg.h"
#include "UART.h"


/************************************************************************/
/*                               LOCAL MACROS                           */
/************************************************************************/
#define SHIFT_FACTOR				8
#define ID_BYTE						0
#define INITIAL_VALUE_ZERO			0
#define INITIAL_VALUE_ONE			1

#define BCM_OVERHEAD		2
#define MAX_DATA_RECEIVED	(MAX_DATA_SEND+BCM_OVERHEAD)
/************************************************************************/
/*                         LOCAL Structures                            */
/************************************************************************/

typedef struct{
	uint8 *PtrFunc    ;
	uint16 BufferSize ;
	uint8  CheckSum    ;
}StrBCM_Buffer_type;

/************************************************************************/
/*							Local Enums                                 */
/************************************************************************/
typedef enum{
	ID_RECEIVE_STATE		 ,
	SIZE_RECEIVE_STATE		 ,
	DATA_RECEIVE_STATE		 ,
	CHECKSUM_RECEIVE_STATE   ,
}EnumBCM_RxState_type;

typedef enum{
	ID_SEND_STATE		 ,
	SIZE_SEND_STATE		 ,
	DATA_SEND_STATE		 ,
	CHECKSUM_SEND_STATE   ,
}EnumBCM_TxState_type;

typedef enum{
	RECEIVED	 ,
	NOT_RECEIVED ,
}EnumBCM_RxFlag_type;

typedef enum{
	SENT_DONE	 ,
	NOT_SENT	 ,
}EnumBCM_TxFlag_type;

typedef enum{
	FIRST_BYTE	  = 1,
	SECOND_BYTE   = 2,
}EnumBCM_SizeFlag_type;

typedef enum{
	UNLOCKED ,
	LOCKED   ,
}EnumBCM_Lock_type;

/************************************************************************/
/*                       GLOBAL STATIC VARIABLES                        */
/************************************************************************/
static volatile uint16 gBufferRxIndex = INITIAL_VALUE_ZERO;
static volatile uint16 gBufferTxIndex = INITIAL_VALUE_ZERO;

static volatile uint16 gBufferRxSize = INITIAL_VALUE_ZERO;

static volatile EnumBCM_Lock_type gEnumBcm_Rx_Lock;
static volatile EnumBCM_Lock_type gEnumBcm_Tx_Lock;

static volatile StrBCM_Buffer_type gStrBcmBuffer;

static volatile EnumBCM_RxState_type gEnumBcm_Rx_state = ID_RECEIVE_STATE;
static volatile EnumBCM_TxState_type gEnumBcm_Tx_state = ID_SEND_STATE;

static volatile EnumBCM_RxFlag_type gEnumBcm_Rx_Flag = NOT_RECEIVED;
static volatile EnumBCM_TxFlag_type gEnumBcm_Tx_Flag = NOT_SENT;

static volatile EnumBCM_SizeFlag_type gEnumBcm_SizeFlag = FIRST_BYTE;

/************************************************************************/
/*                           APIs IMPLEMENTATION                        */
/************************************************************************/
/**
 * Function : BCM_Init
 * Description: this function is to initialize the BCM
 * @param CallBkFun: A pointer to a function to be called when receiving/Sending Finish
 * @return Status: of the initialization according to the Error handling macros 
 **/

EnmBCMError_t BCM_Init(ptrBCMFunCallBk_t CallBkFun)
{
	EnmBCMError_t API_State = OK_BCM;
	StrBCM_Cfg.Bcm_ID = BCM_ID;
	gEnumBcm_Rx_Lock = UNLOCKED;
	gEnumBcm_Tx_Lock = UNLOCKED;

	/* The Call Back Setup */
	if( NULL != CallBkFun)
	{
		switch(StrBCM_Cfg.BCM_Rx_or_Tx)
		{
			case RECEIVE_MODE:
			StrBCM_Cfg.BCMPtr_Rx_FuncCallBk = CallBkFun;
			break;
			case SEND_MODE:
			StrBCM_Cfg.BCMPtr_Tx_FuncCallBk = CallBkFun;
			break;
			case SEND_RECEIVE_MODE:
			StrBCM_Cfg.BCMPtr_Rx_FuncCallBk = CallBkFun;
			StrBCM_Cfg.BCMPtr_Tx_FuncCallBk = CallBkFun;
			break;
			default:
			break;
		}
	}
	else
	{
		API_State = INVALID_POINTER_TO_FUNCTION;
	}
	
	switch(Communication_type)
	{
		case UART:
			/* UART Setup */
			UART_Init();
			UART_SetCallBack(BCM_Tx_Callback);
			break;
		case SPI:
			// N
			break;
		case I2C:
			// N
			break;
		default:
			break;
	}
	return API_State;
}


/**
 * Function : BCM_Rx_SetupRxBuffer
 * Description: This Function is used to setup the Rx buffer
 * @param Buffer : A pointer to the Buffer in the App Layer
 * @param Size : the Size of the Buffer in the App Layer
 * @return Status: of the Setup according to the Error handling
 **/
EnmBCMError_t BCM_Rx_SetupBuffer(uint8 *Buffer,uint16 Size)
{
	EnmBCMError_t API_State = OK_BCM;
	
	if( UNLOCKED == gEnumBcm_Rx_Lock)
	{
		if(NULL != Buffer)
		{
			gStrBcmBuffer.PtrFunc = Buffer;
			gStrBcmBuffer.BufferSize = Size;
			gStrBcmBuffer.CheckSum = INITIAL_VALUE_ZERO;
			gBufferRxIndex = INITIAL_VALUE_ZERO;
			gEnumBcm_Rx_state = ID_RECEIVE_STATE;
			gEnumBcm_SizeFlag = FIRST_BYTE;
		}
		else
		{
			API_State = INVALID_POINTER_TO_BUFFER;
		}
	}
	else
	{
		API_State = BUFFER_LOCKED;
	}
	return API_State;
}


/**
 * Function : BCM_RxDispatcher
 * Description: This Function is used to handling the receiving in run time
 * @return Status: of the Setup according to the Error handling
 **/
EnmBCMError_t BCM_RxDispatcher(void)
{
	EnmBCMError_t API_State = OK_BCM;
	if( LOCKED == gEnumBcm_Rx_Lock )
	{
		if( RECEIVED == gEnumBcm_Rx_Flag )
		{
			gEnumBcm_Rx_Flag = NOT_RECEIVED;
			switch( gEnumBcm_Rx_state )
			{
			case ID_RECEIVE_STATE:
					if( gStrBcmBuffer.PtrFunc[ID_BYTE] == StrBCM_Cfg.Bcm_ID )
					{
						gBufferRxIndex++;
						gEnumBcm_Rx_state = SIZE_RECEIVE_STATE;
					}
					else
					{
						API_State = INVALID_ID;
						BCM_DeInit();
					}
					break;
			case SIZE_RECEIVE_STATE:
					if( FIRST_BYTE == gEnumBcm_SizeFlag )
					{
						gBufferRxSize = gStrBcmBuffer.PtrFunc[FIRST_BYTE];
						gBufferRxIndex++;
						gEnumBcm_SizeFlag = SECOND_BYTE;	
					}
					else if( SECOND_BYTE == gEnumBcm_SizeFlag )
					{
						gBufferRxSize |= ( gStrBcmBuffer.PtrFunc[SECOND_BYTE] << SHIFT_FACTOR );
						gBufferRxIndex++;
						
						if( gBufferRxSize <= gStrBcmBuffer.BufferSize )
						{
							gEnumBcm_Rx_state = DATA_RECEIVE_STATE;
						}
						else
						{
							API_State = INVALID_DATA_LENGTH;
							BCM_DeInit();	
						}
					}
					else
					{
						// Do Nothing
					}
				break;
			case DATA_RECEIVE_STATE:				
					gStrBcmBuffer.CheckSum += gStrBcmBuffer.PtrFunc[gBufferRxIndex];
					gBufferRxIndex++;
					
					if( (gBufferRxIndex + BCM_OVERHEAD) == gStrBcmBuffer.BufferSize)
					{
						gEnumBcm_Rx_state = CHECKSUM_RECEIVE_STATE;
					}
					else
					{
						// Do Nothing
					}
				break;
			case CHECKSUM_RECEIVE_STATE :
					if( gStrBcmBuffer.CheckSum == gStrBcmBuffer.PtrFunc[gBufferRxIndex] )
					{
						StrBCM_Cfg.BCMPtr_Rx_FuncCallBk();
						gEnumBcm_Rx_Lock = UNLOCKED;
					}
					else
					{
						API_State = INVALID_CHECK_SUM;
						BCM_DeInit();	
					}
				break;
			}
		}
		else
		{
			// Do Nothing
		}
	}
	else
	{
		// Do Nothing
	}
	return API_State;
}

/**
 * Function : BCM_DeInit
 * Description: This Function will called to return the BCM to it's Default state
 * @return Status: of the Fu/nction according to the Error handling
 **/
EnmBCMError_t BCM_DeInit(void)
{
	EnmBCMError_t API_State = OK;
	gBufferRxIndex = INITIAL_VALUE_ZERO;
	gBufferRxSize = INITIAL_VALUE_ZERO;
	gEnumBcm_Rx_Lock = UNLOCKED;
	gEnumBcm_Tx_Lock = UNLOCKED;
	gStrBcmBuffer.BufferSize = INITIAL_VALUE_ZERO;
	gStrBcmBuffer.PtrFunc = NULL;
	gStrBcmBuffer.CheckSum = INITIAL_VALUE_ZERO;
	gEnumBcm_Rx_state = ID_RECEIVE_STATE;
	gEnumBcm_Rx_Flag = NOT_RECEIVED;
	gEnumBcm_Tx_Flag = NOT_SENT;
	gEnumBcm_SizeFlag = FIRST_BYTE;

	switch(Communication_type)
	{
		case UART:
		//UART_DeInit();
		break;
		case SPI:
		// N
		break;
		case I2C:
		// N
		break;
		default:
		break;
	}
	return API_State;
}

/**
 * Function : BCM_Tx_Callback
 * Description: This Function will called in when ISR fires By the Call back Mechanism
 * @return Void
 **/
void BCM_Tx_Callback(void)
{
	gEnumBcm_Tx_Flag = SENT_DONE;
}

/**
 * Function : BCM_Rx_Callback
 * Description: This Function will called in when ISR fires By the Call back Mechanism
 * @return Void
 **/
void BCM_Rx_Callback(void)
{
	gStrBcmBuffer.PtrFunc[gBufferRxIndex] = UART_Read();
	gEnumBcm_Rx_Flag = RECEIVED;
	gEnumBcm_Rx_Lock = LOCKED;
}


/**
 * Function : BCM_RxDispatch
 * Description: This Function is used to construct the frame by initializing every element in the structure used
 * Then we lock buffer to make sure that no INITIAL_VALUE_ONE corrupts the data which will be sent
 * @return Status: of the Function according to the Error handling
 **/
EnmBCMError_t BCM_Tx_SetupBuffer(uint8 *Buffer,uint16 Size)
{
	EnmBCMError_t API_State = OK_BCM;
	
	if( UNLOCKED == gEnumBcm_Tx_Lock)
	{
		if ( NULL != Buffer )
		{
			if(Size <= MAX_DATA_SEND)
			{
				gStrBcmBuffer.CheckSum   = INITIAL_VALUE_ZERO;
				gStrBcmBuffer.BufferSize = Size;
				gStrBcmBuffer.PtrFunc  = Buffer;
				gEnumBcm_Tx_Lock			 = LOCKED;
				gEnumBcm_Tx_state			 = ID_SEND_STATE;
				gBufferTxIndex			 = INITIAL_VALUE_ZERO;
				gEnumBcm_Tx_Flag			 = SENT_DONE;
				gEnumBcm_SizeFlag			 = FIRST_BYTE;
			}
			else
			{
				API_State = INVALID_DATA_LENGTH;
			}
		}
		else
		{
			API_State = INVALID_POINTER_TO_BUFFER;
		}
	}
	else
	{
		API_State = BUFFER_LOCKED;
	}
	return API_State;
}


/**
 * Function : BCM_TxDispatcher
 * Description: This Function is used to handle the Sending in the run time
 * @return Void
 **/
void BCM_TxDispatcher(void)
{
	if ( LOCKED == gEnumBcm_Tx_Lock )
	{
		if( SENT_DONE == gEnumBcm_Tx_Flag)
		{
			gEnumBcm_Tx_Flag = NOT_SENT;
			switch(gEnumBcm_Tx_state)
			{
				case ID_SEND_STATE:
					BCM_TxSend(BCM_ID);
					gEnumBcm_Tx_state = SIZE_SEND_STATE;
					break;
				case SIZE_SEND_STATE:
					if( gEnumBcm_SizeFlag == FIRST_BYTE )
					{
						BCM_TxSend( (uint8) gStrBcmBuffer.BufferSize);
						gEnumBcm_SizeFlag = SECOND_BYTE;
					}
					else if( gEnumBcm_SizeFlag == SECOND_BYTE )
					{
						BCM_TxSend( (uint8)(gStrBcmBuffer.BufferSize >> SHIFT_FACTOR) );
						gEnumBcm_SizeFlag = FIRST_BYTE;
						gEnumBcm_Tx_state = DATA_SEND_STATE;
					}
					else
					{
						// Do Nothing
					}
					break;
				case DATA_SEND_STATE:
					if ( gBufferTxIndex < gStrBcmBuffer.BufferSize)
					{
						BCM_TxSend(gStrBcmBuffer.PtrFunc[gBufferTxIndex]);
						gStrBcmBuffer.CheckSum += gStrBcmBuffer.PtrFunc[gBufferTxIndex];
						gBufferTxIndex++;
					}
					
					if( gBufferTxIndex == gStrBcmBuffer.BufferSize )
					{
						gEnumBcm_Tx_state = CHECKSUM_SEND_STATE;
					}
					
					break;
				case CHECKSUM_SEND_STATE:
					BCM_TxSend(gStrBcmBuffer.CheckSum);
					StrBCM_Cfg.BCMPtr_Tx_FuncCallBk();
					gEnumBcm_Tx_Lock = UNLOCKED;
					BCM_DeInit();
					break;
				default:
					break;
			}
		}
		else
		{
			// Don Nothing
		}
	}
	else
	{
		// Do Nothing
	}
}


/**
 * Function : BCM_TxSend
 * Description: This Function is used to Send a Byte of data By the Communication Peripheral
 * @return Status: of the Function according to the Error handling
 **/
EnmBCMError_t BCM_TxSend(uint8 data)
{
	EnmBCMError_t API_State = OK_BCM;
	
	switch(Communication_type)
	{
		case UART:
		/* UART Send */
		UART_Send(data);
		break;
		case SPI:
		// N
		break;
		case I2C:
		// N
		break;
		default:
		API_State = INVALID_ARGUMENT;
		break;
	}
	return API_State;
}