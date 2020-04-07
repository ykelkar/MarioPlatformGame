/*	Name & E-mail: Yash Kelkar		ykelk001@ucr.edu
 *	Lab Section: 25
 *	Assignment: Custom Lab LED Matrix  Exercise 2
 *	Exercise Description: This program is a system where an illuminated column of the LED matrix can be shifted left or right based on 
 *						  button presses. Two buttons control the system: One button shifts the illuminated column right. The other button 
 *						  shifts the illuminated column left. The illuminated row cannot be shifted off of the matrix. When both buttons 
 *						  pressed the program resets to only the first column being illuminated.
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 */


#include <avr/io.h>
#include <avr/interrupt.h>


// #define C4 261.63
// #define D4 293.66
// #define E4 329.63
// #define F4 349.23
// #define G4 392.00
// #define A4 440.00
// #define B4 493.88
// #define C5 523.25
// #define E7 2637.02
// #define C7 2093
// #define G7 3135.96
// #define G6 1567.98
// #define E6 1318.51
// #define A6 1760.00
// #define B6 1975.53
// #define AS6 1864.66
// #define A7 3520
// #define F7 2793.83
// #define C7 2093
// #define D7 2349.32
// #define F6 1396.91
// #define DS7 2489.02
// #define AS7 3729.31
// #define F5 698.46
// #define AS5 932.33
// #define DS6 1244.51
// #define D6 1174.66
// #define C6 1046.5
// #define GS7 3322.44
// #define FS7 2959.96
// #define B7 3951.07
// #define CS6 1108.73
// #define CS7 2217.46
// #define GS6 1661.22
// #define FS6 1479.98
// #define AS3 233.08
// #define AS4 466.16
// #define DS3 155.56
// #define DS4 311.13
// #define F3 174.61
// #define D3 146.83
// #define A3 220
// #define CS4 277.18
// #define GS3 207.65
// #define FS4 369.99
// #define GS4 415.3
// #define B3 246.94
// #define G3 196
// #define E3 164.81
// #define FS4	369.99
// #define B5 987.77
// #define D5 587.33
// #define CS5 554.37
// #define FS5 739.99
// #define A5 880
// #define GS5 830.61
// #define E5 659.25
// #define FS3 185
// 
// #define MAX_NOTES 213
// //Mario main theme melody
// double sm_array[MAX_NOTES] = {
// 	E7, E7, 0, E7,
// 	0, C7, E7, 0,
// 	G7, 0, 0,  0,
// 	G6, 0, 0, 0,
// 	
// 	C7, 0, 0, G6,
// 	0, 0, E6, 0,
// 	0, A6, 0, B6,
// 	0, AS6, A6, 0,
// 	
// 	G6, E7, G7,
// 	A7, 0, F7, G7,
// 	0, E7, 0, C7,
// 	D7, B6, 0, 0,
// 	
// 	C7, 0, 0, G6,
// 	0, 0, E6, 0,
// 	0, A6, 0, B6,
// 	0, AS6, A6, 0,
// 	
// 	G6, E7, G7,
// 	A7, 0, F7, G7,
// 	0, E7, 0, C7,
// 	D7, B6, 0, 0
// };
// 
// //Mario main them tempo
// unsigned char sm_time_array[MAX_NOTES] = {
// 	1, 1, 1, 1, 1, 1, 1, 1,
// 	1, 1, 1, 1, 1, 1, 1, 1,
// 	1, 1, 1, 1, 1, 1, 1, 1,
// 	1, 1, 1, 1, 1, 1, 1, 1,
// 	1, 1, 1, 1, 1, 1, 1, 1,
// 	1, 1 , 1, 1, 1, 1, 1, 1,
// 	1, 1, 1, 1, 1, 1,
// 	1, 1, 1, 1, 1, 1, 1, 1, 1,
// 	1, 1, 1, 1, 1, 1, 1, 1,
// 	1, 1, 1, 1, 1, 1, 1,
// };
// 
// unsigned char sm_wait_array[MAX_NOTES] = {1, 1, 1, 1, 1, 1, 1, 1,
// 	1, 1, 1, 1, 1, 1, 1, 1,
// 	1, 1, 1, 1, 1, 1, 1, 1,
// 	1, 1, 1, 1, 1, 1, 1, 1,
// 	1, 1, 1, 1, 1, 1, 1, 1,
// 	1, 1 , 1, 1, 1, 1, 1, 1,
// 	1, 1, 1, 1, 1, 1,
// 	1, 1, 1, 1, 1, 1, 1, 1, 1,
// 	1, 1, 1, 1, 1, 1, 1, 1,
// 	1, 1, 1, 1, 1, 1, 1,
// };
// 
// double underworld_array[] = {
// 	C4, C5, A3, A4,
// 	AS3, AS4, 0,
// 	0,
// 	C4, C5, A3, A4,
// 	AS3, AS4, 0,
// 	0,
// 	F3, F4, D3, D4,
// 	DS3, DS4, 0,
// 	0,
// 	F3, F4, D3, D4,
// 	DS3, DS4, 0,
// 	0, DS4, CS4, D4,
// 	CS4, DS4,
// 	DS4, GS3,
// 	G3, CS4,
// 	C4, FS4, F4, E3, AS4, A4,
// 	GS4, DS4, B3,
// 	AS3, A3, GS3,
// 	0, 0, 0
// };
// 
// unsigned char underworld_time_array[] = {
// 	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 , 1,
// 	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
// 	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
// 	1, 1, 1, 1, 1, 1, 1, 1, 1 ,1,
// 	1, 1, 1, 1, 1, 1, 1, 1,
// 	1, 1, 1, 1, 1, 1, 1, 1,
// 	1, 1, 1, 1, 1, 1, 1, 1,
// 	1, 1, 1, 1, 1, 1, 1, 1,
// 	1, 1, 1, 1, 1, 1, 1, 1,
// 	1, 1 , 1, 1, 1, 1, 1, 1,
// 	1, 1, 1, 1, 1, 1,
// 	1, 1, 1, 1, 1, 1, 1, 1, 1,
// 	1, 1, 1, 1, 1, 1, 1, 1,
// 	1, 1, 1, 1, 1, 1, 1,
// 	};
// unsigned char underworld_wait_array[] = {
// 	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 , 1,
// 	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
// 	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
// 	1, 1, 1, 1, 1, 1, 1, 1, 1 ,1,
// 	1, 1, 1, 1, 1, 1, 1, 1,
// 	1, 1, 1, 1, 1, 1, 1, 1,
// 	1, 1, 1, 1, 1, 1, 1, 1,
// 	1, 1, 1, 1, 1, 1, 1, 1,
// 	1, 1, 1, 1, 1, 1, 1, 1,
// 	1, 1 , 1, 1, 1, 1, 1, 1,
// 	1, 1, 1, 1, 1, 1,
// 	1, 1, 1, 1, 1, 1, 1, 1, 1,
// 	1, 1, 1, 1, 1, 1, 1, 1,
// 1, 1, 1, 1, 1, 1, 1,};

