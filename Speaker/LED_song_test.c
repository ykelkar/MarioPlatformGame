#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char SONG1 = 0;

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

enum SM_MELODY {
	WAIT,
	PLAY_NOTE,
	WAIT_NOTE,

} melody_state;

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
// 											1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 , 1,
// 											1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
// 											1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
// 											1, 1, 1, 1, 1, 1, 1, 1, 1 ,1,
// 											1, 1, 1, 1, 1, 1, 1, 1,
// 											1, 1, 1, 1, 1, 1, 1, 1,
// 											1, 1, 1, 1, 1, 1, 1, 1,
// 											1, 1, 1, 1, 1, 1, 1, 1,
// 											1, 1, 1, 1, 1, 1, 1, 1,
// 											1, 1 , 1, 1, 1, 1, 1, 1,
// 											1, 1, 1, 1, 1, 1,
// 											1, 1, 1, 1, 1, 1, 1, 1, 1,
// 											1, 1, 1, 1, 1, 1, 1, 1,
// 											1, 1, 1, 1, 1, 1, 1,
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
// 											1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 , 1,
// 											1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
// 											1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
// 											1, 1, 1, 1, 1, 1, 1, 1, 1 ,1,
// 											1, 1, 1, 1, 1, 1, 1, 1,
// 											1, 1, 1, 1, 1, 1, 1, 1,
// 											1, 1, 1, 1, 1, 1, 1, 1,
// 											1, 1, 1, 1, 1, 1, 1, 1,
// 											1, 1, 1, 1, 1, 1, 1, 1,
// 											1, 1 , 1, 1, 1, 1, 1, 1,
// 											1, 1, 1, 1, 1, 1,
// 											1, 1, 1, 1, 1, 1, 1, 1, 1,
// 											1, 1, 1, 1, 1, 1, 1, 1,
// 											1, 1, 1, 1, 1, 1, 1,
											};
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
	DDRB = 0xFF; PORTB = 0x00;
	
	//unsigned char input1 = ~PINC & 0x07;
	unsigned char time_counter = 0;
	// Timer setup
	TimerSet(1);
	TimerOn();

	// PWM Setup
	PWM_on();
	set_PWM(0);

	melody_state = WAIT;
	
	while(1) {
		
		SONG1 = 1;

		if (time_counter == 35){
			tick_melody();
			time_counter=0;
		}
		++time_counter;
		while(!TimerFlag);
		TimerFlag = 0;
	}
}