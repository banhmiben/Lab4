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

enum LEDStates {Start, On1, On1R, On2, On2R} LEDState;

void Tick_LED() {
	
	switch(LEDState) { //transitions
		case(Start) :
			LEDState = On1;
			break;
		case(On1) :
			if (PINA == 0x01) {
				LEDState = On1;
			} else {
				LEDState = On1R;
			} break;
		case(On1R) :
			if (PINA == 0x01) {
				LEDState = On2;
			} else {
				LEDState = On1R;
			} break;
		case(On2) :
			if (PINA == 0x01) {
				LEDState = On2;
			} else {
				LEDState = On2R;
			} break;
		case(On2R) :
			if (PINA == 0x01) {
				LEDState = On1;
			} else {
				LEDState = On2R;
			} break;
		default:
			LEDState = Start;
			break;
	}
	
	switch(LEDState) { //state actions
		case(Start) :
			break;
		case(On1) :
			PORTB = 0x01;
			break;
		case(On1R) :
			PORTB = 0x01;
			break;
		case(On2) :
			PORTB = 0x02;
			break;
		case(On2R) :
			PORTB = 0x02;
			break;
		default: 
			PORTB = 0x01;
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
	LEDState = Start;
    while (1) {
		Tick_LED();
    }
    return 1;
}
