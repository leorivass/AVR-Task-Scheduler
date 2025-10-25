#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdbool.h>

typedef struct Task {

	uint32_t interval;
	uint32_t lastRunTime;
	void (*taskFunction)();
    bool status;
	bool oneShot;

} Task;

struct TaskNode;
typedef struct TaskNode* TaskHandle;

typedef struct TaskNode {

	Task task;
	TaskHandle ID;
	TaskHandle next;	

} TaskNode;

TaskHandle addTask(uint32_t, void(*)(), bool);

void editInterval(TaskHandle, uint32_t);
void deleteTask(TaskHandle);
void disableTask(TaskHandle);
void enableTask(TaskHandle);

void executeTasks();

#endif
