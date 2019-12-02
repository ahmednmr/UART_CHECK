/*
 * EF_Green_kit_Test.h
 *
 *  Created on: 27 Aug 2015
 *      Author: EmbeddedFab
 */

#ifndef EF_GREEN_KIT_TEST_H_
#define EF_GREEN_KIT_TEST_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdlib.h>
#include "../MCAL/EF_DIO.h"
#include "../MCAL/EF_ADC.h"
#include "EF_KeyPad.h"
#include "../ServiceLayer/std_types.h"
#include "../MCAL/EF_PWM.h"
#include "EF_LCD.h"
#include "EF_7Segment.h"

//#include "EF_E2PROM_24C16.h"
#include "EF_E2PROM_24C64.h"



void EF_KIT_Inti();
void EF_Green_Kit_Leds_Relay_test();
void EF_Green_Kit_Buzzer_test();
void EF_Green_Kit_7Seg_Test();
void EF_Green_Kit_ADC_Test();
void EF_Green_Kit_KeyPad_test();


#endif /* EF_GREEN_KIT_TEST_H_ */
