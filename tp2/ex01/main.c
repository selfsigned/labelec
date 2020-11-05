#include <avr/io.h>

// http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061B.pdf
// Chapter 16

// https://eleccelerator.com/avr-timer-calculator/

// PB1 is OC1A

// 62500 timer ticks with a prescaler of clk/256 to get 1Hz at 16MHz
int main() {
	// set our output
	DDRB |= (1 << PB1);

	// 16.11.1 toggle OC1A on compare match
	TCCR1A |= (1 << COM1A0);

	// prescaler of clk/256: CS12
	TCCR1B |= (1 << CS12);

	// tab 16-4 to set CTC mode (clean timer on compare)
	//   -> mode 4: WGM12
	TCCR1B |=  (1 << WGM12);

	// set 16bit timer1 to 0, fig 16.11.4
	TCNT1 = 0;

	// compare register
	OCR1A = 62500;

	for (;;) {}
}
