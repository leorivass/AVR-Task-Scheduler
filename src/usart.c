#include <avr/io.h>
#include <usart.h>
#include <stdarg.h>

#define UBRR_VALUE (F_CPU / 16 / baud_rate - 1)

void Serial_Init(uint16_t baud_rate) {

    /* Set Baud Rate
     *    
     *    The USART Baud Rate Register (UBRRn) and the down-counter connected to it function as a programmable prescaler 
     *   or baud rate generator. A clock is generated each time the counter reaches zero. This clock is the baud rate 
     *   generator clock output. In order to get the baud rate, UBRRn Register must be loaded with a value determined by
     *   F_CPU / (16 * baud_rate) - 1 
     *       
     *   UBRRn Register has two parts: the first one are the four most significant bits and the second one contains 
     *   the eight least significant bits of the USART baud rate
     * 
     */
    UBRR0H = (uint8_t)(UBRR_VALUE >> 8);
    UBRR0L = (uint8_t)UBRR_VALUE;

    /* Set the character size
     *
     *   The UCSZ01:0 bits combined with the UCSZ02 bit in UCSR0B sets the number of data bits (Character Size) in a frame
     *   the Receiver and Transmitter use. 
     *   
     */
    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);

    /* Enable Transmitter
     *
     *   Writing the TXEN0 bit to one enables the USART Transmitter. 
     *
     */  
    UCSR0B |= (1 << TXEN0); 

    return;

}

void Serial_Transmit(char data) {

    /* Evaluate if USART Data Register (UDR0) is empty
     *
     *   The UDRE0 Flag indicates if the transmit buffer (UDR0) is ready to receive new data. If UDRE0 is one, the buffer is
     *   empty, and therefore ready to be written. While the transmit buffer is not empty, the CPU will wait for its use. 
     *
     */
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;

    return;

}

void Serial_Println(const char *format, ...) {

    char buffer[1000];

    va_list args;
    va_start(args, format); 
    
    vsprintf(buffer, format, args); 
    va_end(args); 

    for (int i = 0; buffer[i] != '\0'; i++) {
        Serial_Transmit(buffer[i]);
    }

    Serial_Transmit('\r');
    Serial_Transmit('\n');

    return;

}
