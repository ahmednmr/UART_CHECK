/*
 * main.c
 *
 *  Created on: 5 Oct 2015
 *      Author: EmbeddedFab
 */

#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include "MCAL/EF_UART.h"
#include "util/delay.h"


int main()
{
	UART_cfg_str UART_Structure={9600,8,1,0,FALSE,FALSE,TRUE,TRUE};

	EF_void_UART_Init(&UART_Structure);
	while(1)
	{
		EF_void_UART_SendString((unsigned char *)"\r\nHello from UART");

_delay_ms(2000);
	}
	return 0;
}


