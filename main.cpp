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

void Task5Sec(void);
void Task1Sec(void);

void Tasks_Init(void);

int main(void){
	Tasks_Init();
	    //creating OS tasks

	    OS_CreateNewTask(Task1Sec,10000);
	    OS_CreateNewTask(Task5Sec,50000);
	    //Updat OS
	    while(1) OS_ServeOS();

}

void Tasks_Init(void){
       OS_Init();
    	   uart.println("Init ..");
}

void Task1Sec(void)
{
	static uint8_t FiveSecCount = 1;
	if(FiveSecCount%5 == 0){
		uart.println("Hello");
	}
	FiveSecCount++;
}
void Task5Sec(void)
{
		uart.println("Hello2");

}
