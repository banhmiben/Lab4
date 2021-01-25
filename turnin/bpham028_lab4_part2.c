/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char cnt;
enum States {Start, Init, Wait, Inc, Dec, Reset} State;

void Tick() {
	switch(State) {
		case Start:
			State = Init;
			break;
		case Init:
			State = Wait;
			break;
		case Wait:
			if (PINA == 0x03) {
				State = Reset;
			} else if (PINA == 0x02) {
				State = Dec;
			} else if (PINA == 0x01) {
				State = Inc;
			} break;
		case Inc:
			if (PINA == 0x01) {
				State = Inc;
			} else {
				State = Wait;
			} break;
		case Dec:
			if (PINA != 0x02) {
				State = Wait;
			} else {
				State = Dec;
			} break;
		case Reset:
			if (PINA == 0x03) {
				State = Reset;
			} else {
				State = Wait;
			} break;
		default:
			State = Start;
			break;
	}
	switch(State) {
		case Start:
			break;
		case Init:
			PORTC = 0x07;
			break;
		case Wait:
			break;
		case Inc:
			if (PORTC < 8) {
				++PORTC;
			} break;
		case Dec:
			if (PORTC >= 0) {
				PORTC = PORTC - 1;;
			} break;
		case Reset:
			PORTC = 0x00;
			break;
		default:
			PORTC = 0x07;
			break;
	}
}


int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	State = Start;

	while(1) {
		Tick();
	}

	return 1;
}
