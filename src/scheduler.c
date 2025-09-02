#include <avr/io.h>
#include <stdlib.h>
#include "millis.h"
#include "scheduler.h"
#include "usart.h"

typedef struct Task {

	uint32_t interval;
	uint32_t lastRunTime;
	void (*taskFunction)();

} Task;

typedef struct TaskNode {

	Task task;
	struct TaskNode* next;	

} TaskNode;

TaskNode* head = NULL;

void addTask(uint32_t interval, void(*taskFunction)()) {

	TaskNode* newNode = (TaskNode*)malloc(sizeof(TaskNode));

	if (newNode == NULL) {
        Serial_Println("Error: No se pudo asignar memoria para la tarea");
        return;
    }
	
	newNode->task.interval = interval;
	newNode->task.lastRunTime = 0;
	newNode->task.taskFunction = taskFunction;
	newNode->next = head;
	head = newNode;

	return;

}

void executeTasks() {
 
	TaskNode* currentTask = head;

	while (currentTask != NULL) {
		
		if (millis() - currentTask->task.lastRunTime >= currentTask->task.interval) {
			currentTask->task.lastRunTime = millis();
			currentTask->task.taskFunction();
		}
	
		currentTask = currentTask->next;

	}

	return;

}
