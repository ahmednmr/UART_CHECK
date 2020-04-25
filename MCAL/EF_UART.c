 /***************************************************************
 *  Source File: EF_UART.c
 *
 *  Description: UART driver for ATMEGA32
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
#include <avr/io.h>
#include "EF_UART.h"
#include "EF_SpechialTIMER.h"
#include "../ServiceLayer/std_types.h"
#include <util/delay.h>

/**************************************************
 * Global Variables & Definitions
 *************************************************/
/* structure has the addresses of UART Registers */
const UART_reg_str uart_reg = {&UDR,&UCSRA,&UCSRB,&UCSRC,&UBRRH,&UBRRL};

/****************************************************************************
* Function    : EF_void_UART_Init
*
* DESCRIPTION : init the UART
*
* PARAMETERS  : uart_cfg : pointer to UART_cfg_str which has parameters to init the UART
*
* Return Value: None.
******************************************************************************/
void EF_void_UART_Init(UART_cfg_str *uart_cfg)
{
	/* variable helps in calculating Baud rate */
	U32_t uart_UBBR;
	*uart_reg.UCSRB_Reg = 0x00;
	*uart_reg.UCSRC_Reg = 0x00;

	/* Enable or disable RX,TX module & Interrupt */
	if (uart_cfg->RXInterruptEnable) *uart_reg.UCSRB_Reg |= (1 << RXCIE);
	if (uart_cfg->TXInterruptEnable) *uart_reg.UCSRB_Reg |= (1 << TXCIE);
	if (uart_cfg->ReceiverEnable   ) *uart_reg.UCSRB_Reg |= (1 << RXEN);
	if (uart_cfg->TransmitterEnable) *uart_reg.UCSRB_Reg |= (1 << TXEN);
	/* Parity and Stop bit*/
	*uart_reg.UCSRC_Reg |= (uart_cfg->parity)<<UPM0;
	*uart_reg.UCSRC_Reg |= (uart_cfg->stopBits)<<USBS;

	if (uart_cfg->numberOfDataBits == 9)
	{
		*uart_reg.UCSRB_Reg |= 0x04;
		*uart_reg.UCSRC_Reg |= (1 << URSEL) | 0x06;
	}
	else if(uart_cfg->numberOfDataBits == 5)
	{
	// do nothing
	}
	else if(uart_cfg->numberOfDataBits == 6)
	{
		*uart_reg.UCSRC_Reg |= (1 << URSEL) | 0x02;
	}
	else if(uart_cfg->numberOfDataBits == 7)
	{
		*uart_reg.UCSRC_Reg |= (1 << URSEL) | 0x04;
	}
	else
	{
		*uart_reg.UCSRC_Reg |= (1 << URSEL) | 0x06;
	}


	/* Set the UART Baud rate */


	uart_UBBR =  F_CPU/(uart_cfg->baudrate*16)-1;
	*uart_reg.UBRRH_Reg = (uint8_t)(uart_UBBR>>8);
	*uart_reg.UBRRL_Reg = (uint8_t)uart_UBBR;

	/* using Special Timer to able some UART Function to be unstuck */
	EF_void_TimerCreate(UART_TIMER_ID, UART_WAIT_TIME);


}

/****************************************************************************
* Function    : EF_BOOLEAN_UART_GetChar
*
* DESCRIPTION : Getting the RX byte ,used timer to be unStuck
*
* PARAMETERS  : returnedValue: pointer to the Rx byte
*
* Return Value: return True if Byte is received or false
*
* NOTE		  : special timer must be initialized and enable Global interrupt
* 			    before using this function
******************************************************************************/
BOOLEAN EF_BOOLEAN_UART_GetChar(U8_t * returnedValue)
{
	BOOLEAN reciveFlag   = FALSE;

	EF_void_TimerStart(UART_TIMER_ID);

	/* make UART unstuck*/
    while( (!(*uart_reg.UCSRA_Reg & (1 << RXC))) && (!EF_BOOLEAN_TimerCheck(UART_TIMER_ID)) );
    /* extracting from the previous loop because of receiving byte or Time out*/
    EF_void_TimerStop(UART_TIMER_ID);
    EF_void_TimerReset(UART_TIMER_ID);

    reciveFlag     = TRUE;

    if(!(*uart_reg.UCSRA_Reg & (1 << RXC)))
    {
    	reciveFlag = FALSE;
    }

    *returnedValue = *uart_reg.UDR_Reg;
    return reciveFlag;
}
/****************************************************************************
* Function    : EF_BOOLEAN_UART_PutChar
*
* DESCRIPTION : Sending the TX byte ,used timer to be unStuck
*
* PARAMETERS  : data : TX byte
*
* Return Value: return True if Byte is transmitted or false
*
* NOTE		  : special timer must be initialized and enable Global interrupt
* 			    before using this function
******************************************************************************/
BOOLEAN EF_BOOLEAN_UART_PutChar(U8_t data)
{
	BOOLEAN sendFlag = FALSE;
	EF_void_TimerStart(UART_TIMER_ID);

	/* make UART unstuck */
    while( (!(*uart_reg.UCSRA_Reg & (1 << UDRE))) && (!EF_BOOLEAN_TimerCheck(UART_TIMER_ID)) );
    /* extracting from the previous loop because of receiving byte or Time out*/
    EF_void_TimerStop(UART_TIMER_ID);
    EF_void_TimerReset(UART_TIMER_ID);

	if(*uart_reg.UCSRA_Reg & (1 << UDRE))
	{
		/* USART Transmit Complete */
		*uart_reg.UDR_Reg = data;    /* send character */
		sendFlag = TRUE;
	}
	else
	{
		sendFlag = FALSE;
	}
	return sendFlag;
}
/****************************************************************************
* Function    : EF_u8_UART_WaitChar
*
* DESCRIPTION :  Getting the RX byte
*
* PARAMETERS  : TimeOut
*
* Return Value: U8_t : Rx byte
******************************************************************************/
U8_t EF_u8_UART_WaitChar()
{
	/* wait until receive byte */
    while((!(*uart_reg.UCSRA_Reg & (1 << RXC))) );
    return *uart_reg.UDR_Reg;
}

