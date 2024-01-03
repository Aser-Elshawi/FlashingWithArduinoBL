/*
 * TIMER1.h
 *
 *  Created on: Dec 25, 2023
 *      Author: asere
 */

#ifndef SERVICES_TIMER1_TIMER1_H_
#define SERVICES_TIMER1_TIMER1_H_

#if defined(__AVR_ATmega32__)
    // Configuration for ATmega32
    #define TIMER_PRESCALER_VALUE (256)
    #define TIMER_INTERRUPT_MASK_REGISTER TIMSK
#elif defined(__AVR_ATmega328P__)
    // Configuration for ATmega328P
    #define TIMER_PRESCALER_VALUE (64)
    #define TIMER_INTERRUPT_MASK_REGISTER TIMSK1
#else
    #error "Unsupported AVR microcontroller"
#endif

void TIMER1_Init(void);
uint32_t millis(void);

#endif /* SERVICES_TIMER1_TIMER1_H_ */
