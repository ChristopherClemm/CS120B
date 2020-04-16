/*	Author: Christopher Clemm cclem004@ucr.edu
 *  Partner(s) Name: NA
 *	Lab Section:23
 *	Assignment: Lab #2  Exercise #2
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
	DDRA = 0x00; PORTA = 0xFF;//input
	DDRB = 0xFF; PORTB = 0x00; //output
	DDRB = 0xFF; PORTC = 0x00;

	unsigned char temp1, temp2,temp3, temp4;
	temp1 = 0x00;
	temp2 = 0x00;
	temp3 = 0x00;
	temp4 = 0x00;

	unsigned char cntavail;
    while (1) {
	temp1 = PINA & 0x01;
	temp2 = PINA & 0x02;
	temp3 = PINA & 0x04;
	temp4 = PINA & 0x08;
	
	temp2 = temp2 >> 1;
	temp3 = temp3 >> 2;
	temp4 = temp4 >> 3;

	cntavail = 0x04 - (temp1 + temp2 + temp3 + temp4);
	PORTC = cntavail;
	cntavail = 0x00;


    }
    return 1;
}
