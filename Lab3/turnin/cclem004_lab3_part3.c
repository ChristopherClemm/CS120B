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
	unsigned char tempA,tempC, tempKey, tempS; 
	tempA = 0x00;
	tempS = 0x00;
	tempKey = 0x00;
	tempC = 0x00;
    /* Insert your solution below */
    while (1) {
	tempA = PINA & 0x0F;
	tempS = PINA;

	if(tempA <= 0x02)
	{
		tempC = 0x60;
	}	
	else if(tempA <= 0x04)
	{
	 	tempC = 0x70;
	}
	else if (tempA <= 0x06)
	{
	 	tempC = 0x38; 
	}
	else if (tempA <= 0x09)
	{
		tempC = 0x3C;
	} 
	else if (tempA <= 0x0C)
	{
		tempC = 0x3E;
	}
	else if (tempA <= 0x0F)
	{
		tempC = 0x3F;
	}
	tempS = tempS >> 4;
	if(tempS == 0x03)
	{
		tempKey = 0x80;
	}
	
	PORTC = tempC | tempKey;
	tempC = 0x00;
	tempKey = 0x00;	
    }
    return 1;
}
