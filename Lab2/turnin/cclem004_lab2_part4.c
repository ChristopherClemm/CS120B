/*	Author: Christopher Clemm cclem004@ucr.edu
 *  Partner(s) Name: NA
 *	Lab Section:23
 *	Assignment: Lab #2  Exercise #4
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <stdlib.h>
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;//input
	DDRB = 0x00; PORTB = 0xFF; 
	DDRC = 0x00; PORTC = 0xFF;
	DDRD = 0xFF; PORTD = 0x00; //output

	unsigned char total, massA,massB, massC, diff, temp1, temp2, temp3;
	total = 0x0000;
	massA = 0x00;
	massB = 0x00;
	massC = 0x00;
	temp1 = 0x00;
	temp2 = 0x00;
	diff = 0x00;
	temp3 = 0x00;
	
    while (1) {

	
	massA = PINA;
	massB = PINB;
	massC = PINC;
	total = massA + massB + massC;

	if(total >=  0x008C)
	{
		temp1 = 0x01;			
	}
	diff = abs(massA - massC);
	
	if(diff >= 0x50)
	{
		temp2 = 0x02;	
	}
	temp3 = temp1 | temp2;
	diff = total & 0xFC;
	PORTD = diff | temp3;
	

	


    }
    return 1;
}
