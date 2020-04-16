/*	Author: Christopher Clemm
 *  Partner(s) Name: NA
 *	Lab Section:23
 *	Assignment: Lab #3  Exercise #1
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
	unsigned char count, tempA, tempB; 
	tempA = 0x00;
	tempB = 0x00;
	count = 0x00;
	
    /* Insert your solution below */
    while (1) {
	tempA = PINA;
	while(tempA != 0x00)
	{
		if((tempA & 0x01) == 0x01)
		{
			count++;
		}
		tempA = tempA >> 1;
	
	}
	tempB = PINB;
	 while(tempB != 0x00)                                                                                                    {
                if((tempB & 0x01) == 0x01)
                {                                                                                                                               count++;                                                                                                        }
                tempB = tempB >> 1;                                                                                     
        }
	PORTC = count;
	count = 0x00;	
    }
    return 1;
}
