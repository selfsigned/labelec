#include <avr/io.h>
#include <inttypes.h>

// It would be much better to use a timer based interrupt for debouncing
int main() {
	DDRB |= (1 << PB1);

	// interrupt sense control: rising edge
	EICRA |= (1 << ISC11) | (1 << ISC10);

	// activate interrupts on INT0
	EIMSK |= (1 << INT1);

	// (optional) standby sleep mode
	SMCR |= (1 << SM2) | (1 << SM1);

	// activate interrupts
	__asm__("SEI");

	for (;;){
		__asm__("SLEEP");
	};
}


// Signal to gcc that this is an interrupt,
//    interrupt attribute re-enables the I flag unlike signal
//    see: https://gcc.gnu.org/onlinedocs/gcc/AVR-Function-Attributes.html#AVR-Function-Attributes)
// vector 2 -> INT1
void __vector_2(void) __attribute__ ((signal, used));
void __vector_2(void) {
	PORTB ^= (1 << PB1);
	for (uint32_t i = F_CPU * 0.04; --i;) {}
}
