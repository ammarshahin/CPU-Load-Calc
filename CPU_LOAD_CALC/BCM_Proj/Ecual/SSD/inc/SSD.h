/*
 * 	SSD.h
 *
 * 	Created: 23-Oct-19
 *  Author:  Ammar Shahin
 */ 

#ifndef _SSD_H_
#define _SSD_H_


/************************************************************************/
/*               Defines for the SSD port and enable port               */
/************************************************************************/
#define SSD_PORT  MYPORTB
#define ssd_Enable_PORT  MYPORTD


/************************************************************************/
/*          Enums for the SSD available characters and slots            */
/************************************************************************/
typedef enum{
	c0     ,
	c1     ,
	c2     ,
	c3     ,
	c4     ,
	c5     ,
	c6     ,
	c7     ,
	c8     ,
	c9     ,
	A      ,
	B      ,
	C      ,
	D      ,
	E      ,
	F      ,
	G      ,
	H      ,
	I      ,
	J      ,
	K      ,
	L      ,
	M      ,
	N      ,
	O      ,
	P      ,
	Q      ,
	R      ,
	S      ,
	T      ,
	U      ,
	V      ,
	W      ,
	X      ,
	Y      ,
	Z      ,
}symbole;

typedef enum{
	ssd1     ,
	ssd2     ,
	ssd3     ,
	ssd4     ,
}ssd_Num;

typedef enum{
	ssd1_Enable_Pin   = BIT2 ,
	ssd2_Enable_Pin   = BIT3 ,
	ssd3_Enable_Pin   = BIT6 ,
	ssd4_Enable_Pin   = BIT7 ,
	decimalPoint_Pin  = BIT4 ,
}ssd_Enable_Pin;



/************************************************************************/
/*                   SSDs' Functions' prototypes                      */
/************************************************************************/
void SSD_Display_BCD(uint8 number);
void SSD_Display_8Bit(uint8 number);
void SSD_Display_Decoder(uint8 number);
void SSD_DisplayDecimalPoint(uint8 state);
void SSD_Init_BCD(ssd_Num ssd);
#endif // _SSD_H_ INCLUDED