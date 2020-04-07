/*	Name & E-mail: Yash Kelkar		ykelk001@ucr.edu
 *	Lab Section: 25
 *	Assignment: Custom Lab Project Super Mario
 *	Exercise Description: Super Mario is a two-dimensional platform game. The play controls Mario with a joystick controlling him by either moving left, moving right, 
 *						  diagonally right, diagonally left, or jumping straight up. The goal is the reach the castle at the end of the level which indicates that you 
 *						  have won and the game is over. 
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 */


#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.c"

unsigned char SONG1 = 0;

#define C4 261.63
#define D4 293.66
#define E4 329.63
#define F4 349.23
#define G4 392.00
#define A4 440.00
#define B4 493.88
#define C5 523.25
#define E7 2637.02
#define C7 2093
#define G7 3135.96
#define G6 1567.98
#define E6 1318.51
#define A6 1760.00
#define B6 1975.53
#define AS6 1864.66
#define A7 3520
#define F7 2793.83
#define C7 2093
#define D7 2349.32
#define F6 1396.91
#define DS7 2489.02
#define AS7 3729.31
#define F5 698.46
#define AS5 932.33
#define DS6 1244.51
#define D6 1174.66
#define C6 1046.5
#define GS7 3322.44
#define FS7 2959.96
#define B7 3951.07
#define CS6 1108.73
#define CS7 2217.46
#define GS6 1661.22
#define FS6 1479.98
#define AS3 233.08
#define AS4 466.16
#define DS3 155.56
#define DS4 311.13
#define F3 174.61
#define D3 146.83
#define A3 220
#define CS4 277.18
#define GS3 207.65
#define FS4 369.99
#define GS4 415.3
#define B3 246.94
#define G3 196
#define E3 164.81
#define FS4	369.99
#define B5 987.77
#define D5 587.33
#define CS5 554.37
#define FS5 739.99
#define A5 880
#define GS5 830.61
#define E5 659.25
#define FS3 185

#define MAX_NOTES 213
double sm_array[MAX_NOTES] = {E7, E7, 0, E7, 0, C7, E7, 0,
	G7, 0, 0, 0, G6, 0, 0, 0,
	
	C7, 0, 0, G6, 0, 0, E6, 0,
	0, A6, 0, B6, 0, AS6, A6, 0,
	
	G6, E7, G7, A7, 0, F7, G7, 0,
	E7, 0 , C7, D7, B6, 0, 0,
	
	C7, 0, 0, G6, 0, 0, E6,
	0, 0, A6, 0, B6, 0, AS6, A6, 0,
	
	G6, E7, G7, A7, 0, F7, G7, 0,
	E7, 0, C7, D7, B6, 0, 0,
	
	//underworld theme music
	C4, C5, A3, A4, AS3, AS4, 0, 0, C4, C5, A3, A4, AS3, AS4, 0 , 0,
	F3, F4, D3, D4, DS3, DS4, 0, 0, F3, F4, D3, D4, DS3, DS4, 0, 0,
	DS4, CS4, D4, CS4, DS4, DS4, GS3, G3, CS4, C4, FS4, F4, E3, AS4,
	A4, GS4, DS4, B3, AS3, A3, GS3, 0, 0 ,0,
	E7, E7, 0, E7, 0, C7, E7, 0,
	G7, 0, 0, 0, G6, 0, 0, 0,
	C7, 0, 0, G6, 0, 0, E6, 0,
	0, A6, 0, B6, 0, AS6, A6, 0,
	G6, E7, G7, A7, 0, F7, G7, 0,
	E7, 0 , C7, D7, B6, 0, 0, C7,
	0, 0, G6, 0, 0, E6,
	0, 0, A6, 0, B6, 0, AS6, A6, 0,
	G6, E7, G7, A7, 0, F7, G7, 0,
E7, 0, C7, D7, B6, 0, 0, 1};

unsigned char sm_time_array[MAX_NOTES] = {1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1 , 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1,
	//underworld theme music
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 , 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1 ,1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1 , 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1,
};

unsigned char sm_wait_array[MAX_NOTES] = {1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1 , 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1,
	//underworld theme music
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 , 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1 ,1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1 , 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1,
};

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
signed char count = 0x00;
static unsigned char row[] = {0xFF, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x02, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
							0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80}; // sets the pattern displayed on columns
static unsigned char col[] = {0x7F, 0xF7, 0xF3, 0xF7, 0xBF, 0x9F, 0x8F, 0x8F, 0x9F, 0xBF, 0xEF, 0xF7, 0xF7, 0xFB, 0xBF, 0xFB, 0xFB, 0xFB, 0xFB, 0xFB, 0xF7, 0xF7, 0xEF, 0x9F, 0x9F, 0x8F, 0x8F, 
							0x8F, 0x8F, 0xE3, 0xE3, 0x8F, 0x8F, 0x7F, 0xDF, 0xBB, 0xBF, 0xBB, 0xBF, 0xDF}; // grounds column to display pattern
							
// static unsigned char win_row[] = {0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
// static unsigned char win_col[] = {0x7F, 0xDF, 0xBB, 0xBF, 0xBB, 0xBF, 0xDF};
/*									LEVEL ONE

								ooo		ooo									oooo
 o							oo				oo								oooo
ooo						o						o						oooooooooooo
		  o		o										o	o	o		oooooooooooo
		 oo		oo										o	o	o		oooo	oooo
   o	ooo		ooo										o	o	o		oooo	oooo
oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
*/

unsigned char flag = 0x00;

enum SM1_States {Init, First_Col, Second_Col, Third_Col, Fourth_Col, Fifth_Col, Sixth_Col, Seventh_Col, Eighth_Col, Ninth_Col, 
				Tenth_Col, Eleventh_Col, Twelfth_Col, Thirteenth_Col, Fourteenth_Col, Fifteenth_Col, Sixteenth_Col, Seventeenth_Col, 
				Eighteenth_Col, Ninteenth_Col, Twentieth_Col, Twenty_First_Col, Twenty_Second_Col, Twenty_Third_Col, Twenty_Fourth_Col, 
				Twenty_Fifth_Col, Twenty_Sixth_Col,  Twenty_Seventh_Col,  Twenty_Eighth_Col,  Twenty_Ninth_Col, Thirtieth_Col, Thirty_First_Col,
				Thirty_Second_Col, Thirty_Third_Col, Thirty_Fourth_Col, Thirty_Fifth_Col, Thirty_Sixth_Col, Thirty_Seventh_Col, Thirty_Eighth_Col} state;

