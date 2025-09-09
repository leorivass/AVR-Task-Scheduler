#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "mcu_init.h"
#include "millis.h"
#include "scheduler.h"
#include "usart.h"

#define LED1 3
#define LED2 4

TaskHandle welcomeTask;
TaskHandle blinkTask1;
TaskHandle blinkTask2;
TaskHandle changePatternTask;

void welcomeMessage() {

	Serial_Println("************Scheduler demo started**************");
	Serial_Println("***A welcome message must appear after 2000ms***");
	Serial_Println("***********LED1 blinks every 500ms**************");
	Serial_Println("***********LED2 blinks every 1000ms*************");
	Serial_Println("******The pattern will change after 20s*********\n");

	enableTask(blinkTask1); // First blink task starting...
	enableTask(blinkTask2); // Second blink task staring...

	return;
}

void toggleLED1() {
	PORTA ^= (1 << LED1);
	return;
}

void toggleLED2() {
	PORTA ^= (1 << LED2);
	return;
}

void changePattern() {
	editInterval(blinkTask1, 2000); // LED1 blinks every 2s
	Serial_Println("Now, LED1 blinks every 2s!");
	editInterval(blinkTask2, 5000); // LED2 blinks every 5s
	Serial_Println("Now, LED2 blinks every 5s!");
}

int main() {

	cli();

	GPIO_init();
	TMR0_init();
	Serial_Init(9600);

	sei();

	// Welcome message task (oneShot)
	welcomeTask = addTask(2000, welcomeMessage, true); // Welcome message will be shown after 2s

	// Main tasks 
	blinkTask1 = addTask(500, toggleLED1, false); // LED1 blinks every 500ms
	disableTask(blinkTask1); // blinkTask1 will start disabled

	blinkTask2 = addTask(1000, toggleLED2, false); // LED2 blinks every 1s
	disableTask(blinkTask2); // blinkTask2 will start disabled

	changePatternTask = addTask(20000, changePattern, true); // Change blinky pattern for each LED

	while (1) {
		executeTasks();
	}

	return 0;

}