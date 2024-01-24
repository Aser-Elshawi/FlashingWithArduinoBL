/*
 * UART.h
 *
 *  Created on: Jan 17, 2024
 *      Author: Razi_R
 */

#ifndef MDUART_UART_H_
#define MDUART_UART_H_

#include <avr/io.h>

// Constants for setting the USART baud rate
#define CLOCK_FREQUENCY 16000000UL // Clock speed understand this fully
#define BAUD_RATE 9600
#define MY_UBRR CLOCK_FREQUENCY/16/BAUD_RATE-1 // UBRR: USART Baud Rate Register

// LED pin definitions
extern const uint8_t ledPin;  // Built-in LED pin
extern const uint8_t redPin;  // Red LED pin
extern const uint8_t greenPin;  // Green LED pin
extern const uint8_t bluePin;  // Blue LED pin

class USART {
public:
    USART(unsigned int ubrr);
    void init(unsigned int ubrr);
    bool receive(unsigned char *ret);
    void transmit(unsigned char data);
};

// Function declarations for LED control
void setupIO();
void setRGBColor(int r, int g, int b);
//void setRGBColor(uint8_t r, uint8_t g, uint8_t b);
//void initPWM();
//void setPWMDutyCycle(uint8_t pwmPin, uint8_t dutyCycle);


#endif /* MDUART_UART_H_ */
