/*
 * tp1_entregable.cpp
 *
 * Created: 03/04/2022 10:40:52 p. m.
 * Author : Alejandro Mejía
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
const uint8_t sequence[] = {0x81, 0x42, 0x24, 0x18};
const uint8_t sequence_length = sizeof(sequence) / sizeof(*sequence);

void setup() {
	DDRC = 0x00; // Pulsador: PINC as input
	PORTC = 0x01; // Pull UP: Enable
	DDRB = 0xFF; // LEDs: PINB as Output
}

void turnOn(int state, int position) {
	if (state) {
		PORTB = sequence[(sequence_length - 1) - position];
	} else {
		PORTB = sequence[position];
	}
	_delay_ms(10);
}

void loop(int *state, int *position) {
	turnOn(*state, *position);
	if ((PINC & (1<<PINC0)) == 0) {
		_delay_ms(10);
		while ((PINC & (1<<PINC0)) == 0);
		_delay_ms(10);
		*state = !*state;
		*position = 0;
		} else {
		*position = (*position + 1) % sequence_length;
	}
}


int main(void) {
	setup();
	int position = 0;
	int state = 0; // 0: Normal, 1: Invertido
	while (1) {
		loop(&state, &position);
	}
	return 0;
}

