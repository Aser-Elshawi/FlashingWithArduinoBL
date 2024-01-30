#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <avr/interrupt.h>
#include <OS.h>
#include <Md_QUEUE.h>
#include <UART.h>


using namespace std;


   void Task100ms(void);
   void Task20ms(void);
   void Task1Sec(void);
   void Task5ms(void);
   void Tasks_Init(void);

   //RF24 radio(CE_PIN.PORT_D.PIN_7, CSN_PIN.PORT_B.PIN_0);
   USART Md_USART(MY_UBRR);
int main(void){
	Tasks_Init();
	
	    //creating OS tasks
	    OS_CreateNewTask(Task100ms, 1000);
	    OS_CreateNewTask(Task20ms, 200);
	    OS_CreateNewTask(Task5ms, 50);
	    OS_CreateNewTask(Task1Sec,10000);
	    //Updat OS
	    while(1) OS_ServeOS();

}



void Tasks_Init(void){
       OS_Init();
       DDRB = (1<<5);
}
void Task100ms(void)
{

}

void Task20ms(void)
{
	// here call uart service function


	setupIO();

	char data;
	//initPWM();

	// while (true) {
	if(Md_USART.receive(&data)){
		//PORTB |= (1 << PORTB5);
		if (data == '1') {
			PORTB |= (1 << PORTB5); // Turn on built-in LED
			setRGBColor(0, 10, 0); // Red RGB
			Md_USART.print((char *)"Turning On LED...\n");
		} else if (data == '0') {
			PORTB &= ~(1 << PORTB5); // Turn off built-in LED
			setRGBColor(0, 0, 0); // Off
			Md_USART.print((char *)"Turning Off LED...\n");
		}
	}

}
void Task5ms(void){
	Md_USART.service();
}

void Task1Sec(void)
{
	//PORTB ^= (1<<5);

}
