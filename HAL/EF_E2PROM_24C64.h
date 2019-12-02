/***************************************************************
 *  Source File: EF__E2PROM_24C64.h
 *
 *  Description: This simple driver for _E2PROM_24C64
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
#ifndef _E2PROM_24C64_H_
#define _E2PROM_24C64_H_

#include <avr/io.h>
#include <util/delay.h>
#include "../MCAL/EF_DIO.h"
#include "../MCAL/EF_I2C.h"
#include "../ServiceLayer/std_types.h"

#define EEPROM24C64_MAX_PAGE_NUMBER		   256  //from 0 to 255
#define EEPROM24C64_PAGE_LENGTH			   32
#define EEPROM24C64_LAST_BYTE_ADDRESS      8191


/*********************************************************************
 * Function    : EF_void_EEPROM24C64_Init
 *
 * DESCRIPTION : This function used to initalize the I2C Module
 *
 * PARAMETERS  : None
 *
 * Return Value: Void
 ***********************************************************************/
extern void EF_void_EEPROM24C64_Init ();

/*********************************************************************
 * Function    : void EF_void_EEPROM24C64_Write_Byte( U8_t EEPromAddress, U16_t u16ByteAddress, U8_t u8Data)
 *
 * DESCRIPTION : This function used to Write One byte
 *
 * PARAMETERS  : U8_t EEPromAddress   : 0xA0 or 0xA2
 *               U16_t u16ByteAddress : 0 to LAST_BYTE_ADDRESS
 *               U8_t data
 *
 * Return Value: False if stuck
 ***********************************************************************/
U8_t EF_u8_EEPROM24C64_Write_Byte ( U8_t EEPromAddress, U16_t memory_location, U8_t data);

/*********************************************************************
 * Function    : void EF_u8_EEPROM24C64_Read_Byte(U8_t EEPromAddress, U16_t memory_location , U8_t* pu8RxData);
 *
 * DESCRIPTION : This function used to read One byte
 *
 * PARAMETERS  : U8_t EEPromAddress  : 0xA0 or 0xA2
 *               U8_t u16ByteAddress : 0 to LAST_BYTE_ADDRESS
 *                U8_t* pu8RxData    : pointer to the return data
 *
 * Return Value: false if stuck
 ***********************************************************************/
U8_t EF_u8_EEPROM24C64_Read_Byte (U8_t EEPromAddress, U16_t memory_location , U8_t* pu8RxData);


/*********************************************************************
 * Function    : BOOLEAN EF_BOOLEAN_EEPROM24C64_Write_Page (U8_t EEPromAddress,
 * 										 U8_t u8PageNmber, U8_t* pu8Data , U8_t u8DataLength)
 *
 * DESCRIPTION : This function used to write page
 *
 * PARAMETERS  : U8_t EEPromAddress :  0xA0 or 0xA2
 * 				 U8_t PageNmber: 0 to 255
 *               U8_t* data : Pointer to Data Page
 *               DataLength : Data Length from 1 to 32
 *
 * Return Value: Void
 ***********************************************************************/
BOOLEAN EF_BOOLEAN_EEPROM24C64_Write_Page (U8_t EEPromAddress, U8_t PageNmber, U8_t* data , U8_t DataLength);


/*********************************************************************
 * Function    : BOOLEAN EF_BOOLEAN_EEPROM24C64_Read_Page  ( U8_t EEPromAddress,
 * 								 U8_t u8PageNumber, U8_t* pu8Data , U8_t  u8DataLength)
 *
 * DESCRIPTION : This function used to read page
 *
 * PARAMETERS  : U8_t EEPromAddress :  0xA0 or 0xA2
 * 				 U8_t PageNmber		: 0 to 255
 *               U8_t* data			: Pointer to Data Page
 *               DataLength 		: Data Length from 1 to 32
 *
 * Return Value: Void
 ***********************************************************************/
BOOLEAN EF_BOOLEAN_EEPROM24C64_Read_Page ( U8_t EEPromAddress, U8_t PageNmber, U8_t* data , U8_t  DataLength);

void  test_EEPROM24C64 (U8_t EEPromAddress, U8_t u8PageCounter );

#endif /* _E2PROM_24C64_H_ */
