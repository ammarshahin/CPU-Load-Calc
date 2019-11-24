/*
 * Bcm_PBCfg.h
 *
 * Created: 11/17/2019 7:30:10 PM
 *  Author: Ammar Shahin
 */ 


#ifndef BCM_PBCFG_H_
#define BCM_PBCFG_H_


/************************************************************************/
/*                               INCLUDES                               */
/************************************************************************/
#include "Typedefs.h"
#include "BCM.h"

/************************************************************************/
/*                       STRUCTS AND UNIONS                              */
/************************************************************************/
typedef struct{
	uint8			  Bcm_ID;
	EnumBCM_ComMode_type	  BCM_Rx_or_Tx;
	ptrBCMFunCallBk_t BCMPtr_Rx_FuncCallBk;
	ptrBCMFunCallBk_t BCMPtr_Tx_FuncCallBk;
}StrBCM_Cfg_type;

/************************************************************************/
/*                    Extern Global Variables                           */
/************************************************************************/
extern StrBCM_Cfg_type StrBCM_Cfg;
extern EnumBCM_ComPeriph_type Communication_type;

#endif /* BCM_PBCFG_H_ */