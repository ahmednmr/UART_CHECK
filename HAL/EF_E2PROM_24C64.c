/***************************************************************
 *  Source File: EF_E2PROM_24C16.c
 *
 *  Description: This simple driver for E2PROM_24C16
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

#include "EF_E2PROM_24C64.h"
#include "../MCAL/EF_UART.h"
#include <avr/pgmspace.h>
#include <string.h>
#include <stdlib.h>

/*********************************************************************
 * Function    : EF_void_EEPROM24C64_Init
 *
 * DESCRIPTION : This function used to initalize the I2C Module
 *
 * PARAMETERS  : None
 *
 * Return Value: Void
 ***********************************************************************/
void EF_void_EEPROM24C64_Init ()
{
	EF_void_I2C_Init();
}

/*********************************************************************
 * Function    : void EF_void_EEPROM24C64_Write_Byte( U8_t EEPromAddress, U16_t u16ByteAddress, U8_t u8Data)
 *
 * DESCRIPTION : This function used to Write One byte
 *
 * PARAMETERS  : U8_t EEPromAddress: 0xA0 or 0xA2
 *               U8_t u16ByteAddress : 0 to EEPROM24C64_LAST_BYTE_ADDRESS
 *               U8_t data
 *
 * Return Value: False if stuck
 ***********************************************************************/
U8_t EF_u8_EEPROM24C64_Write_Byte ( U8_t EEPromAddress, U16_t u16ByteAddress, U8_t u8Data)
{
	volatile U8_t u8ReturnStatus = TRUE;


	if (u16ByteAddress > EEPROM24C64_LAST_BYTE_ADDRESS)
	{
		u8ReturnStatus = FALSE;
	}

	EF_void_I2C_Start();                  /* Send Start Bit 						 */

	EF_void_I2C_Write(EEPromAddress);     /* Send Slave address with Operation Write */

	EF_void_I2C_Write( (U8_t)(u16ByteAddress>>8));   /* Send MSB Memory Location Address 			 */

	EF_void_I2C_Write((U8_t)(u16ByteAddress));   /* Send LSB Memory Location Address 			 */

	EF_void_I2C_Write(u8Data);              /* Send Data One byte 					 */



	EF_void_I2C_Stop();
	_delay_ms(20);

	return u8ReturnStatus;
}


/*********************************************************************
 * Function    : void EF_u8_EEPROM24C64_Read_Byte(U8_t EEPromAddress, U16_t memory_location , U8_t* pu8RxData);
 *
 * DESCRIPTION : This function used to read One byte
 *
 * PARAMETERS  : U8_t EEPromAddress  : 0xA0 or 0xA2
 *               U8_t u16ByteAddress : 0 to EEPROM24C64_LAST_BYTE_ADDRESS
 *                U8_t* pu8RxData    : pointer to the return data
 *
 * Return Value: false if stuck
 ***********************************************************************/
