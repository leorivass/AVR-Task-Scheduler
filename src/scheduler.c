#include <avr/io.h>
#include <stdlib.h>
#include <stdbool.h>
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

void editInterval(void(*taskToChange)(), uint32_t newInterval) {

	TaskNode* currentTask = head;
	bool taskFound = false;

	if (currentTask == NULL) {
		Serial_Println("Error: No hay elementos en la lista para editar");
		return;

	}

	while (currentTask != NULL) {

		if (taskToChange == currentTask->task.taskFunction) {
			currentTask->task.interval = newInterval;
			taskFound = true;
			break;

		}

		currentTask = currentTask->next;

	}

	if (!taskFound) Serial_Println("Error: No se encontró la tarea especificada");

	return;

}

void deleteTask(void(*taskToDelete)()) {

	TaskNode* currentTask = head;
	TaskNode* previousTask = NULL;
	
	bool taskFound = false;

	if (currentTask == NULL) {
		Serial_Println("Error: No hay elementos en la lista para eliminar");
		return;

	}

	while (currentTask != NULL) {

		if (currentTask->task.taskFunction == taskToDelete) {
		
			if (currentTask == head) {
				head = currentTask->next;
			}
			else {
				previousTask->next = currentTask->next;
			}

			free(currentTask);

			Serial_Println("La tarea fue eliminada exitosamente");
			
			taskFound = true;
			break;
		}
		
		previousTask = currentTask;
		currentTask = currentTask->next;
		
	}

	if (!taskFound) Serial_Println ("Error: No se encontró la tarea especificada");

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
