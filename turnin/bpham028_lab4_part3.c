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

enum DOOR_States {Start, InitLock, PoundKey, PoundKeyR, YUnlock} DOOR_State;

void Tick_DOOR() {

	unsigned char tmpB;
	switch(DOOR_State) { //transitions
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
			if (PINA == 0x00) {
				DOOR_State = PoundKeyR;
			} else {
				DOOR_State = PoundKey;
			} break;
		case PoundKeyR: 
			if (PINA == 0x00) {
				DOOR_State = PoundKeyR;
			} else if (PINA == 0x02) {
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
			tmpB = 0;
			PORTC = InitLock;
			break;
		case PoundKey:
			PORTC = PoundKey;
			break;
		case PoundKeyR:
			PORTC = PoundKeyR;
			break;
		case YUnlock:
			tmpB = 1;
			PORTC = YUnlock;
			break;
		default:
			break;
	}
	PORTB = tmpB;
}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
	DOOR_State = Start;
    while (1) {
		Tick_DOOR();
    }
    return 1;
}

