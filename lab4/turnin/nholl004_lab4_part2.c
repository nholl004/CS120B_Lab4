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

enum states {start, init, A0Press, A1Press, A0A1Press, cntReset} state;
unsigned char C = 0x00;
unsigned char cnt = 0x00;
unsigned char cnti = 0x00;
void tick()
{
	
	switch(state){
		case start:
			state = init;
			break;
		case init:
			if(PINA == 0x00){ state = init; } else if(PINA == 0x01){ state = A0Press;} else if(PINA == 0x02){ state = A1Press;} else if(PINA == 0x03){ state = A0A1Press;}
			break;
		case A0Press:
			if(PINA == 0x01){ state = A0Press; } else if(PINA == 0x00){ state = cntReset;}
                        break;
		case A1Press:
			if(PINA == 0x02){ state = A1Press; } else if(PINA == 0x00){ state = cntReset;}
			break;
		case A0A1Press:
			if(PINA == 0x03){ state = A0A1Press; } else if((PINA == 0x00)||(PINA == 0x01)||(PINA == 0x02)){ state = cntReset;}
			break;
		case cntReset:
			state = init;
                        break;
		default:
			break;
	}
	switch(state){
		case init:
			if(cnti == 0){ C=0x07; cnti++;}
			break;
		case A0Press:
			if((cnt == 0)&& (C < 0x09)){C = C + 1; cnt++;}
			break;
		case A1Press:
			if((cnt == 0)&& (C > 0x00)){ C = C - 1; cnt++;}
			break;
		case A0A1Press:
			if(cnt == 0){C = 0; cnt++;}
			break;
		case cntReset:
			cnt = 0;
			break;
		default:
			break;
	}
	PORTC = C;
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;

	state = start;
    /* Insert your solution below */
    while (1) {
	tick();
    }
    return 1;
}
