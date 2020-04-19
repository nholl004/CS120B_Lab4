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

enum states {start, init, x, y, z, check, unlock, lock} state;
unsigned char tmp1 = 0x00;
unsigned char cnt = 0x00;
unsigned char cnt1 = 0x00;
unsigned char tmp2 = 0x00;
unsigned char tmp3 = 0x00;
unsigned char B = 0x00;
unsigned char C = 0x00;
void tick()
{
	
	switch(state){
		case start:
			state = init;
			break;
		case init:
			if(PINA == 0x00){ state = init; } else if(PINA == 0x01){ state = x;} else if(PINA == 0x02){ state = y;} else if(PINA == 0x04){ state = z;}
			break;
		case x:
			if(PINA == 0x00){ state = check;}else if(PINA == 0x01){state = x;}		 
                        break;
		case y:
			if((PINA == 0x00)&&(tmp1 + tmp2 + tmp3 == 0x06 )){state = unlock;}else if((PINA == 0x00)&&(tmp1 + tmp2 + tmp3 != 0x06 )){ state = check;}else if((PINA == 0x02)&&(tmp1 + tmp2 + tmp3 != 0x06 )){state = y;}
			break;
		case z:
			if(PINA == 0x00){ state = check;}else if(PINA == 0x04){state = z;}
			break;
		case check:
			if(cnt > 1){state = init;}else if((PINA == 0x01)&& (cnt < 2)){ state = x;} else if((PINA == 0x02)&& (cnt < 2)){ state = y;} else if((PINA == 0x04)&& (cnt < 2)){ state = z;}		
			break;
		case unlock:
			if(PINA == 0x80){state = lock;}else if(PINA == 0x00){ state = unlock;}
                        break;
		case lock:
			state = lock;
			break;
		default:
			break;
	}
	switch(state){
		case init:
			C = 1;
			cnt = 0;
			tmp1 = 0x00;
			tmp2 = 0x00;
			tmp3 = 0x00;
			break;
		case x:
			C = 2;
			tmp1 = 0x01;
			break;
		case y:
			C = 3;
			tmp2 = 0x02;
			break;
		case z:
			C = 4;
			tmp3 = 0x04;
			break;
		case check:
			C = 5;
			cnt++;
			break;
		case unlock:
			C = 6;
			B = 0x01;
			break;
		case lock:
			C = 7;
			B = 0x00;
			break;
		default:
			break;
	}
	PORTB = B;
	PORTC = C;
	PORTD = tmp1 + tmp2 + tmp3;
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	state = start;
    /* Insert your solution below */
    while (1) {
	tick();
    }
    return 1;
}
