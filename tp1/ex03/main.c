#include <avr/io.h>

int main() {
	DDRB = (1 << PB3);

	for(;;) {
		for (long int i = F_CPU / 50; --i;) {
			__asm__("nop");
		}
		PORTB ^= (1 << PB3);
	}
}
