/***************************************************************
 *  Source File: EF_7Segment.c
 *
 *  Description: This simple driver for 7-Segment
 *
 *  History:     Version 1.0  - INIT Version
 *  Date   :     25/08/2014
 *  -------------------------------------------------------
 *  Author :     EmbeddedFab.
 *
 *  Copyright (C) <2014>  <EmbeddedFab>

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>

 **************************************************************/

#include "EF_7Segment.h"

#include <avr/io.h>
#include "../MCAL/EF_DIO.h"
#include <util/delay.h>


/*********************************************************************
 * Function    : void Segment_Init (void);
 *
 * DESCRIPTION : This function used to Initialize 7-Segment
 *
 * PARAMETERS  : void
 *
 *
 * Return Value: Void
 ***********************************************************************/
void EF_void_Segment_Init (void)
{
	/* used 4 bit for data instead of 7 */
	EF_B_DIO_InitPin  (SEGMENT_DATA_PORT , 0,OUTPUT);
	EF_B_DIO_InitPin  (SEGMENT_DATA_PORT , 1,OUTPUT);
	EF_B_DIO_InitPin  (SEGMENT_DATA_PORT , 2,OUTPUT);
	EF_B_DIO_InitPin  (SEGMENT_DATA_PORT , 3,OUTPUT);

	/* DOT Point */
//	EF_B_DIO_InitPin ('B' , DOT_ENABLE,OUTPUT);

	/* used 4 bit for control the four 7Segemnts */
//	EF_B_DIO_InitPin ('A' , FIRST_SEGMENT_ENABLE,  OUTPUT);
//	EF_B_DIO_InitPin ('A' , SECOND_SEGMENT_ENABLE, OUTPUT);
//	EF_B_DIO_InitPin ('B' , FOURTH_SEGMENT_ENABLE, OUTPUT);
//	EF_B_DIO_InitPin ('C' , THIRD_SEGMENT_ENABLE,  OUTPUT);

	EF_B_DIO_InitPin ('C' , FIRST_SEGMENT_ENABLE,  OUTPUT);
	EF_B_DIO_InitPin ('C' , SECOND_SEGMENT_ENABLE, OUTPUT);
	EF_B_DIO_InitPin ('C' , FOURTH_SEGMENT_ENABLE, OUTPUT);
	EF_B_DIO_InitPin ('C' , THIRD_SEGMENT_ENABLE,  OUTPUT);

}


/*********************************************************************
 * Function    : Segment_Display(U8_t SegmentNumber);
 *
 * DESCRIPTION : This function used to display 7-Segment
 *
 * PARAMETERS  : U8_t SegmentNumber : Number in range 0 to 9999
 *
 *
 * Return Value: Void
 ***********************************************************************/
void EF_void_Segment_Display(U16_t SegmentNumber )
{
	U8_t UnitsDigit = 0;
	U8_t TensDigit  = 0;
	U8_t hundreds   = 0;
	U8_t Thousands  = 0;
	U16_t temp;

	/* there are 4 7Segments used as:
	 * [Thousands|hundreds|TensDigit|UnitsDigit] */
	Thousands  = (SegmentNumber / 1000);
	temp       = (SegmentNumber % 1000);
	hundreds   = (U8_t)(temp   / 100);
	temp       =       (temp   % 100);
	TensDigit  = (U8_t)(temp   / 10);
	UnitsDigit = (U8_t)(temp   % 10);

	/* 7segemnts here are common cathode, to turn on any segment make it High
	 * to economize using pins ,multiplexing is used by control pin to each
	 * 7segment and BCD to 7Segment decoder is used to save 3 pins
	 * So All used pins : 4 for Data and 4 for Multiplexing Control
	 *  * */
	if((SegmentNumber >= 1000))         /* Fourth Digi */
	{
		EF_S8_DIO_ClearPin ('B' , FOURTH_SEGMENT_ENABLE);
		EF_S8_DIO_SetPin   ('C' , THIRD_SEGMENT_ENABLE);
		EF_S8_DIO_SetPin   ('A' , FIRST_SEGMENT_ENABLE);
		EF_S8_DIO_SetPin   ('A' , SECOND_SEGMENT_ENABLE);

//		EF_S8_DIO_WritePort(SEGMENT_DATA_PORT , (Thousands & 0x0F));
		EF_7SegmentWriteData(Thousands);
		_delay_ms (5);
	}
	if(SegmentNumber >= 100)            /* Third Digi */
	{
		EF_S8_DIO_ClearPin ('C' , THIRD_SEGMENT_ENABLE);
		EF_S8_DIO_SetPin   ('B' , FOURTH_SEGMENT_ENABLE);
		EF_S8_DIO_SetPin   ('A' , FIRST_SEGMENT_ENABLE);
		EF_S8_DIO_SetPin   ('A' , SECOND_SEGMENT_ENABLE);

//		EF_S8_DIO_WritePort(SEGMENT_DATA_PORT , (hundreds & 0x0F));
		EF_7SegmentWriteData(hundreds);
		_delay_ms (5);
	}
	if(SegmentNumber >= 10)             /* Second Digi */
	{
		EF_S8_DIO_ClearPin ('A' , SECOND_SEGMENT_ENABLE);
		EF_S8_DIO_SetPin   ('A' , FIRST_SEGMENT_ENABLE);
		EF_S8_DIO_SetPin   ('B' , FOURTH_SEGMENT_ENABLE);
		EF_S8_DIO_SetPin   ('C' , THIRD_SEGMENT_ENABLE);
//		EF_S8_DIO_WritePort(SEGMENT_DATA_PORT , (TensDigit & 0x0F));
		EF_7SegmentWriteData(TensDigit);
		_delay_ms (5);
	}
	EF_S8_DIO_ClearPin ('A' , FIRST_SEGMENT_ENABLE);
	EF_S8_DIO_SetPin   ('A' , SECOND_SEGMENT_ENABLE);
	EF_S8_DIO_SetPin   ('C' , THIRD_SEGMENT_ENABLE);
	EF_S8_DIO_SetPin   ('B' , FOURTH_SEGMENT_ENABLE);
//	EF_S8_DIO_WritePort(SEGMENT_DATA_PORT , (UnitsDigit & 0x0F));
	EF_7SegmentWriteData(UnitsDigit);
	_delay_ms (5);

}

void EF_7SegmentWriteData (U8_t Data)
{
	PORTB = (PORTB & 0xF0)|Data;
}

