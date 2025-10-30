#include <avr/io.h>
#include "core/mcu_init.h"
#include "drivers/gpio.h"

void GPIO_init() {

	gpio_set_direction(&DDRH, 5, OUTPUT);
	gpio_set_direction(&DDRE, 4, OUTPUT);

	gpio_set_value(&PORTH, 5, LOW);
	gpio_set_value(&PORTE, 4, LOW);

	return;
}

void TMR0_init() {
	
	/* Initialise counter to 0 */
	TCNT0 = 0;

	/* Enable CTC mode
	 *
	 *	In CTC mode, the counter is cleared to zero when the counter value TCNT0 matches the OCR0A. 
	 *
	 */ 
	TCCR0A |= (1 << WGM01);

	// Set prescaler to 256
	TCCR0B |= (1 << CS02); 

	/* Generate an interrupt every 1ms
	 *
	 *	The 8-bit comparator continuously compares TCNT0 with the Output Compare Register OCR0A.
	 *	Whenever TCNT0 equals 0CR0A, the comparator signals a match. A match will set the Output
	 *	Compare Flag OCF0A at the next timer clock cycle. 
	 *
	 */
	OCR0A = 62;	

	/* Enable Output Compare Match A Interrupt
	 *
	 *	When the OCIE0A bit is written to one, and the I-bit in the Status Register is set, the 
	 *	Compare Match A interrupt is enabled. 
	 *
	 */
	TIMSK0 |= (1 << OCIE0A);

	return;
}
