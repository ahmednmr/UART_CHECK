/*
 * EF_Health_Care.c
 *
 *  Created on: 6 Oct 2015
 *      Author: EmbeddedFab
 */

#include"EF_Health_Care.h"

#define ADC_REF_VOLT 5000
#define RESISTOR_VALUE_DIV 9860
#define ADC_TEMP_PIN 7


volatile int rate[10];                    // used to hold last ten IBI values
volatile unsigned long sampleCounter = 0;          // used to determine pulse timing
volatile unsigned long lastBeatTime = 0;           // used to find the inter beat interval
volatile int P =512;                      // used to find peak in pulse wave
volatile int T = 512;                     // used to find trough in pulse wave
volatile int thresh = 512;                // used to find instant moment of heart beat
volatile int amp = 100;                   // used to hold amplitude of pulse waveform
volatile BOOLEAN firstBeat = TRUE;        // used to seed rate array so we startup with reasonable BPM
volatile BOOLEAN secondBeat = TRUE;       // used to seed rate array so we startup with reasonable BPM
volatile int BPM;                   // used to hold the pulse rate
volatile int Signal=0;                // holds the incoming raw data
volatile int IBI = 600;             // holds the time between beats, the Inter-Beat Interval
volatile BOOLEAN Pulse = FALSE;     // true when pulse wave is high, false when it's low
volatile BOOLEAN QS = FALSE;        // becomes true when Arduoino finds a beat.
volatile unsigned long runningTotal = 0;                   // clear the runningTotal variable
volatile int N =0;
volatile FP32 Temprature=0;
UART_cfg_str Uart_Paramters = {9600, 8, ONE_STOP_BIT, NO_PARITY,0,0,1,1};






void EF_Health_Care_system_int()
{

//	EF_void_ADC_init();
	EF_void_LCD_init();
//	EF_Timr0_Inter_Setup();
//	EF_void_UART_Init(&Uart_Paramters);
//	EF_B_DIO_InitPin('D',5,OUTPUT);
}




FP32 EF_Health_Care_Temp_Read(U8_t AdcPin)
{
	U16_t ADC_Value=0;
	FP32 RTH=0;
	FP32 voltage=0;
	FP32 celsius=0;
//	cli();

	ADC_Value=(EF_u16_ADC_read(ADC_TEMP_PIN));
	voltage = (((FP32)ADC_Value/1023)*ADC_REF_VOLT);

	RTH = ((RESISTOR_VALUE_DIV * voltage ) / (ADC_REF_VOLT - voltage));
	if (RTH >=1822.8) {
		// if temperature between 25ºC and 29.9ºC. R(tª)=6638.20457*(0.95768)^t
		celsius=log(RTH/6638.20457)/log(0.95768);
	} else {
		if (RTH >=1477.1){
			// if temperature between 30ºC and 34.9ºC. R(tª)=6403.49306*(0.95883)^t
			celsius=log(RTH/6403.49306)/log(0.95883);
		} else {
			if (RTH >=1204.8){
				// if temperature between 35ºC and 39.9ºC. R(tª)=6118.01620*(0.96008)^t
				celsius=log(RTH/6118.01620)/log(0.96008);
			}
			else{
				if (RTH >=988.1){
					// if temperature between 40ºC and 44.9ºC. R(tª)=5859.06368*(0.96112)^t
					celsius=log(RTH/5859.06368)/log(0.96112);
				}
				else {
					if (RTH >=811.7){
						// if temperature between 45ºC and 50ºC. R(tª)=5575.94572*(0.96218)^t
						celsius=log(RTH/5575.94572)/log(0.96218);
					}
				}
			}
		}
	}

	celsius=celsius*100;

	//	EF_void_LCD_print_NUM((U16_t)RTH,1);
//	sei();

	return celsius;
}







