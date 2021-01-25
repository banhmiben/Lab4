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

enum DOOR_States {Start, InitLock, PoundKey, YUnlock} DOOR_State;

void Tick() {
	switch(DOOR_State) {
		case Start:
			DOOR_State = InitLock;
			break;
		case InitLock:
			if (PINA == 0x04) {
				DOOR_State = PoundKey;
			} else {
				DOOR_State = InitLock;
			} break;
		case PoundKey:
			if (PINA == 0x02) {
				DOOR_State = YUnlock;
			} else {
				DOOR_State = InitLock;
			} break;
		case YUnlock:
			if (PINA == 0x80) {
				DOOR_State = InitLock;
			} else {
				DOOR_State = YUnlock;
			} break;
		default:
			DOOR_State = Start;
			break;
	}
	switch(DOOR_State) {
		case Start:
			break;
		case InitLock:
			PORTB = 0x00;
			PORTC = InitLock;
			break;
		case PoundKey:
			PORTC = PoundKey;
			break;
		case YUnlock:
			PORTB = 0x01;
			PORTC = YUnlock;
			break;
		default:
			break;
	}
}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
	LEDState = Start;
    while (1) {
		Tick_LED();
    }
    return 1;
}
