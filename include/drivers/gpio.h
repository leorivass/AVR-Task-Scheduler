#ifndef GPIO_H
#define GPIO_H

#include <avr/io.h>

typedef enum {
    GPIO_OK,
    GPIO_ERR_INVALID_DIRECTION,
    GPIO_ERR_INVALID_STATUS,
    GPIO_ERR_INVALID_BIT,
    GPIO_ERR_REGISTER_NOT_EXIST,
    GPIO_ERR_UNKNOWN
} gpio_err_t;

typedef enum {
    INPUT, 
    OUTPUT, 
} direction;

typedef enum {
    LOW, 
    HIGH 
} output_status;

/* Function to declare a pin as an output or input */
int gpio_set_direction(volatile uint8_t *DDR, uint8_t bit, direction dir);

/* Function to interact with the pins */
int gpio_set_value(volatile uint8_t *PORT, uint8_t bit, output_status status);
int gpio_get_value(volatile uint8_t *PIN, uint8_t bit);

#endif