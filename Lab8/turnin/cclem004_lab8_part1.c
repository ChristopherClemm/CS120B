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


void ADC_Init()
{
	ADCSRA |= (1 << ADEN) | ( 1 << ADSC) | (1 << ADATE);
}
unsigned short  my_short = 0x00;

int main(void) {
    /* Insert DDR and PORT initializations */

	DDRB = 0xFF;
	PORTB = 0x00; //ouput
	DDRD = 0xFF;
	PORTD = 0x00; //OUTPUT

	DDRA = 0x00;
	PORTA = 0xFF; //INPUT
	ADC_Init();

    /* Insert your solution below */
    while (1) {
	    my_short = ADC;
	    PORTB = (char)my_short;
	    PORTD = (char)(my_short >> 8);
	
    }
    return 1;
}
