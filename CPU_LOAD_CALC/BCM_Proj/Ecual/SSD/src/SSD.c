/*
 * SSD.c
 *
 * Created: 23-Oct-19 6:10:55 PM
 *  Author: Ammar Shahin
 */ 


#include "Typedefs.h"
#include "Gpio.h"
#include "SSD.h"


/**
 * Description: Function to Initialize the SSD
 * @param ssd is an user defined variable to indicate the Which SSD to display on
 */
void SSD_Init_BCD(ssd_Num ssd)
{
	Gpio_LowerNibbleDirection(SSD_PORT,SET_OUT);
	
	/* Enable the SSD */
	switch(ssd)
	{
		case ssd1 : 
		Gpio_PinDirection(ssd_Enable_PORT,ssd1_Enable_Pin,SET_OUT); 
		Gpio_PinWrite(ssd_Enable_PORT,ssd1_Enable_Pin,TRUE);
		break;
		case ssd2 :
		Gpio_PinDirection(ssd_Enable_PORT,ssd2_Enable_Pin,SET_OUT);
		Gpio_PinWrite(ssd_Enable_PORT,ssd2_Enable_Pin,TRUE);
		break;
		case ssd3 :
		Gpio_PinDirection(ssd_Enable_PORT,ssd3_Enable_Pin,SET_OUT);
		Gpio_PinWrite(ssd_Enable_PORT,ssd3_Enable_Pin,TRUE);
		break;
		case ssd4 :
		Gpio_PinDirection(ssd_Enable_PORT,ssd4_Enable_Pin,SET_OUT);
		Gpio_PinWrite(ssd_Enable_PORT,ssd4_Enable_Pin,TRUE);
		break;
	}
	/* Display the character 0 */ 
	SSD_Display_BCD(0);
}


/**
 * Description: Function to Display to A 7-segment Directly
 * @param number the number to display
 */
void SSD_Display_8Bit(uint8 number)
{
	switch (number)
	{
		case 0:
		Gpio_PortWrite(SSD_PORT,0x7e);
		break;
		case 1:
		Gpio_PortWrite(SSD_PORT,0x30);
		break;
		case 2:
		Gpio_PortWrite(SSD_PORT,0x6d);
		break;
		case 3:
		Gpio_PortWrite(SSD_PORT,0x79);
		break;
		case 4:
		Gpio_PortWrite(SSD_PORT,0x33);
		break;
		case 5:
		Gpio_PortWrite(SSD_PORT,0x5b);
		break;
		case 6:
		Gpio_PortWrite(SSD_PORT,0x5f);
		break;
		case 7:
		Gpio_PortWrite(SSD_PORT,0x70);
		break;
		case 8:
		Gpio_PortWrite(SSD_PORT,0x7f);
		break;
		case 9:
		Gpio_PortWrite(SSD_PORT,0x7b);
		break;
		case A:
		Gpio_PortWrite(SSD_PORT,0x77);
		break;
		case B:
		Gpio_PortWrite(SSD_PORT,0b00111110);
		break;
		case C:
		Gpio_PortWrite(SSD_PORT,0b10011100);
		break;
		case D:
		Gpio_PortWrite(SSD_PORT,0b01111010);
		break;
		case E:
		Gpio_PortWrite(SSD_PORT,0x4f);
		break;
		case F:
		Gpio_PortWrite(SSD_PORT,0x47);
		break;
		default:
		break;
	}
}


/**
 * Description: Function to Display to a Decoded 7-segment 
 * @param number the number to display
 */
void SSD_Display_Decoder(uint8 number)
{
	uint16 counter = 0; // delay to show the number
	while(counter++ < 1000)
	{
		Gpio_PinWrite(ssd_Enable_PORT,ssd2_Enable_Pin,TRUE);
		Gpio_PinWrite(ssd_Enable_PORT,ssd1_Enable_Pin,FALSE);
		SSD_Display_BCD(number/10);
		Gpio_PinWrite(ssd_Enable_PORT,ssd2_Enable_Pin,FALSE);
		Gpio_PinWrite(ssd_Enable_PORT,ssd1_Enable_Pin,TRUE);
		SSD_Display_BCD(number%10);
	}
}

/**
 * Description: Function to set the Lower Nibble to the value of the number 
 * @param number the number to display [0 to F only]
 */
void SSD_Display_BCD(uint8 number)
{
	Gpio_LowerNibbleDirection(SSD_PORT,SET_OUT);
	Gpio_LowerNibbleWrite(SSD_PORT,number);
}

/**
 * Description: Function to set the Decimal Point 
 * @param state the State of the decimal Point
 */
void SSD_DisplayDecimalPoint(uint8 state)
{
	//Av_gpioPinDirection(ssd_Enable_PORT,decimalPoint_Pin,set_OUT);
	if(state)
	{
		SSD_Display_BCD(10); // TRUE
	}
	else
	{
		Gpio_PinWrite(ssd_Enable_PORT,decimalPoint_Pin,FALSE); // FALSE
	}
}