/****************************************************************************
* Function    : EF_void_UART_PutChar
*
* DESCRIPTION : Sending the TX byte
*
* PARAMETERS  : Tx_byte
*
* Return Value: None
*
******************************************************************************/
void EF_void_UART_PutChar(U8_t data)
{
	while(!(*uart_reg.UCSRA_Reg & (1 << UDRE)));  /* wait until UDR ready */
	*uart_reg.UDR_Reg = data;    				  /* send character 	  */
}

/****************************************************************************
* Function    : EF_void_UART_SendArray
*
* DESCRIPTION : sending arrays of bytes
*
*
* PARAMETERS  : array 		: pointer to TX data
*				Length		: lenght of array
*
* Return Value: None
*
******************************************************************************/
void EF_void_UART_SendArray(U8_t *array, U8_t Length)
{
    U8_t ArrayIndex;
    for(ArrayIndex = 0; ArrayIndex< Length; ArrayIndex++)
    {
    	EF_void_UART_PutChar(array[ArrayIndex]);
	}
}
void EF_void_UART_Send_data_temp(U16_t s16Numberstring)
{
	U8_t ArrayIndex = 0;
	char s8DisplayStr[6] = {0};
	/* convert number to ASCII */


	itoa(s16Numberstring, s8DisplayStr, 10);
	EF_void_UART_SendArray((U8_t *)"Temperature : ",15);
	for(ArrayIndex = 0; s8DisplayStr[ArrayIndex] != 0; ArrayIndex++)
	{

		EF_void_UART_PutChar(s8DisplayStr[ArrayIndex]);
		if(ArrayIndex==1)EF_void_UART_PutChar('.');
		_delay_ms(1);
	}
	EF_void_UART_SendArray((U8_t *)" C ",3);

}


void EF_void_UART_Send_data_PBM(U16_t s16Numberstring)
{
	U8_t ArrayIndex = 0;
	char s8DisplayStr[6] = {0};
	/* convert number to ASCII */


	itoa(s16Numberstring, s8DisplayStr, 10);
	EF_void_UART_SendArray((U8_t *)"          PBM : ",16);
	for(ArrayIndex = 0; s8DisplayStr[ArrayIndex] != 0; ArrayIndex++)
	{

		EF_void_UART_PutChar(s8DisplayStr[ArrayIndex]);
		_delay_us(10);
	}

}
/****************************************************************************
* Function    : EF_void_UART_Send_Integer
*
* DESCRIPTION : convert from digit to ascii
*
* PARAMETERS  : pointer to integer number
*
* Return Value: None
*
******************************************************************************/
void EF_void_UART_Send_Integer(U16_t s16Numberstring)
{
	//todod change this function
	U8_t ArrayIndex = 0;
	char s8DisplayStr[6] = {0};
	/* convert number to ASCII */

	itoa(s16Numberstring, s8DisplayStr, 10);

	for(ArrayIndex = 0; s8DisplayStr[ArrayIndex] != 0; ArrayIndex++)
	{
		EF_void_UART_PutChar(s8DisplayStr[ArrayIndex]);
	}

}
/****************************************************************************
* Function    : EF_void_UART_SendString
*
* DESCRIPTION : print array without giving its size
*
* PARAMETERS  : array of ascii
*
* Return Value: None
*
******************************************************************************/
void EF_void_UART_SendString(unsigned char *array)
{
    U8_t ArrayIndex = 0;

	while ( array[ArrayIndex] != 0)
	{
    	EF_void_UART_PutChar(array[ArrayIndex]);
    	ArrayIndex++;
	}
}
/****************************************************************************
* Function    : EF_void_UART_SendNewLine
*
* DESCRIPTION : sending 2 bytes "/r/n"
*
* Return Value: None
*
******************************************************************************/
void EF_void_UART_SendNewLine()
{
	EF_void_UART_PutChar(0x0D);
	EF_void_UART_PutChar(0x0A);
}
void EF_void_UART_update_time(U8_t hours, U8_t minutes, U8_t seconds)
{
	char temp[2];



	itoa(hours/10,temp,10);
	EF_void_UART_SendString((U8_t *)temp);
	itoa(hours%10,temp,10);
	EF_void_UART_SendString((U8_t *)temp);
	EF_void_UART_SendString((U8_t *)":");

	itoa(minutes/10,temp,10);
	EF_void_UART_SendString((U8_t *)temp);
	itoa((minutes%10),temp,10);
	EF_void_UART_SendString((U8_t *)temp);
	EF_void_UART_SendString((U8_t *)":");
	itoa(seconds/10,temp,10);
	EF_void_UART_SendString((U8_t *)temp);
	itoa(seconds%10,temp,10);
	EF_void_UART_SendString((U8_t *)temp);
}
