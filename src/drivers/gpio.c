#include <assert.h>
#include "drivers/gpio.h"

pins_desc pins_map[] = {
    {&DDRA, &PORTA, &PINA, {22, 23, 24, 25, 26, 27, 28, 29}, 0}, 
    {&DDRB, &PORTB, &PINB, {53, 52, 51, 50, 10, 11, 12, 13}, 0},  
    {&DDRC, &PORTC, &PINC, {37, 36, 35, 34, 33, 32, 31, 30}, 0},
    {&DDRD, &PORTD, &PIND, {21, 20, 19, 18, -1, -1, -1, 38}, 0},
    {&DDRE, &PORTE, &PINE, {0, 1, -1, 5, 2,  3, -1,  -1}, 0},
    /* This space is for register F */
    {&DDRG, &PORTG, &PING, {41, 40, 39, -1, -1, 4, -1, -1}, 0},
    {&DDRH, &PORTH, &PINH, {17, 16, -1, 6, 7, 8, 9, -1}, 0},
    {&DDRJ, &PORTJ, &PINJ, {15, 14, -1, -1, -1, -1, -1, -1}, 0},
    /* This space is for register k */
    {&DDRL, &PORTL, &PINL, {49, 48, 47, 46, 45, 44, 43, 42}, 0}
};

pins_desc find_gpio_desc(uint8_t pin) {

    for(uint8_t i = 0; i < (sizeof(pins_map) / sizeof(pins_desc)); i++) {
        for(uint8_t j = 0; j < 8; j++) {
            if (pins_map[i].digitalPins[j] == pin) {
                pins_map[i].bit = j;
                return pins_map[i];
            }
        }
    }

    return (pins_desc){0};
}

void gpio_set_direction(uint8_t pin, direction direction) {
    
    assert(pin >= 0 && pin <= 54);

    pins_desc gpio_desc = find_gpio_desc(pin);

    switch (direction) {
 
        case INPUT:
            *(gpio_desc.ddr) = *(gpio_desc.ddr) & ~(1 << gpio_desc.bit);
            break;

        case OUTPUT:
            *(gpio_desc.ddr) = *(gpio_desc.ddr) | (1 << gpio_desc.bit);
            break;

    }

    return;
}

void gpio_set_value(uint8_t pin, output_status status) {
    
    assert(pin >= 0 && pin <= 54);

    pins_desc gpio_desc = find_gpio_desc(pin);

    switch (status) {
 
        case LOW:
            *(gpio_desc.port) = *(gpio_desc.port) & ~(1 << gpio_desc.bit);
            break;

        case HIGH:
            *(gpio_desc.port) = *(gpio_desc.port) | (1 << gpio_desc.bit);
            break;

    }

    return;
}

int gpio_get_value(uint8_t pin) {

    assert(pin >= 0 && pin <= 54);

    pins_desc gpio_desc = find_gpio_desc(pin); 

    if (*(gpio_desc.pin) & (1 << gpio_desc.bit)) {
        return HIGH;
    }
    else {
        return LOW;
    }

    return 0;
}