/*
 * pushButton.c
 *
 * Created: 10/22/2019 10:21:42 AM
 *  Author: Ammar Shahin
 */ 

#include "Typedefs.h"
#include "Gpio.h"
#include "pushButton.h"

/**
 * Description: Function to Initiate the Push Button.
 * @param push_Button the number of the pushButton [pushButton0,pushButton1]
 */
void pushButton_Init(pushButton push_Button)
{
	switch(push_Button)
	{
		case pushButton0 :
			Gpio_PinDirection(pushButton0_PORT,pushButton0_PIN,SET_IN);
			break;
		case pushButton1 :
			Gpio_PinDirection(pushButton1_PORT,pushButton1_PIN,SET_IN);
			break;
	}
}

/**
 * Description: Function to get the status of the Push button(Value).
 * @param push_Button the number of the push button [pushButton0,pushButton1]
 * @return the value(state) of the push button
 */
uint8 pushButton_Get_Status(pushButton push_Button)
{
	sint8 result0 = NO_CHANGE,result1,result2;
	switch(push_Button)
	{
		case pushButton0 :
			result1 = Gpio_PinRead(pushButton0_PORT,pushButton0_PIN);
			result2 = Gpio_PinRead(pushButton0_PORT,pushButton0_PIN);
			if(result1 == result2)
			{
				result0 = result1; 
			}else
			{
				result0 = NO_CHANGE;
			}
			break;
		case pushButton1 :
			result1 = Gpio_PinRead(pushButton1_PORT,pushButton1_PIN);
			result2 = Gpio_PinRead(pushButton1_PORT,pushButton1_PIN);
			if(result1 == result2)
			{
				result0 = result1;
			}else
			{
				result0 = NO_CHANGE;
			}
			break;
	}
	return result0;
}