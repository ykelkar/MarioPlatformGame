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

void transmit_data(unsigned char data) {
	int i;
	for (i = 0; i < 8 ; ++i) {
		// Sets SRCLR to 1 allowing data to be set
		// Also clears SRCLK in preparation of sending data
		PORTC = 0x08;
		// set SER = next bit of data to be sent.
		PORTC |= ((data >> i) & 0x01);
		// set SRCLK = 1. Rising edge shifts next bit of data into the shift register
		PORTC |= 0x02;
	}
	// set RCLK = 1. Rising edge copies data from �Shift� register to �Storage� register
	PORTC |= 0x04;
	// clears all lines in preparation of a new transmission
	PORTC = 0x00;
}

unsigned char j = 0x00;
unsigned char button = 0x00;
static unsigned char row[] = {0x3C, 0x24, 0x24, 0x3C}; // sets the pattern displayed on columns
static unsigned char col[] = {0xDF, 0xEF, 0xF7, 0xFB}; // grounds column to display pattern
	

enum SM1_States {Init, First_Col, Second_Col, Third_Col, Fourth_Col} state;

void SM1_Tick() 
{
	button = ~PINC & 0xF0;
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
			state = First_Col;
			break;
			
		default:
			break;
	}
		switch (state)
		{
			case Init:
			j = 0;
			PORTA = row[j];
			PORTB = col[j];
			break;
			
			case First_Col:
			j = 0;
			PORTA = row[j];
			PORTB = col[j];
			break;
			
			case Second_Col:
			j = 1;
			PORTA = row[j];
			PORTB = col[j];
			break;
			
			case Third_Col:
			j = 2;
			PORTA = row[j];
			PORTB = col[j];
			break;
			
			case Fourth_Col:
			j = 3;
			PORTA = row[j];
			PORTB = col[j];
			break;
			
			default:
			break;
		}
}

enum button_States {Init1, Changer, Up, Down, Right, Left, Wait} move_state;

unsigned char time_counter = 0x00;

void SM2_Tick()
{
	switch(move_state)
	{
		case Init1:
			move_state = Changer;
			break;
			
		case Changer:
			if (button == 0x10)
			{
				move_state = Up;
			}
			else if (button == 0x20)
			{
				move_state = Down;
			}
			else if (button == 0x40)
			{
				move_state = Right;
			}
			else if (button == 0x80)
			{
				move_state = Left;
			}
			else if (button == 0xF0)
			{
				move_state = Init;
			}
			else
			{
				move_state = Changer;
			}
			break;
			
		case Up:
			move_state = Wait;
			break;
			
		case Down:
			move_state = Wait;
			break;
			
		case Right:
			move_state = Wait;
			break;
			
		case Left:
			move_state = Wait;
			break;
			
		case Wait:
			if (button == 0x10)
			{
				move_state = Up;
			}
			else if (button == 0x20)
			{
				move_state = Down;
			}
			else if (button == 0x40)
			{
				move_state = Right;
			}
			else if (button == 0x80)
			{
				move_state = Left;
			}
			else 
			{
				move_state = Changer;
			}
			break;
			
			default:
				break;
	}
	switch(move_state)
	{
		case Init1:
			break;
			
		case Changer:
			break;
			
		case Up:
			if ((time_counter % 300 == 0) && (col[3] != 0xFE))
			{
				col[0] = (col[0] >> 1) | 0x80;
				col[1] = (col[1] >> 1) | 0x80;
				col[2] = (col[2] >> 1) | 0x80;
				col[3] = (col[3] >> 1) | 0x80;
			}
			break;
		
		case Down:
			if ((time_counter % 300 == 0) && (col[0] != 0x7F))
			{
				col[0] = (col[0] << 1) | 0x01;
				col[1] = (col[1] << 1) | 0x01;
				col[2] = (col[2] << 1) | 0x01;
				col[3] = (col[3] << 1) | 0x01;
			}
			break;
		
		case Right:
			if ((time_counter % 300 == 0) && (row[3] != 0xF0))
			{
				row[0] = row[0] << 1;
				row[1] = row[1] << 1;
				row[2] = row[2] << 1;
				row[3] = row[3] << 1;
			}
			break;
			
		case Left:
			if ((time_counter % 300 == 0) && (row[0] != 0x0F))
			{
				row[0] = row[0] >> 1;
				row[1] = row[1] >> 1;
				row[2] = row[2] >> 1;
				row[3] = row[3] >> 1;
			}
			break;
			
		case Wait:
			break;
			
		default:
			break;
	}
}

enum States {init, display} ex_state;
unsigned char seg7=0x00;
void Tick_display(){

	switch (ex_state){
		case init:
		ex_state = display;
		break;

		case display:
		ex_state = display;
	
		break;
	}

	switch (ex_state){

		case init:
		break;

		case display:
		if (time_counter % 1000 == 0)
		{
			if(seg7==0x00)
			{
				transmit_data(0x0C);
			}
			if (seg7 == 0x01){
				transmit_data(0xF9);
			}
			if (seg7 == 0x02){
				transmit_data(0xA4);
			}
			if (seg7 == 0x03){
				transmit_data(0xB0);
			}
			if (seg7 == 0x04){
				transmit_data(0x99);
			}
			if (seg7 == 0x05){
				transmit_data(0x92);
			}
			if (seg7 == 0x06){
				transmit_data(0x82);
			}
			if (seg7 == 0x07){
				transmit_data(0xF8);
			}
			if (seg7 == 0x08){
				transmit_data(0x80);
			}
			//seg7++;
		}
		break;

	}
}

int main()
{
	DDRA = 0xFF; PORTA = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0x0F; PORTC = 0xF0;
	
	TimerSet(1);
	TimerOn();
	
	while(1)
	{
		SM1_Tick();
		SM2_Tick();
		Tick_display();
		while(!TimerFlag);
		TimerFlag = 0;
		time_counter++;
	}
	return 0;	
}