/*
 * EF_Green_hit_Test.c
 *
 *  Created on: 27 Aug 2015
 *      Author: EmbeddedFab
 */


#include "EF_Green_kit_Test.h"

#include "../MCAL/EF_UART.h"

#define BUZZER_PIN      7           //PORTD
#define BUZZER_PORT     'D'

#define LED1_PIN        4           //PORTA
#define LED2_PIN        5           //PORTA
#define LED3_PIN        6           //PORTC
#define LED4_PIN        7           //PORTC
//#define LED_PORTC      'D'
#define LED_PORT      'D'

//#define RELAY1_PIN 6
//#define RELAY2_PIN 7


#define ADC_POT_CHANL        7
#define ADC_TEMP_CHANL       6
#define ADC_LDR_CHANL        2

UART_cfg_str Uart_Paraters = {9600, 8, ONE_STOP_BIT, NO_PARITY,0,0,1,1};


U8_t *Data_lcd[20] =
{
		(U8_t*) "Welcome:)",//0
		(U8_t*)"EmbeddedFab",//1
		(U8_t*)"1-Leds test",//2
		(U8_t*)"2-Buzzer Test",//3
		(U8_t*)"3-7Segment Test",//4
		(U8_t*)"4-ADC Test",//5
		(U8_t*)"5-EEPROM Test",//6
		(U8_t*)"6-RTC Test",//7
		(U8_t*)"Leds and Relay ",//8
		(U8_t*)"PRSS 9 to return...",//9
		(U8_t*)"BUZZER Testing...",//10
		(U8_t*)"Testing OK ",//11
		(U8_t*)"7SEG Testing... ",//12
		(U8_t*)"ADC Testing... "//13

};

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

void EF_KIT_Inti()
{
	EF_void_LCD_init();

	_delay_ms(100);
	EF_void_LCD_Clear_Screen();
	EF_void_LCD_goto(1,4);
	EF_void_LCD_print(*Data_lcd);
	EF_void_LCD_goto(2,3);
	EF_void_LCD_print(*(Data_lcd+1));
	_delay_ms(3000);
	EF_void_LCD_Clear_Screen();
	EF_void_LCD_print(" Development Kit ");
	EF_void_LCD_goto(2,5);
	EF_void_LCD_print("  Test  ");

	_delay_ms(2000);
}


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

void EF_Green_Kit_Leds_Relay_test()
{

	EF_B_DIO_InitPin(LED_PORT,LED1_PIN,OUTPUT);
	EF_B_DIO_InitPin(LED_PORT,LED2_PIN,OUTPUT);
	EF_B_DIO_InitPin(LED_PORT,LED3_PIN,OUTPUT);
	EF_B_DIO_InitPin(LED_PORT,LED4_PIN,OUTPUT);
	EF_B_DIO_InitPin(BUZZER_PORT,BUZZER_PIN,OUTPUT);
	//	EF_B_DIO_InitPin('d',RELAY2_PIN,OUTPUT);

	EF_S8_DIO_SetPin(LED_PORT,LED1_PIN);
	EF_S8_DIO_ClearPin(LED_PORT,BUZZER_PIN);
	EF_S8_DIO_SetPin(LED_PORT,LED2_PIN);
	EF_S8_DIO_SetPin(LED_PORT,LED3_PIN);
	EF_S8_DIO_SetPin(LED_PORT,LED4_PIN);

	EF_void_LCD_Clear_Screen();
	////////////////////////////////////////////
	EF_void_LCD_goto(1,1);
	EF_void_LCD_print(*(Data_lcd+8));
	EF_void_LCD_goto(2,4);
	EF_void_LCD_print("Testing...");
	_delay_ms(600);

	EF_S8_DIO_ClearPin(LED_PORT,LED1_PIN);
	EF_S8_DIO_ClearPin(LED_PORT,LED2_PIN);
	EF_S8_DIO_ClearPin(LED_PORT,LED3_PIN);
	EF_S8_DIO_ClearPin(LED_PORT,LED4_PIN);
	_delay_ms(1000);

	EF_S8_DIO_SetPin(LED_PORT,LED3_PIN);
	EF_S8_DIO_SetPin(LED_PORT,LED4_PIN);
	EF_S8_DIO_SetPin(LED_PORT,LED1_PIN);
	EF_S8_DIO_SetPin(LED_PORT,LED2_PIN);
	_delay_ms(1000);

	EF_S8_DIO_ClearPin(LED_PORT,LED1_PIN);
	EF_S8_DIO_ClearPin(LED_PORT,LED2_PIN);
	EF_S8_DIO_ClearPin(LED_PORT,LED3_PIN);
	EF_S8_DIO_ClearPin(LED_PORT,LED4_PIN);
	_delay_ms(1000);

	EF_S8_DIO_SetPin(LED_PORT,LED3_PIN);
	EF_S8_DIO_SetPin(LED_PORT,LED4_PIN);
	EF_S8_DIO_SetPin(LED_PORT,LED1_PIN);
	EF_S8_DIO_SetPin(LED_PORT,LED2_PIN);
	_delay_ms(1000);

	EF_S8_DIO_ClearPin(LED_PORT,LED1_PIN);
	EF_S8_DIO_ClearPin(LED_PORT,LED3_PIN);
	_delay_ms(500);

	EF_S8_DIO_ClearPin(LED_PORT,LED2_PIN);
	EF_S8_DIO_ClearPin(LED_PORT,LED4_PIN);

	_delay_ms(500);

	EF_S8_DIO_SetPin(LED_PORT,LED3_PIN);
	EF_S8_DIO_SetPin(LED_PORT,LED1_PIN);
	_delay_ms(500);

	EF_S8_DIO_SetPin(LED_PORT,LED4_PIN);
	EF_S8_DIO_SetPin(LED_PORT,LED2_PIN);


	EF_void_LCD_Clear_Screen();

	EF_void_LCD_print((unsigned char *) " Test Done :)");
	_delay_ms(2000);

}

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

