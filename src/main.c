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
TaskHandle deleteAllTasks;

void welcomeMessage() {

	Serial_Println("************Scheduler demo started**************");
	Serial_Println("***A welcome message must appear after 2000ms***");
	Serial_Println("***********LED1 blinks every 500ms**************");
	Serial_Println("***********LED2 blinks every 1000ms*************");
	Serial_Println("******The pattern will change after 20s*********\n");

	enableTask(blinkTask1); 
	enableTask(blinkTask2); 

	return;
}

void toggleLED1() {
	
	if (gpio_get_value(&PINE, 4) == LOW) {
		gpio_set_value(&PORTE, 4, HIGH);
	}
	else {
		gpio_set_value(&PORTE, 4, LOW);
	}

	return;
}

void toggleLED2() {

	if (gpio_get_value(&PINH, 5) == LOW) {
		gpio_set_value(&PORTH, 5, HIGH);
	}
	else {
		gpio_set_value(&PORTH, 5, LOW);
	}

	return;
}

void changePattern() {
	editInterval(blinkTask1, 2000);
	Serial_Println("Now, LED1 blinks every 2s!");
	editInterval(blinkTask2, 5000); 
	Serial_Println("Now, LED2 blinks every 5s!");
}

void deleteAddedTasks() {
	deleteTask(welcomeTask);
	deleteTask(blinkTask1);
	deleteTask(blinkTask2);
	deleteTask(changePatternTask);
	deleteTask(deleteAllTasks);
}

int main() {

	cli();

	GPIO_init();
	TMR0_init();
	Serial_Init(9600);

	sei();

	/* Welcome message task (oneShot) */
	addTask(&welcomeTask, 2000, welcomeMessage, true); 

	/* LED1 blinks every 500ms */
	addTask(&blinkTask1, 500, toggleLED1, false);  
	disableTask(blinkTask1);

	/* LED2 blinks every 1s */
	addTask(&blinkTask2, 1000, toggleLED2, false);  
	disableTask(blinkTask2); 

	/* Change blinky pattern for each LED (oneShot) */
	addTask(&changePatternTask, 20000, changePattern, true); 

	/* Delete all added tasks (oneShot) */
	addTask(&deleteAllTasks, 30000, deleteAddedTasks, true);

	while (1) {
		executeTasks();
	}

	return 0;

}