/*
 * UARTStreamBuf
 *
 *  Created on: Dec 27, 2023
 *      Author: asere
 */

#ifndef UART_UART_H_
#define UART_UART_H_

#ifdef __UART__
#define EXTERN
#else
#define EXTERN extern
#endif

#define RX_HWBUFF_SIZE	5
#define TX_HWBUFF_SIZE	100

typedef enum HWuart_Status_E{
	HWuart_Rx_No_Data,
	HWuart_Rx_OK,
	HWuart_Rx_OK_Again,
	HWuart_Rx_OverFlow,
	HWuart_Tx_Ok,
	HWuart_Tx_BufferFull,
	HWuart_TX_Buffered,
	HWuart_Tx_OverFlow,
	HWuart_MEM_ERR
	}HWuart_Status_T;

typedef enum HWuart_state_E{
		HWuart_transmitting,
		HWuart_trans_in_byte,
		HWuart_trans_overflow,
		HWuart_idle
	}HWuart_state_T;

#if defined(__AVR_ATmega32__)
#define EnableTxInterrupt()		UCSRB |= (1<<UDRIE)

#define DisableTxInterrupt()	UCSRB &= ~(1<<UDRIE)

#define EnableRxInterrupt()		UCSRB |= (1 << RXCIE)

#define DisableRxInterrupt()	UCSRB &= ~(1<<RXCIE)
#elif defined(__AVR_ATmega328P__)
#define EnableTxInterrupt()		UCSR0B |= (1<<UDRIE0)

#define DisableTxInterrupt()	UCSR0B &= ~(1<<UDRIE0)

#define EnableRxInterrupt()		UCSR0B |= (1 << RXCIE0)

#define DisableRxInterrupt()	UCSR0B &= ~(1<<RXCIE0)
#endif

class UART {
public:
		 UART(long USART_BAUDRATE=9600);
	void printd(int value);
    void print(const char* format);
    void println(const char* format);

private:
    int getIntLength(int value);
    void intToCharArray(int value, char* buffer,int length);
    void init(long USART_BAUDRATE);
    void transmit(char c);
};

EXTERN UART uart;
#undef EXTERN
#endif /* UART_UART_H_ */
