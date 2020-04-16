/*	Author: Christopher Clemm
 *  Partner(s) Name: NA
 *	Lab Section:23
 *	Assignment: Lab #3  Exercise #5
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
	DDRB = 0xFE; PORTB = 0x01; //input
	DDRC = 0xFF; PORTC = 0x00; //output
	DDRD = 0x00; PORTD = 0xFF;
	unsigned char tempA, tempS,out; 
	tempA = 0x0000;
	tempS = 0x00;
	out = 0x01;
	
	
    /* Insert your solution below */
    while (1) {
	tempA = PINB & 0x01;
	tempS = PIND << 1;
	tempA = tempA | tempS;
	if(tempA >= 0x0046)
	{
	 out = 0x02;
	}
	else if (tempA > 5)
	{
		out = 0x04;
	}
	else
	{
		out = 0x00;
	}
	PORTB = out;
	
	tempA = 0x0000; 
	out = 0x00;
    }
    return 1;
}
