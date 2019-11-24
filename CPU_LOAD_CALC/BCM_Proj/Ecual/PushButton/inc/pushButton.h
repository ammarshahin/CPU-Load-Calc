/*
 * pushButton.h
 *
 * Created: 10/22/2019 10:22:07 AM
 *  Author: Ammar Shahin
 */ 


#ifndef PUSHBUTTON_H_
#define PUSHBUTTON_H_


/************************************************************************/
/*                            Files Inculded                            */
/************************************************************************/
#include "pushButtonConfig.h"

/************************************************************************/
/*				            Functions Prototypes                         */
/************************************************************************/
void pushButton_Init(pushButton push_Button);
uint8 pushButton_Get_Status(pushButton push_Button);

#endif /* PUSHBUTTON_H_ */