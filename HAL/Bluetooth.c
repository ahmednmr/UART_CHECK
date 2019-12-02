/*
 * Bluetooth.c
 *
 *  Created on: Dec 2, 2019
 *      Author: embeddedfab
 */


#include "Bluetooth.h"



void EF_void_BLUETOOTH_Init(void)
{
	UART_cfg_str  Uart_Bluetooth={9600,8,ONE_STOP_BIT,NO_PARITY,0,0,1,1};
	EF_void_UART_Init(&Uart_Bluetooth);
}



void EF_void_Send_char(char x)
{
	EF_BOOLEAN_UART_PutChar(x);

}

char EF_void_Get_char(void)
{
	return(	EF_u8_UART_WaitChar());
}

void EF_Void_BLUETOOTH_WriteArray(char *BUFFER ,char Len)
{

while(Len>0)
{
	EF_void_Send_char(*BUFFER++);
	Len--;
	_delay_ms(2);       //it must be delay between every char and the other
}


}


void EF_Void_BLUETOOTH_ReadArray(char *BUFFER , char Len)
{

	while(Len>0)
	{
		*BUFFER++=EF_u8_UART_WaitChar();
		Len--;
	}


}


void EF_Void_BLUETOOTH_Send_String(char *BUFFER)
{
char i=0;
while(BUFFER[i]!=0)
{
	EF_void_Send_char(BUFFER[i]);
	i++;
	_delay_ms(3);       //it must be delay between every char and the other
}


}


void EF_Void_BLUETOOTH_ReadArray_untill_Searchkey(char *BUFFER , char Len,char *Searchkey)
{
	char i=0;

	while(Len>0)
	{
		BUFFER[i]=EF_u8_UART_WaitChar();
		if((BUFFER[i-3]==*Searchkey)&&(BUFFER[i-2]==*(Searchkey+1))&&(BUFFER[i-1]==*(Searchkey+2))&&(BUFFER[i]==*(Searchkey+3)))
		{
		  break;
		}
		i++;
		Len--;
	}

}


