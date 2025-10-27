#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "core/scheduler.h"
#include "core/mcu_init.h"
#include "utils/millis.h"
#include "drivers/usart.h"
#include "drivers/gpio.h"

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
	
	if (gpio_get_value(LED1) == 0) {
		gpio_set_value(LED1, HIGH);
	}
	else {
		gpio_set_value(LED1, LOW);
	}

	return;
}

void toggleLED2() {
	
	if (gpio_get_value(LED2) == 0) {
		gpio_set_value(LED2, HIGH);
	}
	else {
		gpio_set_value(LED2, LOW);
	}

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
	addTask(&welcomeTask, 2000, welcomeMessage, true); // Welcome message will be shown after 2s

	// Main tasks 
	addTask(&blinkTask1, 500, toggleLED1, false); // LED1 blinks every 500ms
	disableTask(blinkTask1); // blinkTask1 will start disabled

	addTask(&blinkTask2, 1000, toggleLED2, false); // LED2 blinks every 1s
	disableTask(blinkTask2); // blinkTask2 will start disabled

	addTask(&changePatternTask, 20000, changePattern, true); // Change blinky pattern for each LED

	while (1) {
		executeTasks();
	}

	return 0;

}