void SM1_Tick() //DISPLAYS GAME PLATFORM
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
			state = Seventh_Col;	
			break;
			
		case Seventh_Col:
			if (count > 2) // this will be two off LEDs between the next pattern
			{
				state = Eighth_Col;
			}
			else
			{
				state = First_Col;
			}
			break;
			
		case Eighth_Col:
			if (count > 3) // this will be two off LEDs between the next pattern
			{
				state = Ninth_Col;
			}
			else
			{
				state = First_Col;
			}
			break;
			
		case Ninth_Col:
			if (count > 4) // this will be two off LEDs between the next pattern
			{
				state = Tenth_Col;
			}
			else
			{
				state = First_Col;
			}
			break;
			
		case Tenth_Col:
			if (count > 7)
			{
				state = Eleventh_Col;
			}
			else 
			{
				state = First_Col;
			}
			break;
			
		case Eleventh_Col:
			if (count > 9)
			{
				state = Twelfth_Col;
			}
			else
			{
				state = First_Col;
			}
			break;
			
		case Twelfth_Col:
			if (count > 10)
			{
				state = Thirteenth_Col;
			}
			else 
			{
				state = First_Col;
			}
			break;
			
		case Thirteenth_Col:
			if (count > 12)
			{
				state = Fourteenth_Col;
			}
			else
			{
				state = First_Col;
			}
			break;
			
		case Fourteenth_Col:
			if (count > 13)
			{
				state = Fifteenth_Col;
			}
			else
			{
				state = First_Col;	
			}
			break;
			
		case Fifteenth_Col:
			if (count > 14)
			{
				state = Sixteenth_Col;
			}
			else
			{
				state = First_Col;
			}
			break;
		
		case Sixteenth_Col:
			if (count > 16)
			{
				state = Seventeenth_Col;
			}
			else
			{
				state = First_Col;
			}
			break;
			
		case Seventeenth_Col:
			if (count > 17)
			{
				state = Eighteenth_Col;
			}
			else
			{
				state = First_Col;
			}
			break;
			
		case Eighteenth_Col:
			if (count > 18)
			{
				state = Ninteenth_Col;
			}
			else
			{
				state = First_Col;
			}
			break;
		
		case Ninteenth_Col:
			if (count > 20)
			{
				state = Twentieth_Col;
			}
			else
			{
				state = First_Col;
			}
			break;
			
		case Twentieth_Col:
			if (count > 21)
			{
				state = Twenty_First_Col;
			}
			else 
			{
				state = First_Col;
			}
			break;
			
		case Twenty_First_Col:
			if (count > 23)
			{
				state = Twenty_Second_Col;
			}
			else
			{
				state = First_Col;	
			}
			break;
			
		case Twenty_Second_Col:
			if (count > 26)
			{
				state = Twenty_Third_Col;
			}
			else
			{
				state = First_Col;
			}
			break;
		
		case Twenty_Third_Col:
			if (count > 27)
			{
				state = Twenty_Fourth_Col;
			}
			else
			{
				state = First_Col;
			}
			break;
			
		case Twenty_Fourth_Col:
			if (count > 29)
			{
				state = Twenty_Fifth_Col;
			}
			else
			{
				state = First_Col;
			}
			break;
			
		case Twenty_Fifth_Col:
			if (count > 30)
			{
				state = Twenty_Sixth_Col;
			}
			else
			{
				state = First_Col;
			}
			break;
			
		case Twenty_Sixth_Col:
			if (count > 33)
			{
				state = Twenty_Seventh_Col;
			}
			else
			{
				state = First_Col;
			}
			break;
			
		case Twenty_Seventh_Col:
		if (count > 34)
		{
			state = Twenty_Eighth_Col;
		}
		else
		{
			state = First_Col;
		}
		break;
		
		case Twenty_Eighth_Col:
		if (count > 35)
		{
			state = Twenty_Ninth_Col;
		}
		else
		{
			state = First_Col;
		}
		break;
		
		case Twenty_Ninth_Col:
		if (count > 36)
		{
			state = Thirtieth_Col;
		}
		else
		{
			state = First_Col;
		}
		break;
		
		case Thirtieth_Col:
		if (count > 37)
		{
			state = Thirty_First_Col;
		}
		else
		{
			state = First_Col;
		}
		break;
		
		case Thirty_First_Col:
		if (count > 38)
		{
			state = Thirty_Second_Col;
		}
		else
		{
			state = First_Col;
		}
		break;
		
		case Thirty_Second_Col:
			if (count > 39)
			{
				state = Thirty_Third_Col;
			}
			else
			{
				state = First_Col;
			}
			break;
			
		case Thirty_Third_Col:
			if (count > 40)
			{
				state = Thirty_Fourth_Col;
			}
			else
			{
				state = First_Col;
			}
			break; 
		
		case Thirty_Fourth_Col:
			if (count > 41)
			{
				state = Thirty_Fifth_Col;
			}
			else
			{
				state = First_Col;
			}
			break;
		
		case Thirty_Fifth_Col:
			if (count > 42)
			{
				state = Thirty_Sixth_Col;
			}
			else
			{
				state = First_Col;
			}
			break;
		
		case Thirty_Sixth_Col:
			if (count > 43)
			{
				state = Thirty_Seventh_Col;
			}
			else
			{
				state = First_Col;
			}
			break;
		
		case Thirty_Seventh_Col:
			if (count > 44)
			{
				state = Thirty_Eighth_Col;
			}
			else
			{
				state = First_Col;
			}
			break;
		
		case Thirty_Eighth_Col:
			state = Thirty_Third_Col;
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
			
		case Thirteenth_Col:
			j = 12;
			PORTC = row[j];
			PORTD = col[j];
			break;
			
		case Fourteenth_Col:
			j = 13;
			PORTC = row[j];
			PORTD = col[j];
			break;
			
		case Fifteenth_Col:
			j = 15;
			PORTC = row[j];
			PORTD = col[j];
			break;
			
		case Sixteenth_Col:
			j = 16;
			PORTC = row[j];
			PORTD = col[j];
			break;
			
		case Seventeenth_Col:
			j = 17;
			PORTC = row[j];
			PORTD = col[j];
			break;
		
		case Eighteenth_Col:
			j = 18;
			PORTC = row[j];
			PORTD = col[j];
			break;
		
		case Ninteenth_Col:
			j = 19;
			PORTC = row[j];
			PORTD = col[j];
			break;
			
		case Twentieth_Col:
			j = 20;
			PORTC = row[j];
			PORTD = col[j];
			break;
		
		case Twenty_First_Col:
			j = 21;
			PORTC = row[j];
			PORTD = col[j];
			break;
		
		case Twenty_Second_Col:
			j = 22;
			PORTC = row[j];
			PORTD = col[j];
			break;
			
		case Twenty_Third_Col:
			j = 23;
			PORTC = row[j];
			PORTD = col[j];
			break;
			
		case Twenty_Fourth_Col:
			j = 24;
			PORTC = row[j];
			PORTD = col[j];
			break;
			
		case Twenty_Fifth_Col:
			j = 25;
			PORTC = row[j];
			PORTD = col[j];
			break;
			
		case Twenty_Sixth_Col:
			j = 26;
			PORTC = row[j];
			PORTD = col[j];
			break;
			
		case Twenty_Seventh_Col:
		j = 27;
		PORTC = row[j];
		PORTD = col[j];
		break;
		
		case Twenty_Eighth_Col:
		j = 28;
		PORTC = row[j];
		PORTD = col[j];
		break;
		
		case Twenty_Ninth_Col:
		j = 29;
		PORTC = row[j];
		PORTD = col[j];
		break;
		
		case Thirtieth_Col:
		j = 30;
		PORTC = row[j];
		PORTD = col[j];
		break;
		
		case Thirty_First_Col:
		j = 31;
		PORTC = row[j];
		PORTD = col[j];
		break;
		
		case Thirty_Second_Col:
		j = 32;
		PORTC = row[j];
		PORTD = col[j];
		break;
		
		case Thirty_Third_Col:
		j = 33;
		PORTC = row[j];
		PORTD = col[j];
		break;
		
		case Thirty_Fourth_Col:
		j = 34;
		PORTC = row[j];
		PORTD = col[j];
		break;
		
		case Thirty_Fifth_Col:
		j = 35;
		PORTC = row[j];
		PORTD = col[j];
		break;
		
		case Thirty_Sixth_Col:
		j = 36;
		PORTC = row[j];
		PORTD = col[j];
		break;
		
		case Thirty_Seventh_Col:
		j = 37;
		PORTC = row[j];
		PORTD = col[j];
		break;
		
		case Thirty_Eighth_Col:
		j = 38;
		PORTC = row[j];
		PORTD = col[j];
		break;
			
		default:
			break;
	}
}

enum button_States {Init1, Set_Flag, Next} move_state;

unsigned char yes = 0x00;
unsigned char ending = 0x00;
unsigned long score = 0x00;
unsigned char fall = 0x00;

// void Reset_Game()
// {
// 	row[1] = 0x04; row[2] = 0x08; row[3] = 0x10; row[4] = 0x20; row[5] = 0x40; row[6] = 0x80; row[7] = 0x80; row[8] = 0x80; row[9] = 0x80; row[10] = 0x80; row[11] = 0x80; 
// 	row[12] = 0x80; row[13] = 0x80; row[15] = 0x80; row[16] = 0x80; row[17] = 0x80; row[18] = 0x80; row[19] = 0x80; row[20] = 0x80; row[21] = 0x80; row[22] = 0x80; 
// 	row[23] = 0x80; row[24] = 0x80; row[25] = 0x80; row[26] = 0x80; row[27] = 0x80; row[28] = 0x80; row[29] = 0x80; row[30] = 0x80; row[31] = 0x80; row[32] = 0x80;
// 	row[14] = 0x02; col[14] = 0xBF;
// 	count = -1;
// }

