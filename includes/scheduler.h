#ifndef SCHEDULER_H
#define SCHEDULER_H

void addTask(uint32_t, void(*)());
void editInterval(void(*)(), uint32_t);
void executeTasks();

#endif
