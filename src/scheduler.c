#include <avr/io.h>
#include <stdlib.h>
#include "millis.h"
#include "scheduler.h"
#include "usart.h"

TaskNode* head = NULL;

void addTask(uint32_t interval, void(*taskFunction)(), bool oneShot) {

	TaskNode* newNode = (TaskNode*)malloc(sizeof(TaskNode));

	if (newNode == NULL) {
        Serial_Println("Error: Memory could not be assigned for the task");
        return;
    }
	
	newNode->task.interval = interval;
	newNode->task.lastRunTime = 0;
	newNode->task.taskFunction = taskFunction;
	newNode->task.status = true;
	newNode->task.oneShot = oneShot;
	newNode->next = head;
	head = newNode;

	return;

}

void editInterval(void(*taskToChange)(), uint32_t newInterval) {

	TaskSearchResult result = findTask(taskToChange);

	if (result.found) {
		result.taskFound->task.interval = newInterval;
	}

	return;

}

void deleteTask(void(*taskToDelete)()) {

	TaskSearchResult result = findTask(taskToDelete);

	if (result.found) {
		
		if (result.taskFound == head) {
			head = result.taskFound->next;
		}
		else {
			result.previousTask->next = result.taskFound->next;
		}

		free(result.taskFound);
		Serial_Println("Task was removed succesfully");

	}

	return;

}

TaskSearchResult findTask(void(*taskToFind)()) {

	TaskSearchResult result;

	result.taskFound = NULL;
	result.previousTask = NULL;
	result.found = false;

	TaskNode* currentNode = head;
	TaskNode* previousNode = NULL;

	if (currentNode == NULL) {
		Serial_Println("Error: There are no elements in the list");
		return result;
	}

	while (currentNode != NULL) {

		if (currentNode->task.taskFunction == taskToFind) {
			result.taskFound = currentNode;
			result.previousTask = previousNode;
			result.found = true;
				
			break;
		}

		previousNode = currentNode;
		currentNode = currentNode->next;

	}

	if (!result.found) Serial_Println("Error: Task could not be found");

	return result;

}

void disableTask(void(*taskToDisable)()) {

	TaskSearchResult result = findTask(taskToDisable);

	if (result.found) {
		result.taskFound->task.status = false;
	}

	return;

}

void enableTask(void(*taskToEnable)()) {

	TaskSearchResult result = findTask(taskToEnable);

	if (result.found) {
		result.taskFound->task.status = true;
	}

	return;

}

void executeTasks() {
 
	TaskNode* currentTask = head;
	bool oneShotFlag;

	while (currentTask != NULL) {

		oneShotFlag = false;
		
		if (millis() - currentTask->task.lastRunTime >= currentTask->task.interval && currentTask->task.status) {
			currentTask->task.lastRunTime = millis();
			currentTask->task.taskFunction();

			if (currentTask->task.oneShot) {
				TaskNode* taskToDelete = currentTask;
				currentTask = currentTask->next;

				oneShotFlag = true;

				deleteTask(taskToDelete->task.taskFunction);
			}

		}
	
		if (!oneShotFlag) currentTask = currentTask->next;

	}

	return;

}
  