/*
 * main.c
 *
 *  Created on: 5 Oct 2015
 *      Author: EmbeddedFab
 */

#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include "HAL/Bluetooth.h"

int main()
{
char incoming_data[20]={0};
char Turn_on_array[20]="turn on lamb";
char Turn_off_array[20]="turn off lamb";


	EF_void_BLUETOOTH_Init();

	EF_B_DIO_InitPin('D',4,OUTPUT);    // init Relay as Output
	EF_S8_DIO_ClearPin('D',4);
	while(1)
	{


		memset(incoming_data, 0,20*sizeof(char));

		EF_Void_BLUETOOTH_ReadArray_untill_Searchkey(incoming_data,20,"lamb");

		if(strcmp(incoming_data,Turn_on_array)==0)
		{
			EF_S8_DIO_SetPin('D',4);   //turn on Relay
		}

		else if(strcmp(incoming_data,Turn_off_array)==0)
		{
	       EF_S8_DIO_ClearPin('D',4);
		}

		EF_Void_BLUETOOTH_Send_String(incoming_data);


	}
	return 0;
}


