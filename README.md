# AVR-Task-Scheduler
A simple linked list-based task scheduler implemented in C for AVR microcontrollers, designed and tested on the ATmega2560.

## Features
- **TaskHandle system** for efficient task management
- Add repetitive or one-shot tasks with custom intervals 
- Edit task intervals at runtime
- Delete tasks at runtime
- Enable/disable tasks at runtime
- Execute tasks based on millis()

## Example Usage
The included `main.c` demonstrates the scheduler functionality with a simple LED blinking example.

## Requirements
- AVR-GCC toolchain
- ATmega2560 or compatible AVR microcontroller