// enum Win_States {Init3, Win_one, Win_two, Win_three, Win_four, Win_five, Win_six}  win_state;
// 
// unsigned char w = 0x00;
// 
// void Winner()
// {
// 	switch(win_state)
// 	{
// 		case Init3:
// 		state = Win_one;
// 		break;
// 		
// 		case Win_one:
// 		state = Win_two;
// 		break;
// 		
// 		case Win_two:
// 		state = Win_three;
// 		break;
// 		
// 		
// 		case Win_three:
// 		state = Win_four;
// 		break;
// 		
// 		case Win_four:
// 		state = Win_five;
// 		break;
// 		
// 		case Win_five:
// 		state = Win_six;
// 		break;
// 		
// 		case Win_six:
// 		state = Win_one;
// 		break;
// 	}
// 	
// 	switch(win_state)
// 	{
// 		case Init3:
// 		w = 0;
// 		PORTC = 0x00;
// 		PORTD = 0x00;
// 		break;
// 		
// 		case Win_one:
// 		w = 0;
// 		PORTC = win_row[w];
// 		PORTD = win_col[w];
// 		break;
// 		
// 		case Win_two:
// 		w = 1;
// 		PORTC = win_row[w];
// 		PORTD = win_col[w];
// 		break;
// 		
// 		case Win_three:
// 		w = 2;
// 		PORTC = win_row[w];
// 		PORTD = win_col[w];
// 		break;
// 		
// 		case Win_four:
// 		w = 3;
// 		PORTC = win_row[w];
// 		PORTD = win_col[w];
// 		break;
// 		
// 		case Win_five:
// 		w = 4;
// 		PORTC = win_row[w];
// 		PORTD = win_col[w];
// 		break;
// 		
// 		case Win_six:
// 		w = 5;
// 		PORTC = win_row[w];
// 		PORTD = win_col[w];
// 		break;
// 	}
// }
void shift_mario()
{
	if (((time_counter) % 1000 == 0) && (flag == 1) &&(ending < 6))
	{
		row[1] = row[1] >> 1; //Second_Col
		row[2] = row[2] >> 1; //Third_Col
		row[3] = row[3] >> 1; //Fourth_Col
		row[4] = row[4] >> 1; //Fifth_Col
		row[5] = row[5] >> 1; //Sixth
		row[6] = row[6] >> 1;
		
		if (count == 0)
		{
			if ((col[14] == 0xFB) && (row[14] == 0x04 >> count))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x10 >> count))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xBF) && (row[14] == 0x10 >> count))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xDF) && (row[14] == 0x20 >> count))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x40 >> count))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> count))
			{
				row[14] = row[14] >> 1;
			}
		}
		else if (count == 1)
		{
			if ((col[14] == 0xFB) && (row[14] == 0x04 >> count))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x10 >> count))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xBF) && (row[14] == 0x10 >> count))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xDF) && (row[14] == 0x20 >> count))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x40 >> count))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> count))
			{
				row[14] = row[14] >> 1;
			}
		}
		else if (count == 2)
		{
			if ((col[14] == 0xFB) && (row[14] == 0x04 >> count))
			{
				//Reset_Game();
				row[1] = 0x04; row[2] = 0x08; row[3] = 0x10; row[4] = 0x20; row[5] = 0x40; row[6] = 0x80;
				row[14] = 0x02; col[14] = 0xBF;
				count = -1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x10 >> count))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xBF) && (row[14] == 0x10 >> count))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xDF) && (row[14] == 0x20 >> count))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x40 >> count))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> count))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xBF) && (row[14] == 0x80))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xDF) && (row[14] == 0x80))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80))
			{
				row[14] = row[14] >> 1;
			}
		}
		else if (count == 3)
		{
			if ((col[14] == 0xFB) && (row[14] == 0x04 >> count))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x10 >> count))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xBF) && (row[14] == 0x10 >> count))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xDF) && (row[14] == 0x20 >> count))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x40 >> count))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> count))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 1))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 1))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 1))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80))
			{
				row[14] = row[14] >> 1;
			}
		}
		else if (count == 4)
		{
			if ((col[14] == 0xFB) && (row[14] == 0x04 >> count))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x10 >> count))
			{
				fall = 1;
			}
			else if ((col[14] == 0xBF) && (row[14] == 0x10 >> count))
			{
				row[1] = 0x04; row[2] = 0x08; row[3] = 0x10; row[4] = 0x20; row[5] = 0x40; row[6] = 0x80; row[7] = 0x80; row[8] = 0x80;
				row[14] = 0x02; col[14] = 0xBF;
				count = -1;
			}
			else if ((col[14] == 0xDF) && (row[14] == 0x20 >> count))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x40 >> count))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> count))
			{
				row[14] = row[14] >> 1;
			}	
			else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 2))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 2))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 2))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 1))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80))
			{
				row[14] = row[14] >> 1;
			}
		}
		else if (count == 5)
		{
			if ((col[14] == 0xDF) && (row[14] == 0x20 >> count))
			{
				row[1] = 0x04; row[2] = 0x08; row[3] = 0x10; row[4] = 0x20; row[5] = 0x40; row[6] = 0x80; row[7] = 0x80; row[8] = 0x80; row[9] = 0x80;
				row[14] = 0x02; col[14] = 0xBF;
				count = -1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x40 >> count))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> count))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 3))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 3))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 3))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 2))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 1))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xDF) && (row[14] == 0x80))
			{
				row[14] = row[14] >> 1;
			}
		}
		else if (count == 6)
		{
			if ((col[14] == 0xEF) && (row[14] == 0x40 >> count))
			{
				row[1] = 0x04; row[2] = 0x08; row[3] = 0x10; row[4] = 0x20; row[5] = 0x40; row[6] = 0x80; row[7] = 0x80; row[8] = 0x80; row[9] = 0x80; row[10] = 0x80;
				row[14] = 0x02; col[14] = 0xBF;
				count = -1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> count))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 4))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 4))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 4))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 3))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 2))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 1))
			{
				row[14] = row[14] >> 1;
			}
		}
		else if (count == 7)
		{
			if ((col[14] == 0xF7) && (row[14] == 0x80 >> count))
			{
				fall = 1;
			}
			else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 5))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 5))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 5))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 4))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 3))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 2))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80))
			{
				row[14] = row[14] >> 1;
			}
		}
		else if (count == 8)
		{
			if ((col[14] == 0xBF) && (row[14] == 0x80 >> 6))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 6))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 6))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 5))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 4))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 3))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 1))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80))
			{
				row[14] = row[14] >> 1;
			}
		}
		else if (count == 9)
		{
			if ((col[14] == 0xBF) && (row[14] == 0x80 >> 7))
			{
				row[1] = 0x04; row[2] = 0x08; row[3] = 0x10; row[4] = 0x20; row[5] = 0x40; row[6] = 0x80; row[7] = 0x80; row[8] = 0x80; row[9] = 0x80; row[10] = 0x80;
				row[11] = 0x80; row[12] = 0x80; row[13] = 0x80;
				row[14] = 0x02; col[14] = 0xBF;
				count = -1;
			}
			else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 7))
			{
				row[1] = 0x04; row[2] = 0x08; row[3] = 0x10; row[4] = 0x20; row[5] = 0x40; row[6] = 0x80; row[7] = 0x80; row[8] = 0x80; row[9] = 0x80; row[10] = 0x80;
				row[11] = 0x80; row[12] = 0x80; row[13] = 0x80;
				row[14] = 0x02; col[14] = 0xBF;
				count = -1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 7))
			{
				row[1] = 0x04; row[2] = 0x08; row[3] = 0x10; row[4] = 0x20; row[5] = 0x40; row[6] = 0x80; row[7] = 0x80; row[8] = 0x80; row[9] = 0x80; row[10] = 0x80;
				row[11] = 0x80; row[12] = 0x80; row[13] = 0x80;
				row[14] = 0x02; col[14] = 0xBF;
				count = -1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 6))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 5))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 4))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 2))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 1))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80))
			{
				row[14] = row[14] >> 1;
			}
		}
		else if (count == 10)
		{
			if ((col[14] == 0xBF) && (row[14] == 0x80 >> 8))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 8))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 8))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 7))
			{
				fall = 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 6))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 5))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 3))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 2))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 1))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80))
			{
				row[14] = row[14] >> 1;
			}
		}
		else if (count == 11)
		{
			if ((col[14] == 0xF7) && (row[14] == 0x80 >> 8))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 7))
			{
				fall = 1;
			}
			else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 6))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 4))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 3))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 2))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 1))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80))
			{
				row[14] = row[14] >> 1;
			}
		}
		else if (count == 12)
		{
			if ((col[14] == 0xEF) && (row[14] == 0x80 >> 8))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 7))
			{
				fall = 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 5))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 4))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 3))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 2))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 1))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80))
			{
				row[14] = row[14] >> 1;
			}
		}
		else if (count == 13)
		{
			if ((col[14] == 0xDF) && (row[14] == 0x80 >> 8))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 6))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 5))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 4))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 3))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 2))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 1))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80))
			{
				row[14] = row[14] >> 1;
			}
		}
		else if (count == 14)
		{
			if ((col[14] == 0xEF) && (row[14] == 0x80 >> 7))
			{
				fall = 1;
			}
			if ((col[14] == 0xF7) && (row[14] == 0x80 >> 6))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 5))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 4))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 3))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 2))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 1))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80))
			{
				row[14] = row[14] >> 1;
			}
		}
		else if (count == 15)
		{
			if ((col[14] == 0xEF) && (row[14] == 0x80 >> 8))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 7))
			{
				fall = 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 6))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 5))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 4))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 3))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 2))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 1))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80))
			{
				row[14] = row[14] >> 1;
			}
		}
		else if (count == 16)
		{
			if ((col[14] == 0xF7) && (row[14] == 0x80 >> 8))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 7))
			{
				fall = 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 6))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 5))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 4))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 3))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 2))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 1))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80))
			{
				row[14] = row[14] >> 1;
			}
		}
		else if (count == 17)
		{
			if ((col[14] == 0xF7) && (row[14] == 0x80 >> 8))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 7))
			{
				fall = 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 6))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 5))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 4))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 3))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 2))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 1))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80))
			{
				row[14] = row[14] >> 1;
			}
		}
		else if (count == 18)
		{
			if ((col[14] == 0xFB) && (row[14] == 0x80 >> 8))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 7))
			{
				fall = 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 6))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 5))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 4))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 3))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 2))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 1))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80))
			{
				row[14] = row[14] >> 1;
			}
		}
		else if (count == 19)
		{
			if ((col[14] == 0xFB) && (row[14] == 0x80 >> 8))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 7))
			{
				fall = 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 6))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 5))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 4))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 3))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 2))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 1))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80))
			{
				row[14] = row[14] >> 1;
			}
		}
		else if (count == 20)
		{
			if ((col[14] == 0xFB) && (row[14] == 0x80 >> 8))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 7))
			{
				fall = 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 6))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 5))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 4))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 3))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 2))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 1))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80))
			{
				row[14] = row[14] >> 1;
			}
		}
		else if (count == 21)
		{
			if ((col[14] == 0xFD) && (row[14] == 0x80 >> 8))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 7))
			{
				fall = 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 6))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 5))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 4))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 3))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 2))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 1))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80))
			{
				row[14] = row[14] >> 1;
			}
		}
		else if (count == 22)
		{
			if ((col[14] == 0xFD) && (row[14] == 0x80 >> 8))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 7))
			{
				fall = 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 6))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 5))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 4))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 3))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 2))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 1))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80))
			{
				row[14] = row[14] >> 1;
			}
		}
		else if (count == 23)
		{
			if ((col[14] == 0xFD) && (row[14] == 0x80 >> 8))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 7))
			{
				fall = 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 6))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 5))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 4))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 3))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 2))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 1))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80))
			{
				row[14] = row[14] >> 1;
			}
		}
		else if (count == 24)
		{
			if ((col[14] == 0xFB) && (row[14] == 0x80 >> 8))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 7))
			{
				fall = 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 6))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 5))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 4))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 3))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 2))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 1))
			{
				row[14] = row[14] >> 1;
			}
		}
		else if (count == 25)
		{
			if ((col[14] == 0xFD) && (row[14] == 0x80 >> 8))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 7))
			{
				fall = 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 6))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 5))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 4))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 3))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 2))
			{
				row[14] = row[14] >> 1;
			}
		}
		else if (count == 26)
		{
			if ((col[14] == 0xFD) && (row[14] == 0x80 >> 8))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 7))
			{
				fall = 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 6))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 5))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 4))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 3))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xBF) && (row[14] == 0x80))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xBF) && (row[14] == 0x80))
			{
				row[14] = row[14] >> 1;
			}
		}
		else if (count == 27)
		{
			if ((col[14] == 0xFD) && (row[14] == 0x80 >> 8))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 7))
			{
				fall = 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 6))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 5))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 4))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 1))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 1))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80))
			{
				row[14] = row[14] >> 1;
			}
		}
		else if (count == 28)
		{
			if ((col[14] == 0xFB) && (row[14] == 0x80 >> 8))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 7))
			{
				fall = 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 6))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 5))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 2))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 2))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 1))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80))
			{
				row[14] = row[14] >> 1;
			}
		}
		else if (count == 29)
		{
			if ((col[14] == 0xFB) && (row[14] == 0x80 >> 8))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 7))
			{
				fall = 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 6))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 3))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 3))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 2))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 1))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xBF) && (row[14] == 0x80))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xDF) && (row[14] == 0x80))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80))
			{
				row[14] = row[14] >> 1;
			}
		}
		else if (count == 30)
		{
			if ((col[14] == 0xF7) && (row[14] == 0x80 >> 8))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 7))
			{
				fall = 1;
			}
			else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 4))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 4))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 3))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 2))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 1))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 1))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 1))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80))
			{
				row[14] = row[14] >> 1;
			}
		}
		else if (count == 31)
		{
			if ((col[14] == 0xF7) && (row[14] == 0x80 >> 8))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 5))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 5))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 4))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 3))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 2))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 2))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 2))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 1))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80))
			{
				row[14] = row[14] >> 1;
			}
		}
		else if (count == 32)
		{
			if ((col[14] == 0xBF) && (row[14] == 0x80 >> 6))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 6))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 5))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 4))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 3))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 3))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 3))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 2))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 1))
			{
				row[14] = row[14] >> 1;
			}
		}
		else if (count == 33)
		{
			if ((col[14] == 0xBF) && (row[14] == 0x80 >> 7))
			{
				row[1] = 0x04; row[2] = 0x08; row[3] = 0x10; row[4] = 0x20; row[5] = 0x40; row[6] = 0x80; row[7] = 0x80; row[8] = 0x80; row[9] = 0x80; row[10] = 0x80;
				row[11] = 0x80; row[12] = 0x80; row[13] = 0x80; row[15] = 0x80; row[16] = 0x80; row[17] = 0x80; row[18] = 0x80; row[19] = 0x80; row[20] = 0x80; row[21] = 0x80; 
				row[22] = 0x80; row[23] = 0x80; row[24] = 0x80; row[25] = 0x80; row[26] = 0x80; row[27] = 0x80; row[28] = 0x80; row[29] = 0x80; row[30] = 0x80; row[31] = 0x80; 
				row[32] = 0x80;
				row[14] = 0x02; col[14] = 0xBF;
				count = -1;
			}
			else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 7))
			{
				row[1] = 0x04; row[2] = 0x08; row[3] = 0x10; row[4] = 0x20; row[5] = 0x40; row[6] = 0x80; row[7] = 0x80; row[8] = 0x80; row[9] = 0x80; row[10] = 0x80;
				row[11] = 0x80; row[12] = 0x80; row[13] = 0x80; row[15] = 0x80; row[16] = 0x80; row[17] = 0x80; row[18] = 0x80; row[19] = 0x80; row[20] = 0x80; row[21] = 0x80;
				row[22] = 0x80; row[23] = 0x80; row[24] = 0x80; row[25] = 0x80; row[26] = 0x80; row[27] = 0x80; row[28] = 0x80; row[29] = 0x80; row[30] = 0x80; row[31] = 0x80;
				row[32] = 0x80;
				row[14] = 0x02; col[14] = 0xBF;
				count = -1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 6))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 5))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 4))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 4))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 4))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 3))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 2))
			{
				row[14] = row[14] >> 1;
			}
		}
		else if (count == 34)
		{
			if ((col[14] == 0xBF) && (row[14] == 0x80 >> 8))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 8))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 7))
			{
				fall = 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 6))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 5))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 5))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 5))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 4))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 3))
			{
				row[14] = row[14] >> 1;
			}
		}
		else if (count == 35)
		{
			if ((col[14] == 0xEF) && (row[14] == 0x80 >> 8))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 7))
			{
				fall = 1;
			}
			else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 6))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 6))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 6))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 5))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 4))
			{
				row[14] = row[14] >> 1;
			}
		}
		else if (count == 36)
		{
			if ((col[14] == 0xEF) && (row[14] == 0x80 >> 8))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 7))
			{
				row[1] = 0x04; row[2] = 0x08; row[3] = 0x10; row[4] = 0x20; row[5] = 0x40; row[6] = 0x80; row[7] = 0x80; row[8] = 0x80; row[9] = 0x80; row[10] = 0x80;
				row[11] = 0x80; row[12] = 0x80; row[13] = 0x80; row[15] = 0x80; row[16] = 0x80; row[17] = 0x80; row[18] = 0x80; row[19] = 0x80; row[20] = 0x80; row[21] = 0x80;
				row[22] = 0x80; row[23] = 0x80; row[24] = 0x80; row[25] = 0x80; row[26] = 0x80; row[27] = 0x80; row[28] = 0x80; row[29] = 0x80; row[30] = 0x80; row[31] = 0x80;
				row[32] = 0x80;
				row[14] = 0x02; col[14] = 0xBF;
				count = -1;
			}
			else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 7))
			{
				row[1] = 0x04; row[2] = 0x08; row[3] = 0x10; row[4] = 0x20; row[5] = 0x40; row[6] = 0x80; row[7] = 0x80; row[8] = 0x80; row[9] = 0x80; row[10] = 0x80;
				row[11] = 0x80; row[12] = 0x80; row[13] = 0x80; row[15] = 0x80; row[16] = 0x80; row[17] = 0x80; row[18] = 0x80; row[19] = 0x80; row[20] = 0x80; row[21] = 0x80;
				row[22] = 0x80; row[23] = 0x80; row[24] = 0x80; row[25] = 0x80; row[26] = 0x80; row[27] = 0x80; row[28] = 0x80; row[29] = 0x80; row[30] = 0x80; row[31] = 0x80;
				row[32] = 0x80;
				row[14] = 0x02; col[14] = 0xBF;
				count = -1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 7))
			{
				row[1] = 0x04; row[2] = 0x08; row[3] = 0x10; row[4] = 0x20; row[5] = 0x40; row[6] = 0x80; row[7] = 0x80; row[8] = 0x80; row[9] = 0x80; row[10] = 0x80;
				row[11] = 0x80; row[12] = 0x80; row[13] = 0x80; row[15] = 0x80; row[16] = 0x80; row[17] = 0x80; row[18] = 0x80; row[19] = 0x80; row[20] = 0x80; row[21] = 0x80;
				row[22] = 0x80; row[23] = 0x80; row[24] = 0x80; row[25] = 0x80; row[26] = 0x80; row[27] = 0x80; row[28] = 0x80; row[29] = 0x80; row[30] = 0x80; row[31] = 0x80;
				row[32] = 0x80;
				row[14] = 0x02; col[14] = 0xBF;
				count = -1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 6))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 5))
			{
				row[14] = row[14] >> 1;
			}
		}
		else if (count == 37)
		{
			if ((col[14] == 0xBF) && (row[14] == 0x80 >> 8))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 8))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 8))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 7))
			{
				fall = 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 6))
			{
				row[14] = row[14] >> 1;
			}
		}
		else if (count == 38)
		{
			if ((col[14] == 0xF7) && (row[14] == 0x80 >> 8))
			{
				row[14] = row[14] >> 1;
			}
			else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 7))
			{
				fall = 1;
			}
		}
		else if (count == 39)
		{
			if ((col[14] == 0xF7) && (row[14] == 0x80 >> 8))
			{
				row[14] = row[14] >> 1;
			}
		}
		if (count > 2) //Seventh_Col
		{
			row[7] = row[7] >> 1;
		}
		if (count > 3) //Eigth_Col
		{
			row[8] = row[8] >> 1;
		}
		if (count > 4) //Ninth_Col
		{
			row[9] = row[9] >> 1;
		}
		if (count > 7) //Tenth_Col
		{
			row[10] = row[10] >> 1;
		}
		if (count > 9) //Eleventh_Col
		{
			row[11] = row[11] >> 1;
		}
		if (count > 10) //Twelfth_Col
		{
			row[12] = row[12] >> 1;
		}
		if (count > 12)
		{
			row[13] = row[13] >> 1;
		}
		if (count > 13)
		{
			row[15] = row[15] >> 1;
		}
		if (count > 14)
		{
			row[16] = row[16] >> 1;
		}
		if (count > 16)
		{
			row[17] = row[17] >> 1;
		}
		if (count > 17)
		{
			row[18] = row[18] >> 1;
		}
		if (count > 18)
		{
			row[19] = row[19] >> 1;
		}
		if (count > 20)
		{
			row[20] = row[20] >> 1;
		}
		if (count > 21)
		{
			row[21] = row[21] >> 1;
		}
		if (count > 23)
		{
			row[22] = row[22] >> 1;
		}
		if (count > 26)
		{
			row[23] = row[23] >> 1;
		}
		if (count > 27)
		{
			row[24] = row[24] >> 1;
		}
		if (count > 29)
		{
			row[25] = row[25] >> 1;
		}
		if (count > 30)
		{
			row[26] = row[26] >> 1;
		}
		if (count > 33)
		{
			row[27] = row[27] >> 1;
			ending++;
		}
		if (count > 34)
		{
			row[28] = row[28] >> 1;
		}
		if (count > 35)
		{
			row[29] = row[29] >> 1;
		}
		if (count > 36)
		{
			row[30] = row[30] >> 1;
		}
		if (count > 37)
		{
			row[31] = row[31] >> 1;
		}
		if (count > 38)
		{
			row[32] = row[32] >> 1;
		}
		count++;
	}
}

