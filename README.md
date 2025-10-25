# AVR-Task-Scheduler
A simple linked list-based task scheduler implemented in C for AVR microcontrollers, designed and tested on the ATmega2560.

## Features
- **TaskHandle system** for efficient task management
- Add repetitive or one-shot tasks with custom intervals 
- Edit task intervals at runtime
- Delete tasks at runtime
- Enable/disable tasks at runtime
- Execute tasks based on millis()

## Requirements
- AVR-GCC toolchain
- CMake
- Atmega2560 or compatible AVR microcontroller

## Usage

### 1. Clone the repository
```bash
git clone https://github.com/leorivass/AVR-Task-Scheduler.git
```

### 2. Init CMake in the build directory
```bash
cd build
cmake ..
```

### 3. Compile the task scheduler in the build directory
```bash
make
```

### 4. Flash the program to the microcontroller
```bash
make flash
```

> **Note:** The `main.c` program includes an example to demonstrate the scheduler functionality.
