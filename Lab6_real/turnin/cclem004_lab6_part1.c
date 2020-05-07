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
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{Init, First, Second, Third}state;
void tick();
unsigned char i = 0x00;

int main(void) {

	DDRB = 0xFF;
	PORTB = 0x00;
	TimerSet(1000);
	TimerOn();
	//unsigned char tmpB = 0x00;
	
    /* Insert DDR and PORT initializations */

    /* Insert your solution below */
    while (1) {
	tick();
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}

void tick()
{
	switch(state)
	{
		case Init:
		{
			state = First;
			break;
		}
		case First:
		{
			state = Second;
			break;
		}
		case Second:
		{
			state = Third;
			break;
		}
		case Third:
		{
			state = First;
			break;
		}
		default:
		{
			state = Init;
			break;
		}
	

	}
	switch(state)
	{
		case Init:
			break;
		case First:
			PORTB = 0x01;
			break;
		case Second:
			PORTB = 0x02;
			break;
		case Third:
			PORTB = 0x04;
			break;
		default:
			break;
	}



}