//unsigned char button = 0x00;

void SM2_Tick() //SHIFTS GAME PLATFORM
{
	//button = ~PINB & 0x01;
	switch(move_state)
	{
		case Init1:
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
			flag = 0;
			count = 0;
			break;
			
		case Set_Flag:
			if ((time_counter) % 1000 == 0) //CHANGE BACK TO 1500
			{
// 				if (button == 0x01)
// 				{
					flag = 1;
				//}	
			}
// 			if (yes > 0)
// 			{
// 				flag = 1;
// 			}
			break;
			
		case Next:
			shift_mario();
			break;
	}
}

enum Mario_state {Init2, Display, Jump_Up, Fall_Down, Left, Right, Jump_Up_Right, Jump_Up_Left} mario_state; 

unsigned char mario_counter = 0x00;
unsigned char i = 0x00;

void Mario_Tick() //CONTROLS ONE LED WHICH IS "MARIO"
{
	uint16_t x, y;
	
	switch(mario_state)
	{
		case Init2:
			mario_state = Display;
			break;
			
		case Display:
		x = readadc(0);
		y = readadc(1);
		if (y > 600) //Jump_Up
		{
			if (x > 575)
			{
				mario_state = Jump_Up_Right;
			}
			else if (x < 500)
			{
				mario_state = Jump_Up_Left;
			}
			else
			{
				mario_state = Jump_Up;
			}
		}
		else if (fall == 1) //Fall_Down
		{
			fall = 0;
			mario_state = Fall_Down;
		}
		else if (x < 530) //LEFT
		{
			if (count == 0)
			{
				if ((col[14] == 0xFB) && (row[14] == 0x10))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Left;
				}
			}
			else if (count == 1)
			{
				if ((col[14] == 0xFB) && (row[14] == 0x10 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xBF) && (row[14] == 0x80))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Left;
				}
			}
			else if (count == 2)
			{
				if ((col[14] == 0xFB) && (row[14] == 0x10 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 1))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Left;
				}
			}
			else if (count == 3)
			{
				if ((col[14] == 0xFB) && (row[14] == 0x10 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 2))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Left;
				}
			}
			else if (count == 4)
			{
				if ((col[14] == 0xFB) && (row[14] == 0x10 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 3))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x80))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Left;
				}
			}
			else if (count == 5)
			{
				if ((col[14] == 0xFB) && (row[14] == 0x10 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 4))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 1))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xDF) && (row[14] == 0x80))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Left;
				}
			}
			else if (count == 6)
			{
				if ((col[14] == 0xFB) && (row[14] == 0x10 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 5))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 2))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 1))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xBF) && (row[14] == 0x80))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Left;
				}
			}
			else if (count == 7)
			{
				if ((col[14] == 0xFB) && (row[14] == 0x10 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 6))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 3))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 2))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 1))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Left;
				}
			}
			else if (count == 8)
			{
				if ((col[14] == 0xFB) && (row[14] == 0x10 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 7))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 4))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 3))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 2))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Left;
				}
			}
			else if (count == 9)
			{
				if ((col[14] == 0xBF) && (row[14] == 0x80 >> 8))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 5))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 4))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 3))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Left;
				}
			}
			else if (count == 10)
			{
				if ((col[14] == 0xEF) && (row[14] == 0x80 >> 6))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 5))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 4))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Left;
				}
			}
			else if (count == 11)
			{
				if ((col[14] == 0xEF) && (row[14] == 0x80 >> 7))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 6))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 5))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Left;
				}
			}
			else if (count == 12)
			{
				if ((col[14] == 0xEF) && (row[14] == 0x80 >> 8))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 7))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 6))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Left;
				}
			}
			else if (count == 13)
			{
				if ((col[14] == 0xDF) && (row[14] == 0x80 >> 8))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 7))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Left;
				}
			}
			else if (count == 14)
			{
				if ((col[14] == 0xBF) && (row[14] == 0x80 >> 8))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Left;
				}
			}
			else if (count == 29)
			{
				if ((col[14] == 0xBF) && (row[14] == 0x80))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Left;
				}
			}
			else if (count == 30)
			{
				if ((col[14] == 0xBF) && (row[14] == 0x80 >> 1))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Left;
				}
			}
			else if (count == 31)
			{
				if ((col[14] == 0xBF) && (row[14] == 0x80 >> 2))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Left;
				}
			}
			else if (count == 32)
			{
				if ((col[14] == 0xBF) && (row[14] == 0x80 >> 3))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xBF) && (row[14] == 0x80))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Left;
				}
			}
			else if (count == 33)
			{
				if ((col[14] == 0xBF) && (row[14] == 0x80 >> 4))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 1))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Left;
				}
			}
			else if (count == 34)
			{
				if ((col[14] == 0xBF) && (row[14] == 0x80 >> 5))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 2))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Left;
				}
			}
			else if (count == 35)
			{
				if ((col[14] == 0xBF) && (row[14] == 0x80 >> 6))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 3))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Left;
				}
			}
			else if (count == 36)
			{
				if ((col[14] == 0xBF) && (row[14] == 0x80 >> 7))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 4))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Left;
				}
			}
			else if (count == 37)
			{
				if ((col[14] == 0xBF) && (row[14] == 0x80 >> 8))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xBF) && (row[14] == 0x80 >> 5))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Left;
				}
			}
			else if (count == 38)
			{
				if ((col[14] == 0xBF) && (row[14] == 0x80 >> 6))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Left;
				}
			}
			else if (count == 39)
			{
				if ((col[14] == 0xBF) && (row[14] == 0x80 >> 7))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Left;
				}
			}
			else if (count == 40)
			{
				if ((col[14] == 0xBF) && (row[14] == 0x80 >> 8))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Left;
				}
			}
			else
			{
				mario_state = Left;
			}
		}
		else if (x > 600) //RIGHT
		{
			if (count == 0)
			{
				if ((col[14] == 0xFB) && (row[14] == 0x04))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xBF) && (row[14] == 0x10))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xDF) && (row[14] == 0x20))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x40))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Right;
				}
			}
			else if (count == 1)
			{
				if ((col[14] == 0xFB) && (row[14] == 0x04 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xBF) && (row[14] == 0x10 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xDF) && (row[14] == 0x20 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x40 >> count))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Right;
				}
			}
			else if (count == 2)
			{
				if ((col[14] == 0xFB) && (row[14] == 0x04 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xBF) && (row[14] == 0x10 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xDF) && (row[14] == 0x20 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x40 >> count))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Right;
				}
			}
			else if (count == 3)
			{
				if ((col[14] == 0xBF) && (row[14] == 0x10 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xDF) && (row[14] == 0x20 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x40 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xBF) && (row[14] == 0x40))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Right;
				}
			}
			else if (count == 4)
			{
				if ((col[14] == 0xBF) && (row[14] == 0x10 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xDF) && (row[14] == 0x20 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x40 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xBF) && (row[14] == 0x40 >> 1))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Right;
				}
			}
			else if (count == 5)
			{
				if ((col[14] == 0xBF) && (row[14] == 0x10 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xDF) && (row[14] == 0x20 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x40 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xBF) && (row[14] == 0x40 >> 2))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Right;
				}
			}
			else if (count == 6)
			{
				if ((col[14] == 0xBF) && (row[14] == 0x10 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xDF) && (row[14] == 0x20 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x40 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xBF) && (row[14] == 0x40 >> 3))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Right;
				}
			}
			else if (count == 7)
			{
				if ((col[14] == 0xBF) && (row[14] == 0x10 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xDF) && (row[14] == 0x20 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x40 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xBF) && (row[14] == 0x40 >> 4))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Right;
				}
			}
			else if (count == 8)
			{
				if ((col[14] == 0xBF) && (row[14] == 0x10 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xDF) && (row[14] == 0x20 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x40 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xBF) && (row[14] == 0x40 >> 5))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Right;
				}
			}
			else if (count == 9)
			{
				if ((col[14] == 0xBF) && (row[14] == 0x40 >> 6))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Right;
				}
			}
			else if (count == 10)
			{
				if ((col[14] == 0xBF) && (row[14] == 0x40 >> 7))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Right;
				}
			}
			else if (count == 11)
			{
				if ((col[14] == 0xBF) && (row[14] == 0x40 >> 8))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Right;
				}
			}
			else if (count == 27)
			{
				if ((col[14] == 0xBF) && (row[14] == 0x40))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Right;
				}
			}
			else if (count == 28)
			{
				if ((col[14] == 0xBF) && (row[14] == 0x40 >> 1))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Right;
				}
			}
			else if (count == 29)
			{
				if ((col[14] == 0xBF) && (row[14] == 0x40 >> 2))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xBF) && (row[14] == 0x40))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Right;
				}
			}
			else if (count == 30)
			{
				if ((col[14] == 0xBF) && (row[14] == 0x40 >> 3))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xBF) && (row[14] == 0x40 >> 1))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Right;
				}
			}
			else if (count == 31)
			{
				if ((col[14] == 0xBF) && (row[14] == 0x40 >> 4))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xBF) && (row[14] == 0x40 >> 2))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Right;
				}
			}
			else if (count == 32)
			{
				if ((col[14] == 0xBF) && (row[14] == 0x40 >> 5))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xBF) && (row[14] == 0x40 >> 3))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Right;
				}
			}
			else if (count == 33)
			{
				if ((col[14] == 0xBF) && (row[14] == 0x40 >> 6))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xBF) && (row[14] == 0x40 >> 4))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Right;
				}
			}
			else if (count == 34)
			{
				if ((col[14] == 0xBF) && (row[14] == 0x40 >> 7))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xBF) && (row[14] == 0x40 >> 5))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Right;
				}
			}
			else if (count == 35)
			{
				if ((col[14] == 0xBF) && (row[14] == 0x40 >> 8))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xBF) && (row[14] == 0x40 >> 6))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Right;
				}
			}
			else if (count == 36)
			{
				if ((col[14] == 0xBF) && (row[14] == 0x40 >> 7))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Right;
				}
			}
			else if (count == 37)
			{
				if ((col[14] == 0xBF) && (row[14] == 0x40 >> 6))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Right;
				}
			}
			else 
			{
				mario_state = Right;
			}
		}
