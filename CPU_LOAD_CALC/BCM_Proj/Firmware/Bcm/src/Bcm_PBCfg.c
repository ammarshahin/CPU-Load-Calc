/*
 * Bcm_PBCfg.c
 *
 * Created: 11/17/2019 7:30:34 PM
 *  Author: Ammar Shahin
 */ 

/************************************************************************/
/*				              Files Includes                            */
/************************************************************************/
#include "Bcm_PBCfg.h"
#include "BCM.h"

/************************************************************************/
/*				       GLOBAL Variable Definitions                      */
/************************************************************************/

/* Create an object of the BCM_Rx_Config_t Structure */
StrBCM_Cfg_type StrBCM_Cfg = {
	BCM_ID      ,
	SEND_MODE   ,
	NULL		,
	NULL		,
};
	
EnumBCM_ComPeriph_type Communication_type = UART;