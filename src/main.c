#include <avr/io.h>
#include <avr/interrupt.h>
#include "mcu_init.h"
#include "millis.h"
#include "scheduler.h"
#include "usart.h"

void firstTask() {

	PORTA ^= (1 << LED1);
	Serial_Println("El primer led ha sido encendido!");
	return;

}

void secondTask() {

	PORTA ^= (1 << LED2);
	Serial_Println("El segundo led ha sido encendido!");
	return;

}

int main() {

	cli();

	GPIO_init();
	TMR0_init();
	Serial_Init(9600);

	sei();

	addTask(1000, firstTask); 
	addTask(2000, secondTask);

	while(1) {

		executeTasks();

	}

	return 0;	

}
