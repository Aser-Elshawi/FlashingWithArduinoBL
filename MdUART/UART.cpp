/*
 * UART.cpp
 *
 *  Created on: Jan 17, 2024
 *      Author: Razi_R
 */


#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <Md_QUEUE.h>
#include <UART.h>



// Output PINs for LEDs
const uint8_t ledPin = 13; // Built-in LED pin on the board

const uint8_t redPin = 11;
const uint8_t greenPin = 10;
const uint8_t bluePin = 9;

USART::USART(unsigned int ubrr) {
    init(ubrr);
}

void USART::init(unsigned int ubrr) {
    // Set baud rate
    UBRR0H = (unsigned char)(ubrr >> 8);//USART Baud Rate Register High
    UBRR0L = (unsigned char)(ubrr);  //USART Baud Rate Register Low

    // Enable receiver and transmitter
    UCSR0B = (1 << RXEN0) | (1 << TXEN0); //USART Control and Status Register B

    // Set frame format: 8 data, 2 stop bits
    UCSR0C = (1 << USBS0) | (3 << UCSZ00); /*USART Control and Status Register C
                                            is used for setting the frame format
                                            of the USART communication.;
                                            USBS0 (Stop Bit Select) bit in UCSR0C.
                                            This configures the USART to use 2 stop
                                             bits in each frame.;
                                             3 << UCSZ00: This sets the UCSZ00 and
                                             UCSZ01 bits. The 3 in binary is 11,
                                             which sets the UCSZ00 and UCSZ01 bits
                                             to configure the USART for 8-bit data
                                             frames
                                            */
}

bool USART::receive(char *ret) {
    // Wait for data to be received
    if ((UCSR0A & (1 << RXC0))){
    	*ret = UDR0;
    	return true;
    }else{
    	return false;
    }
    									/* USART Control and Status Register A;
    }
    									RXC0: This is a bit within the UCSR0A
    									register, which is set (1) when there
    									is unread data in the receive buffer.
    									It stands for "Receive Complete".*/
    				/*UDR0: This is the USART Data Register,
     	 	 	 	where received data is stored. Reading
     	 	 	 	 from UDR0 gives you the byte that was
     	 	 	 	 just received via USART.*/
}

void USART::transmit(char data) { // Not using it now
    // Wait for empty transmit buffer
   /* while (!(UCSR0A & (1 << UDRE0))); /*UCSR0A & (1 << UDRE0): This bitwise
     	 	 	 	 	 	 	 	 	AND operation checks the status of the
     	 	 	 	 	 	 	 	 	 UDRE0 bit. The loop continues
     	 	 	 	 	 	 	 	 	 (while (!(UCSR0A & (1 << UDRE0)))) as long
     	 	 	 	 	 	 	 	 	  as the UDRE0 bit is not set, indicating
     	 	 	 	 	 	 	 	 	  the buffer is not ready for new data.*/

	_queue.enque(data);
}

void USART::print(char * str){
	while(*str != '\0'){
		transmit(*(str++));
	}
}

void USART::service(void){
	if ((UCSR0A & (1 << UDRE0)) && _queue.size()){
		UDR0 = _queue.dequeue();
	}
}
void setupIO() {
    // Set LED pins as output
	/*DDRB stands for Data Direction Register associated with port B*/
    DDRB |= (1 << DDB5); // Built-in LED pin as output
    DDRB |= (1 << DDB3); // Red LED pin as output; Digital PIN 11
    DDRB |= (1 << DDB2); // Green LED pin as output; Digital PIN 10
    DDRB |= (1 << DDB1); // Blue LED pin as output; Digital PIN 9
}

void setRGBColor(int r, int g, int b) {
    // Common cathode RGB LED
    if (r > 0) {
        PORTB |= (1 << PORTB3); // Turn Red on
    } else {
        PORTB &= ~(1 << PORTB3); // Turn Red off
    }

    if (g > 0) {
        PORTB |= (1 << PORTB2); // Turn Green on
    } else {
        PORTB &= ~(1 << PORTB2); // Turn Green off
    }

    if (b > 0) {
        PORTB |= (1 << PORTB1); // Turn Blue on
    } else {
        PORTB &= ~(1 << PORTB1); // Turn Blue off
    }
}

/*void initPWM() {
    // Configure Timer 1 for Fast PWM mode on pins 9 and 10
    TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);
    TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1 << CS11); // Prescaler = 8

    // Configure Timer 2 for Fast PWM mode on pin 11
    TCCR2A |= (1 << COM2A1) | (1 << WGM21) | (1 << WGM20);
    TCCR2B |= (1 << CS21); // Prescaler = 8

    ICR1 = 255; // PWM range is 0 to 255
}

// Set PWM duty cycle for each LED pin
void setPWMDutyCycle(uint8_t pwmPin, uint8_t dutyCycle) {
    switch (pwmPin) {
        case 9:  OCR1A = dutyCycle; break; // Pin 9 uses Timer 1
        case 10: OCR1B = dutyCycle; break; // Pin 10 uses Timer 1
        case 11: OCR2A = dutyCycle; break; // Pin 11 uses Timer 2
    }
}

void setRGBColor(uint8_t r, uint8_t g, uint8_t b) {
    setPWMDutyCycle(11, r); // Red LED on pin 11
    setPWMDutyCycle(10, g); // Green LED on pin 10
    setPWMDutyCycle(9, b);  // Blue LED on pin 9
}*/