//unsigned char SONG1 = 0;
//unsigned char SONG2 = 0;
//unsigned char SONG3 = 0;
// unsigned char SONG4 = 0;
// unsigned char SONG5 = 0;
//unsigned char SONG7 = 0;

volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1. C programmer should clear to 0.

// Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
unsigned long _avr_timer_M = 1; // Start count from here, down to 0. Default 1 ms.
unsigned long _avr_timer_cntcurr = 0; // Current internal count of 1ms ticks

void TimerOn()
{
	// AVR timer/counter controller register TCCR1
	TCCR1B = 0x0B;// bit3 = 0: CTC mode (clear timer on compare)
	// bit2bit1bit0=011: pre-scaler /64
	// 00001011: 0x0B
	// SO, 8 MHz clock or 8,000,000 /64 = 125,000 ticks/s
	// Thus, TCNT1 register will count at 125,000 ticks/s

	// AVR output compare register OCR1A.
	OCR1A = 125;	// Timer interrupt will be generated when TCNT1==OCR1A
	// We want a 1 ms tick. 0.001 s * 125,000 ticks/s = 125
	// So when TCNT1 register equals 125,
	// 1 ms has passed. Thus, we compare to 125.
	// AVR timer interrupt mask register
	TIMSK1 = 0x02; // bit1: OCIE1A -- enables compare match interrupt

	//Initialize avr counter
	TCNT1=0;

	_avr_timer_cntcurr = _avr_timer_M;
	// TimerISR will be called every _avr_timer_cntcurr milliseconds

	//Enable global interrupts
	SREG |= 0x80; // 0x80: 1000000
}

