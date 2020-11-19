#include <inttypes.h>
#include <avr/io.h>

#define UBRR_VALUE ((F_CPU / 8UL / UART_BAUDRATE) - 1)

void uart_init(uint16_t ubrr)
{
	// set baud rate
	UBRR0 = ubrr;

	// frame format 8bit, no parity, 1 stop bit
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);

	// U2X (double the speed)
	UCSR0A = (1 << U2X0);

	// enable tx and rx
	UCSR0B |= (1 << TXEN0) | (1 << RXEN0);
}

void uart_tx(char c)
{
	// wait for empty buffer
	while (!(UCSR0A & (1 << UDRE0)));

	UDR0 = c;
}

char uart_rx()
{
	while (!(UCSR0A & (1<<RXC0)));

	return UDR0;
}

int main()
{
	uart_init(UBRR_VALUE);

	for (;;) {
		uart_tx(uart_rx());
	}
}