// 		else if ((y > 600) && (x < 530))
// 		{
// 			mario_state = Jump_Up_Left;
// 		}
// 		else if ((y > 575) && (x > 575))
// 		{
// 			mario_state = Jump_Up_Right;
// 		}
		else
		{
			mario_state = Display;
		}
		break;
		
		case Jump_Up:
			if ((i < 4) && (col[14] != 0xFE))
			{
				if (count == 0)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x04))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x08))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x10))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up;
					}
				}
				else if (count == 1)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x04 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x08 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x10 >> count))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up;
					}
				}
				else if (count == 2)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x04 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x08 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x10 >> count))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up;
					}
				}
				else if (count == 3)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x04 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x08 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x10 >> count))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up;
					}
				}
				else if (count == 4)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x04 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x08 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x10 >> count))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up;
					}
				}
				else if (count == 5)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x04 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x08 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x10 >> count))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up;
					}
				}
				else if (count == 6)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x04 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x08 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x10 >> count))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up;
					}
				}
				else if (count == 7)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x04 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x08 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x10 >> count))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up;
					}
				}
				else if (count == 8)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x04 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x08 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x10 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x80))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up;
					}
				}
				else if (count == 9)
				{
					if ((col[14] == 0xDF) && (row[14] == 0x80 >> 1))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up;
					}
				}
				else if (count == 10)
				{
					if ((col[14] == 0xDF) && (row[14] == 0x80 >> 2))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up;
					}
				}
				else if (count == 11)
				{
					if ((col[14] == 0xDF) && (row[14] == 0x80 >> 3))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 1))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up;
					}
				}
				else if (count == 12)
				{
					if ((col[14] == 0xDF) && (row[14] == 0x80 >> 4))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 2))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 1))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up;
					}
				}
				else if (count == 13)
				{
					if ((col[14] == 0xDF) && (row[14] == 0x80 >> 5))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 3))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 2))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up;
					}
				}
				else if (count == 14)
				{
					if ((col[14] == 0xDF) && (row[14] == 0x80 >> 6))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 4))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 3))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 1))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up;
					}
				}
				else if (count == 15)
				{
					if ((col[14] == 0xDF) && (row[14] == 0x80 >> 7))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 5))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 4))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 2))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 1))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up;
					}
				}
				else if (count == 16)
				{
					if ((col[14] == 0xDF) && (row[14] == 0x80 >> 8))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 6))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 5))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 3))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 2))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 1))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up;
					}
				}
				else if (count == 17)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x80 >> 7))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 6))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 4))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 3))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 2))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up;
					}
				}
				else if (count == 18)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x80 >> 8))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 7))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 5))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 4))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 3))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 1))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up;
					}
				}
				else if (count == 19)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x80 >> 8))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 6))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 5))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 4))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 2))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 1))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up;
					}
				}
				else if (count == 20)
				{
					if ((col[14] == 0xF7) && (row[14] == 0x80 >> 7))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 6))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 5))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 3))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 2))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 1))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up;
					}
				}
				else if (count == 21)
				{
					if ((col[14] == 0xF7) && (row[14] == 0x80 >> 8))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 7))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 6))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 4))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 3))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 2))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up;
					}
				}
				else if (count == 22)
				{
					if ((col[14] == 0xF7) && (row[14] == 0x80 >> 8))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 7))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 5))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 4))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 3))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 1))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up;
					}
				}
				else if (count == 23)
				{
					if ((col[14] == 0xF7) && (row[14] == 0x80 >> 8))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 6))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 5))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 4))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 2))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 1))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up;
					}
				}
				else if (count == 24)
				{
					if ((col[14] == 0xF7) && (row[14] == 0x80 >> 7))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 6))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 5))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 3))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 2))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x80))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up;
					}
				}
				else if (count == 25)
				{
					if ((col[14] == 0xF7) && (row[14] == 0x80 >> 8))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 7))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 6))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 4))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 3))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 1))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up;
					}
				}
				else if (count == 26)
				{
					if ((col[14] == 0xF7) && (row[14] == 0x80 >> 8))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 7))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 5))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 4))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 2))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up;
					}
				}
				else if (count == 27)
				{
					if ((col[14] == 0xF7) && (row[14] == 0x80 >> 8))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 6))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 5))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 3))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up;
					}
				}
				else if (count == 28)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x80 >> 7))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 6))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 4))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up;
					}
				}
				else if (count == 29)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x80 >> 8))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 7))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 5))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up;
					}
				}
				else if (count == 30)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x80 >> 8))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 6))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up;
					}
				}
				else if (count == 31)
				{
					if ((col[14] == 0xDF) && (row[14] == 0x80 >> 7))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up;
					}
				}
				else if (count == 32)
				{
					if ((col[14] == 0xDF) && (row[14] == 0x80 >> 8))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up;
					}
				}
				else
				{
					mario_state = Jump_Up;
				}
			}
			else
			{
				mario_state = Fall_Down;
			}
			break;
		
		case Fall_Down:
			if (count == 0)
			{
				if (col[14] == 0xBF)
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xDF) && (row[14] == 0x20))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x40))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x10))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x08))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x04))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Fall_Down;
				}	
			}
			if (count == 1)
			{
				if (col[14] == 0xBF)
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xDF) && (row[14] == 0x20 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x40 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x10 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x08 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x04 >> count))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Fall_Down;
				}
			}
			if (count == 2)
			{
				if (col[14] == 0xBF)
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xDF) && (row[14] == 0x20 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x40 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x10 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x08 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x04 >> count))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Fall_Down;
				}
			}
			if (count == 3)
			{
				if (col[14] == 0xBF)
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xDF) && (row[14] == 0x20 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x40 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x10 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x08 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x04 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Fall_Down;
				}
			}
			if (count == 4)
			{
				if (col[14] == 0xBF)
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xDF) && (row[14] == 0x20 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x40 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x10 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x08 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x04 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 1))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x80))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Fall_Down;
				}
			}
			if (count == 5)
			{
				if (col[14] == 0xBF)
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xDF) && (row[14] == 0x20 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x40 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x10 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x08 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x04 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 2))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 1))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xDF) && (row[14] == 0x80))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Fall_Down;
				}
			}
			if (count == 6)
			{
				if (col[14] == 0xBF)
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xDF) && (row[14] == 0x20 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x40 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x10 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x08 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x04 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 3))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 2))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 1))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Fall_Down;
				}
			}
			if (count == 7)
			{
				if (col[14] == 0xBF)
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xDF) && (row[14] == 0x20 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x40 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x10 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x08 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x04 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 4))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 3))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 2))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Fall_Down;
				}
			}
			if (count == 8)
			{
				if (col[14] == 0xBF)
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xDF) && (row[14] == 0x20 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x40 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x10 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x08 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x04 >> count))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 5))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 4))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 3))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Fall_Down;
				}
			}
			if (count == 9)
			{
				if (col[14] == 0xBF)
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 6))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 5))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 4))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 1))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Fall_Down;
				}
			}
			if (count == 10)
			{
				if (col[14] == 0xBF)
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 7))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 6))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 5))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 2))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x80))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Fall_Down;
				}
			}
			if (count == 11)
			{
				if (col[14] == 0xBF)
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 8))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 7))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 6))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 3))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 1))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x80))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Fall_Down;
				}
			}
			if (count == 12)
			{
				if (col[14] == 0xBF)
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 8))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 7))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 4))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 2))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 1))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Fall_Down;
				}
			}
			if (count == 13)
			{
				if (col[14] == 0xBF)
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 8))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 5))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 3))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 2))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Fall_Down;
				}
			}
			if (count == 14)
			{
				if (col[14] == 0xBF)
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 6))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 4))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 3))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 1))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Fall_Down;
				}
			}
			if (count == 15)
			{
				if (col[14] == 0xBF)
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 7))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 5))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 4))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 2))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 1))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Fall_Down;
				}
			}
			if (count == 16)
			{
				if (col[14] == 0xBF)
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 8))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 6))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 5))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 3))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 2))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 1))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Fall_Down;
				}
			}
			if (count == 17)
			{
				if (col[14] == 0xBF)
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 7))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 6))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 4))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 3))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 2))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Fall_Down;
				}
			}
			if (count == 18)
			{
				if (col[14] == 0xBF)
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 8))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 7))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 5))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 4))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 3))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 1))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Fall_Down;
				}
			}
			if (count == 19)
			{
				if (col[14] == 0xBF)
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 8))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 6))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 5))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 4))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 2))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 1))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Fall_Down;
				}
			}
			if (count == 20)
			{
				if (col[14] == 0xBF)
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 7))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 6))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 5))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 3))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 2))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 1))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Fall_Down;
				}
			}
			if (count == 21)
			{
				if (col[14] == 0xBF)
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 8))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 7))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 6))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 4))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 3))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 2))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x80))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Fall_Down;
				}
			}
			if (count == 22)
			{
				if (col[14] == 0xBF)
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 8))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 7))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 5))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 4))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 3))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 1))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x80))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Fall_Down;
				}
			}
			if (count == 23)
			{
				if (col[14] == 0xBF)
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 8))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 6))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 5))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 4))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 2))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 1))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Fall_Down;
				}
			}
			if (count == 24)
			{
				if (col[14] == 0xBF)
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 7))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 6))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 5))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 3))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 2))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Fall_Down;
				}
			}
			if (count == 25)
			{
				if (col[14] == 0xBF)
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 8))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 7))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 6))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 4))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 3))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 1))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Fall_Down;
				}
			}
			if (count == 26)
			{
				if (col[14] == 0xBF)
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 8))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 7))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 5))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 4))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 2))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Fall_Down;
				}
			}
			if (count == 27)
			{
				if (col[14] == 0xBF)
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFD) && (row[14] == 0x80 >> 8))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 6))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 5))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 3))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x80))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Fall_Down;
				}
			}
			if (count == 28)
			{
				if (col[14] == 0xBF)
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 7))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 6))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 4))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 1))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Fall_Down;
				}
			}
			if (count == 29)
			{
				if (col[14] == 0xBF)
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 8))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 7))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 5))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 2))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 1))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Fall_Down;
				}
			}
			if (count == 30)
			{
				if (col[14] == 0xBF)
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xFB) && (row[14] == 0x80 >> 8))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 6))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 3))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 2))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Fall_Down;
				}
			}
			if (count == 31)
			{
				if (col[14] == 0xBF)
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 7))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 4))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 3))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 1))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Fall_Down;
				}
			}
			if (count == 32)
			{
				if (col[14] == 0xBF)
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 8))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 5))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 4))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 2))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Fall_Down;
				}
			}
			if (count == 33)
			{
				if (col[14] == 0xBF)
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 6))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 5))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 3))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 2))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Fall_Down;
				}
			}
			if (count == 34)
			{
				if (col[14] == 0xBF)
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 7))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 6))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 4))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 3))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Fall_Down;
				}
			}
			if (count == 35)
			{
				if (col[14] == 0xBF)
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 8))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 7))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 5))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 4))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Fall_Down;
				}
			}
			if (count == 36)
			{
				if (col[14] == 0xBF)
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 8))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 6))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 5))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Fall_Down;
				}
			}
			if (count == 37)
			{
				if (col[14] == 0xBF)
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 7))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 6))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Fall_Down;
				}
			}
			if (count == 38)
			{
				if (col[14] == 0xBF)
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 8))
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 7))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Fall_Down;
				}
			}
			if (count == 39)
			{
				if (col[14] == 0xBF)
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 8))
				{
					mario_state = Display;
				}
				else
				{
					mario_state = Fall_Down;
				}
			}
			if (count > 39)
			{
				if (col[14] == 0xBF)
				{
					mario_state = Display;
				}
				else if ((col[14] == 0xBF) && (row[14] == 0x10))
				{
// 					LCD_ClearScreen();
// 					LCD_Cursor(1);
// 					LCD_DisplayString(1, "WINNER!");
				}
				else
				{
					mario_state = Fall_Down;
				}
			}
			break;
			
		case Left:
			mario_state = Display;
			break;
			
		case Right:
			mario_state = Display;
			break;
		
		case Jump_Up_Right:
			if ((i < 4) && (row[14] != 0x80) && (col[14] != 0xFE))
			{
				if (count == 0)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x04))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x08))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x10))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Right;
					}
				}
				else if (count == 1)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x04 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x08 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x10 >> count))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Right;
					}
				}
				else if (count == 2)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x04 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x08 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x10 >> count))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Right;
					}
				}
				else if (count == 3)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x04 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x08 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x10 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x40))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x40))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x40))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Right;
					}
				}
				else if (count == 4)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x04 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x08 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x10 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x40 >> 1))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x40 >> 1))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x40 >> 1))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Right;
					}
				}
				else if (count == 5)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x04 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x08 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x10 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x40 >> 2))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x40 >> 2))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x40 >> 2))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Right;
					}
				}
				else if (count == 6)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x04 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x08 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x10 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x40 >> 3))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x40 >> 3))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x40 >> 3))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Right;
					}
				}
				else if (count == 7)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x04 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x08 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x10 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x40 >> 4))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x40 >> 4))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x40 >> 4))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Right;
					}
				}
				else if (count == 8)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x04 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x08 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x10 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x80))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x40 >> 5))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x40 >> 5))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x40 >> 5))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Right;
					}
				}
				else if (count == 9)
				{
					if ((col[14] == 0xDF) && (row[14] == 0x80 >> 1))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x40 >> 6))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x40 >> 6))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x40 >> 6))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Right;
					}
				}
				else if (count == 10)
				{
					if ((col[14] == 0xDF) && (row[14] == 0x80 >> 2))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x40 >> 7))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x40 >> 7))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x40 >> 7))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Right;
					}
				}
				else if (count == 11)
				{
					if ((col[14] == 0xDF) && (row[14] == 0x80 >> 3))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 1))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x40 >> 8))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x40 >> 8))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x40 >> 8))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Right;
					}
				}
				else if (count == 12)
				{
					if ((col[14] == 0xDF) && (row[14] == 0x80 >> 4))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 2))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 1))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Right;
					}
				}
				else if (count == 13)
				{
					if ((col[14] == 0xDF) && (row[14] == 0x80 >> 5))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 3))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 2))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Right;
					}
				}
				else if (count == 14)
				{
					if ((col[14] == 0xDF) && (row[14] == 0x80 >> 6))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 4))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 3))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 1))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Right;
					}
				}
				else if (count == 15)
				{
					if ((col[14] == 0xDF) && (row[14] == 0x80 >> 7))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 5))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 4))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 2))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 1))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Right;
					}
				}
				else if (count == 16)
				{
					if ((col[14] == 0xDF) && (row[14] == 0x80 >> 8))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 6))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 5))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 3))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 2))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 1))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Right;
					}
				}
				else if (count == 17)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x80 >> 7))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 6))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 4))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 3))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 2))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Right;
					}
				}
				else if (count == 18)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x80 >> 8))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 7))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 5))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 4))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 3))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 1))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Right;
					}
				}
				else if (count == 19)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x80 >> 8))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 6))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 5))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 4))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 2))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 1))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Right;
					}
				}
				else if (count == 20)
				{
					if ((col[14] == 0xF7) && (row[14] == 0x80 >> 7))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 6))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 5))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 3))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 2))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 1))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Right;
					}
				}
				else if (count == 21)
				{
					if ((col[14] == 0xF7) && (row[14] == 0x80 >> 8))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 7))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 6))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 4))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 3))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 2))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Right;
					}
				}
				else if (count == 22)
				{
					if ((col[14] == 0xF7) && (row[14] == 0x80 >> 8))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 7))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 5))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 4))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 3))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 1))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Right;
					}
				}
				else if (count == 23)
				{
					if ((col[14] == 0xF7) && (row[14] == 0x80 >> 8))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 6))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 5))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 4))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 2))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 1))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Right;
					}
				}
				else if (count == 24)
				{
					if ((col[14] == 0xF7) && (row[14] == 0x80 >> 7))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 6))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 5))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 3))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 2))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x80))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Right;
					}
				}
				else if (count == 25)
				{
					if ((col[14] == 0xF7) && (row[14] == 0x80 >> 8))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 7))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 6))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 4))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 3))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 1))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Right;
					}
				}
				else if (count == 26)
				{
					if ((col[14] == 0xF7) && (row[14] == 0x80 >> 8))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 7))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 5))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 4))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 2))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Right;
					}
				}
				else if (count == 27)
				{
					if ((col[14] == 0xF7) && (row[14] == 0x80 >> 8))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 6))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 5))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 3))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x40))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x40))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Right;
					}
				}
				else if (count == 28)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x80 >> 7))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 6))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 4))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x40 >> 1))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x40 >> 1))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Right;
					}
				}
				else if (count == 29)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x80 >> 8))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 7))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 5))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x40 >> 2))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x40 >> 2))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Right;
					}
				}
				else if (count == 30)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x80 >> 8))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 6))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x40 >> 3))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x40 >> 3))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x40))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x40))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x40))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Right;
					}
				}
				else if (count == 31)
				{
					if ((col[14] == 0xDF) && (row[14] == 0x80 >> 7))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x40 >> 4))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x40 >> 4))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x40 >> 1))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x40 >> 1))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x40 >> 1))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Right;
					}
				}
				else if (count == 32)
				{
					if ((col[14] == 0xDF) && (row[14] == 0x80 >> 8))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x40 >> 5))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x40 >> 5))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x40 >> 2))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x40 >> 2))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x40 >> 2))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Right;
					}
				}
				else if (count == 33)
				{
					if ((col[14] == 0xBF) && (row[14] == 0x40 >> 6))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x40 >> 6))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x40 >> 3))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x40 >> 3))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x40 >> 3))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Right;
					}
				}
				else if (count == 34)
				{
					if ((col[14] == 0xBF) && (row[14] == 0x40 >> 7))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x40 >> 7))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x40 >> 4))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x40 >> 4))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x40 >> 4))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Right;
					}
				}
				else if (count == 35)
				{
					if ((col[14] == 0xBF) && (row[14] == 0x40 >> 8))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x40 >> 8))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x40 >> 5))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x40 >> 5))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x40 >> 5))
					{
						mario_state = Fall_Down;
					}
					else 
					{
						mario_state = Jump_Up_Right;
					}
				}
				else if (count == 36)
				{
					if ((col[14] == 0xBF) && (row[14] == 0x40 >> 6))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x40 >> 6))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x40 >> 6))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Right;
					}
				}
				else if (count == 37)
				{
					if ((col[14] == 0xBF) && (row[14] == 0x40 >> 7))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x40 >> 7))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x40 >> 7))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Right;
					}
				}
				else if (count == 38)
				{
					if ((col[14] == 0xBF) && (row[14] == 0x40 >> 8))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x40 >> 8))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x40 >> 8))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Right;
					}
				}
				else
				{
					mario_state = Jump_Up_Right;
				}
			}
			else
			{
				mario_state = Fall_Down;
			}
			break;
			
		case Jump_Up_Left:
			if ((i < 4) && (row[14] != 0x01) && (col[14] != 0xFE))
			{
				if (count == 0)
				{
					
					if ((col[14] == 0xEF) && (row[14] == 0x04))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x08))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x10))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x01))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Left;
					}
				}
				else if (count == 1)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x04 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x08 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x10 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x01))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Left;
					}
				}
				else if (count == 2)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x04 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x08 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x10 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x01))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Left;
					}
				}
				else if (count == 3)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x04 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x08 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x10 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x01))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Left;
					}
				}
				else if (count == 4)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x04 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x08 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x10 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x01))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Left;
					}
				}
				else if (count == 5)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x04 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x08 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x10 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x01))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Left;
					}
				}
				else if (count == 6)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x04 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x08 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x10 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x01))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Left;
					}
				}
				else if (count == 7)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x04 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x08 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x10 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x01))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Left;
					}
				}
				else if (count == 8)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x04 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x08 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x10 >> count))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x80))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x01))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Left;
					}
				}
				else if (count == 9)
				{
					if ((col[14] == 0xDF) && (row[14] == 0x80 >> 1))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x01))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Left;
					}
				}
				else if (count == 10)
				{
					if ((col[14] == 0xDF) && (row[14] == 0x80 >> 2))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x01))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Left;
					}
				}
				else if (count == 11)
				{
					if ((col[14] == 0xDF) && (row[14] == 0x80 >> 3))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 1))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x01))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Left;
					}
				}
				else if (count == 12)
				{
					if ((col[14] == 0xDF) && (row[14] == 0x80 >> 4))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 2))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 1))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x01))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Left;
					}
				}
				else if (count == 13)
				{
					if ((col[14] == 0xDF) && (row[14] == 0x80 >> 5))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 3))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 2))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x01))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Left;
					}
				}
				else if (count == 14)
				{
					if ((col[14] == 0xDF) && (row[14] == 0x80 >> 6))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 4))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 3))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 1))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x01))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Left;
					}
				}
				else if (count == 15)
				{
					if ((col[14] == 0xDF) && (row[14] == 0x80 >> 7))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 5))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 4))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 2))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 1))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x01))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Left;
					}
				}
				else if (count == 16)
				{
					if ((col[14] == 0xDF) && (row[14] == 0x80 >> 8))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 6))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 5))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 3))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 2))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 1))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x01))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Left;
					}
				}
				else if (count == 17)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x80 >> 7))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 6))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 4))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 3))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 2))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x01))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Left;
					}
				}
				else if (count == 18)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x80 >> 8))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 7))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 5))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 4))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 3))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 1))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x01))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Left;
					}
				}
				else if (count == 19)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x80 >> 8))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 6))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 5))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 4))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 2))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 1))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x01))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Left;
					}
				}
				else if (count == 20)
				{
					if ((col[14] == 0xF7) && (row[14] == 0x80 >> 7))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 6))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 5))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 3))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 2))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 1))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x01))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Left;
					}
				}
				else if (count == 21)
				{
					if ((col[14] == 0xF7) && (row[14] == 0x80 >> 8))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 7))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 6))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 4))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 3))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 2))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x01))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Left;
					}
				}
				else if (count == 22)
				{
					if ((col[14] == 0xF7) && (row[14] == 0x80 >> 8))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 7))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 5))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 4))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 3))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 1))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x01))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Left;
					}
				}
				else if (count == 23)
				{
					if ((col[14] == 0xF7) && (row[14] == 0x80 >> 8))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 6))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 5))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 4))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 2))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 1))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x01))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Left;
					}
				}
				else if (count == 24)
				{
					if ((col[14] == 0xF7) && (row[14] == 0x80 >> 7))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 6))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 5))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 3))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 2))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x80))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x01))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Left;
					}
				}
				else if (count == 25)
				{
					if ((col[14] == 0xF7) && (row[14] == 0x80 >> 8))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 7))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 6))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 4))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 3))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 1))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x01))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Left;
					}
				}
				else if (count == 26)
				{
					if ((col[14] == 0xF7) && (row[14] == 0x80 >> 8))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xF7) && (row[14] == 0x80 >> 7))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 5))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 4))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 2))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x01))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Left;
					}
				}
				else if (count == 27)
				{
					if ((col[14] == 0xF7) && (row[14] == 0x80 >> 8))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 6))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 5))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 3))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x01))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Left;
					}
				}
				else if (count == 28)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x80 >> 7))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 6))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 4))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x01))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Left;
					}
				}
				else if (count == 29)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x80 >> 8))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xEF) && (row[14] == 0x80 >> 7))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 5))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x01))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Left;
					}
				}
				else if (count == 30)
				{
					if ((col[14] == 0xEF) && (row[14] == 0x80 >> 8))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xDF) && (row[14] == 0x80 >> 6))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x01))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Left;
					}
				}
				else if (count == 31)
				{
					if ((col[14] == 0xDF) && (row[14] == 0x80 >> 7))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x01))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Left;
					}
				}
				else if (count == 32)
				{
					if ((col[14] == 0xDF) && (row[14] == 0x80 >> 8))
					{
						mario_state = Fall_Down;
					}
					else if ((col[14] == 0xBF) && (row[14] == 0x01))
					{
						mario_state = Fall_Down;
					}
					else
					{
						mario_state = Jump_Up_Left;
					}
				}
				else
				{
					mario_state = Jump_Up_Left;
				}
			}
			else
			{
				mario_state = Fall_Down;
			}
			break;
			
		default:
			break;
	}
	switch(mario_state)
	{
		case Init:
			PORTC = row[14];
			PORTD = col[14];
			break;
			
		case Display:
			i = 0;
			PORTC = row[14];
			PORTD = col[14];
			break;
			
		case Jump_Up:
			if ((mario_counter % 200) == 0)
			{
				col[14] = (col[14] >> 1) | 0x80;
				i++;
			}
			PORTC = row[14];
			PORTD = col[14];
			break;
				
		case Fall_Down:
			i = 0;
			if ((mario_counter % 200) == 0)
			{
				col[14] = (col[14] << 1) | 0x01;
			}
			PORTC = row[14];
			PORTD = col[14];
			break;
				
		case Left:
			if (((mario_counter % 200) == 0) && (row[14] != 0x01))
			{
				row[14] = row[14] >> 1;
				fall = 1;
			}
			PORTC = row[14];
			PORTD = col[14];
			break;
				
		case Right:
			if (((mario_counter % 200) == 0) && (row[14] != 0x80))
			{
				row[14] = row[14] << 1;
				fall = 1;
			}
			PORTC = row[14];
			PORTD = col[14];
			break;
		
		case Jump_Up_Right:
			if (((mario_counter % 200) == 0) && (row[14] != 0x80))
			{
				row[14] = row[14] << 1;
				col[14] = (col[14] >> 1) | 0x80;
				i++;
			}
			PORTC = row[14];
			PORTD = col[14];
			break;
			
		case Jump_Up_Left:
			if (((mario_counter % 200) == 0) && (row[14] != 0x01))
			{
				row[14] = row[14] >> 1;
				col[14] = (col[14] >> 1) | 0x80;
				i++;
			}
			PORTC = row[14];
			PORTD = col[14];
			break;
		
		default:
			break;
	}
}