U8_t EF_u8_EEPROM24C64_Read_Byte (U8_t EEPromAddress, U16_t u16ByteAddress , U8_t* pu8RxData)
{
	volatile U8_t u8ReturnStatus = TRUE;


	if (u16ByteAddress > EEPROM24C64_LAST_BYTE_ADDRESS)
	{
		u8ReturnStatus = FALSE;
	}

	EF_void_I2C_Start();                      /* Send Start Bit 						 */

	EF_void_I2C_Write(EEPromAddress);         /* Send Slave address with Operation Write */

	EF_void_I2C_Write((U8_t)(u16ByteAddress>>8));       /* Send Memory Location Address 			 */

	EF_void_I2C_Write((U8_t)(u16ByteAddress));       /* Send Memory Location Address 			 */

	EF_void_I2C_Start();                      /* Send Restart Bit 						 */

	EF_void_I2C_Write(EEPromAddress | 1);     /* Send Slave address with Operation read  */

	*pu8RxData = EF_U8_I2C_Read_Byte(0);

	EF_void_I2C_Stop();


return u8ReturnStatus;
}

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
//BOOLEAN EF_BOOLEAN_EEPROM24C64_Read_Page ( U8_t EEPromAddress, U8_t u8PageNumber, U8_t* pu8Data , U8_t  u8DataLength)
//{
//	U8_t u8iterator = 0;
//	volatile U8_t  u8ReturnStatus = TRUE;
//	U16_t u16PageBoundaryAddress = 0;
//
//	if ((u8DataLength > EEPROM24C64_PAGE_LENGTH) ||(u8PageNumber >= EEPROM24C64_MAX_PAGE_NUMBER) || (pu8Data == NULL) )
//	{
//		u8ReturnStatus = FALSE;
//	}
//	if (u8ReturnStatus == TRUE)
//	{
//		u8ReturnStatus = EF_u8_I2C_Start();                  /* Send Start Bit 						 */
//		if (u8ReturnStatus == TRUE)
//		{
//			/* slave address: [1|0|1|0|A2|A1|A0|R/W'] */
//			u8ReturnStatus = EF_u8_I2C_sendData ( EEPromAddress );     /* Send Slave address with Operation Write */
//			if (u8ReturnStatus == TRUE)
//			{
//				u16PageBoundaryAddress = u8PageNumber*EEPROM24C64_PAGE_LENGTH;
//				/* send the byte address, the start of page, and decrement 1 as it was started by 1 in the argument */
//				u8ReturnStatus = EF_u8_I2C_sendData( (U8_t)(u16PageBoundaryAddress>>8));   /* Send Memory Location Address */
//				if (u8ReturnStatus == TRUE)
//				{
//					u8ReturnStatus = EF_u8_I2C_sendData( (U8_t)(u16PageBoundaryAddress));   /* Send Memory Location Address */
//
//					if (u8ReturnStatus == TRUE)
//					{
//						u8ReturnStatus = EF_u8_I2C_Start();                      /* Send Restart Bit 						 */
//						if (u8ReturnStatus == TRUE)
//						{
//							u8ReturnStatus = EF_u8_I2C_sendData( (EEPromAddress) | 1);     /* Send Slave address with Operation read  */
//							if (u8ReturnStatus == TRUE)
//							{
//								for (u8iterator = 0; u8iterator < u8DataLength; u8iterator++)
//								{
//									if (u8iterator == u8DataLength -1)
//									{
//										u8ReturnStatus = EF_u8_I2C_receiveData_NACK((pu8Data +u8iterator));
//									}
//									else
//									{
//										u8ReturnStatus = EF_u8_I2C_receiveData_ACK((pu8Data +u8iterator));
//									}
//									if (u8ReturnStatus == FALSE)
//									{
//										break;
//									}
//								}
//							}
//						}
//					}
//				}
//			}
//		}
//
//		EF_void_I2C_stop();
//	}
//
//	return u8ReturnStatus;
//}
//
///*********************************************************************
// * Function    : BOOLEAN EF_BOOLEAN_EEPROM24C64_Write_Page (U8_t EEPromAddress,
// * 										 U8_t u8PageNmber, U8_t* pu8Data , U8_t u8DataLength)
// *
// * DESCRIPTION : This function used to write page
// *
// * PARAMETERS  : U8_t EEPromAddress :  0xA0 or 0xA2
// * 				 U8_t PageNmber: 0 to 255
// *               U8_t* data : Pointer to Data Page
// *               DataLength : Data Length from 1 to 32
// *
// * Return Value: Void
// ***********************************************************************/
//BOOLEAN EF_BOOLEAN_EEPROM24C64_Write_Page (U8_t EEPromAddress, U8_t u8PageNmber, U8_t* pu8Data , U8_t u8DataLength)
//{
//	volatile U8_t  u8ReturnStatus = TRUE;
//	U8_t  u8Iterator = 0;
//	U16_t u16PageBoundaryAddress = 0;
//
//
//	if ( (u8DataLength > EEPROM24C64_PAGE_LENGTH) || (u8PageNmber >= EEPROM24C64_MAX_PAGE_NUMBER) || (pu8Data == NULL) )
//	{
//		u8ReturnStatus = FALSE;
//	}
//	if (u8ReturnStatus == TRUE)
//	{
//		u8ReturnStatus = EF_u8_I2C_Start();                  /* Send Start Bit */
//		if (u8ReturnStatus == TRUE)
//		{
//			/* slave address: [1|0|1|0|A2|A1|A0|R/W'] */
//			u8ReturnStatus = EF_u8_I2C_sendData ( EEPromAddress  );     /* Send Slave address with Operation Write */
//			if (u8ReturnStatus == TRUE)
//			{
//				u16PageBoundaryAddress = u8PageNmber*EEPROM24C64_PAGE_LENGTH;
//				/* send the byte address, the start of page, and decrement 1 as it was started by 1 in the argument */
//				u8ReturnStatus = EF_u8_I2C_sendData((U8_t) (u16PageBoundaryAddress>>8));   /* Send Memory Location Address */
//				if (u8ReturnStatus == TRUE)
//				{
//					u8ReturnStatus = EF_u8_I2C_sendData((U8_t) (u16PageBoundaryAddress));   /* Send Memory Location Address */
//					if (u8ReturnStatus == TRUE)
//					{
//						for (u8Iterator = 0; u8Iterator < u8DataLength; u8Iterator++)
//						{
//							u8ReturnStatus = EF_u8_I2C_sendData( *(pu8Data + u8Iterator) );                /* Send Data One byte */
//							if (u8ReturnStatus == FALSE)
//							{
//								break;
//							}
//						}
//					}
//				}
//			}
//		}
//		EF_void_I2C_stop();
//		/* after write , you must wait 20 ms */
//		_delay_ms(20);
//	}
//
//	return u8ReturnStatus;
//}



//void  test_EEPROM24C64 (U8_t EEPromAddress, U8_t u8PageCounter )
//{
//	U8_t EpromData   [20]   =  {1, 2, 3,4,5,6,7,8,9,0,
//			9, 8, 7,6,5,4,3,2,1,0 };
//	U8_t EpromRxData [20] = {0};
//	EF_BOOLEAN_EEPROM24C64_Write_Page (EEPromAddress ,u8PageCounter,  EpromData   , 20);
//	EF_BOOLEAN_EEPROM24C64_Read_Page  (EEPromAddress, u8PageCounter,  EpromRxData , 20);
//
//	if(0 == memcmp(EpromData,EpromRxData, 20))
//	{
//#ifdef DEBUG
//		//			for (u8Counter = 0; u8Counter <20; u8Counter++ )
//		//			{
//		//				EF_void_UART_HextoASCII(&EpromRxData[u8Counter]);
//		//				EF_void_UART_PutChar (' ');
//		//			}
//		EF_void_UART_HextoASCII(&u8PageCounter);
//		EF_void_UART_PutChar ('\r');EF_void_UART_PutChar ('\n');
//#endif
//	}
//	else
//	{
//		EF_void_UART_PutChar ('L');
//	}
//}
