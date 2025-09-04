#include <avr/io.h>
#include <avr/interrupt.h>
#include "mcu_init.h"
#include "millis.h"
#include "scheduler.h"
#include "usart.h"

#define LED1	3
#define LED2	4

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

void thirdTask() {

	editInterval(secondTask, 10000);
	return;

}

int main() {

	cli();

	GPIO_init();
	TMR0_init();
	Serial_Init(9600);

	sei();

	addTask(1000, firstTask); 
	addTask(1000, secondTask);
	addTask(10000, thirdTask);

	while(1) {

		executeTasks();

	}

	return 0;	

}
