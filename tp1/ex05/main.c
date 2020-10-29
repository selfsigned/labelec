#include <avr/io.h>

int main () {
	short int prev_state = 0;
	short int button;
	DDRB = (1 << PB3);

	for (;;) {
		button = (PIND & (1 << PD3));
		if  (prev_state && !button) {
			for (long int i = F_CPU / 500; --i;) {};
			PORTB ^= (1 << PB3);
		}
		prev_state = button;
	}
}
