#include <avr/io.h>

int main() {
	DDRB = (1 << PB3);

	for (;;) {
		PORTB = !(PIND & (1 << PD3)) ? (1 << PB3) : 0;
	}
}
