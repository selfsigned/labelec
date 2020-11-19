#include <avr/io.h>

#define UBRR_VALUE ((F_CPU / 16UL / UART_BAUDRATE) - 1)

void timer_init()
{
	//prescaler clk/256
	TCCR1B |= (1 << CS12);

	// TIMER1_OVF enable
	TIMSK1 |= (1 << TOIE1);
}

void uart_init()
{
	// set baud rate
	UBRR0 = UBRR_VALUE;

	// frame format 8bit, no parity, 1 stop bit
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);

	// enable tx
	UCSR0B |= (1 << TXEN0);
}

void uart_tx(char c)
{
	UDR0 = c;
}

int main()
{
	uart_init();
	timer_init();

	__asm__("SEI");
	for (;;) {
		__asm__("SLEEP");
	}
}

void TIMER1_OVF_vect(void) __attribute__ ((signal, used));
void TIMER1_OVF_vect() {
	uart_tx('Z');
}
