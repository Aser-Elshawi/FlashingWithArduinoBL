/*
 * TIMER1.c
 *
 *  Created on: Dec 25, 2023
 *      Author: asere
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include "TIMER1.h"



// Global variable to store milliseconds
volatile uint32_t milliseconds = 0;

void TIMER1_Init(void){
	// Set Timer1 in CTC mode with OCR1A as TOP
	    TCCR1B |= (1 << WGM12);

	    // Set prescaler (adjust as needed for your application)
	    TCCR1B |= (1 << CS12);

	    // Set the compare match value for 1ms resolution
	    OCR1A = F_CPU / TIMER_PRESCALER_VALUE / 1000 - 1;

	    // Enable Timer1 compare match A interrupt
	    TIMER_INTERRUPT_MASK_REGISTER |= (1 << OCIE1A);

	    // Enable global interrupts
	    sei();
}
ISR(TIMER1_COMPA_vect) {
    // Increment milliseconds on each Timer1 compare match
    milliseconds++;
}
// Function to get the current time in milliseconds
uint32_t millis() {
    uint32_t msValue;
    cli();
    msValue = milliseconds;
    sei();
    return msValue;
}
