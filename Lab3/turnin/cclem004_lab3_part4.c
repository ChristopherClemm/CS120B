/*	Author: Christopher Clemm
 *  Partner(s) Name: NA
 *	Lab Section:23
 *	Assignment: Lab #3  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF; //input
	DDRB = 0x00; PORTB = 0xFF; //input
	DDRC = 0xFF; PORTC = 0x00; //output
	unsigned char tempA, tempS; 
	tempA = 0x00;
	tempS = 0x00;
	
	
    /* Insert your solution below */
    while (1) {
	tempA = PINA & 0x0F;
	tempS = PINA & 0xF0;
	
	tempA = tempA << 4;
	tempS = tempS >> 4;
	
	PORTB = tempS;
	PORTC = tempA;	
	
	

    }
    return 1;
}