void EF_Health_Care_Heart_Pulse_Read(U8_t ADC_PIN)
{

	Signal = EF_u16_ADC_read(ADC_PIN);              // read the Pulse Sensor
	sampleCounter += 2;                         // keep track of the time in mS with this variable
	N = sampleCounter - lastBeatTime;       // monitor the time since the last beat to avoid noise

	//  find the peak and trough of the pulse wave

	// avoid dichrotic noise by waiting 3/5 of last IBI
	// T is the trough
	// keep track of lowest point in pulse wave
	if(Signal < thresh && N > (IBI/5)*3){
		if (Signal < T){
			T = Signal;
		}
	}

	// threshold condition helps avoid noise
	// P is the peak
	// keep track of highest point in pulse wave
	if(Signal > thresh && Signal > P){
		P = Signal;
	}




	//  NOW IT'S TIME TO LOOK FOR THE HEART BEAT
	// signal surges up in value every time there is a pulse

	if (N > 250){                                   // avoid high frequency noise
		if ( (Signal > thresh) && (Pulse == FALSE) && (N > (IBI/5)*3) ){
			Pulse = TRUE;                               // set the Pulse flag when we think there is a pulse
			EF_S8_DIO_ClearPin('D',5);              // turn on  LED
			IBI = sampleCounter - lastBeatTime;         // measure time between beats in mS
			lastBeatTime = sampleCounter;               // keep track of time for next pulse

			if(firstBeat){                         // if it's the first time we found a beat, if firstBeat == TRUE
				firstBeat = FALSE;                 // clear firstBeat flag
				return;                            // IBI value is unreliable so discard it
			}
			if(secondBeat){                        // if this is the second beat, if secondBeat == TRUE
				secondBeat = FALSE;                 // clear secondBeat flag
				for(int i=0; i<=9; i++){         // seed the running total to get a realisitic BPM at startup
					rate[i] = IBI;
				}
			}

			// keep a running total of the last 10 IBI values


			for(int i=0; i<=8; i++){                // shift data in the rate array
				rate[i] = rate[i+1];              // and drop the oldest IBI value
				runningTotal += rate[i];          // add up the 9 oldest IBI values
			}

			rate[9] = IBI;                          // add the latest IBI to the rate array
			runningTotal += rate[9];                // add the latest IBI to runningTotal
			runningTotal /= 10;                     // average the last 10 IBI values
			BPM = 60000/runningTotal;               // how many beats can fit into a minute? that's BPM!
			QS = TRUE;                              // set Quantified Self flag
			// QS FLAG IS NOT CLEARED INSIDE THIS ISR
		}
	}

	if (Signal < thresh && Pulse == TRUE){     // when the values are going down, the beat is over
		EF_S8_DIO_SetPin('D',5);              // turn on  LED
		Pulse = FALSE;                         // reset the Pulse flag so we can do it again
		amp = P - T;                           // get amplitude of the pulse wave
		thresh = amp/2 + T;                    // set thresh at 50% of the amplitude
		P = thresh;                            // reset these for next time
		T = thresh;
	}

	if (N > 2500){                             // if 2.5 seconds go by without a beat
		thresh = 512;                          // set thresh default
		P = 512;                               // set P default
		T = 512;                               // set T default
		lastBeatTime = sampleCounter;          // bring the lastBeatTime up to date
		firstBeat = TRUE;                      // set these to avoid noise
		secondBeat = TRUE;                     // when we get the heartbeat back
	}



}
void EF_Timr0_Inter_Setup(){
	//Prescaler = FCPU/1024
	TCCR0|=(1<<CS01)|(1<<CS00);
	//Enable Overflow Interrupt Enable
	TIMSK|=(1<<TOIE0);
	//Initialize Counter
	TCNT0=1;
	// MAKE SURE GLOBAL INTERRUPTS ARE ENABLED
	sei();
}


ISR(TIMER0_OVF_vect){                         // triggered when Timer2 counts to 124
	cli();
	EF_Health_Care_Heart_Pulse_Read(5);
	if (QS == TRUE){                       // Quantified Self flag is true when arduino finds a heartbeat


		Temprature=EF_Health_Care_Temp_Read(7);
		EF_void_UART_Send_data_temp(Temprature);

		EF_void_UART_Send_data_PBM(BPM);   // send heart rate with a 'B' prefix

		EF_void_UART_PutChar('\r');
		EF_void_UART_PutChar('\n');
		QS = FALSE;                      // reset the Quantified Self flag for next time
	}
	TIFR &= ~(1 << TOV0);
	TCNT0=1;
	sei();


}