void TimerOff()
{
	TCCR1B = 0x00; // bit3bit1bit0=000: timer off
}

void TimerISR()
{
	TimerFlag = 1;
}

// In our approach, the C programmer does not touch this ISR, but rather TimerISR()
ISR(TIMER1_COMPA_vect)
{
	// CPU automatically calls when TCNT1 == OCR1 (every 1 ms per TimerOn settings)
	_avr_timer_cntcurr--; // Count down to 0 rather than up to TOP
	if (_avr_timer_cntcurr == 0)
	{ // results in a more efficient compare
		TimerISR(); // Call the ISR that the user uses
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

// Set TimerISR() to tick every M ms
void TimerSet(unsigned long M)
{
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

void set_PWM(double frequency) {
	static double current_frequency; // Keeps track of the currently set frequency
	// Will only update the registers when the frequency changes, otherwise allows
	// music to play uninterrupted.
	if (frequency != current_frequency) {
		if (!frequency) { TCCR3B &= 0x08; } //stops timer/counter
		else { TCCR3B |= 0x03; } // resumes/continues timer/counter
		
		// prevents OCR3A from overflowing, using prescaler 64
		// 0.954 is smallest frequency that will not result in overflow
		if (frequency < 0.954) { OCR3A = 0xFFFF; }
		
		// prevents OCR0A from underflowing, using prescaler 64					// 31250 is largest frequency that will not result in underflow
		else if (frequency > 31250) { OCR3A = 0x0000; }
		
		// set OCR3A based on desired frequency
		else { OCR3A = (short)(8000000 / (128 * frequency)) - 1; }

		TCNT3 = 0; // resets counter
		current_frequency = frequency; // Updates the current frequency
	}
}

void PWM_on() {
	TCCR3A = (1 << COM3A0);
	// COM3A0: Toggle PB3 on compare match between counter and OCR0A
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	// WGM02: When counter (TCNT0) matches OCR0A, reset counter
	// CS01 & CS30: Set a prescaler of 64
	set_PWM(0);
}

void PWM_off()
{
	TCCR0A = 0x00;
	TCCR0B = 0x00;
}

unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}

void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are
	// in Free Running Mode, a new conversion will trigger
	// whenever the previous conversion completes.
}

void InitADC(void)
{
	ADMUX|=(1<<REFS0);
	ADCSRA|=(1<<ADEN)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2); //ENABLE ADC, PRESCALER 128
}
uint16_t readadc(uint8_t ch)
{
	ch&=0b00000111;         //ANDing to limit input to 7
	ADMUX = (ADMUX & 0xf8)|ch;  //Clear last 3 bits of ADMUX, OR with ch
	ADCSRA|=(1<<ADSC);        //START CONVERSION
	while((ADCSRA)&(1<<ADSC));    //WAIT UNTIL CONVERSION IS COMPLETE
	return(ADC);        //RETURN ADC VALUE
}


unsigned char j = 0x00;
unsigned long time_counter = 0x00;
unsigned char count = 0x00;
static unsigned char row[] = {0xFF, 0x1C, 0x08, 0x80, 0x40, 0x20, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x02}; // sets the pattern displayed on columns
static unsigned char col[] = {0x7F, 0xF7, 0xFB, 0x8F, 0x9F, 0xBF, 0x8F, 0x9F, 0xBF, 0xEF, 0xF7, 0xF7, 0xFB, 0xBF}; // grounds column to display pattern
	
