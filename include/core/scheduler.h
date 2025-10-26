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

typedef enum {

	SCHDLR_OK,
	SCHDLR_ERR_NULL,
	SCHDLR_ERR_NO_TASKS,

} scheduler_error_t;

TaskHandle addTask(uint32_t, void(*)(), bool);

int editInterval(TaskHandle, uint32_t);
int deleteTask(TaskHandle);
int disableTask(TaskHandle);
int enableTask(TaskHandle);

int executeTasks();

#endif
