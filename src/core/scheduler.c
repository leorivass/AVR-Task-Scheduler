#include <avr/io.h>
#include <stdlib.h>

#include "core/scheduler.h"
#include "utils/millis.h"

TaskHandle head = NULL;
TaskHandle previousNode = NULL;

int addTask(TaskHandle* taskHandle, uint32_t interval, void(*taskFunction)(), bool oneShot) {

	TaskHandle newNode = (TaskHandle)malloc(sizeof(TaskNode));

	if (newNode == NULL) return -SCHDLR_ERR_TASK_NOT_CREATED;

	newNode->task.interval = interval;
	newNode->task.lastRunTime = 0;
	newNode->task.taskFunction = taskFunction;
	newNode->task.status = true;
	newNode->task.oneShot = oneShot;
	newNode->ID = newNode;
	*taskHandle = newNode;

	if (head == NULL) head = newNode;
	else previousNode->next = newNode;

	newNode->next = NULL;
	previousNode = newNode;

	return SCHDLR_OK;
}

int editInterval(TaskHandle taskToChange, uint32_t newInterval) {

	if (taskToChange == NULL) return -SCHDLR_ERR_NULL;

	taskToChange->task.interval = newInterval;
	return SCHDLR_OK;
}

int deleteTask(TaskHandle taskToDelete) {

	TaskNode* currentNode = head;
	TaskNode* previousNode = NULL;

	if (taskToDelete == NULL) return -SCHDLR_ERR_NULL;
	if (currentNode == NULL)  return -SCHDLR_ERR_NO_TASKS;

	while (currentNode != NULL) {

		if (currentNode->ID == taskToDelete->ID) break;

		previousNode = currentNode;
		currentNode = currentNode->next;

	}

	if (currentNode == head) head = currentNode->next;
	else previousNode->next = currentNode->next;

	free(currentNode);

	return SCHDLR_OK;
}

int disableTask(TaskHandle taskToDisable) {

	if (taskToDisable == NULL) return -SCHDLR_ERR_NULL;

	taskToDisable->task.status = false;
	return SCHDLR_OK;
}

int enableTask(TaskHandle taskToEnable) {

	if (taskToEnable == NULL) return -SCHDLR_ERR_NULL;

	taskToEnable->task.status = true;
	return SCHDLR_OK;
}

int executeTasks() {
 
	TaskNode* currentTask = head;
	TaskNode* oldTask = NULL;
	bool oneShotFlag;

	uint32_t currentMillis = millis();

	if (currentTask == NULL) return -SCHDLR_ERR_NO_TASKS;

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

	return SCHDLR_OK;
}
