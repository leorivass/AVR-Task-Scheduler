#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdbool.h>

void addTask(uint32_t, void(*)(), bool);
void editInterval(void(*)(), uint32_t);
void deleteTask(void(*)());
void executeTasks();
void disableTask(void(*)());
void enableTask(void(*)());

typedef struct Task {

	uint32_t interval;
	uint32_t lastRunTime;
	void (*taskFunction)();
    bool status;
	bool oneShot;

} Task;

typedef struct TaskNode {

	Task task;
	struct TaskNode* next;	

} TaskNode;

typedef struct {

	TaskNode* taskFound;
	TaskNode* previousTask;
	bool found;

} TaskSearchResult;

TaskSearchResult findTask(void(*)());

#endif
