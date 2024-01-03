#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <avr/interrupt.h>
#include <RF24.h>
#include <OS.h>
#include <UART.h>
using namespace std;


   void Task100ms(void);
   void Task10ms(void);
   void Task1Sec(void);
   void Tasks_Init(void);

   RF24 radio(CE_PIN.PORT_D.PIN_7, CSN_PIN.PORT_B.PIN_0);

int main(void){
	Tasks_Init();
	
	    //creating OS tasks
	    OS_CreateNewTask(Task100ms, 1000);
	    OS_CreateNewTask(Task10ms, 100);
	    OS_CreateNewTask(Task1Sec,10000);
	    //Updat OS
	    while(1) OS_ServeOS();

}



void Tasks_Init(void){
       OS_Init();
       DDRB = (1<<5);
       _delay_ms(1000);
       if(!radio.begin()){
    	   uart.println("didn't initialize..");
       }else{
    	   uart.println("Wooooha ..");
       }
       radio.startListening();
}
void Task100ms(void)
   {


   }

   void Task10ms(void)
   {

   }


   void Task1Sec(void)
   {
	   //PORTB ^= (1<<5);

   }