/*									LEVEL ONE

								ooo		ooo									oooo
 o							oo				oo								oooo
ooo						o						o						oooooooooooo
		  o		o										o	o	o		oooooooooooo
		 oo		oo										o	o	o		oooo	oooo
		ooo		ooo										o	o	o		oooo	oooo
oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
*/

enum SM1_States {Init, First_Col, Second_Col, Third_Col, Fourth_Col, Fifth_Col, Sixth_Col, Seventh_Col, Eighth_Col, Ninth_Col, 
				Tenth_Col, Eleventh_Col, Twelfth_Col, Thirteenth_State} state;

void SM1_Tick() 
{
	switch (state)
	{
		case Init:
			state = First_Col;
			break;
			
		case First_Col:
			state = Second_Col;
			break;
			
		case Second_Col:
			state = Third_Col;
			break;
			
		
		case Third_Col:
			state = Fourth_Col;
			break;
			
		case Fourth_Col:
			state = Fifth_Col;
			break;
		
		case Fifth_Col:
			state = Sixth_Col;
			break;
		
		case Sixth_Col:
			if (count > 2) // this will be two off LEDs between the next pattern
			{
				state = Seventh_Col;	
			}
			else 
			{
				state = First_Col;
			}
			break;
			
		case Seventh_Col:
			if (count > 3) // this will be two off LEDs between the next pattern
			{
				state = Eighth_Col;
			}
			else
			{
				state = First_Col;
			}
			break;
			
		case Eighth_Col:
			if (count > 4) // this will be two off LEDs between the next pattern
			{
				state = Ninth_Col;
			}
			else
			{
				state = First_Col;
			}
			break;
			
		case Ninth_Col:
			if (count > 7)
			{
				state = Tenth_Col;
			}
			else 
			{
				state = First_Col;
			}
			break;
			
		case Tenth_Col:
			if (count > 9)
			{
				state = Eleventh_Col;
			}
			else
			{
				state = First_Col;
			}
			break;
			
		case Eleventh_Col:
			if (count > 10)
			{
				state = Twelfth_Col;
			}
			else 
			{
				state = First_Col;
			}
			break;
			
		case Twelfth_Col:
			if (count > 11)
			{
				state = Thirteenth_State;
			}
			else
			{
				state = First_Col;
			}
			break;
			
		case Thirteenth_State:
			state = First_Col;
			break;
			
		default:
			break;
	}
	switch (state)
	{
		case Init:
			j = 0;
			PORTC = row[j];
			PORTD = col[j];
			break;
			
		case First_Col:
			j = 0;
			PORTC = row[j];
			PORTD = col[j];
			break;
			
		case Second_Col:
			j = 1;
			PORTC = row[j];
			PORTD = col[j];
			break;
			
		case Third_Col:
			j = 2;
			PORTC = row[j];
			PORTD = col[j];
			break;
			
		case Fourth_Col:
			j = 3;
			PORTC = row[j];
			PORTD = col[j];
			break;
			
		case Fifth_Col:
			j = 4;
			PORTC = row[j];
			PORTD = col[j];
			break;
			
		case Sixth_Col:
			j = 5;
			PORTC = row[j];
			PORTD = col[j];
			break;
			
		case Seventh_Col:
			j = 6;
			PORTC = row[j];
			PORTD = col[j];
			break;
			
		case Eighth_Col:
			j = 7;
			PORTC = row[j];
			PORTD = col[j];
			break;
			
		case Ninth_Col:
			j = 8;
			PORTC = row[j];
			PORTD = col[j];
			break;
			
		case Tenth_Col:
			j = 9;
			PORTC = row[j];
			PORTD = col[j];
			break;
			
		case Eleventh_Col:
			j = 10;
			PORTC = row[j];
			PORTD = col[j];
			break;
			
		case Twelfth_Col:
			j = 11;
			PORTC = row[j];
			PORTD = col[j];
			break;
			
		case Thirteenth_State:
			j = 12;
			PORTC = row[j];
			PORTD = col[j];
			break;
			
		default:
			break;
	}
}

