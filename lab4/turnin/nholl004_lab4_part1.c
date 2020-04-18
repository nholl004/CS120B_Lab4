/*	Author: nholl004
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

enum states {start, init, initPress, next, nextPress} state;

void tick()
{
	switch(state){
		case start:
			state = init;
			break;
		case init:
			if(PINA == 0x00){ state = init; } else if(PINA == 0x01){ state = initPress;}
			break;
		case initPress:
			if(PINA == 0x01){ state = initPress; } else if(PINA == 0x00){ state = next;}
                        break;
		case next:
			if(PINA == 0x00){ state = next; } else if(PINA == 0x01){ state = nextPress;}
                        break;
		case nextPress:
			if(PINA == 0x01){ state = nextPress; } else if(PINA == 0x00){ state = init;}
                        break;
		default:
			break;
	}
	switch(state){
		case init: 
			PORTB = 0x01;
			break;
		case initPress:
			PORTB = 0x02;
			break;
		case nextPress:
			PORTB = 0x01;
			break;
		default:
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

	state = start;
    /* Insert your solution below */
    while (1) {
	tick();
    }
    return 1;
}