void EF_Green_Kit_Buzzer_test()
{

	EF_B_DIO_InitPin(BUZZER_PORT,BUZZER_PIN,OUTPUT);

	EF_S8_DIO_ClearPin(LED_PORT,BUZZER_PIN);

	EF_void_LCD_Clear_Screen();

	////////////////////////////////////////////
	EF_void_LCD_goto(1,1);
	EF_void_LCD_print(*(Data_lcd+10));

	_delay_ms(2000);

	EF_S8_DIO_SetPin(BUZZER_PORT,BUZZER_PIN);
	_delay_ms(1000);

	EF_S8_DIO_ClearPin(BUZZER_PORT,BUZZER_PIN);

	EF_void_LCD_Clear_Screen();

	EF_void_LCD_goto(1,1);
	EF_void_LCD_print((unsigned char *) "Test Done");
	_delay_ms(1000);
}

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
void EF_Green_Kit_7Seg_Test()
{
	unsigned int data  = 0;
	unsigned int data1 = 0;
	unsigned int fixed = 0;


	EF_void_Segment_Init();
	EF_void_LCD_Clear_Screen();

	EF_void_LCD_goto(1,1);
	EF_void_LCD_print(*(Data_lcd+12));
	while(1)
	{
		if(data1 > 25)
		{
			data+= 1111;
		}
		if(data % 1111 == 0 && data1 > 25)
		{
			fixed = data;
			data1=0;
		}
		data1++;

		EF_void_Segment_Display(fixed);
		//		if(data > 11110)
		if(data > 9999)
			break;
	}
	EF_void_LCD_Clear_Screen();

	EF_void_LCD_print((unsigned char *) "7SEG TESTED");
	_delay_ms(1200);
}
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
void EF_Green_Kit_ADC_Test()
{

	U16_t ADC_Value=0;

	EF_void_LCD_Clear_Screen();
	EF_void_LCD_goto(1,1);
	EF_void_LCD_print(*(Data_lcd+13));
	int index = 0;

	_delay_ms(2000);

	while(index < 12)
	{
		EF_void_LCD_Clear_Screen();
		EF_void_LCD_goto(1,1);
		EF_void_LCD_print((unsigned char *) "POTENTIOMETER ..");
		ADC_Value=EF_u16_ADC_read(ADC_POT_CHANL);

		EF_void_LCD_print_NUM(ADC_Value,2);
		_delay_ms(500);
		index ++ ;

	}
	EF_void_LCD_Clear_Screen();
	_delay_ms(2000);
	EF_void_LCD_print((unsigned char *) "POTEN TESTED");
	_delay_ms(1000);
}



void EF_Green_Kit_KeyPad_test()
{
	U8_t Keypress = 0;
	EF_void_KeyPad_Init();

	EF_void_LCD_Clear_Screen();
	EF_void_LCD_goto(1,1);
	EF_void_LCD_print((unsigned char *) "KEYPAD Testing");
	_delay_ms(2000);
	EF_void_LCD_Clear_Screen();
	EF_void_LCD_goto(1,1);
	EF_void_LCD_print((unsigned char *) *(Data_lcd+9));

	_delay_ms(2000);

	U8_t flag = 0;
	while(1)
	{

		Keypress = EF_u8_KeyPad_Scan();
		if(Keypress > 0 && flag == 0)
		{
			EF_void_LCD_goto(1,1);
			EF_void_LCD_print_NUM(Keypress , 2);
			flag = 1;
			if(Keypress==9)
			{
				break;
			}
		}
		else if (Keypress == 0 && flag == 1)
		{
			flag = 0;
		}
	}
	EF_void_LCD_Clear_Screen();
	EF_void_LCD_goto(1,1);
	EF_void_LCD_print((unsigned char *) "KEYPAD Done");

}