enum button_States {Init1, Set_Flag, Next} move_state;

unsigned char flag = 0x00;
void SM2_Tick()
{
	switch(move_state)
	{
		case Init:
			move_state = Set_Flag;
			break;
					
		case Set_Flag:
			move_state = Next;
			break;
			
		case Next:
			move_state = Next;
			break;
	}
	
	switch(move_state)
	{
		case Init1:
			break;
			
		case Set_Flag:
			if (((time_counter) % 1500 == 0)) //CHANGE BACK TO 1500
			{
				flag = 1;	
			}
			break;
			
		case Next:
			if (((time_counter) % 1500 == 0) && (flag == 1))
			{
				row[1] = row[1] >> 1; //Second_Col
				row[2] = row[2] >> 1; //Third_Col	 
				row[3] = row[3] >> 1; //Fourth_Col
				row[4] = row[4] >> 1; //Fifth_Col
				row[5] = row[5] >> 1; //Sixth
				
				if (count > 2) //Seventh_Col
				{
					row[6] = row[6] >> 1;
				}
				if (count > 3) //Eigth_Col
				{
					row[7] = row[7] >> 1;
				}
				if (count > 4) //Ninth_Col
				{
					row[8] = row[8] >> 1; 
				}
				if (count > 7) //Tenth_Col
				{
					row[9] = row[9] >> 1;
				}
				if (count > 9) //Eleventh_Col
				{
					row[10] = row[10] >> 1; 
				}
				if (count > 10) //Twelfth_Col
				{
					row[11] = row[11] >> 1;
				}
				if (count > 12)
				{
					row[12] = row[12] >> 1;
				}
				count++;
			}
			break;
	}
}

enum Mario_state {Init2, Display} mario_state;



void Mario_Tick()
{
	uint16_t x, y;
	
	switch(mario_state)
	{
		case Init2:
			mario_state = Display;
			break;
			
		case Display:
			mario_state = Display;
			break;
	}
	switch(mario_state)
	{
		case Init:
			PORTC = row[13];
			PORTD = col[13];
			break;
			
		case Display:
			x = readadc(0);
			y = readadc(1);
			
			if(y < 530) //DOWN
			{
				if (((time_counter % 300) == 0) && (col[13] != 0xBF))
				{
					col[13] = (col[13] << 1) | 0x01;
				}
				PORTC = row[13];
				PORTD = col[13];
			}
			else if (y > 600) //UP
			{
				if (((time_counter % 300) == 0) && (col[13] != 0xFE))
				{
					col[13] = (col[13] >> 1) | 0x80;
				}
				PORTC = row[13];
				PORTD = col[13];
			}
			else if(x < 530) //LEFT
			{
				if (((time_counter % 300) == 0) && (row[13] != 0x01))
				{
					row[13] = row[13] >> 1;				
				}
				PORTC = row[13];
				PORTD = col[13];
			}
			else if(x > 600) //RIGHT
			{
				if (((time_counter % 300) == 0) && (row[13] != 0x80))
				{
					row[13] = row[13] << 1;
				}
				PORTC = row[13];
				PORTD = col[13];
			}
			else
			{
				PORTC = row[13];
				PORTD = col[13];
			}
			
// 			;
// 			unsigned short adcval = ADC;
// 			if(adcval < 530)
// 			{
// 				if (((time_counter % 300) == 0) && (row[13] != 0x01))
// 				{
// 					row[13] = row[13] >> 1;	
// 				}
// 				PORTC = row[13];
// 				PORTD = col[13];
// 			}
// 			else if (adcval > 600)
// 			{
// 				if (((time_counter % 300) == 0) && (row[13] != 0x80))
// 				{
// 					row[13] = row[13] << 1;
// 				}
// 				PORTC = row[13];
// 				PORTD = col[13];
// 			}
// 			else
// 			{
// 				PORTC = row[13];
// 				PORTD = col[13];
// 			}
			break;
	}
}

