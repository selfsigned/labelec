#include <avr/io.h>

// Relevant datasheet http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf
// chapter 13.2

// We need to turn on the led by setting PB3 to high
int main() {
	// PB3 is, as it's name imply, the third pin on PORTB
	//
	// Table 13-1 indicates that we need both and DDB and PORTB set to 1 on PB3
	PORTB = (1 << PB3);
	DDRB = (1 << PB3);
}
