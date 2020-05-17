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
unsigned short max = 0xC7;
unsigned short eight = 0x00;
int main(void) {
    /* Insert DDR and PORT initializations */

	DDRB = 0xFF;
	PORTB = 0x00; //ouput
	DDRD = 0xFF;
	PORTD = 0x00; //OUTPUT

	DDRA = 0x00;
	PORTA = 0xFF; //INPUT
	ADC_Init();
	eight =(max/8);
    /* Insert your solution below */
    while (1) {
	    my_short = ADC;
	    if(my_short <= eight)
	    {
		PORTB = 0x01;
	    }
	    else if (my_short <= eight*2)
            {
                PORTB = 0x03;
            }
	    else if (my_short <= eight*3)
            {
                PORTB = 0x07;
            }
	    else if (my_short <= eight*4)
	    {
                PORTB = 0x0F;
            }
	    else if (my_short <= eight*5)
            {
                PORTB = 0x1F;
            }
	    else if (my_short <= eight*6)
            {
                PORTB = 0x3F;
            }
	    else if (my_short <= eight*7)
            {
                PORTB = 0x7F;
            }
	    else
		{
			PORTB = 0xFF;
		}

	
    }
    return 1;
}