enum SM_MELODY {WAIT, PLAY_NOTE, WAIT_NOTE} melody_state;
	
void tick_melody(void) {
	static unsigned char index = 0;
	static unsigned char count = 0;
	switch (melody_state) { // Transitions

		case WAIT:
			index = 0;
			count = 0;
			if (SONG1) {
				melody_state = PLAY_NOTE;
				//SONG1 = 0;
			}
			else {
				melody_state = WAIT;
			}
			break;

		case PLAY_NOTE:
			if (count < sm_time_array[index])
			{
				set_PWM(sm_array[index]);
				count++;
				melody_state = PLAY_NOTE;
			}
			else {
				count = 0;
				/*if (index < MAX_NOTES -1){
					melody_state = PLAY_NOTE;
					++index;
				}
				else{
					melody_state = WAIT_PRESS;
				}*/
				melody_state = WAIT_NOTE;
			}
			break;

		case WAIT_NOTE:
			if (count < sm_wait_array[index]) {
				set_PWM(0);
				count++;
				melody_state = WAIT_NOTE;
			}
			else {
				count = 0;
				if (sm_array[index] != '1') {
					index++;
					melody_state = PLAY_NOTE;
				}
				else {
					SONG1 = 0;
					melody_state = WAIT;
				}
			}
			break;

		}
}

