/*
 * OStimer.c
 *
 * Created: 10/19/2019 7:54:53 PM
 *  Author: asere
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <OStimer.h>
#include <OS.h>

void Init_OStimer(void){
	uint8_t CompareValue;
	// initialize 100us timer compare interrupt
	CompareValue = (F_CPU/80000); // divide by 8 prescaler, 10000 to reach 100us
	// Set ASSR for sync timer 2
	ASSR &= ~(1<< AS2); // timer 2 is sourced from F_CPU clock (Crystal Osc)
   #if  defined(__AVR_ATmega32__)
	// start timer0 on 8 prescaler
	TCCR2 = (1<<CS21);
	// Clear timer on compare match
	TCCR2 |= (1<<WGM21);
	// Set value for comparator interrupt
	OCR2 = CompareValue;
	// Clear Interrupt flag for output compare
	TIFR = (1<<OCF2);
	// Enable Compare interrupt
	TIMSK |= (1<<OCIE2);
	#elif defined(__AVR_ATmega328P__)
	TCCR2B |= (1<<CS21);
	TCCR2A |= (1<<WGM21);
	OCR2A = CompareValue;
	TIFR2 = (1<<OCF2A);
	TIMSK2 |= (1<<OCIE2A);
	#endif
	sei();
}
ISR(TIMER2_COMPA_vect){
	// every 100us call OS handler
	OS_handlerCallBack();
}
