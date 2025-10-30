# AVR-Task-Scheduler
A FIFO linked list-based task scheduler implemented in C for AVR microcontrollers, designed and tested on the Atmega2560.

## Features
- **TaskHandle system** based on millis for efficient task management
- Add repetitive or one-shot tasks with custom intervals 
- Edit task intervals at runtime
- Delete, enable, and disable tasks at runtime
- Hardware Abstraction Layer (HAL) for GPIO pins

## Requirements
- AVR-GCC toolchain
- CMake
- An AVR microcontroller

## Usage

### 1. Clone the repository
```bash
git clone https://github.com/leorivass/AVR-Task-Scheduler.git
```

### 2. Modify CMakeLists.txt for your microcontroller (optional)
- If your microcontroller is different from the Atmega2560, check and modify the next variables or parameters in CMakeLists.txt
```
set(MCU atmega2560)
avrdude -v -c {this_parameter} -p {this_parameter} -P /dev/ttyACM0 -U flash:w:main.hex -D
```
- If you are using an Atmega2560, you can leave everything unchanged.
- Next to MCU in ```set(MCU atmega2560)```, place the microcontroller you are using to test this project. 
- `-c` parameter corresponds to the programmer you have. If you are using an Arduino board to program your MCU, you can leave this parameter unchanged. To look for the value you need to put here, according to your programmer, use the next command:
```
  avrdude -c ?
```
- `-p` parameter corresponds to your MCU. AVRDUDE is a program for downloading and uploading the on-chip memories of Microchip's AVR microcontrollers. To look for the value you need to put here, according to your MCU, use the next command:
```
  avrdude -p ?
```
- After making the right changes, save the file and go to the next step.
    
### 3. Init CMake in the build directory
```
cd build
cmake ..
```

### 4. Compile the task scheduler in the build directory
```
make
```

### 5. Flash the program to the microcontroller
```
make flash
```

## Where can I start to program?
The `main.c` file is the entry point of the project, where you can start implementing your ideas in code. By default, `main.c` includes an example to show the scheduler functionality. This example uses the serial port. If you want to visualize the messages through the terminal, at least on Linux, you can install `screen` by using the following command:

```
sudo apt install screen
```

To execute a terminal, use the following command:

```
screen /dev/ttyACM0 9600
```

Where `/dev/ttyACM0` is the character device file associated with your programmer or MCU, and `9600` is the baud rate configured in `main.c`.

## Contributing

Feel free to submit issues, fork the repository, and create pull requests for any improvements.

## License

This project is licensed under the MIT LICENSE.


