/*
 * EF_Health_Care.h
 *
 *  Created on: 6 Oct 2015
 *      Author: EmbeddedFab
 */

#ifndef EF_HEALTH_CARE_H_
#define EF_HEALTH_CARE_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../MCAL/EF_UART.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../MCAL/EF_DIO.h"
#include "../MCAL/EF_ADC.h"
#include "../ServiceLayer/std_types.h"
#include "EF_LCD.h"
#include <math.h>




void EF_Health_Care_system_int();

FP32 EF_Health_Care_Temp_Read(U8_t AdcPin);
void EF_Health_Care_Heart_Pulse_Read(U8_t ADC_PIN);
void EF_Timr0_Inter_Setup();
#endif /* EF_HEALTH_CARE_H_ */