// enum Song_state {WAIT, PLAY_NOTE, WAIT_NOTE, WAIT_PRESS, play_underworld, wait_underworld} song_state;
// 	
// void Song_Tick()
// {
// 	static unsigned char index = 0;
// 	static unsigned char cnt = 0;
// 	switch (song_state) { // Transitions
// 
// 		case WAIT:
// 			index = 0;
// 			cnt = 0;
// 			if (SONG1) {
// 				song_state = PLAY_NOTE;
// 				//SONG1 = 0;
// 			}
// 			else if (SONG2){
// 				song_state = play_underworld;
// 				//SONG2 = 0;
// 			}
// 			else {
// 				song_state = WAIT;
// 			}
// 			break;
// 
// 		case PLAY_NOTE:
// 			if (cnt < sm_time_array[index])
// 			{
// 				set_PWM(sm_array[index]);
// 				cnt++;
// 				song_state = PLAY_NOTE;
// 			}
// 			else {
// 				cnt = 0;
// 				/*if (index < MAX_NOTES -1){
// 					song_state = PLAY_NOTE;
// 					++index;
// 				}
// 				else{
// 					song_state = WAIT_PRESS;
// 				}*/
// 				song_state = WAIT_NOTE;
// 			}
// 			break;
// 
// 		case WAIT_NOTE:
// 			if (cnt < sm_wait_array[index]) {
// 				set_PWM(0);
// 				cnt++;
// 				song_state = WAIT_NOTE;
// 			}
// 			else {
// 				cnt = 0;
// 				if (sm_array[index] != '1') {
// 					index++;
// 					song_state = PLAY_NOTE;
// 				}
// 				else {
// 					SONG1 = 0;
// 					SONG7 = 1;
// 					song_state = WAIT;
// 				}
// 			}
// 			break;
// 
// 		case WAIT_PRESS:
// 			if (!GetBit(PINA, 0)) {
// 				song_state = WAIT_PRESS;
// 			}
// 			else {
// 				song_state = WAIT;
// 			}
// 			break;
// 
// 		case play_underworld:
// 			if (cnt < underworld_time_array[index])
// 			{
// 				set_PWM(underworld_array[index]);
// 				cnt++;
// 				song_state = play_underworld;
// 			}
// 			else {
// 				cnt = 0;
// 				/*if (index < MAX_NOTES -1){
// 					song_state = PLAY_NOTE;
// 					++index;
// 				}
// 				else{
// 					song_state = WAIT_PRESS;
// 				}*/
// 				song_state = wait_underworld;
// 			}
// 			break;
// 
// 		case wait_underworld:
// 		if (cnt < underworld_wait_array[index]) {
// 			set_PWM(0);
// 			cnt++;
// 			song_state = wait_underworld;
// 		}
// 		else {
// 			cnt = 0;
// 			if (underworld_array[index] != '1') {
// 				index++;
// 				song_state = play_underworld;
// 			}
// 			else {
// 				SONG2 = 0;
// 				SONG7 = 1;
// 				song_state = WAIT;
// 			}
// 		}
// 		break;
// 	}
// }

int main()
{
//	unsigned char button = 0x00;
//	unsigned char song_counter = 0x00;
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	
	TimerSet(1);
	TimerOn();
	
	//ADC_init();
	InitADC();
//	button = ~PINA & 0x03;
	while(1)
	{
		
// 		if (button == 0x01){
// 			SONG1 = 1;
// 		}
// 		if (button == 0x02){
// 			SONG2 = 1;
// 		}
// 		if (button == 0x00){
// 			SONG7 = 1;
// 
// 		}
		Mario_Tick();
		SM1_Tick();
		SM2_Tick();
		
// 		if (song_counter == 35)
// 		{
// 			Song_Tick();
// 			song_counter = 0;
// 		}
		while(!TimerFlag);
		TimerFlag = 0;
		time_counter++;
//		song_counter++;
	}
	return 0;	
}