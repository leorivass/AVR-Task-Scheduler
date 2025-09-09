#include <avr/io.h>
#include <stdlib.h>
#include "millis.h"
#include "scheduler.h"
#include "usart.h"

TaskHandle head = NULL;

TaskHandle addTask(uint32_t interval, void(*taskFunction)(), bool oneShot) {

	TaskHandle newNode = (TaskHandle)malloc(sizeof(TaskNode));

	if (newNode == NULL) {
        Serial_Println("Error: Memory could not be assigned for the task");
        return NULL;
    }
	
	newNode->task.interval = interval;
	newNode->task.lastRunTime = 0;
	newNode->task.taskFunction = taskFunction;
	newNode->task.status = true;
	newNode->task.oneShot = oneShot;
	newNode->next = head;
	newNode->ID = newNode;
	head = newNode;

	return newNode;

}

void editInterval(TaskHandle taskToChange, uint32_t newInterval) {
	taskToChange->task.interval = newInterval;
	return;
}

void deleteTask(TaskHandle taskToDelete) {

	TaskNode* currentNode = head;
	TaskNode* previousNode = NULL;

	if (currentNode == NULL) {
		Serial_Println("Error: There are no elements in the list");
		return;
	}

	while (currentNode != NULL) {

		if (currentNode->ID == taskToDelete->ID) break;

		previousNode = currentNode;
		currentNode = currentNode->next;

	}

	if (currentNode == head) head = currentNode->next;
	else previousNode->next = currentNode->next;

	free(currentNode);

	return;

}

void disableTask(TaskHandle taskToDisable) {
	taskToDisable->task.status = false;
	return;
}

void enableTask(TaskHandle taskToEnable) {
	taskToEnable->task.status = true;
	return;
}

void executeTasks() {
 
	TaskNode* currentTask = head;
	TaskNode* oldTask = NULL;
	bool oneShotFlag;

	uint32_t currentMillis = millis();

	while (currentTask != NULL) {

		oneShotFlag = false;
		
		if (currentMillis - currentTask->task.lastRunTime >= currentTask->task.interval && currentTask->task.status) {
			currentTask->task.lastRunTime = currentMillis;
			currentTask->task.taskFunction();

			if (currentTask->task.oneShot) {
				oldTask = currentTask;
				currentTask = currentTask->next;
				deleteTask(oldTask);

				oneShotFlag = true;
			}
		}
	
		if(!oneShotFlag) {
			oldTask = currentTask;
			currentTask = currentTask->next;
		}
	}

	return;

}
