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
	SCHDLR_ERR_TASK_NOT_CREATED

} scheduler_error_t;

int addTask(TaskHandle taskHandle, uint32_t interval, void(*taskFunction)(), bool oneShot);

int editInterval(TaskHandle taskToChange, uint32_t newInterval);
int deleteTask(TaskHandle taskToDelete);
int disableTask(TaskHandle taskToDisable);
int enableTask(TaskHandle taskToEnable);

int executeTasks();

#endif
