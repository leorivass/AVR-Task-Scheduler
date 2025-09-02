#include <avr/io.h>
#include <avr/interrupt.h>
#include "millis.h"

volatile uint32_t miliseconds = 0;

ISR(TIMER0_COMPA_vect) {
	miliseconds++;
}

uint32_t millis() {

	uint8_t sreg = SREG;
	
	cli();
	uint32_t ms = miliseconds;
	
	SREG = sreg;

	return ms;

}
