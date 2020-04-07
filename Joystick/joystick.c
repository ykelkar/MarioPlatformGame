#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are
	// in Free Running Mode, a new conversion will trigger
	// whenever the previous conversion completes.
}

enum SM_states6 {Start6, ADC_val} SM_state6;

void SM_Tick6()
{
	switch(SM_state6)
	{
		case Start6:
		PORTC = 0x01;
		PORTD = 0x7F;
		SM_state6=ADC_val;
		break;

		case ADC_val:
		;
		unsigned short adcval=ADC;
		if(adcval<530)
		{
			PORTC=PORTC|0xFE;
			PORTC = PORTC << 1;
		}
		else if (adcval>600)
		{
			PORTC = PORTC | 0xF1;
		PORTC = PORTC >> 1;		}
		else
		{
			PORTC=PORTC | 0xFE;
		}
		SM_state6=ADC_val;
		break;
	}
}

int main()
{
	DDRC = 0xFF; PORTC = 0x00;
	DDRA = 0x00; PORTA = 0xFF;
	DDRD = 0xFF; PORTD = 0x00;
	
	SM_state6 = Start6;
	
	ADC_init();
	
	while(1)
	{
		SM_Tick6();
	}
}