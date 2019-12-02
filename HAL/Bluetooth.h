/*
 * Bluetooth.h
 *
 *  Created on: Dec 2, 2019
 *      Author: embeddedfab
 */

#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

#include <avr/io.h>
#include <util/delay.h>
#include "../MCAL/EF_DIO.h"
#include "../MCAL/EF_UART.h"





void EF_void_BLUETOOTH_Init(void);
void EF_void_Send_char(char x);
char EF_void_Get_char(void);
void EF_Void_BLUETOOTH_WriteArray(char *BUFFER ,char Len);
void EF_Void_BLUETOOTH_ReadArray(char *BUFFER , char Len);
void EF_Void_BLUETOOTH_Send_String(char *BUFFER);
void EF_Void_BLUETOOTH_ReadArray_untill_Searchkey(char *BUFFER , char Len,char *Searchkey);


#endif /* BLUETOOTH_H_ */
