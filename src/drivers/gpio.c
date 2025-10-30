#include <assert.h>
#include "drivers/gpio.h"

int gpio_set_direction(volatile uint8_t *DDR, uint8_t bit, direction dir) {
    
    if (DDR == NULL) return -GPIO_ERR_REGISTER_NOT_EXIST;
    if (bit > 7) return -GPIO_ERR_INVALID_BIT;

    switch (dir) {

        case INPUT:
            *DDR &= ~(1 << bit);
            break;
        
        case OUTPUT:
            *DDR |= (1 << bit);
            break;

        default:
            return -GPIO_ERR_INVALID_DIRECTION;

    }
    
    return GPIO_OK;
}

int gpio_set_value(volatile uint8_t *PORT, uint8_t bit, output_status status) {

    if (PORT == NULL) return -GPIO_ERR_REGISTER_NOT_EXIST;
    if (bit > 7) return -GPIO_ERR_INVALID_BIT;

    switch (status) {

        case LOW:
            *PORT &= ~(1 << bit);
            break;
        
        case HIGH:
            *PORT |= (1 << bit);
            break;

        default:
            return -GPIO_ERR_INVALID_STATUS;

    }
    
    return GPIO_OK;
}

int gpio_get_value(volatile uint8_t *PIN, uint8_t bit) {

    if (PIN == NULL) return -GPIO_ERR_REGISTER_NOT_EXIST;
    if (bit > 7) return -GPIO_ERR_INVALID_BIT;
    
    if (*PIN & (1 << bit)) {
        return HIGH;
    }
    else {
        return LOW;
    }

    return GPIO_ERR_UNKNOWN;
}