#ifndef GPIO_H
#define GPIO_H

#include <avr/io.h>

typedef enum {
    INPUT, 
    OUTPUT, 
} direction;

typedef enum {
    LOW, 
    HIGH 
} output_status;

typedef struct pins_desc {
    volatile uint8_t *ddr;
    volatile uint8_t *port;
    volatile uint8_t *pin;
    const int8_t digitalPins[8]; 
    uint8_t bit;
} pins_desc;

pins_desc find_gpio_desc(uint8_t pin);

/* Function to declare a pin as an output or input */
void gpio_set_direction(uint8_t pin, direction direction);

/* Function to interact with the pins */
void gpio_set_value(uint8_t pin, output_status status);
int gpio_get_value(uint8_t pin);

#endif