int main()
{
	unsigned char song_counter = 0x00;
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	
	TimerSet(1);
	TimerOn();
	
	PWM_on();
	set_PWM(0);
	
	melody_state = WAIT;
	
	InitADC();
	LCD_init();
	while(1)
	{
		SONG1 = 1;
		Mario_Tick();
		SM1_Tick();
		SM2_Tick();
// 		if (count > 39)
// 		{
// 			row[1] = row[2] = row[3] = row[4] = row[5] = row[6] = row[7] = row[8] = row[9] = row[10] = row[11] = row[12] = row[13] = row[15] = row[16] = row[17] = row[18] = 0x00;
// 			row[19] = row[20] = row[21] = row[22] = row[23] = row[24] = row[25] = row[26] = row[27] = row[28] = row[29] = row[30] = row[31] = row[14] = row[32] = 0x00;
// 			col[1] = col[2] = col[3] = col[4] = col[5] = col[6] = col[7] = col[8] = col[9] = col[10] = col[11] = col[12] = col[13] = col[15] = col[16] = col[17] = col[18] = 0x00; 
// 			col[19] = col[20] = col[21] = col[22] = col[23] = col[24] = col[25] = col[26] = col[27] = col[28] = col[29] = col[30] = col[31] = col[14] = col[32] = 0x00;
// 			Winner();
// 		}

		if (song_counter == 35)
		{
			tick_melody();
			song_counter = 0;
		}
		while(!TimerFlag);
		TimerFlag = 0;
		time_counter++;
		song_counter++;
		mario_counter++;
	}
	return 0;	
}