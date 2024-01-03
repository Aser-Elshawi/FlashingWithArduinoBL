/*
 * Copyright (c) 2010 by Cristian Maglie <c.maglie@arduino.cc>
 * Copyright (c) 2014 by Paul Stoffregen <paul@pjrc.com> (Transaction API)
 * Copyright (c) 2014 by Matthijs Kooijman <matthijs@stdin.nl> (SPISettings AVR)
 * Copyright (c) 2014 by Andrew J. Kroll <xxxajk@gmail.com> (atomicity fixes)
 * SPI Master library for arduino.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */

#ifndef _SPI_H_INCLUDED
#define _SPI_H_INCLUDED


class SPIClass {
public:
  inline static uint8_t begin(void){
	    //_SPI.begin(); porting
	    // Start SPI on the ATMEGA32 and ATMEGA
	#if defined(__AVR_ATmega32__)
		DDRB |= (1<<4);
		DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK);
	#elif defined(__AVR_ATmega328P__)
		// must set the SS pin as output to insure proper SPI master mode
		DDRB |= (1<<2);
		//PORTB |=(1<<2);
#define DDR_SPI DDRB
#define DD_MOSI PB3
#define DD_SCK  PB5
	#endif

	  	//SPCR &= ~(1<< DORD);
	    //SPCR &= ~((1<< CPOL) | (1 << CPHA));
	    //SPSR |= (1<<SPI2X);
	    DDR_SPI |= (1<<DD_MOSI)|(1<<DD_SCK);
	    // Set SPI to master mode
	    SPSR &= ~(1<<SPI2X);
	    SPCR = (1<<MSTR)| (1<<SPE)|(1<<SPR0);

	    return 1;

  }
  // Write to the SPI bus (MOSI pin) and also receive (MISO pin)
  inline static uint8_t transfer(uint8_t data) {
    SPDR = data;
    /*
     * The following NOP introduces a small delay that can prevent the wait
     * loop form iterating when running at the maximum speed. This gives
     * about 10% more speed, even if it seems counter-intuitive. At lower
     * speeds it is unnoticed.
     */
    asm volatile("nop");
    while (!(SPSR & (1<<SPIF))); // wait
    return SPDR;
  }
  inline static void transfer(void *buf, uint16_t count) {
    if (count == 0) return;
    uint8_t *p = (uint8_t *)buf;
    SPDR = *p;
    while (--count > 0) {
      uint8_t out = *(p + 1);
      while (!(SPSR & (1<<SPIF)));
      uint8_t in = SPDR;
      SPDR = out;
      *p++ = in;
    }
    while (!(SPSR & (1<<SPIF)));
    *p = SPDR;
  }
};

extern SPIClass SPI;

#endif
