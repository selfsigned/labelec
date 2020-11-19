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
	UCSR0A |= (1 << U2X0);

	// enable tx and rx
	UCSR0B |= (1 << TXEN0) | (1 << RXEN0);

	// enable rx interrupt
	UCSR0B |= (1 << RXCIE0);
}

void uart_tx(char c)
{
	// wait for empty buffer
	while (!(UCSR0A & (1 << UDRE0)));

	UDR0 = c;
}

int main()
{
	uart_init(UBRR_VALUE);

	__asm__("SEI");
	for (;;) {}
}

void __attribute__ ((signal, used)) USART_RX_vect() {
	char c = UDR0;

	if (c >= 'a' && c <= 'z') {
		c -= 32;
	} else if (c >= 'A' && c <= 'Z') {
		c += 32;
	}
	uart_tx(c);
}
