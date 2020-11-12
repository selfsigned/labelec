#include <avr/io.h>
#include <inttypes.h>

// http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061B.pdf

#define TIMER1_PRE 256

volatile int8_t mid;

int main() {
	DDRB |= (1 << PB1);

	// clock 0 
	// clk/1024
	TCCR0B |= (1 << CS02) | (1 << CS00);
	
	// CTC mode
	TCCR0A |= (1 << WGM01);

	//toggle COMP B
	TCCR0A |= (1 << COM0B0);

	// 200HZ
	OCR0A = 77; // F_CPU / (1024 * 200) - 1;
	mid = OCR0A / 2;

	// enable timer0 interrupt
	TIMSK0 |= (1 << OCIE0B);

	// clock 1
	// prescaler of clk/256
	TCCR1B |= (1 << CS12);

	// tab 16-4 to set PWM fast 8
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12) | (1 << WGM13);

	/* // tab 16-2 non-inverting */
	TCCR1A |= (1 << COM1A1) ;

	__asm__("SEI");
	for (;;) {__asm__("SLEEP");}
}

// TIMER0 COMP_B
void __vector_15(void) __attribute__ ((signal, used));
void __vector_15(void) {
	static uint8_t i = 0;

	if (++i < mid) { // fade in
		ICR1 = F_CPU / TIMER1_PRE - 1;
		OCR1A = F_CPU / (TIMER1_PRE * (i * 0.1)) - 1;
	} else { // fade out
		OCR1A = F_CPU / TIMER1_PRE - 1;
		ICR1 = F_CPU / (TIMER1_PRE * (i * 0.1)) - 1;

		if (i == OCR0A) {i = 0;}
	};
}
