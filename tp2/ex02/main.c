#include <avr/io.h>

// http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061B.pdf

// fast PWM
int main() {
	DDRB |= (1 << PB1);

	// prescaler of clk/256
	TCCR1B |= (1 << CS12);

	// tab 16-4 to set PWM fast 8
	//   -> mode 14: WGM13 WMG12 WGM11
	//               TOP: ICR1
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12) | (1 << WGM13);

	// tab 16-2 non-inverting
	TCCR1A |= (1 << COM1A1);

	// 10% duty cycle
	ICR1 = (F_CPU/256) - 1;
	OCR1A = ((F_CPU/256)-1) * 0.10;
	for (;;) {}
}
